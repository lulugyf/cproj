#include "framework.h"

/******************************************************
��������:	uGetStrByName
��������:	
����ʱ��:	2011-2-16
��������:	����utype�����нڵ㣬Ȼ��ȡ�����ֺʹ���������ͬ���ַ��������ء�
			����ȡ˳��Ϊ�������ڣ������ȴ���utype�ڵķ�utype�ڵ㣬Ȼ��ȡ�ڵ�Ϊutype�ݹ��������
�������:
	@	pu				����utype
	@	name			��Ҫȡ���Ľڵ�����
�������:
	@   char*			ȡ����Ӧ�ڵ����Ƶ�ֵ������ڵ㲻�����򷵻�NULL
����˵��:
 
�����¼:
 
******************************************************/
char* uGetStrByName(const utype* pu, char* buf, int bufSize, const char* name)
{
    UPOS p;
    memset(buf, 0, bufSize);
    //���ҵ�ǰutype���Ƿ�������Ϊname�Ľڵ㣬������򷵻ؽڵ�ֵ
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
        //���Ȱ��������µ�˳��ȡutype��ǰĿ¼�����нڵ㣬
        //���жϽڵ��Ƿ�Ϊutype��Ϊutype�����utype��Ȼ��ص�����
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
	const char *psServiceName,		//��������
	TCtrlInfo *ptCtrlInfo,			//����Ӫҵ����ȡ
	const char *psDbLabel,			//���ݿ��ǩ����
	const char *psUtypeFunc,		//�������BP����
	const utype *pu_in,				//�������Utype
	struct timeval *tp_begin,		//������ÿ�ʼʱ��
	const int retCode,              //���񷵻ش���
	const char *retMsg              //���񷵻���Ϣ
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
	
	//��ʼʱ�䴦��
	l_begin=localtime(&tp_begin->tv_sec);
	sprintf(strbegin,"%d%02d%02d%02d%02d%02d",
		l_begin->tm_year+1900,	//���
		l_begin->tm_mon+1,		//�·�
		l_begin->tm_mday,		//����
		l_begin->tm_hour,		//Сʱ
		l_begin->tm_min,		//����
		l_begin->tm_sec			//��
	);
	
	//����ʱ�䴦��
	gettimeofday(&tp_end,NULL);
	l_end=localtime(&tp_end.tv_sec);
	sprintf(strend,"%d%02d%02d%02d%02d%02d",
		l_end->tm_year+1900,	//���
		l_end->tm_mon+1,		//�·�
		l_end->tm_mday,			//����
		l_end->tm_hour,			//Сʱ
		l_end->tm_min,			//����
		l_end->tm_sec			//��
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
	
	//zhanghqҪ�����ID_NO
	uGetStrByName(pu_in,  sIdNo, sizeof(sIdNo), "ID_NO");
	
	uGetStrByName(pu_in,  sBusiAccept, sizeof(sBusiAccept), "OUT_BUSI_ACCEPT");
	
	printf("mktime(l_end)=%ld\n",mktime(l_end));
	printf("mktime(l_begin)=%ld\n",mktime(l_begin));
	
	printf("NMLOGLINE|%s|%s|%s|%s|%s|%ld|%s|%s|%ld|%s|%s|%s\n", 
		psServiceName,									//������
		sOpCode,										//ģ�����
		sServiceNo,										//�绰����
		sIdNo,											//�û�����
		sLoginNo,										//��������
		lRetCode,										//�������Ƿ�ɹ���0�ɹ���1ʧ��
		strbegin,										//��ʼʱ��
		strend,											//����ʱ��
		tp_end.tv_sec-tp_begin->tv_sec,					//ʱ��
		sGroupId,										//Ӫҵ��group_id
		sSelfGroup,										//�Ƿ�����Ӫҵ��
		sSerialNo										//TD��־��ʶ
		);
	
	//��¼����ķ��������־�� ɽ���ƶ��˵�������
	const char *store_path, *openflag;
	char logfile[128];
	//int fileid;
	FILE *fp;
	char tempbuf[2048];
	
	store_path = cfgGetStr("ERRLOG", "DATA_PATH");
	if(store_path[0] == 0)
		return 0; //���û������, �����
	sprintf(logfile, "svc_%s", psServiceName);
	openflag = cfgGetStr("ERRLOG", logfile);
	if(openflag[0] != '1')
		return 0; // ���񿪹�û�򿪣� �˳�

	//filename: TUXLOG.yyyymmddHH
	sprintf(logfile, "%s/TUXLOG.%04d%02d%02d%02d",
			store_path,
			l_end->tm_year+1900, l_end->tm_mon+1, l_end->tm_mday, l_end->tm_hour);
	//fileid = open(logfile, O_WRONLY|O_CREAT|O_APPEND, 0666);
	fp = fopen(logfile, "a");
	if(fp == NULL)
		return 0;
	sprintf(tempbuf, "NMLOGLINE|%s|%s|%s|%s|%s|%ld|%s|%s|%ld|%s|%s|%s|%s|%d|%s\n", 
		psServiceName,									//������
		sOpCode,										//ģ�����
		sServiceNo,										//�绰����
		sIdNo,											//�û�����
		sLoginNo,										//��������
		lRetCode,										//�������Ƿ�ɹ���0�ɹ���1ʧ��
		strbegin,										//��ʼʱ��
		strend,											//����ʱ��
		tp_end.tv_sec-tp_begin->tv_sec,					//ʱ��
		sGroupId,										//Ӫҵ��group_id
		sSelfGroup,										//�Ƿ�����Ӫҵ��
		sSerialNo,										//TD��־��ʶ
		sBusiAccept,
		retCode,
		retMsg
		);

	fwrite(tempbuf, strlen(tempbuf), 1, fp);
	fclose(fp);

	return 0;
}

void GlobalBusiInit(const char *psServiceName,		//��������
	const char *psDbLabel,							//���ݿ��ǩ����
	const char *psUtypeFunc,						//�������BP����
	const utype *pu_in								//�������Utype
)
{
	TOprInfo sOprInfo;
	
	memset(&sOprInfo, 0 ,sizeof(&sOprInfo));
	
	//�������
	uGetStrByName(pu_in,sOprInfo.sServiceNo, sizeof(sOprInfo.sServiceNo) , "SERVICE_NO");
	if(0 == strcmp(sOprInfo.sServiceNo, ""))
	{
		uGetStrByName(pu_in,sOprInfo.sServiceNo, sizeof(sOprInfo.sServiceNo) , "PHONE_NO");
	}
	//����
	uGetStrByName(pu_in,sOprInfo.sLoginNo, sizeof(sOprInfo.sLoginNo) , "LOGIN_NO");
	//��������
	uGetStrByName(pu_in,sOprInfo.sOpCode, sizeof(sOprInfo.sOpCode) , "OP_CODE");
	//�ͻ��Ӵ�ID
	uGetStrByName(pu_in,sOprInfo.sContactId, sizeof(sOprInfo.sContactId) , "CONTACT_ID");
	//������ˮ
	uGetStrByName(pu_in,sOprInfo.sLoginAccept, sizeof(sOprInfo.sLoginAccept) , "LOGIN_ACCEPT");
	
	//������Ϣ����
	GlobalInitOprInfo(sOprInfo);	
}