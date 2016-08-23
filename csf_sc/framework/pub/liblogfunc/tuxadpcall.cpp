#include "framework.h"

/******************************************************
构件名称:	uGetStrByName
编码作者:	
编码时间:	2011-2-16
功能描述:	遍历utype下所有节点，然后取到名字和传入名字相同的字符串并返回。
			（获取顺序为从外往内，即：先处理utype内的非utype节点，然后取节点为utype递归调用自身）
输入参数:
	@	pu				传入utype
	@	name			需要取出的节点名称
输出参数:
	@   char*			取到相应节点名称的值，如果节点不存在则返回NULL
其他说明:
 
变更记录:
 
******************************************************/
char* uGetStrByName(const utype* pu, char* buf, int bufSize, const char* name)
{
    UPOS p;
    memset(buf, 0, bufSize);
    //查找当前utype下是否有名字为name的节点，如果有则返回节点值
    if(UPOS_END !=(p = utFind(pu, name)))
    {
		switch(pu->ppe[p]->type)
		{
			case U_INT:snprintf(buf, bufSize - 1, "%d", utGetInt(pu, name, p));break;
			case U_LONG:snprintf(buf, bufSize - 1, "%ld", utGetLong(pu, name, p));break;
			case U_DOUBLE:snprintf(buf, bufSize - 1, "%0.2f", utGetDouble(pu, name, p));break;
			case U_STRING:snprintf(buf, bufSize - 1, "%s", utGetStr(pu, name, p));break;
			default:strcpy(buf, "");break;
		}
		return buf;
	}

    char sUtypeNodeName[127 + 1];
    uAutoPtr uTmp(uInit(0));
    uTmp = utClone(pu);
    int iLen = uTmp->cnt; 
    
    for(int i = 0; i < iLen; i ++)
    {
        //首先按从上往下的顺序取utype当前目录下所有节点，
        //并判断节点是否为utype，为utype则进入utype，然后回调自身
        memset(sUtypeNodeName, 0, sizeof(sUtypeNodeName));
        strcpy(sUtypeNodeName, utGetName(pu, i));
        //printf("*****************sUtypeNodeName=[%s]***********************\n", sUtypeNodeName);
        int uTypeType = utGetType(pu, sUtypeNodeName);
        if(U_STRUCT == uTypeType)
        {
            uGetStrByName(utGetStruct(pu, sUtypeNodeName), buf, bufSize, name);
            if('\0' != buf[0])
            {
                return buf;
            }
        }
    }
    return buf;
}
char* getSelfGroupId(const char* sGroupId, char* sSelfGroup, TCtrlInfo *ptCtrlInfo)
{
    otl_nocommit_stream qSelfGroup(1,
					"SELECT B.PARENT_CLASS_CODE GROUP_ID FROM BS_CHNGROUP_DICT A,BS_CHNCLASS_REL B\
                    WHERE A.CLASS_CODE=B.CLASS_CODE \
                       AND B.DENORM_LEVEL=1\
                       AND A.GROUP_ID = :GROUP_ID<char[11]>", GETDB(ptCtrlInfo));

    if(NULL == sGroupId)
    {
    	qSelfGroup<<otl_null();
    }
    else
    {
	    qSelfGroup<<sGroupId;
    }

    qSelfGroup.flush();
    if(!qSelfGroup.eof())
    {
    	qSelfGroup>>sSelfGroup;
	}

	return sSelfGroup;
}

int NMLogCallBack(
	const char *psServiceName,		//服务名称
	TCtrlInfo *ptCtrlInfo,			//自有营业厅获取
	const char *psDbLabel,			//数据库标签名称
	const char *psUtypeFunc,		//服务调用BP名称
	const utype *pu_in,				//输入参数Utype
	struct timeval *tp_begin,		//服务调用开始时间
	const int retCode,              //服务返回代码
	const char *retMsg              //服务返回信息
	)
{
	struct	timeval tp_end;
	struct	tm *l_begin;
	struct	tm *l_end;
	char strbegin[40];
	char strend[40];
	char sGroupId[11];
	char buf[128];
	char sSelfGroup[17];
	char sOpCode[6];
	char sServiceNo[101];
	char sLoginNo[21];
	char sSerialNo[41];
	char sIdNo[41];
	char sBusiAccept[128];

	memset(strbegin, 0, sizeof(strbegin));
	memset(strend, 0, sizeof(strend));
	memset(sGroupId, 0, sizeof(sGroupId));
	memset(sSelfGroup, 0, sizeof(sSelfGroup));
	memset(sBusiAccept, 0, sizeof(sBusiAccept));
	
	//开始时间处理
	l_begin=localtime(&tp_begin->tv_sec);
	sprintf(strbegin,"%d%02d%02d%02d%02d%02d",
		l_begin->tm_year+1900,	//年份
		l_begin->tm_mon+1,		//月份
		l_begin->tm_mday,		//日期
		l_begin->tm_hour,		//小时
		l_begin->tm_min,		//分钟
		l_begin->tm_sec			//秒
	);
	
	//结束时间处理
	gettimeofday(&tp_end,NULL);
	l_end=localtime(&tp_end.tv_sec);
	sprintf(strend,"%d%02d%02d%02d%02d%02d",
		l_end->tm_year+1900,	//年份
		l_end->tm_mon+1,		//月份
		l_end->tm_mday,			//日期
		l_end->tm_hour,			//小时
		l_end->tm_min,			//分钟
		l_end->tm_sec			//秒
	);
	
	long		lRetCode = 0;

	lRetCode = ptCtrlInfo->lErrCode == 0 ? 0 : 1;

	uGetStrByName(pu_in,  sGroupId, sizeof(sGroupId), "GROUP_ID");
	uGetStrByName(pu_in,  sOpCode, sizeof(sOpCode), "OP_CODE");
	uGetStrByName(pu_in,  sServiceNo, sizeof(sServiceNo), "SERVICE_NO");
	if(0 == strcmp(sServiceNo, ""))
	{
		uGetStrByName(pu_in,  sServiceNo, sizeof(sServiceNo), "PHONE_NO");
	}
	uGetStrByName(pu_in,  sLoginNo, sizeof(sLoginNo), "LOGIN_NO");
	uGetStrByName(pu_in,  sSerialNo, sizeof(sSerialNo), "SERIAL_NO");
	if(0 != strcmp(sGroupId, ""))
	{
		getSelfGroupId(sGroupId, sSelfGroup, ptCtrlInfo);
	}
	
	//zhanghq要求加上ID_NO
	uGetStrByName(pu_in,  sIdNo, sizeof(sIdNo), "ID_NO");
	
	uGetStrByName(pu_in,  sBusiAccept, sizeof(sBusiAccept), "OUT_BUSI_ACCEPT");
	
	printf("mktime(l_end)=%ld\n",mktime(l_end));
	printf("mktime(l_begin)=%ld\n",mktime(l_begin));
	
	printf("NMLOGLINE|%s|%s|%s|%s|%s|%ld|%s|%s|%ld|%s|%s|%s\n", 
		psServiceName,									//服务名
		sOpCode,										//模块代码
		sServiceNo,										//电话号码
		sIdNo,											//用户号码
		sLoginNo,										//操作工号
		lRetCode,										//调服务是否成功，0成功、1失败
		strbegin,										//开始时间
		strend,											//结束时间
		tp_end.tv_sec-tp_begin->tv_sec,					//时长
		sGroupId,										//营业厅group_id
		sSelfGroup,										//是否自有营业厅
		sSerialNo										//TD日志标识
		);
	
	//记录额外的服务调用日志， 山西移动端到端需求
	const char *store_path, *openflag;
	char logfile[128];
	//int fileid;
	FILE *fp;
	char tempbuf[2048];
	
	store_path = cfgGetStr("ERRLOG", "DATA_PATH");
	if(store_path[0] == 0)
		return 0; //如果没有配置, 则忽略
	sprintf(logfile, "svc_%s", psServiceName);
	openflag = cfgGetStr("ERRLOG", logfile);
	if(openflag[0] != '1')
		return 0; // 服务开关没打开， 退出

	//filename: TUXLOG.yyyymmddHH
	sprintf(logfile, "%s/TUXLOG.%04d%02d%02d%02d",
			store_path,
			l_end->tm_year+1900, l_end->tm_mon+1, l_end->tm_mday, l_end->tm_hour);
	//fileid = open(logfile, O_WRONLY|O_CREAT|O_APPEND, 0666);
	fp = fopen(logfile, "a");
	if(fp == NULL)
		return 0;
	sprintf(tempbuf, "NMLOGLINE|%s|%s|%s|%s|%s|%ld|%s|%s|%ld|%s|%s|%s|%s|%d|%s\n", 
		psServiceName,									//服务名
		sOpCode,										//模块代码
		sServiceNo,										//电话号码
		sIdNo,											//用户号码
		sLoginNo,										//操作工号
		lRetCode,										//调服务是否成功，0成功、1失败
		strbegin,										//开始时间
		strend,											//结束时间
		tp_end.tv_sec-tp_begin->tv_sec,					//时长
		sGroupId,										//营业厅group_id
		sSelfGroup,										//是否自有营业厅
		sSerialNo,										//TD日志标识
		sBusiAccept,
		retCode,
		retMsg
		);

	fwrite(tempbuf, strlen(tempbuf), 1, fp);
	fclose(fp);

	return 0;
}

void GlobalBusiInit(const char *psServiceName,		//服务名称
	const char *psDbLabel,							//数据库标签名称
	const char *psUtypeFunc,						//服务调用BP名称
	const utype *pu_in								//输入参数Utype
)
{
	TOprInfo sOprInfo;
	
	memset(&sOprInfo, 0 ,sizeof(&sOprInfo));
	
	//服务号码
	uGetStrByName(pu_in,sOprInfo.sServiceNo, sizeof(sOprInfo.sServiceNo) , "SERVICE_NO");
	if(0 == strcmp(sOprInfo.sServiceNo, ""))
	{
		uGetStrByName(pu_in,sOprInfo.sServiceNo, sizeof(sOprInfo.sServiceNo) , "PHONE_NO");
	}
	//工号
	uGetStrByName(pu_in,sOprInfo.sLoginNo, sizeof(sOprInfo.sLoginNo) , "LOGIN_NO");
	//操作代码
	uGetStrByName(pu_in,sOprInfo.sOpCode, sizeof(sOprInfo.sOpCode) , "OP_CODE");
	//客户接触ID
	uGetStrByName(pu_in,sOprInfo.sContactId, sizeof(sOprInfo.sContactId) , "CONTACT_ID");
	//交易流水
	uGetStrByName(pu_in,sOprInfo.sLoginAccept, sizeof(sOprInfo.sLoginAccept) , "LOGIN_ACCEPT");
	
	//操作信息处理
	GlobalInitOprInfo(sOprInfo);	
}