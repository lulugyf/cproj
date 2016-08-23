#include "boss_srv.h"
#include "boss_define.h"
#include "publicsrv.h"

#include <stdarg.h>

#ifndef _SXATOMPUBLICFUNC
#define	_SXATOMPUBLICFUNC

#ifndef SQLCA
EXEC SQL INCLUDE SQLCA;
#endif

#ifndef SQLDA
EXEC SQL INCLUDE SQLDA;
#endif

/*
发送短信函数
最后一个参数必须以'null'结束

op_fee -发送额度如果没有，填0

*/

int fInsertDxOpr(char *login_accept,char *phone_no,char *dxop_code,char *login_no,char *region_code,char *id_no,int op_fee,char *fmt, ...)
{
	int i,j,acount;
	char 	mvalue[200];
	char    vTokStr[20][100];
	char    *strBuf=NULL;
	va_list args;
	
	EXEC SQL BEGIN DECLARE SECTION;
	/***下面是用到的主变量****/		
	char        vlogin_accept[23];
	char		vphone_no[16];
	char		vmsg[256];
	long		vorder_code;
	char		vdxop_code[5];
	char		vlogin_no[7];
	
	int			vop_fee;
	int 		vmsg_level;
	char 		vid_no[23];
	int			vprint_order;
	int			vback_code;
	char		vis_send[2];
	char		vis_cust[2];
	char		vregion_code[3];
	char		vbusiness_code[5];
	char		vnew_line[2];
	char		vprint_text1[256];
	char		vin_value[31];
	char 		vprint_text2[256];
	char		mFuncText[255];
	
	long    SequenceOfShortMsg = 0;
	EXEC SQL END DECLARE SECTION;   
	
	memset(vlogin_accept,0,sizeof(vlogin_accept));
	  
	memset(vphone_no,0,sizeof(vphone_no));
	memset(vmsg,0,sizeof(vmsg));
	memset(vdxop_code,0,sizeof(vdxop_code));
	memset(vlogin_no,0,sizeof(vlogin_no));
	memset(vis_send,0,sizeof(vis_send));
	memset(vis_cust,0,sizeof(vis_cust));
	memset(vnew_line,0,sizeof(vnew_line));
	memset(vprint_text1,0,sizeof(vprint_text1));
	memset(vin_value,0,sizeof(vin_value));
	memset(vprint_text2,0,sizeof(vprint_text2));
	memset(vbusiness_code,0,sizeof(vbusiness_code));
	
	memset(vregion_code,0,sizeof(vregion_code));
	memset(vdxop_code,0,sizeof(vdxop_code));
	memset(vlogin_no,0,sizeof(vlogin_no));
	
	vop_fee=0;
	vmsg_level=0;
	vorder_code=0;
	vback_code=0;
	strcpy(vlogin_accept,login_accept);
	strcpy(vphone_no,phone_no);
	strcpy(vdxop_code,dxop_code);
	strcpy(vlogin_no,login_no);
	strcpy(vregion_code,region_code);
	vop_fee=0;
	strcpy(vid_no,id_no);
	/* delete by hehj for 159
	if (phone_no[0]!='1' || phone_no[1]!='3')
	{
		printf("手机号码非法，没有发送\n");
		return 0;
	}
add end 20060706*/
	for ( i=0;i<20;i++ )
	{
		memset(vTokStr,'0',sizeof(vTokStr));
  }
	va_start(args,fmt);
    strBuf=fmt;
    acount=0;
	while (strcmp(strBuf,"end")!=0)
	{
		sprintf(vTokStr[acount],"%s",strBuf);
		acount++;
		printf(":%s\n",strBuf);
		strBuf=NULL;
        strBuf=va_arg(args,char *);
	}
    va_end(args);
	printf("acount:%d\n",acount);
	EXEC SQL select op_fee,msg_level,is_send,is_cust into :vop_fee,:vmsg_level,:vis_send,:vis_cust from sDxopCfgCode 
	 	where region_code=:vregion_code and dxop_code=:vdxop_code;
	if (SQLCODE!=0)
	{
		printf("取短信配置信息失败region_code:%s,dxop_code:%s\n",vregion_code,vdxop_code);
		return 0;
	} 	
	if (strcmp(vis_send,"N")==0)
	{
		printf("不发送短信 region_code:%s,dxop_code:%s\n",vregion_code,vdxop_code);
		return 0;
	}
	if (op_fee>vop_fee)
	{
		printf("%s额度条件不满足，不发短信,传入额度:%d,配置额度%d\n",phone_no,op_fee,vop_fee);
		return 0;
	}
	if (strcmp(vis_cust,"Y")==0)
	{
		EXEC SQL select business_code into :vbusiness_code from dCustBusiness where id_no=:vid_no and business_code=:vdxop_code;
		if(SQLCODE!=0)
		{
			printf("取定制信息失败id_no:%d,dxop_code:%s\n",vid_no,vdxop_code);
			return -1;
		} 	
	}
	
	/*开始取数据发送短信*/
	EXEC SQL DECLARE CUR_Code1 CURSOR for
	    select nvl(dx_order,0),nvl(new_line,'null'),nvl(op_text1,'null'),nvl(op_value,'null'),nvl(op_text2,'null') 
	    from sDxopConfig where region_code=:vregion_code and dxop_code=:vdxop_code order by dx_order;
	EXEC SQL OPEN CUR_Code1;
	EXEC SQL FETCH CUR_Code1
		 into  :vprint_order,:vnew_line, :vprint_text1, :vin_value, :vprint_text2;
	memset(mFuncText,0,sizeof(mFuncText));
	j=0;	
	printf("vregion_code:%s,vdxop_code:%s\n",vregion_code,vdxop_code);
	printf("sqlcode:%d\n",SQLCODE);
	while (SQLCODE == 0)
	{
		printf("bbbbbbbbbbbbbb\n");
		rtrim(vprint_text1);
		rtrim(vin_value);
		rtrim(vprint_text2);
		if (strcmp(vprint_text1,"null")!=0)
			strcat(mFuncText,vprint_text1);					
		if (strcmp(vin_value,"null")!=0)
		{
			memset(mvalue,0,sizeof(mvalue));
			sprintf(mvalue,vTokStr[j]);
			rtrim(mvalue);
			strcat(mFuncText,mvalue);
			j++;
		}
						
		if (strcmp(vprint_text2,"null")!=0)
			strcat(mFuncText,vprint_text2);
		if (strcmp(vnew_line,"y")==0)
		{
			printf("acc:%s,%d,%s,%d,%d,%s,%s\n",vlogin_accept,vmsg_level,vphone_no,vorder_code,vback_code,vdxop_code,vlogin_no);
			printf("mFuncText:%s\n",mFuncText);
			/*写短信发送表*/
			/* add by liuxma begin 2008-7-23 14:33:01 先取序列，然后插入短信表中，解决本地序列插入异地表bug */
			EXEC SQL SELECT wCommonShortMsgcid.nextval intO :SequenceOfShortMsg FROM dual;
			if (SQLCODE != 0)
			{
				printf("取短信发送序列失败:%d,%s\n",SQLCODE,SQLERRMSG);
				EXEC SQL CLOSE CUR_Code1;
				return -10;
			}
			/**修改分月返还1319和分月赠送1317插wcommonshortcj,实现晚上10点到第2天早上8点不发送短信,防止晚上跑分月返还的时候,发送短信打扰用户.modify by xiangzhi**/			
			if(strcmp(vdxop_code,"1319")!=0 && strcmp(vdxop_code,"1317")!=0&&strcmp(vdxop_code,"1327")!=0&&strcmp(vdxop_code,"1345")!=0)
			{
					EXEC SQL INSERT into wCommonShortMsg select :SequenceOfShortMsg,:vlogin_accept,:vmsg_level,:vphone_no,:mFuncText,:vorder_code,:vback_code,:vdxop_code,:vlogin_no,sysdate,sysdate from dual;
					memset(mFuncText,0,sizeof(mFuncText));
					if (SQLCODE != 0)
					{
						printf("Insert into wCommonShortMsg Error:%d,%s\n",SQLCODE,SQLERRMSG);
						EXEC SQL CLOSE CUR_Code1;
						return -10;
					}
			}
			else if(strcmp(vdxop_code,"1319")==0 ||strcmp(vdxop_code,"1317")==0||strcmp(vdxop_code,"1327")==0)
			{
					/*----------------------------
					EXEC SQL INSERT into wMonthPayShortMsg (COMMAND_ID, LOGIN_ACCEPT, MSG_LEVEL, PHONE_NO, MSG, ORDER_CODE, BACK_CODE, DX_OP_CODE, LOGIN_NO, OP_TIME)
					values (:SequenceOfShortMsg, :vlogin_accept,:vmsg_level,:vphone_no,:mFuncText,:vorder_code,:vback_code,:vdxop_code,:vlogin_no,sysdate);
					memset(mFuncText,0,sizeof(mFuncText));
					if (SQLCODE != 0)
					{
						printf("Insert into wshort_fyzs_msg Error:%d,%s\n",SQLCODE,SQLERRMSG);
						EXEC SQL CLOSE CUR_Code1;
						return -10;
					}
					-------------------------------------*/
			}
			else if(strcmp(vdxop_code,"1345")==0)
			{
					/*----------------------------
					EXEC SQL INSERT into wOweTotalShortMsg (COMMAND_ID, LOGIN_ACCEPT, MSG_LEVEL, PHONE_NO, MSG, ORDER_CODE, BACK_CODE, DX_OP_CODE, LOGIN_NO, OP_TIME)
					values (:SequenceOfShortMsg, :vlogin_accept, :vmsg_level,:vphone_no,:mFuncText,:vorder_code,:vback_code,:vdxop_code,:vlogin_no,sysdate);
					memset(mFuncText,0,sizeof(mFuncText));
					if (SQLCODE != 0)
					{
						printf("Insert into wshort_dxzd_msg Error:%d,%s\n",SQLCODE,SQLERRMSG);
						EXEC SQL CLOSE CUR_Code1;
						return -10;
					}
					-------------------------------------*/
			}		
			/**
					EXEC SQL INSERT into wCommonShortMsg select wCommonShortMsgcid.nextval,:vlogin_accept,:vmsg_level,:vphone_no,:mFuncText,:vorder_code,:vback_code,:vdxop_code,:vlogin_no,sysdate,sysdate from dual;
					memset(mFuncText,0,sizeof(mFuncText));
					if (SQLCODE != 0)
					{
						printf("Insert into wCommonShortMsg Error:%d,%s\n",SQLCODE,SQLERRMSG);
						EXEC SQL CLOSE CUR_Code1;
						return -10;
					}
			**/						
		}
		vprint_order=0;
		memset(vnew_line,0,sizeof(vnew_line));
		memset(vprint_text1,0,sizeof(vprint_text1));
		memset(vin_value,0,sizeof(vin_value));
		memset(vprint_text2,0,sizeof(vprint_text2));
		
		EXEC SQL FETCH CUR_Code1
		 into  :vprint_order,:vnew_line, :vprint_text1, :vin_value, :vprint_text2;
	}
	EXEC SQL CLOSE CUR_Code1;	
	
	return 0;
}



/*
op_code
id_no
login_accept
*/

int fInsertElcOpr(char *inop_code,char *inid_no,char *inlogin_accept,char *fmt, ...)
{
     return 0;
}

#endif
