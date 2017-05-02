/**************************************************************************************
 *
 *	FileName:
 *		cms_writeback.c
 *
 *	Version:
 *		V2.0.0 2013/4/18
 *
 *	DESC:
 *		长流程工单回写进程
 *
 *	Vx.x.x YYYY/MM/DD by author
 *		modify desc
 *
 ***************************************************************************************/
 

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
extern int get_WorkInfo_back();
extern int get_MsisdnInHlr();
extern int get_ImsiInHlr();
extern int get_PropertyID();
extern int save_WorkOrder();
extern int testdir();
extern int copy_address();
extern void free_address();
extern int get_NewMsisdninhlr();
extern int put_NewMsisdnintotab();
/********add by zhr 2013/4/18 **********/
extern int wrtback_so_Ack();
extern int get_WorkInfo_back();

char *procname;
char tablecode[32];
FILE *logfp;
struct WorkOrderInfo   *WorkOrderPtr,*WorkOrderTail,WOlist[100],WoNordcList[100];
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
int ReadDBCfg(char *inSection,char *outdbname,char *outusername,char *outpassword);
static int readcfg(char *cfgname,char *section,char *key,char *value) ;
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
    int i,j,order_num,wo_num,nd_tb_num;
    FILE *cfgfp;
    char wo_tablecode[32],*cptr;
    char msisdn_info[64],newhlr_code[3+1];
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
    char tem_attr_str[2048];
    char mul_attr[128];
    char mul_tmp[1024];
    /*查询路由管理HLR归属用*/
    int s_hlrlen;
    char ldapstr[64];
    char *s_hlr;
    /*使用路由管理标志*/
    char r_flag;
    /********add by zhaodw2011-12-26**********/
    char g_dbname[256];
    char g_dbuser[256];
    char g_dbpass[256];
    
    /********add by zhr 2013/4/18 **********/
    int t_du_flag;/*剔重标志位*/
    
    memset(g_dbname,0X00,sizeof(g_dbname));
    memset(g_dbuser,0X00,sizeof(g_dbuser));
    memset(g_dbpass,0X00,sizeof(g_dbpass));
    
    /*****************************************/

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
        sprintf(logfilename,"%s/CMS_BACK%04d%02d%02d",logdir,
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
    /************add by zhaodw 2011-12-26****************************/
    if(ReadDBCfg(dbsection,g_dbname,g_dbuser,g_dbpass) < 0)
	{
		fprintf(logfp,"从密码文件读取用户名密码失败\n");
        fclose(logfp);
		printf("从密码文件读取用户名密码失败\n");
		return (-5);
	}
	/*****************************************************************/
    /*** 登陆数据库 ***/
    if (db_login(g_dbname,g_dbuser,g_dbpass))
    {
        fprintf(logfp,"db_login dbname[%s]user[%s]pass[%s] failed!\n",g_dbname,g_dbuser,g_dbpass);
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
    
    /*fprintf(logfp,"MainSvcConf info:\n");*/
    for (; MainSvcConfHead.next;)
    {
        MainSvcConfPtr=MainSvcConfHead.next;
        MainSvcConfHead.next=MainSvcConfPtr->next;

        /*fprintf(logfp,"%s | %s | %s | %s | %s | %c | %d | %s | %s | %s \n",
                MainSvcConfPtr->main_svc_id,
                MainSvcConfPtr->main_action_group,
                MainSvcConfPtr->cell_code,
                MainSvcConfPtr->hlr_group,
                MainSvcConfPtr->workorder_id,
                MainSvcConfPtr->workorder_type,
                MainSvcConfPtr->workorder_seq,
                MainSvcConfPtr->issend_code,
                MainSvcConfPtr->is_value_map,
                MainSvcConfPtr->is_mul_com);*/

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

    	/*fprintf(logfp,"MsisdnInHlr info:\n");*/
    	MsisdnInHlrPtr=MsisdnInHlrHead.next;
    	while (MsisdnInHlrPtr)
    	{
    	    /*fprintf(logfp,"%s | %s\n",MsisdnInHlrPtr->msisdn_seg,MsisdnInHlrPtr->hlr_code);*/
    	    cp_hashtable_put(cp_MsisdnInHlr,MsisdnInHlrPtr->msisdn_seg,MsisdnInHlrPtr->hlr_code);
    	    MsisdnInHlrPtr=MsisdnInHlrPtr->next;
    	}
    	fflush(logfp);

    	
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

    /*fprintf(logfp,"HlrGroup info:\n");*/
    HlrGroupPtr=HlrGroupHead.next;
    while (HlrGroupPtr)
    {
        /*fprintf(logfp,"%s | %s\n",HlrGroupPtr->hlr_group,HlrGroupPtr->hlr_code);*/
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

    /*fprintf(logfp,"WorkOrderSave info:\n");*/
    WorkOrderSavePtr=WorkOrderSaveHead.next;
    while (WorkOrderSavePtr)
    {
        /*fprintf(logfp,"%s | %s | %s\n",WorkOrderSavePtr->cell_code,WorkOrderSavePtr->hlr_code,WorkOrderSavePtr->save_code);*/
        sprintf(cp_key,"%s|%s\0",WorkOrderSavePtr->cell_code,WorkOrderSavePtr->hlr_code);
        cp_hashtable_put(cp_WorkOrderSave,cp_key,WorkOrderSavePtr->save_code);
        WorkOrderSavePtr=WorkOrderSavePtr->next;
    }
    fflush(logfp);

    /*** get datas and write back ***/
    for (;;)
    {
        /*** get datas ***/
        gettimeofday(&tpstart, NULL);
        memset(&OrderInfoHead,0x0,sizeof(OrderInfoHead));
        order_num=get_WorkInfo_back(tablecode,&OrderInfoHead);
        gettimeofday(&tpend, NULL);
        if (order_num<0)
        {
            fprintf(logfp,"get_orderInfo(%s) failed[%d]\n",tablecode,order_num);
            fflush(logfp);
            break;
        }
        else if (order_num==0)
        {
            sleep(3);
            time(&t);
            tv=localtime(&t);
            if (today!=tv->tm_mday)
            {
                today=tv->tm_mday;
                if (strncmp("stdout",logdir,6) && strncmp("STDOUT",logdir,6))
                {
                    memset(logfilename,0x0,sizeof(logfilename));
                    sprintf(logfilename,"%s/CMS%04d%02d%02d",logdir,tv->tm_year+1900,tv->tm_mon+1,tv->tm_mday);
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
						
						/*** 从应用路由管理器查询号码hlr归属 ***/
						{
            
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

                /*add by liupengc 15:31 2011/11/15 */
				char tmp_service_no[32];
			    long l_service_no;
				l_service_no = atol(OrderInfoPtr->service_no);
				sprintf(tmp_service_no , "%ld", l_service_no);
			    /*memset(tmp_service_no, 0, sizeof(tmp_service_no)); */
          		/* strcpy(msisdn_info,OrderInfoPtr->service_no); */
          		strcpy(msisdn_info, tmp_service_no);
				
				msisdn_info[7]=0;
          		cptr=cp_hashtable_get(cp_MsisdnInHlr,msisdn_info);
          		if(cptr)
          		{
            		strcpy(OrderInfoPtr->hlr_code,cptr);
          		}
          		else
          		{
            		memset(newhlr_code,0x00,sizeof(newhlr_code));
            		if(get_NewMsisdninhlr(msisdn_info,newhlr_code)>0)
            		{
            			strcpy(OrderInfoPtr->hlr_code,newhlr_code);
              			cp_hashtable_put(cp_MsisdnInHlr,msisdn_info,newhlr_code);
              			put_NewMsisdnintotab(msisdn_info);
              	}
            		else
            		{
              		strcpy(OrderInfoPtr->hlr_code,ONLY_ONE);
              	}
          		}
           	}
           	#endif
            /*** find hlr_group ***/
            cptr=cp_hashtable_get(cp_HlrGroup,OrderInfoPtr->hlr_code);
            if (cptr)
                strcpy(OrderInfoPtr->hlr_group,cptr);
            else
                strcpy(OrderInfoPtr->hlr_group,OrderInfoPtr->hlr_code);

           /* fprintf(logfp,"\nservice work：%04d-%s-%s-%d-%s-%s-%s-%s-%s-%s-%s--\n",i,
                    OrderInfoPtr->oss_order_id,
                    OrderInfoPtr->service_no,
                    OrderInfoPtr->order_priority,
                    OrderInfoPtr->create_time,
                    OrderInfoPtr->process_node_id,
                    OrderInfoPtr->cut_flag,
                    OrderInfoPtr->cut_flag_wo,
                    OrderInfoPtr->property_char,
                    OrderInfoPtr->hlr_code,
                    OrderInfoPtr->hlr_group);*/

            /*** parse MainSvcId ***/
            sprintf(cp_key,"%s|100000",OrderInfoPtr->process_node_id);
            /*strcpy(cp_key,"S00001|100000|BS0045|1001|D33");*/
            if(debug) printf("cp_key=[%s]==========\n",cp_key);



            WorkOrderPtr=cp_hashtable_get(cp_WorkOrderInfo,cp_key);
            for (; WorkOrderPtr; WorkOrderPtr=WorkOrderPtr->next)
            {

            	  if (strcmp(WorkOrderPtr->cell_code,IS_HLR) || strcmp(OrderInfoPtr->hlr_group,WorkOrderPtr->hlr_group)==0)
                {
                   /*if(debug) fprintf(logfp,"MAINKEY===%s:%s|%s|%s|%c|%d|%s|%s|%s|\n",cp_key,WorkOrderPtr->cell_code,WorkOrderPtr->hlr_group,WorkOrderPtr->workorder_id,WorkOrderPtr->workorder_type,WorkOrderPtr->workorder_seq,WorkOrderPtr->issend_code,WorkOrderPtr->is_value_map,WorkOrderPtr->is_mul_com);*/
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
                   		memset(mul_attrname,0,sizeof(mul_attrname));
                   		memset(mul_cutgrp,0,sizeof(mul_cutgrp));
                   		memset(mul_attrcut,0,sizeof(mul_attrcut));
                   		memset(mul_str,0,sizeof(mul_str));
                   		memset(attr_str,0x0,sizeof(attr_str));
                   		memset(mul_attr,0x0,sizeof(mul_attr));
                   		memset(tem_attr_str,0x0,sizeof(tem_attr_str));

                   		cmsget_value(WorkOrderPtr->is_mul_com,"mul_attrname",mul_attrname,sizeof(mul_attrname));
                   		cmsget_value(WorkOrderPtr->is_mul_com,"mul_cutgrp",mul_cutgrp,sizeof(mul_cutgrp));
                   		cmsget_value(WorkOrderPtr->is_mul_com,"mul_attrcut",mul_attrcut,sizeof(mul_attrcut));

                   		getMul_str(WorkOrderPtr->workorder_datas,"|",mul_attrname,mul_str);
                   		getOther_char(WorkOrderPtr->workorder_datas,mul_attrname,tem_attr_str);

                   		if(debug) printf("mul_attrname=[%s]=mul_cutgrp=[%s]=mul_attrcut=[%s]==mul_attrcut=[%s]=mul_str=[%s]=====\n",mul_attrname,mul_cutgrp,mul_attrcut,mul_attrcut,mul_str);
                   		mul_attrcount = 0;
                   		/*属性组循环*/
                   		for(mul_len = 0 ; mul_len < strlen(mul_str) ; mul_len ++)
                   		{
                   			if((mul_str[mul_len] == mul_cutgrp[0]) && (mul_len > 0))
                   			{
                   				memset(WorkOrderPtr->workorder_datas,0x0,sizeof(WorkOrderPtr->workorder_datas));
                   				sprintf(WorkOrderPtr->workorder_datas,"%s%s%s%d=%s|",tem_attr_str,attr_str,mul_attrname,mul_attrcount,mul_attr);
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
                   				memset(WorkOrderPtr->workorder_datas,0x0,sizeof(WorkOrderPtr->workorder_datas));
                   				sprintf(WorkOrderPtr->workorder_datas,"%s%s%s%d=%s|",tem_attr_str,attr_str,mul_attrname,mul_attrcount,mul_attr);
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
                   					sprintf(mul_tmp,"%s%d=%s|",mul_attrname,mul_attrcount,mul_attr);
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
                            strcmp(WOlist[i].workorder_id,WOlist[j].workorder_id)==0 &&
                            WOlist[i].workorder_seq == WOlist[j].workorder_seq)
                    {
                        if (WOlist[i].workorder_type==IS_SEND)
                        {
                            if (WOlist[j].workorder_type==IS_SEND)
                            {
                                if (strcmp(WOlist[i].workorder_datas,WOlist[j].workorder_datas)==0)
                                {
                                    /*if(debug) fprintf(logfp,"------REDUCE:i=%d,j=%d\n",i,j);*/
                                    WOlist[i].workorder_send=IS_REDUCE;
                                }
                            }
                            else
                            {
                                /*if(debug) fprintf(logfp,"------REDUCE:i=%d,j=%d\n",i,j);*/
                                WOlist[i].workorder_send=IS_REDUCE;
                            }
                        }
                        else
                        {
                            if (WOlist[j].workorder_type==IS_SEND)
                            {
                                /*if(debug) fprintf(logfp,"------REDUCE:i=%d,j=%d\n",i,j);*/
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
            
            /*** 从wolist剔除重复派生表 ***/     
            nd_tb_num = 0;
            memcpy((struct WorkOrderInfo *)&WoNordcList[nd_tb_num++], (struct WorkOrderInfo *)&WOlist[0], sizeof(struct WorkOrderInfo));
            for (i=0; i<wo_num; i++)
            {
            		for (j=0; j<nd_tb_num; j++)
            		{
            				t_du_flag=1;
            				if (strcmp(WoNordcList[j].wo_tablecode,WOlist[i].wo_tablecode)==0)
            						break;
            				else
            				{
            					t_du_flag=0;
            					continue;
            				}
            		}
            		if (t_du_flag==0)
            				memcpy((struct WorkOrderInfo *)&WoNordcList[nd_tb_num++], (struct WorkOrderInfo *)&WOlist[i], sizeof(struct WorkOrderInfo));
            }
          
            gettimeofday(&tpstart, NULL);
						
            /*** write back so_workitem ***/
            if (wrtback_so_Ack(OrderInfoPtr,WoNordcList,nd_tb_num,tablecode,wostatus)<0)
            {
                fprintf(logfp,"save_WorkOrder() failed!\n");
                fclose(logfp);

                continue;
            }
            gettimeofday(&tpend, NULL);
            /*if(debug) fprintf(logfp,"\n-save_WorkOrder--SPEND--[%d]##\n",tpend.tv_usec-tpstart.tv_usec);*/
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
/*****************************************************************\
 *  程 序 名  :		ReadDataBaseCfg
 *  程序功能  :		读取数据库配置
 *  输    入  :
 *			获取信息标识:	inSection
 *			数据库名称:	outdbname
 *			数据库用户:	outusername
 *			数据库密码:	outpassword
 *	输    出  :
 *				0:表示成功; -1：表示失败
 *  编 程 者  :
 *  编写日期  :
 *  修 改 者  :
 *  内    容  :
 *  日    期  :
 \*****************************************************************/
int ReadDBCfg(char *inSection,char *outdbname,char *outusername,char *outpassword)
{
	int 	locResult = 0;
	char	errmsg[4096];
	size_t	len;
	char	buffer[64];
	char    cfgname[100];

	memset(cfgname,0,sizeof(cfgname));
	/*printf("inSection=[%s]\n",inSection);*/
	if(getenv("BOSSCONFIG") == NULL)
	{
		sprintf(cfgname,"%s","./cfg/.bossconfig");
	}
	else
		sprintf(cfgname,getenv("BOSSCONFIG"));

	if((locResult=readcfg(cfgname,inSection,"DBUSER",outusername))<=0)		
	{

		return -1;
	} 

	if((locResult=readcfg(cfgname,inSection,"DBPASSWD",outpassword))<=0)		
	{

		return -1;
	} 

	if((locResult=readcfg(cfgname,inSection,"DBSERV",outdbname))<=0)		
	{

		return -1;
	}	
/*#ifdef WIN32
	decrypt2(outusername);
	decrypt2(outpassword);
#else
	len = strlen(outusername);
	memset(buffer,0,sizeof(buffer));
	desdec(outusername,buffer,len);
	sprintf(outusername,"%s",buffer);

	len = strlen(outpassword);
	memset(buffer,0,sizeof(buffer));
	desdec(outpassword,buffer,len);
	sprintf(outpassword,"%s",buffer);
#endif*/
	printf("=========username[%s]\n",outusername);
	printf("=========outpassword[%s]\n",outpassword);
    decrypt2(outusername);
	decrypt2(outpassword);
	printf("=========username[%s]\n",outusername);
	printf("=========outpassword[%s]\n",outpassword);
	return 0;
}
int DcReadCfg(char* section, char* key, char* value)
{
	FILE*   cfgfile;
	char    buff[200];
	char    section_ext[200];
	char    key_value[200];
	int     find=0;
	char    value_ext[200];
	char    cfgname[100];

	memset(cfgname,0,sizeof(cfgname));	
	memset(section_ext,0,sizeof(section_ext));
	memset(key_value,0,sizeof(key_value));
	memset(buff,0,sizeof(buff));
	memset(value_ext,0,sizeof(value_ext));

	if(getenv("BOSSCONFIG") == NULL)
	{
		sprintf(cfgname,"%s","./cfg/.bossconfig");
	}
	else
		sprintf(cfgname,getenv("BOSSCONFIG"));

	if((cfgfile = fopen(cfgname,"r"))==NULL)
		return -1;

	/*查找section*/
	sprintf(section_ext, "[%s]", section);
	for(;fgets(buff, sizeof(buff), cfgfile);)
	{
		if(buff[0] == '#')
			continue;
		if(buff[0]!= '[')
			continue;
		if(strstr(buff, section_ext) == NULL)
			continue;
		else
		{
			find = 1;
			break;
		}
	}

	if(find==0)
	{
		fclose(cfgfile);
		return -2;
	}

	/*查找key=value*/

	value_ext[0] = '0';
	find=0;

	for(; fgets(buff, sizeof(buff), cfgfile); )
	{
		if(buff[0] == '#')
			continue;
		if(strstr(buff, key) == NULL)
			continue;
		else
		{
			sprintf(key_value, "%s=%%s\n", key);
			sscanf(buff, key_value, value_ext);
			find = 1;
			break;
		}
	}

	fclose(cfgfile);
	if(find == 0)
		return -3; /* No such proces */

	if(value_ext[0] == '\0')
		return 1;   /* Interrupted system call */
	else
	{
		strcpy(value,value_ext);
		return 1;
	}
}

/*****************************************************************\
* 	函 数 名	:	decrypt_rc2_array
* 	函数功能	:	解密函数
* 	编 程 者	:  	神州数码有限公司
* 	编写日期	:	2002.08.09
*	输入参数	:	des密钥、解密前字符串，解密字符串长度
*	输出参数	:	解密后字符串
* 	修 改 者	: 	
* 	修改内容	:  	
* 	修改日期	:	
\*****************************************************************/
int decrypt_rc2_array(unsigned char * buf,const int buf_len,char * key);


/*****************************************************************\
* 	函 数 名	:	crypt_rc2_array
* 	函数功能	:	加密函数
* 	编 程 者	:  	神州数码有限公司
* 	编写日期	:	2002.08.09
*	输入参数	:	des密钥、加密前字符串，加密字符串长度
*	输出参数	:	加密后字符串
* 	修 改 者	: 	
* 	修改内容	:  	
* 	修改日期	:	
\*****************************************************************/

int crypt_rc2_array(unsigned char * buf,const int buf_len,char * key);



int rc2_keyschedule(unsigned short xkey[64],const unsigned char *key,unsigned len,unsigned bits);
/*****************************************************************\
* 	函 数 名	:	rc2_encrypt
* 	函数功能	:	对8位字符进行加密
* 	编 程 者	:  	神州数码有限公司
* 	编写日期	:	2002.08.09
*	输入参数	:	des密钥、解密前字符串，解密字符串长度
*	输出参数	:	解密后字符串
* 	修 改 者	: 	
* 	修改内容	:  	
* 	修改日期	:	
\*****************************************************************/


void rc2_encrypt(const unsigned short xkey[64],const unsigned char *plain,unsigned char *cipher);
/*****************************************************************\
* 	函 数 名	:	rc2_encrypt_chr
* 	函数功能	:	对1位字符进行加密
* 	编 程 者	:  	神州数码有限公司
* 	编写日期	:	2002.08.09
*	输入参数	:	des密钥、解密前字符串，解密字符串长度
*	输出参数	:	解密后字符串
* 	修 改 者	: 	
* 	修改内容	:  	
* 	修改日期	:	
\*****************************************************************/


void rc2_encrypt_chr(const unsigned short xkey[64],const unsigned char *plain,unsigned char *cipher);
/*****************************************************************\
* 	函 数 名	:	rc2_decrypt
* 	函数功能	:	对8位字符进行解密
* 	编 程 者	:  	神州数码有限公司
* 	编写日期	:	2002.08.09
*	输入参数	:	des密钥、解密前字符串，解密字符串长度
*	输出参数	:	解密后字符串
* 	修 改 者	: 	
* 	修改内容	:  	
* 	修改日期	:	
\*****************************************************************/



void rc2_decrypt(const unsigned short xkey[64],unsigned char *plain,const unsigned char *cipher);
/*****************************************************************\
* 	函 数 名	:	rc2_decrypt_chr
* 	函数功能	:	对1位字符进行解密
* 	编 程 者	:  	神州数码有限公司
* 	编写日期	:	2002.08.09
*	输入参数	:	des密钥、解密前字符串，解密字符串长度
*	输出参数	:	解密后字符串
* 	修 改 者	: 	
* 	修改内容	:  	
* 	修改日期	:	
\*****************************************************************/
void rc2_decrypt_chr(const unsigned short xkey[64],unsigned char *plain,const unsigned char *cipher);


int rc2_keyschedule(unsigned short xkey[64],
					const unsigned char *key,
					unsigned len,
					unsigned bits )
{
	unsigned char x;
	unsigned i;
	/* 256-entry permutation table, probably derived somehow from pi */
	static const unsigned char permute[256] = {
		217,120,249,196, 25,221,181,237, 40,233,253,121, 74,160,216,157,
		198,126, 55,131, 43,118, 83,142, 98, 76,100,136, 68,139,251,162,
		23,154, 89,245,135,179, 79, 19, 97, 69,109,141,  9,129,125, 50,
		189,143, 64,235,134,183,123, 11,240,149, 33, 34, 92,107, 78,130,
		84,214,101,147,206, 96,178, 28,115, 86,192, 20,167,140,241,220,
		18,117,202, 31, 59,190,228,209, 66, 61,212, 48,163, 60,182, 38,
		111,191, 14,218, 70,105,  7, 87, 39,242, 29,155,188,148, 67,  3,
		248, 17,199,246,144,239, 62,231,  6,195,213, 47,200,102, 30,215,
		8,232,234,222,128, 82,238,247,132,170,114,172, 53, 77,106, 42,
		150, 26,210,113, 90, 21, 73,116, 75,159,208, 94,  4, 24,164,236,
		194,224, 65,110, 15, 81,203,204, 36,145,175, 80,161,244,112, 57,
		153,124, 58,133, 35,184,180,122,252,  2, 54, 91, 37, 85,151, 49,
		45, 93,250,152,227,138,146,174,  5,223, 41, 16,103,108,186,201,
		211,  0,230,207,225,158,168, 44, 99, 22,  1, 63, 88,226,137,169,
		13, 56, 52, 27,171, 51,255,176,187, 72, 12, 95,185,177,205, 46,
		197,243,219, 71,229,165,156,119, 10,166, 32,104,254,127,193,173
	};

	if(!(len > 0 && len <= 128))
	{
		printf("参数不对！\n");
		return -1;
	}
	if(!(bits <= 1024))
	{
		printf("参数不对！\n");
		return -1;
	}
	if (!bits)
		bits = 1024;

	memcpy(xkey, key, len);

	/* Phase 1: Expand input key to 128 bytes */
	if (len < 128) {
		i = 0;
		x = ((unsigned char *)xkey)[len-1];
		do {
			x = permute[(x + ((unsigned char *)xkey)[i++]) & 255];
			((unsigned char *)xkey)[len++] = x;
		} while (len < 128);
	}

	/* Phase 2 - reduce effective key size to "bits" */
	len = (bits+7) >> 3;
	i = 128-len;
	x = permute[((unsigned char *)xkey)[i] & (255 >> (7 & -bits))];
	((unsigned char *)xkey)[i] = x;

	while (i--) {
		x = permute[ x ^ ((unsigned char *)xkey)[i+len] ];
		((unsigned char *)xkey)[i] = x;
	}

	/* Phase 3 - copy to xkey in little-endian order */
	i = 63;
	do {
		xkey[i] =  ((unsigned char *)xkey)[2*i] +
			(((unsigned char *)xkey)[2*i+1] << 8);
	} while (i--);

	return 0;
}

void rc2_encrypt(const unsigned short xkey[64],
				 const unsigned char *plain,
				 unsigned char *cipher )
{
	unsigned x76, x54, x32, x10, i;

	x76 = (plain[7] << 8) + plain[6];
	x54 = (plain[5] << 8) + plain[4];
	x32 = (plain[3] << 8) + plain[2];
	x10 = (plain[1] << 8) + plain[0];

	for (i = 0; i < 16; i++) {
		x10 += (x32 & ~x76) + (x54 & x76) + xkey[4*i+0];
		x10 = (x10 << 1) + (x10 >> 15 & 1);

		x32 += (x54 & ~x10) + (x76 & x10) + xkey[4*i+1];
		x32 = (x32 << 2) + (x32 >> 14 & 3);

		x54 += (x76 & ~x32) + (x10 & x32) + xkey[4*i+2];
		x54 = (x54 << 3) + (x54 >> 13 & 7);

		x76 += (x10 & ~x54) + (x32 & x54) + xkey[4*i+3];
		x76 = (x76 << 5) + (x76 >> 11 & 31);

		if (i == 4 || i == 10) {
			x10 += xkey[x76 & 63];
			x32 += xkey[x10 & 63];
			x54 += xkey[x32 & 63];
			x76 += xkey[x54 & 63];
		}
	}

	cipher[0] = (unsigned char)x10;
	cipher[1] = (unsigned char)(x10 >> 8);
	cipher[2] = (unsigned char)x32;
	cipher[3] = (unsigned char)(x32 >> 8);
	cipher[4] = (unsigned char)x54;
	cipher[5] = (unsigned char)(x54 >> 8);
	cipher[6] = (unsigned char)x76;
	cipher[7] = (unsigned char)(x76 >> 8);

	return;
}

void rc2_encrypt_chr(const unsigned short xkey[64],
					 const unsigned char *plain,
					 unsigned char *cipher )
{
	unsigned char src;
	int i;
	src=(*plain);

	for(i=0;i<64;i++)
	{
		src += ( xkey[i] >> 8 & 255);
		src ^= ( xkey[i] & 255 ); 
		src = (src << 5 & 224) + (src >> 3 & 31);

		if((i%16) == 4 || (i%16) == 5 | (i%16) == 14)
		{
			src ^= ( xkey[i] >> 8 & 255 );
			src -= ( xkey[i] & 255);
		}
	}

	*cipher = src;

	return;
}

void rc2_decrypt( const unsigned short xkey[64],
				 unsigned char *plain,
				 const unsigned char *cipher )
{
	unsigned x76, x54, x32, x10, i;

	x76 = (cipher[7] << 8) + cipher[6];
	x54 = (cipher[5] << 8) + cipher[4];
	x32 = (cipher[3] << 8) + cipher[2];
	x10 = (cipher[1] << 8) + cipher[0];

	i = 15;
	do 
	{
		x76 &= 65535;
		x76 = (x76 << 11) + (x76 >> 5);
		x76 -= (x10 & ~x54) + (x32 & x54) + xkey[4*i+3];

		x54 &= 65535;
		x54 = (x54 << 13) + (x54 >> 3);
		x54 -= (x76 & ~x32) + (x10 & x32) + xkey[4*i+2];

		x32 &= 65535;
		x32 = (x32 << 14) + (x32 >> 2);
		x32 -= (x54 & ~x10) + (x76 & x10) + xkey[4*i+1];

		x10 &= 65535;
		x10 = (x10 << 15) + (x10 >> 1);
		x10 -= (x32 & ~x76) + (x54 & x76) + xkey[4*i+0];

		if (i == 5 || i == 11) 
		{
			x76 -= xkey[x54 & 63];
			x54 -= xkey[x32 & 63];
			x32 -= xkey[x10 & 63];
			x10 -= xkey[x76 & 63];
		}
	} while (i--);

	plain[0] = (unsigned char)x10;
	plain[1] = (unsigned char)(x10 >> 8);
	plain[2] = (unsigned char)x32;
	plain[3] = (unsigned char)(x32 >> 8);
	plain[4] = (unsigned char)x54;
	plain[5] = (unsigned char)(x54 >> 8);
	plain[6] = (unsigned char)x76;
	plain[7] = (unsigned char)(x76 >> 8);

	return;
}

void rc2_decrypt_chr(const unsigned short xkey[64],
					 unsigned char *plain,
					 const unsigned char *cipher)
{
	unsigned char src;
	int i;
	src=(*cipher);

	for(i=63;i>=0;i--)
	{
		if((i%16) == 4 || (i%16) == 5 | (i%16) == 14)
		{
			src += (xkey[i] & 255);
			src ^= ( xkey[i] >> 8 & 255 );
		}

		src = (src << 3 & 248) + (src >> 5 & 7);
		src ^= ( xkey[i] & 255 ); 
		src -= ( xkey[i] >> 8 & 255);
	}

	*plain = src;

	return;
}

int decrypt_rc2_array(unsigned char * buf,
					  const int buf_len,
					  char * key)
{
	unsigned short xkey[64];
	unsigned char in[9];
	unsigned char out[9];
	char *p;
	int i,j,k;
	int m;
	if (buf_len<0)
		return -1;
	if(rc2_keyschedule(xkey,key,strlen(key),0)<0)
	{
		printf("初始化密码表错误！\n");
		return -1;
	}
	j=buf_len/8;
	for (i=0;i<j;i++)
	{
		for(k=0;k<8;k++)
		{
			in[k]=buf[i*8+k];
		}	
		rc2_decrypt(xkey,out,in);
		for(k=0;k<8;k++)
		{
			buf[i*8+k]=out[k];
		}	
	}

	p=&buf[i*8];
	if(strlen(p)>0)
	{
		for(m=0;m<(buf_len-8*i);m++)
		{
			char chr_in,chr_out;
			chr_in=*(p+m);
			rc2_decrypt_chr(xkey,&chr_out,&chr_in);
			*(p+m)=chr_out;
		}
	}

	return 0;
}

int crypt_rc2_array(unsigned char * buf, const int buf_len,char * key)
{
	unsigned short xkey[64];
	unsigned char in[9];
	unsigned char out[9];
	char *p;
	int i,j,k;
	int m;
	if (buf_len<0)
		return -1;
	if(rc2_keyschedule( xkey,key,strlen(key),0)<0)
	{
		printf("初始化密码表错误！\n");
		return -1;
	}
	j=buf_len/8;
	for (i=0;i<j;i++)
	{
		for(k=0;k<8;k++)
		{
			in[k]=buf[i*8+k];
		}	
		rc2_encrypt(xkey,in,out);
		for(k=0;k<8;k++)
		{
			buf[i*8+k]=out[k];
		}	
	}

	p=&buf[i*8];
	if(strlen(p)>0)
	{
		for(m=0;m<(buf_len-8*i);m++)
		{
			char chr_in,chr_out;
			chr_in=*(p+m);
			rc2_encrypt_chr(xkey,&chr_in,&chr_out);
			*(p+m)=chr_out;
		}
	}

	return 0;
}

/***********************
*函数： int decrypt(char *encrychr)
*功能：封装了密钥的解密函数(用于数据库的用户和口令的解密)
*2005-12-10 16:36 sunxh add 
***********************/
int decrypt2(char *encrychr)
{
	char srcbuf[256]; 	
	int i;
	char key[33];
	int len;
	char ctmp[3];

	memset(srcbuf,0,sizeof(srcbuf));	
	memset(key,0,sizeof(key));
	memset(ctmp,0,sizeof(ctmp));

	strcpy(key,"qwertyuiopasdfghjklzxcvbnm");

	len=strlen(encrychr);

	for(i=0;i<len/2;i++)
	{
		int tmp;
		memset(ctmp,0,sizeof(ctmp));
		memcpy(ctmp,&(encrychr[2*i]),2);
		sscanf(ctmp,"%2x",&tmp);
		srcbuf[i]=(char)tmp;
	}

	decrypt_rc2_array(srcbuf,i,key);	 	
	memset(encrychr,0,sizeof(encrychr));
	sprintf(encrychr,srcbuf);

	return 1; 	
}	


/***********************
*函数： int encrypt2(char *srcbuf)
*功能：封装了密钥的加密函数(用于数据库的用户和口令的加密)
*2005-12-10 16:36 sunxh add 
***********************/
int encrypt2(char* srcbuf)
{
	char key[33];
	char encrychr[1024];
	char ctmp[3];
	int len;
	int i;


	memset(key,0,sizeof(key));
	memset(ctmp,0,sizeof(ctmp));
	memset(encrychr,0,sizeof(encrychr));

	strcpy(key,"qwertyuiopasdfghjklzxcvbnm");

	len=strlen(srcbuf);
	crypt_rc2_array(srcbuf,len,key);

	for(i=0;i<len;i++)
	{
		int tmp;
		tmp=0;
		memcpy((void *)(&tmp),(void *)(&srcbuf[i]),1);
		memset(ctmp,0,sizeof(ctmp));
		sprintf(&(encrychr[2*i]),"%02x",srcbuf[i]&0xFF);
	}

	memset(srcbuf,'\0',sizeof(srcbuf));		
	sprintf(srcbuf,"%s",encrychr);

	return 1;
}


/***********************
*函数： int encrypt(const char *sstrf)
*功能：操作员口令加密函数
*2005-12-10 16:36 sunxh add 
***********************/
static char* encrypt1(const char *sstr)
{
	int i,slen;
	char tstr1[50],c[2];

	memset(c,'\0',sizeof(c));
	memset(tstr1,'\0',sizeof(tstr1));

	slen=strlen(sstr);

	for(i=1;i<=slen;i++)
	{
		c[0]=(char)(((*(sstr+i-1)*i+slen)%96+32)%128);
		strcat(tstr1,c);
	}

	return tstr1;
}


/***********************
*函数： char * decrypt(char *tt)
*功能：操作员口令解密函数
*2005-12-10 16:36 sunxh add 
***********************/
char * decrypt(char *tt)
{
	int slen,i,j;
	char pwd[11];
	memset(pwd,0,11);
	slen=strlen(tt);
	for(i=0;i<slen;i++)
	{
		j=0;
		for(;(((tt[i]-32-slen+96*j)%(i+1)!=0)||((tt[i]-32-slen+96*j)/(i+1)<48))&&(j<10);j++);
		if (j>=10) return "Sorry,max length of password is up to 10";
		sprintf(pwd,"%s%c",pwd,(tt[i]-32-slen+96*j)/(i+1));
	}
	return pwd;
}
static int readcfg(char *cfgname,char *section,char *key,char *value)                                              
{                                                             
	FILE 			*cfgfile = NULL;                                            
	char 			buff[1024];                                          
	char 			section_ext[1024];                                   
	char 			key_value[1024];                                     
	int 			find=0;                                               
	char 			value_ext[1024];                                     
                                                              
	if((cfgfile=fopen(cfgname,"r"))==NULL)
	{                    
		return -1;
	}                                                
                                                              
	/*查找section*/                                           
	sprintf(section_ext,"[%s]",section);                      
                                                              
	for(;fgets(buff,sizeof(buff),cfgfile);)                   
	{                                                         
		if(buff[0]=='#')                                      
			continue;                                         
		if(buff[0]!='[')                                      
			continue;                                         
		if(strstr(buff,section_ext)==NULL)                    
			continue;                                         
		else                                                  
		{                                                     
			find=1;                                           
			break;                                            
		}                                                     
	}                                                         
                                                              
	if(find==0)                                               
	{                                                         
		fclose(cfgfile);                                      
		return -2;                                            
	}                                                         
                                                              
	/*查找key=value*/                                         
	value_ext[0]	= 0;                                           
	find			= 0;                                                   
                                                              
	for(;fgets(buff,sizeof(buff),cfgfile);)                   
	{                                                         
		if(buff[0]=='#')                                      
			continue;                                         
		if(strstr(buff,key)==NULL)                            
			continue;                                         
		else                                                  
		{                                                     
			sprintf(key_value,"%s=%%s\n",key);                
			sscanf(buff,key_value,value_ext);                 
			find=1;                                           
			break;                                            
		}                                                     
	}                                                         
                                                              
	fclose(cfgfile);                                          
	if(find==0)
	{                                               
		return -3;                                            
    }                                                          
	if(value_ext[0]==0)
	{                                       
		return -4;
	}                                            
	else                                                      
	{                                                         
		strcpy(value,value_ext);                              
		return 1;                                             
	}                                                         
                                                              
	                                                
}
