#include "h.h"
#ifdef ROUTEFLAG
#include "arms_config.h"
#endif
#include "cms.h"



#include <cprops/hashtable.h>

extern int GenDaemon();

extern int db_login();
extern int get_MainSvcConf();
extern int get_OrderProperty();
extern int get_MainActionGroup();
extern int get_HlrGroup();
extern int get_WorkOrderSave();
extern int get_OrderInfo();
extern int get_WorkInfo();
extern int get_MsisdnInHlr();
extern int get_ImsiInHlr();
extern int get_PropertyID();
extern int save_WorkOrder();
extern int testdir();
extern int copy_address();
extern void free_address();


char *procname;
char tablecode[32];
FILE *logfp;
struct WorkOrderInfo   *WorkOrderPtr,*WorkOrderTail,WOlist[1024];
struct MainSvcConf     MainSvcConfHead,*MainSvcConfPtr,*MainSvcConfTail;
struct SubSvcConf      SubSvcConfHead,*SubSvcConfPtr;
struct OrderProperty   OrderPropertyHead,*OrderPropertyPtr;
struct MainActionGroup MainActionGroupHead,*MainActionGroupPtr;
struct SubSvcGroup     SubSvcGroupHead,*SubSvcGroupPtr;
struct HlrGroup        HlrGroupHead,*HlrGroupPtr;
struct MsisdnInHlr     MsisdnInHlrHead,*MsisdnInHlrPtr;
struct ImsiInHlr       ImsiInHlrHead,*ImsiInHlrPtr;
struct PropertyID      PropertyIDHead,*PropertyIDPtr;
struct WorkOrderSave   WorkOrderSaveHead,*WorkOrderSavePtr;

struct OrderInfo       OrderInfoHead,*OrderInfoPtr;
struct SubSvcInfo      *SubSvcPtr;
struct PropertyInfo    *PropertyPtr,*PropertyDatas,*Propertytemp,*PropertyMapPtr;

struct PropertyValueMapping PropertyValueMappHead,*PropertyValueMappPtr;
struct RelaPropGroup    RelaPropGroupHead,*RelaPropGroupPtr;
struct RelaPropPty    *RelaPropPtyPtr,*RelaPropPtyTail,*RelaPropPtyHead;
struct RelaPropGroupMap *RelaPropGroupMapPtr,*RelaPropGroupMapTail,*RelaPropGroupMapHead;
cp_hashtable *cp_PropertyID=NULL;
cp_hashtable *cp_MsisdnInHlr=NULL;
cp_hashtable *cp_ImsiInHlr=NULL;
cp_hashtable *cp_MainActionGroup=NULL;
cp_hashtable *cp_SubSvcGroup=NULL;
cp_hashtable *cp_HlrGroup=NULL;
cp_hashtable *cp_WorkOrderSave=NULL;
cp_hashtable *cp_WorkOrderInfo=NULL;
cp_hashtable *cp_ValueMapping=NULL;
cp_hashtable *cp_RelaPropGroup=NULL;
char cp_key[1024],**cp_key_list,cp_value[1024];
char RelaProp_propval[60];
char RelaProp_svcid[60];
char RelaProp_id[60];
char wostatus;
void Usage(char *s)
{
    printf("\n%s\n\n",s);
    printf("Usage:%s -Ttablecode [-Udbsection] [-Llogdir] [-v]\n\n",procname);
    exit(1);
}

void LogOut(int sig)
{
    printf("LogOut signal==%d\n",sig);
    if (logfp)
    {
        fprintf(logfp,"LogOut signal==%d\n",sig);
        fclose(logfp);
    }

    exit(1);
}

int main(int argc,char **argv)
{
    char inputstr[2048];
    char cfgstr[512];
    char dbsection[64];
    char logfilename[512],logdir[512];
    char rcfg[512];
    int debug = 1;
    char dbug;
    char key_id[255];
    char key_value[255];
    time_t t;
    struct tm *tv;
    int today;
    int i,j,order_num,wo_num;
    FILE *cfgfp;
    char wo_tablecode[32],*cptr;
    char msisdn_info[64];
    char imsi_info[64];
    struct timeval  tpstart, tpend;
    procname=argv[0];
    logfp=NULL;
    char    lua_res[128];
    /*多值指令用*/
    char mul_attrname[32];
    char mul_cutgrp[32];
    char mul_attrcut[32];
    char mul_str[2048];
    int mul_attrcount = 0;
    int mul_len = 0;
    int mul_attr_len = 0;
    char attr_str[2048];
    char mul_attr[128];
    char mul_tmp[1024]; 
    /*查询路由管理HLR归属用*/
    int s_hlrlen;
    char ldapstr[64];
    char *s_hlr; 
    /*使用路由管理标志*/
    char r_flag; 

    memset(inputstr,0x0,sizeof(inputstr));
    for (i=0; i<argc; i++)
    {
        strcat(inputstr,argv[i]);
        strcat(inputstr," ");
    }

    /*if (GenDaemon()<0)
    {
        printf("GenDaemon() failed!\n");
        exit(1);
    }*/

    signal(SIGTERM,LogOut);
    signal(SIGPIPE,SIG_IGN);
    signal(SIGCLD,SIG_IGN);
    signal(SIGINT,LogOut);

    memset(tablecode,0x0,sizeof(tablecode));
    memset(dbsection,0x0,sizeof(dbsection));
 
    memset(logdir,0x0,sizeof(logdir));
    memset(rcfg,0x0,sizeof(rcfg));

    while (--argc>0)
    {
        if (argv[argc][0]!='-')
            Usage("Incorrect Parameter!");

        switch (argv[argc][1])
        {
        case 'T':
            strncpy(tablecode,argv[argc]+2,8);
            break;
        case 'U':
            strncpy(dbsection,argv[argc]+2,30);
            break;
        case 'L':
            strncpy(logdir,argv[argc]+2,240);
            break;
        case 'v':
            printf("\n\n  version = %s\n\n",VERSION);
            exit(0);
        case 'W':
            wostatus=argv[argc][2];
            break;
        case 'D':
        		dbug=argv[argc][2];
        		break;
        default:
            Usage("Unknow Parameter!");
            break;
        }
    }

    if (strlen(logdir)<1)
    {
        if (getenv("LOGDIR")==NULL)
            Usage("LOGDIR env not exist!");
        else
            strcpy(logdir,getenv("LOGDIR"));
    }

		if(dbug == 'D')
		{
			debug = 1;
		}
		else
		{
			debug = 0;
		}
		
		
		
    if (strncmp("stdout",logdir,6)==0 || strncmp("STDOUT",logdir,6)==0)
    {
        if(debug) printf("\n\nLOG to STDOUT!\n\n\n");
        logfp=stdout;
    }
    else
    {
        if (testdir(logdir))
            Usage("Incorrect logdir!");

        time(&t);
        tv=localtime(&t);
        memset(logfilename,0x0,sizeof(logfilename));
        sprintf(logfilename,"%s/CMS%04d%02d%02d",logdir,
                tv->tm_year+1900,tv->tm_mon+1,tv->tm_mday);

        logfp=fopen(logfilename,"a");
        if (logfp==NULL)
        {
            if(debug) printf("can't open %s for LOG!\n",logfilename);
            exit(1);
        }
    }
    #ifdef ROUTEFLAG
    {
			if (strlen(rcfg)<1)
    	{
        	if (getenv("ROUTECFG")==NULL)
            Usage("ROUTECFG env not exist!");
        	else
            strcpy(rcfg,getenv("ROUTECFG"));
    	}
  	}
  	#endif
    
    time(&t);
    tv=localtime(&t);
    fprintf(logfp,"\n\nINIT %04d/%02d/%02d %02d:%02d:%02d\n",
            tv->tm_year+1900,tv->tm_mon+1,tv->tm_mday,
            tv->tm_hour,tv->tm_min,tv->tm_sec);
    fprintf(logfp,"%s[%d]\n",inputstr,argc);
    fflush(logfp);

    today=tv->tm_mday;

    if (strlen(tablecode)==0)
        Usage("Incorrect tablecode!");

    fprintf(logfp,"tablecode===%s\n\n",tablecode);
    fflush(logfp);
	
    if (strlen(dbsection)<1)
    {
        memset(cfgstr,0x0,sizeof(cfgstr));
        
        
        
        
        
        
        
        
        
        if (getenv("ETCDIR")==NULL)
            Usage("get ETCDIR evc not exist!");
        else
            strcpy(cfgstr,getenv("ETCDIR"));
        strcat(cfgstr,DBLOGIN);

        cfgfp=fopen(cfgstr,"r");
        if (cfgfp==NULL)
        {
            fprintf(logfp,"can't open %s for read[%d]\n",cfgstr,errno);
            fclose(logfp);
            exit(1);
        }

        memset(dbsection,0x0,sizeof(dbsection));
      

        fscanf(cfgfp,"%s",dbsection);
        fclose(cfgfp);
    }
    
		#ifdef ROUTEFLAG
		
			/*初始化应用路由管理器*/
			if(arms_init(rcfg))
			{
				fprintf(logfp,"init(%s) failed!\n",rcfg);
        fclose(logfp);
        
        exit(1);
			}
		#endif
    /*** 登陆数据库 ***/
    if (db_login(dbsection))
    {
        fprintf(logfp,"db_login(%s) failed!\n",dbsection);
        fclose(logfp);
        exit(1);
    }
    fprintf(logfp,"db_login() success!\n");
    fflush(logfp);

   

  


    /* INIT MainSvcConf INFO */
    cp_WorkOrderInfo=cp_hashtable_create_by_option(COLLECTION_MODE_NOSYNC |
                     COLLECTION_MODE_COPY |
                     COLLECTION_MODE_DEEP,
                     6000,
                     cp_hash_istring,
                     (cp_compare_fn) strcmp,
                     (cp_copy_fn) strdup,
                     (cp_destructor_fn) free,
                     (cp_copy_fn) copy_address,
                     (cp_destructor_fn) free_address);

    memset(&MainSvcConfHead,0x0,sizeof(MainSvcConfHead));
    if (get_MainSvcConf(&MainSvcConfHead))
    {
        fprintf(logfp,"get_MainSvcConfHead() failed!\n");
        fclose(logfp);
        exit(1);
    }

    fprintf(logfp,"MainSvcConf info:\n");
    for (; MainSvcConfHead.next;)
    {
        MainSvcConfPtr=MainSvcConfHead.next;
        MainSvcConfHead.next=MainSvcConfPtr->next;

        fprintf(logfp,"%s | %s | %s | %s | %s | %c | %d | %s | %s | %s \n",
                MainSvcConfPtr->main_svc_id,
                MainSvcConfPtr->main_action_group,
                MainSvcConfPtr->cell_code,
                MainSvcConfPtr->hlr_group,
                MainSvcConfPtr->workorder_id,
                MainSvcConfPtr->workorder_type,
                MainSvcConfPtr->workorder_seq,
                MainSvcConfPtr->issend_code,
                MainSvcConfPtr->is_value_map,
                MainSvcConfPtr->is_mul_com);

        WorkOrderPtr=(struct WorkOrderInfo *)malloc(sizeof(struct WorkOrderInfo));
        if (WorkOrderPtr==NULL)
        {
            fprintf(logfp,"malloc(struct WorkOrderInfo) failed[%d]\n",errno);
            fclose(logfp);
            exit(1);
        }

        memset(WorkOrderPtr,0x0,sizeof(struct WorkOrderInfo));
        strcpy(WorkOrderPtr->cell_code,MainSvcConfPtr->cell_code);
        strcpy(WorkOrderPtr->hlr_group,MainSvcConfPtr->hlr_group);
        strcpy(WorkOrderPtr->workorder_id,MainSvcConfPtr->workorder_id);
        WorkOrderPtr->workorder_type=MainSvcConfPtr->workorder_type;
        WorkOrderPtr->workorder_seq=MainSvcConfPtr->workorder_seq;
        strcpy(WorkOrderPtr->issend_code,MainSvcConfPtr->issend_code);
        strcpy(WorkOrderPtr->is_value_map,MainSvcConfPtr->is_value_map);
        strcpy(WorkOrderPtr->is_mul_com,MainSvcConfPtr->is_mul_com);
				
        sprintf(cp_key,"%s|%s\0",MainSvcConfPtr->main_svc_id,MainSvcConfPtr->main_action_group);

        WorkOrderTail=cp_hashtable_get(cp_WorkOrderInfo,cp_key);
        if (WorkOrderTail)
        {
            for (; WorkOrderTail->next; WorkOrderTail=WorkOrderTail->next);
            WorkOrderTail->next=WorkOrderPtr;
        }
        else
        {
            cp_hashtable_put(cp_WorkOrderInfo,cp_key,WorkOrderPtr);
        }

        free(MainSvcConfPtr);
    }
    fflush(logfp);

    

    /* INIT OrderProperty INFO 
    memset(&OrderPropertyHead,0x0,sizeof(OrderPropertyHead));
    if (get_OrderProperty(&OrderPropertyHead))
    {
        fprintf(logfp,"get_OrderProperty() failed!\n");
        fclose(logfp);
        exit(1);
    }

    fprintf(logfp,"OrderProperty info:\n");
    for (; OrderPropertyHead.next;)
    {
        OrderPropertyPtr=OrderPropertyHead.next;
        OrderPropertyHead.next=OrderPropertyPtr->next;

        fprintf(logfp,"%s | %s | %s | %s | %s | %s | %s | %s | %c | %d\n",
                OrderPropertyPtr->main_svc_id,
                OrderPropertyPtr->main_action_group,
                OrderPropertyPtr->svc_id,
                OrderPropertyPtr->property_id,
                OrderPropertyPtr->property_value,
                OrderPropertyPtr->cell_code,
                OrderPropertyPtr->hlr_group,
                OrderPropertyPtr->workorder_id,
                OrderPropertyPtr->workorder_type,
                OrderPropertyPtr->workorder_seq);

        WorkOrderPtr=(struct WorkOrderInfo *)malloc(sizeof(struct WorkOrderInfo));
        if (WorkOrderPtr==NULL)
        {
            fprintf(logfp,"malloc(struct WorkOrderInfo) failed[%d]\n",errno);
            fclose(logfp);
            exit(1);
        }

        memset(WorkOrderPtr,0x0,sizeof(struct WorkOrderInfo));
        strcpy(WorkOrderPtr->cell_code,OrderPropertyPtr->cell_code);
        strcpy(WorkOrderPtr->hlr_group,OrderPropertyPtr->hlr_group);
        strcpy(WorkOrderPtr->workorder_id,OrderPropertyPtr->workorder_id);
        WorkOrderPtr->workorder_type=OrderPropertyPtr->workorder_type;
        WorkOrderPtr->workorder_seq=OrderPropertyPtr->workorder_seq;

        sprintf(cp_key,"%s|%s|%s|%s|%s\0",
                OrderPropertyPtr->main_svc_id,
                OrderPropertyPtr->main_action_group,
                OrderPropertyPtr->svc_id,
                OrderPropertyPtr->property_id,
                OrderPropertyPtr->property_value);

        WorkOrderTail=cp_hashtable_get(cp_WorkOrderInfo,cp_key);
        if (WorkOrderTail)
        {
            for (; WorkOrderTail->next; WorkOrderTail=WorkOrderTail->next);
            WorkOrderTail->next=WorkOrderPtr;
        }
        else
        {
            cp_hashtable_put(cp_WorkOrderInfo,cp_key,WorkOrderPtr);
        }

        free(OrderPropertyPtr);
    }
    fflush(logfp);

		*/


  

    /*** display WorkOrderInfo ***/
    /*fprintf(logfp,"\nDisplay WorkOrderInfo:\n\n");
    cp_key_list=(char **)cp_hashtable_get_keys(cp_WorkOrderInfo);
    for (i=0; i<cp_WorkOrderInfo->items; i++)
    {
        fprintf(logfp,"KEY===[%s]\n",cp_key_list[i]);

        WorkOrderPtr=cp_hashtable_get(cp_WorkOrderInfo,cp_key_list[i]);
        for (; WorkOrderPtr; WorkOrderPtr=WorkOrderPtr->next)
        {
            fprintf(logfp,"   %s & %s & %s & %c & %d |\n",
                    WorkOrderPtr->cell_code,
                    WorkOrderPtr->hlr_group,
                    WorkOrderPtr->workorder_id,
                    WorkOrderPtr->workorder_type,
                    WorkOrderPtr->workorder_seq);
        }
    }
    fprintf(logfp,"\n");
    fflush(logfp);*/

    #ifndef ROUTEFLAG
    /*if(!ROUTEFLAG)
    {*/
    	/* INIT MsisdnInHlr INFO */
    	memset(&MsisdnInHlrHead,0x0,sizeof(MsisdnInHlrHead));
    	if (get_MsisdnInHlr(&MsisdnInHlrHead))
    	{
    	    fprintf(logfp,"get_MsisdnInHlr() failed!\n");
    	    fclose(logfp);
    	    exit(1);
    	}
    	
    	cp_MsisdnInHlr=cp_hashtable_create_by_option(COLLECTION_MODE_NOSYNC |
    	               COLLECTION_MODE_COPY |
    	               COLLECTION_MODE_DEEP,
    	               10000,
    	               cp_hash_istring,
    	               (cp_compare_fn) strcmp,
    	               (cp_copy_fn) strdup,
    	               (cp_destructor_fn) free,
    	               (cp_copy_fn) strdup,
    	               (cp_destructor_fn) free);
    	
    	fprintf(logfp,"MsisdnInHlr info:\n");
    	MsisdnInHlrPtr=MsisdnInHlrHead.next;
    	while (MsisdnInHlrPtr)
    	{
    	    fprintf(logfp,"%s | %s\n",
    	            MsisdnInHlrPtr->msisdn_seg,
    	            MsisdnInHlrPtr->hlr_code);
    	
    	    cp_hashtable_put(cp_MsisdnInHlr,MsisdnInHlrPtr->msisdn_seg,MsisdnInHlrPtr->hlr_code);
    	
    	    MsisdnInHlrPtr=MsisdnInHlrPtr->next;
    	}
    	fflush(logfp);
    	
    	/* INIT ImsiInHlr INFO */
    	/*memset(&ImsiInHlrHead,0x0,sizeof(ImsiInHlrHead));
    	if (get_ImsiInHlr(&ImsiInHlrHead))
    	{
    	    fprintf(logfp,"get_ImsiInHlr() failed!\n");
    	    fclose(logfp);
    	    exit(1);
    	}
    	
    	cp_ImsiInHlr=cp_hashtable_create_by_option(COLLECTION_MODE_NOSYNC |
    	             COLLECTION_MODE_COPY |
    	             COLLECTION_MODE_DEEP,
    	             10000,
    	             cp_hash_istring,
    	             (cp_compare_fn) strcmp,
    	             (cp_copy_fn) strdup,
    	             (cp_destructor_fn) free,
    	             (cp_copy_fn) strdup,
    	             (cp_destructor_fn) free);
    	
    	fprintf(logfp,"ImsiInHlr info:\n");
    	ImsiInHlrPtr=ImsiInHlrHead.next;
    	while (ImsiInHlrPtr)
    	{
    	    fprintf(logfp,"%s | %s\n",
    	            ImsiInHlrPtr->imsi_seg,
    	            ImsiInHlrPtr->hlr_code);
    	
    	    cp_hashtable_put(cp_ImsiInHlr,ImsiInHlrPtr->imsi_seg,ImsiInHlrPtr->hlr_code);
    	
    	    ImsiInHlrPtr=ImsiInHlrPtr->next;
    	}
    	fflush(logfp);*/
		/*}*/
		#endif
    /* INIT HlrGroup INFO */
    memset(&HlrGroupHead,0x0,sizeof(HlrGroupHead));
    if (get_HlrGroup(&HlrGroupHead))
    {
        fprintf(logfp,"get_HlrGroup() failed!\n");
        fclose(logfp);
        exit(1);
    }

    cp_HlrGroup=cp_hashtable_create_by_option(COLLECTION_MODE_NOSYNC |
                COLLECTION_MODE_COPY |
                COLLECTION_MODE_DEEP,
                100,
                cp_hash_istring,
                (cp_compare_fn) strcmp,
                (cp_copy_fn) strdup,
                (cp_destructor_fn) free,
                (cp_copy_fn) strdup,
                (cp_destructor_fn) free);

    fprintf(logfp,"HlrGroup info:\n");
    HlrGroupPtr=HlrGroupHead.next;
    while (HlrGroupPtr)
    {
        fprintf(logfp,"%s | %s\n",
                HlrGroupPtr->hlr_group,
                HlrGroupPtr->hlr_code);

        cp_hashtable_put(cp_HlrGroup,HlrGroupPtr->hlr_code,HlrGroupPtr->hlr_group);

        HlrGroupPtr=HlrGroupPtr->next;
    }
    fflush(logfp);

    /* INIT WorkOrderSave INFO */
    memset(&WorkOrderSaveHead,0x0,sizeof(WorkOrderSaveHead));
    if (get_WorkOrderSave(&WorkOrderSaveHead))
    {
        fprintf(logfp,"get_WorkOrderSave() failed!\n");
        fclose(logfp);
        exit(1);
    }

    cp_WorkOrderSave=cp_hashtable_create_by_option(COLLECTION_MODE_NOSYNC |
                     COLLECTION_MODE_COPY |
                     COLLECTION_MODE_DEEP,
                     100,
                     cp_hash_istring,
                     (cp_compare_fn) strcmp,
                     (cp_copy_fn) strdup,
                     (cp_destructor_fn) free,
                     (cp_copy_fn) strdup,
                     (cp_destructor_fn) free);

    fprintf(logfp,"WorkOrderSave info:\n");
    WorkOrderSavePtr=WorkOrderSaveHead.next;
    while (WorkOrderSavePtr)
    {
        fprintf(logfp,"%s | %s | %s\n",
                WorkOrderSavePtr->cell_code,
                WorkOrderSavePtr->hlr_code,
                WorkOrderSavePtr->save_code);

        sprintf(cp_key,"%s|%s\0",WorkOrderSavePtr->cell_code,WorkOrderSavePtr->hlr_code);
        cp_hashtable_put(cp_WorkOrderSave,cp_key,WorkOrderSavePtr->save_code);

        WorkOrderSavePtr=WorkOrderSavePtr->next;
    }
    fflush(logfp);

    /* INIT PropertyID INFO */
    /*memset(&PropertyIDHead,0x0,sizeof(PropertyIDHead));
    if (get_PropertyID(&PropertyIDHead))
    {
        fprintf(logfp,"get_PropertyID() failed!\n");
        fclose(logfp);
        exit(1);
    }

    cp_PropertyID=cp_hashtable_create_by_option(COLLECTION_MODE_NOSYNC |
                  COLLECTION_MODE_COPY |
                  COLLECTION_MODE_DEEP,
                  100,
                  cp_hash_istring,
                  (cp_compare_fn) strcmp,
                  (cp_copy_fn) strdup,
                  (cp_destructor_fn) free,
                  (cp_copy_fn) strdup,
                  (cp_destructor_fn) free);

    fprintf(logfp,"PropertyID info:\n");
    PropertyIDPtr=PropertyIDHead.next;
    while (PropertyIDPtr)
    {
        fprintf(logfp,"%s | %s \n",
                PropertyIDPtr->property_id,
                PropertyIDPtr->property_name);

        cp_hashtable_put(cp_PropertyID,PropertyIDPtr->property_id,PropertyIDPtr->property_name);

        PropertyIDPtr=PropertyIDPtr->next;
    }
    fflush(logfp);*/

    /*** get datas and parse ***/
    for (;;)
    {
        /*** get datas ***/
        gettimeofday(&tpstart, NULL);
				

        memset(&OrderInfoHead,0x0,sizeof(OrderInfoHead));
        order_num=get_WorkInfo(tablecode,&OrderInfoHead);
				
        gettimeofday(&tpend, NULL);

        if(debug) fprintf(logfp,"\n-get_OrderInfo--SPEND--[%d]##\n",tpend.tv_usec-tpstart.tv_usec);
        if (order_num<0)
        {
            fprintf(logfp,"get_orderInfo(%s) failed[%d]\n",tablecode,order_num);
            fflush(logfp);

            break;
        }
        else if (order_num==0)
        {
            /*fprintf(logfp,"not found any datas,sleep 3!\n");
            fflush(logfp);*/

            sleep(3);

            time(&t);
            tv=localtime(&t);

            if (today!=tv->tm_mday)
            {
                today=tv->tm_mday;

                if (strncmp("stdout",logdir,6) && strncmp("STDOUT",logdir,6))
                {
                    memset(logfilename,0x0,sizeof(logfilename));
                    sprintf(logfilename,"%s/CMS%04d%02d%02d",logdir,
                            tv->tm_year+1900,tv->tm_mon+1,tv->tm_mday);

                    fclose(logfp);
                    logfp=fopen(logfilename,"a");
                    if (logfp==NULL)
                    {
                        if(debug) printf("can't open %s for LOG!\n",logfilename);
                        exit(1);
                    }
                }
            }

            continue;
        }
				
        for (i=0,OrderInfoPtr=OrderInfoHead.next; OrderInfoPtr; OrderInfoPtr=OrderInfoPtr->next,i++)
        {
            wo_num=0;
						#ifdef ROUTEFLAG
						{
            	/*** 从应用路由管理器查询号码hlr归属 ***/
            
            	memset(ldapstr,0x0,sizeof(ldapstr));
            	sprintf(ldapstr,"cn=%s,ou=phone",OrderInfoPtr->service_no);
            	arms_process(ldapstr,&s_hlr,&s_hlrlen);
            
            	if((strstr(s_hlr,"success")) == NULL)
            	{
            		fprintf(logfp,"应用路由管理器查询号码hlr归属 failed[%s]\n",s_hlr);
            		fflush(logfp);
            		up_workorder(OrderInfoPtr,tablecode,'F',s_hlr);
            		continue;
            	}       
            
            	strcpy(OrderInfoPtr->hlr_code,s_hlr + (strstr(s_hlr,"hlrcode=") - s_hlr + 8));
            	if(debug) printf("^^^^^^^^^^^^^^^^^^^^^^%s^^^^^^\n",OrderInfoPtr->hlr_code);
           	}
           	#else
           	{
           		/*** find MSISDN & hlr_code ***/
      				memset(msisdn_info,0x0,sizeof(msisdn_info));
      				
        				
          		strcpy(msisdn_info,OrderInfoPtr->service_no);
          		msisdn_info[8]=0;
          		cptr=cp_hashtable_get(cp_MsisdnInHlr,msisdn_info);
          		if(cptr)
          		{
            		strcpy(OrderInfoPtr->hlr_code,cptr);
          		}
          		else
          		{
            		msisdn_info[7]=0;
            		if(debug) printf("--------^^^^^^msisdn=%s^^^^^^\n",msisdn_info);
            		cptr=cp_hashtable_get(cp_MsisdnInHlr,msisdn_info);
            		if(cptr)
            		{
              		strcpy(OrderInfoPtr->hlr_code,cptr);
              	}
            		else
            		{
              		strcpy(OrderInfoPtr->hlr_code,ONLY_ONE);
              	}
          		}
          			
      				if(debug) printf("--------^^^^^^%s^^^^^^\n",OrderInfoPtr->hlr_code);
           	}
           	#endif
            /*** find hlr_group ***/
            cptr=cp_hashtable_get(cp_HlrGroup,OrderInfoPtr->hlr_code);
            if (cptr)
                strcpy(OrderInfoPtr->hlr_group,cptr);
            else
                strcpy(OrderInfoPtr->hlr_group,OrderInfoPtr->hlr_code);

            fprintf(logfp,"\nservice work：%04d-%s-%s-%d-%s-%s-%s-%s-%s-%s-%s--\n",i,
                    OrderInfoPtr->oss_order_id,
                    OrderInfoPtr->service_no,
                    OrderInfoPtr->order_priority,
                    OrderInfoPtr->create_time,
                    OrderInfoPtr->process_node_id,
                    OrderInfoPtr->cut_flag,
                    OrderInfoPtr->cut_flag_wo,
                    OrderInfoPtr->property_char,
                    OrderInfoPtr->hlr_code,
                    OrderInfoPtr->hlr_group);

            /*** parse MainSvcId ***/
            sprintf(cp_key,"%s|100000",OrderInfoPtr->process_node_id);
            /*strcpy(cp_key,"S00001|100000|BS0045|1001|D33");*/
            if(debug) printf("cp_key=[%s]==========\n",cp_key);
            
            
                    
            WorkOrderPtr=cp_hashtable_get(cp_WorkOrderInfo,cp_key);
            for (; WorkOrderPtr; WorkOrderPtr=WorkOrderPtr->next)
            {
            	  if (strcmp(WorkOrderPtr->cell_code,IS_HLR) || strcmp(OrderInfoPtr->hlr_group,WorkOrderPtr->hlr_group)==0)
                {
                   if(debug) fprintf(logfp,"MAINKEY===%s:%s|%s|%s|%c|%d|%s|%s|%s|\n",cp_key,
                            WorkOrderPtr->cell_code,
                            WorkOrderPtr->hlr_group,
                            WorkOrderPtr->workorder_id,
                            WorkOrderPtr->workorder_type,
                            WorkOrderPtr->workorder_seq,
                            WorkOrderPtr->issend_code,
                            WorkOrderPtr->is_value_map,
                            WorkOrderPtr->is_mul_com);
										
                    strcpy(WorkOrderPtr->workorder_datas,OrderInfoPtr->property_char);
                   
                   
                   
    							
                   int send_flag = 0;
                   send_flag = 0;
                   /*判断条件发送*/ 
                   if(strcmp(WorkOrderPtr->issend_code,"1") == 0)
                   {
                   		/*memcpy(&WOlist[wo_num++],(struct WorkOrderInfo *)WorkOrderPtr,sizeof(struct WorkOrderInfo));*/
                   		send_flag = 1;
                   }
                   else
                   { 
                   		
                   		memset(lua_res,0,sizeof(lua_res));       
                   		pro_lua(WorkOrderPtr->workorder_datas,WorkOrderPtr->issend_code,lua_res);
                   		
                   		if(debug) printf("lua_res=[%s]==========\n",lua_res);
                   		
                   		if(strcmp(lua_res,"1") == 0)
                   		{
                   				send_flag = 1;
                   		}
                   }
                   
                   if(send_flag == 1)
                   {
                   	
                   	if(strcmp(WorkOrderPtr->is_mul_com,"0") == 0)
                   	{
                   		if(debug) printf("WorkOrderPtr->workorder_datas=[%s]=WorkOrderPtr->is_value_map=[%s]=========\n",WorkOrderPtr->workorder_datas,WorkOrderPtr->is_value_map);
                   		
                   		/*值映射*/
                   		if(strcmp(WorkOrderPtr->is_value_map,"0") != 0)
                   		{
                   			memset(lua_res,0,sizeof(lua_res));       
                   			pro_lua(WorkOrderPtr->workorder_datas,WorkOrderPtr->is_value_map,lua_res);
                   			if(debug) printf("lua_res=[%s]==========\n",lua_res);
                   			strcpy(WorkOrderPtr->workorder_datas,lua_res);
                   		}
                   		memcpy(&WOlist[wo_num++],(struct WorkOrderInfo *)WorkOrderPtr,sizeof(struct WorkOrderInfo));
                   	}
                   	else
                   	{
                   		/*属性多值指令发送,配置如(mul_attrname=APN,attr_cut=|,mul_cutgrp=&,mul_attrcut=*)*/		
                   		memset(mul_attrname,0,sizeof(mul_attrname));
                   		memset(mul_cutgrp,0,sizeof(mul_cutgrp));
                   		memset(mul_attrcut,0,sizeof(mul_attrcut));
                   		memset(mul_str,0,sizeof(mul_str));
                   		memset(attr_str,0x0,sizeof(attr_str));
                   		memset(mul_attr,0x0,sizeof(mul_attr));
                   		
                   		cmsget_value(WorkOrderPtr->is_mul_com,"mul_attrname",mul_attrname,sizeof(mul_attrname));
                   		cmsget_value(WorkOrderPtr->is_mul_com,"mul_cutgrp",mul_cutgrp,sizeof(mul_cutgrp));
                   		cmsget_value(WorkOrderPtr->is_mul_com,"mul_attrcut",mul_attrcut,sizeof(mul_attrcut));
                   		cmsget_value(WorkOrderPtr->workorder_datas,mul_attrname,mul_str,sizeof(mul_str));
                   		
                   		if(debug) printf("mul_attrname=[%s]=mul_cutgrp=[%s]=mul_attrcut=[%s]==mul_attrcut=[%s]=mul_str=[%s]=====\n",mul_attrname,mul_cutgrp,mul_attrcut,mul_attrcut,mul_str);
                   		mul_attrcount = 0;
                   		/*属性组循环*/
                   		for(mul_len = 0 ; mul_len < strlen(mul_str) ; mul_len ++)
                   		{
                   			if((mul_str[mul_len] == mul_cutgrp[0]) && (mul_len > 0))
                   			{          
                   				sprintf(WorkOrderPtr->workorder_datas,"%smulatt%d=%s|",attr_str,mul_attrcount,mul_attr);
                   				memset(mul_attr,0x0,sizeof(mul_attr));
                   				memset(attr_str,0x0,sizeof(attr_str));
                   				mul_attr_len = 0;
                   				mul_attrcount = 0;
                   				
                   				if(debug) printf("1WorkOrderPtr->workorder_datas=[%s]=WorkOrderPtr->is_value_map=[%s]=========\n",WorkOrderPtr->workorder_datas,WorkOrderPtr->is_value_map);
                   				/*值映射*/
                   				if(strcmp(WorkOrderPtr->is_value_map,"0") != 0)
                   				{
                   					memset(lua_res,0,sizeof(lua_res));       
                   					pro_lua(WorkOrderPtr->workorder_datas,WorkOrderPtr->is_value_map,lua_res);
                   					if(debug) printf("lua_res=[%s]==========\n",lua_res);
                   					strcpy(WorkOrderPtr->workorder_datas,lua_res);
                   				}
                   				memcpy(&WOlist[wo_num++],(struct WorkOrderInfo *)WorkOrderPtr,sizeof(struct WorkOrderInfo));
                   				
                   			}
                   			else if(mul_len == strlen(mul_str) - 1)
                   			{                   				
                   				/*strcpy(WorkOrderPtr->workorder_datas,attr_str);*/
                   				sprintf(WorkOrderPtr->workorder_datas,"%smulatt%d=%s|",attr_str,mul_attrcount,mul_attr);
                   				memset(attr_str,0x0,sizeof(attr_str));
                   				mul_attr_len = 0;
                   				mul_attrcount = 0;
                   				
                   				if(debug) printf("2WorkOrderPtr->workorder_datas=[%s]=WorkOrderPtr->is_value_map=[%s]=========\n",WorkOrderPtr->workorder_datas,WorkOrderPtr->is_value_map);
                   				/*值映射*/
                   				if(strcmp(WorkOrderPtr->is_value_map,"0") != 0)
                   				{
                   					memset(lua_res,0,sizeof(lua_res));       
                   					pro_lua(WorkOrderPtr->workorder_datas,WorkOrderPtr->is_value_map,lua_res);
                   					if(debug) printf("lua_res=[%s]==========\n",lua_res);
                   					strcpy(WorkOrderPtr->workorder_datas,lua_res);
                   				}
                   				memcpy(&WOlist[wo_num++],(struct WorkOrderInfo *)WorkOrderPtr,sizeof(struct WorkOrderInfo));
                   				
                   			}
                   			else
                   			{
                   				if(mul_str[mul_len] != mul_attrcut[0])
                   				{
                   					
                   					mul_attr[mul_attr_len ++] = mul_str[mul_len];
                   					if(debug) printf("---3----mul_attr[%s]-------\n",mul_attr);
          
                   				}
                   				else
                   				{
                   					mul_attr[mul_attr_len] = '\0';
                   					if(debug) printf("---2----mul_attr[%s]-------\n",mul_attr);
                   					memset(mul_tmp,0x0,sizeof(mul_tmp));
                   					sprintf(mul_tmp,"mulatt%d=%s|",mul_attrcount,mul_attr);
                   					strcat(attr_str,mul_tmp);
                   					if(debug) printf("-------attr_str[%s]-------\n",attr_str);
                   					memset(mul_attr,0x0,sizeof(mul_attr));
                   					mul_attr_len = 0;
                   					mul_attrcount ++ ;
                   				}
                   			}
                   		}
                   	}
                   }
                }
            }

            

           



            /*** init workorder_send ***/
            for (i=0; i<wo_num; i++)
            {
                WOlist[i].workorder_send=NOT_REDUCE;
            }

            /*** reduce WOlist ***/
            for (i=0; i<wo_num; i++)
            {
                for (j=i+1; j<wo_num; j++)
                {
                    if (strcmp(WOlist[i].cell_code,WOlist[j].cell_code)==0 &&
                            strcmp(WOlist[i].hlr_group,WOlist[j].hlr_group)==0 &&
                            strcmp(WOlist[i].workorder_id,WOlist[j].workorder_id)==0)
                    {


                        if (WOlist[i].workorder_type==IS_SEND)
                        {
                            if (WOlist[j].workorder_type==IS_SEND)
                            {
                                if (strcmp(WOlist[i].workorder_datas,WOlist[j].workorder_datas)==0)
                                {
                                    if(debug) fprintf(logfp,"------REDUCE:i=%d,j=%d\n",i,j);
                                    WOlist[i].workorder_send=IS_REDUCE;
                                }
                            }
                            else
                            {
                                if(debug) fprintf(logfp,"------REDUCE:i=%d,j=%d\n",i,j);
                                WOlist[i].workorder_send=IS_REDUCE;
                            }
                        }
                        else
                        {
                            if (WOlist[j].workorder_type==IS_SEND)
                            {
                                if(debug) fprintf(logfp,"------REDUCE:i=%d,j=%d\n",i,j);
                                WOlist[j].workorder_send=IS_REDUCE;
                            }
                        }
                    }
                }
            }

						

            /*** find wo_tablecode ***/
            for (i=0; i<wo_num; i++)
            {
                if (strcmp(WOlist[i].cell_code,IS_HLR)==0)
                    sprintf(cp_key,"%s|%s\0",WOlist[i].cell_code,OrderInfoPtr->hlr_code);
                else
                    sprintf(cp_key,"%s|%s\0",WOlist[i].cell_code,ONLY_ONE);

                cptr=cp_hashtable_get(cp_WorkOrderSave,cp_key);
                if (cptr)
                {
                    strcpy(WOlist[i].wo_tablecode,cptr);
                }
                else
                {
                    strcpy(WOlist[i].wo_tablecode,DEF_TCODE);
                }
            }

            gettimeofday(&tpstart, NULL);
						
            /*** save WOlist ***/
            if (save_WorkOrder(OrderInfoPtr,WOlist,wo_num,tablecode,wostatus)<0)
            {
                fprintf(logfp,"save_WorkOrder() failed!\n");
                fclose(logfp);

                continue;
            }
            gettimeofday(&tpend, NULL);
            if(debug) fprintf(logfp,"\n-save_WorkOrder--SPEND--[%d]##\n",tpend.tv_usec-tpstart.tv_usec);
        }
        /*** free OrderInfo ***/
        
        for (; OrderInfoHead.next;)
        {
            OrderInfoPtr=OrderInfoHead.next;
            OrderInfoHead.next=OrderInfoPtr->next;

            free(OrderInfoPtr);
        }
        
        fflush(logfp);
    }
		
    fclose(logfp);
    #ifdef ROUTEFLAG
    {
    	arms_quit();  /*退出应用路由管理*/
    }
    #endif
    exit(0);
}
