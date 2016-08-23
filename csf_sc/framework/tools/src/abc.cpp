#include <iostream>
#include <fstream>
#include <map>

//////////////////// oracle occi head
#define OTL_ORA9I // Compile OTL 4/OCI8
#include <otlv4.h> // include the OTL 4 header file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;


/*读取指定section 下的所有key,value，保存在map中*/
#include <map>
#include <iostream>

int cfg_get_keys(const char *CFG_file, const char *section, map<string, string> *amap);


typedef enum optype{
	OT_NULL=0,
	OT_INERT,
	OT_SELECT,
	OT_UPDATE,
	OT_DELETE
} e_optype;

typedef struct table{
	char tbname[32];
	e_optype op;
} t_table;



extern t_table ta[100];
extern int sufx;

otl_connect db;
otl_connect db_dict;
bool has_dict;

void ansy_sql(char* s, size_t len);
int inner_trim(char* s);
int sqlcat(char* s, char* s1, size_t s1len, int lastLine);

int parseSuffix(char* sqlText,const char* src, char* parseText, const char* suff)
{
	int i=0;
	int pp, p2=0;
	size_t len=strlen(suff);
	for(pp=0;sqlText[pp]!=0;++pp){
		if(sqlText[pp]=='~'&&sqlText[pp+1]!=0){
			sqlText[pp]='%';
			sqlText[pp+1]='s';
			++i;
			++pp;
		}
	}
	for(pp=0;src[pp]!=0;++pp, ++p2){
		if(src[pp]=='~'&&src[pp+1]!=0){
			memcpy(parseText+p2, suff, len);
			p2+=len-1;
			++pp;
		}else parseText[p2]=src[pp];
	}
	parseText[p2]=0;
	return i;
}
char parseCmd(char * sqlText)
{
	char cmd[20];
	int bb,pp,ll;

	pp=0;
	bb=0;
	ll=0;
	while(sqlText[pp]==' '||sqlText[pp]=='\t'){
		if(sqlText[pp]==0){
			fprintf(stderr, "请输入sql语句!\n");
			exit(1);
		}
		pp++;
	}
	bb=pp;
	while(sqlText[pp]!=' ' && sqlText[pp]!='\t' && sqlText[pp]!='\\' && sqlText[pp]!='\n' && sqlText[pp]!='#'){
		ll++;
		pp++;
	}
	memset(cmd,0,sizeof(cmd));
	strncpy(cmd,sqlText+bb,ll);

	for(int i = 0; i < ll; i++)
                cmd[i] = toupper(cmd[i]);

	if(strcmp(cmd,"INSERT")==0)
		return 'I';
	else if(strcmp(cmd,"DELETE")==0)
		return 'D';
	else if(strcmp(cmd,"UPDATE")==0)
		return 'U';
	else if(strcmp(cmd,"SELECT")==0)
		return 'S';
	else
		return 'N';

}

int genInit(char * funcName,char * sCode)
{
	sprintf(sCode,"%s","#include <allBCP.h>\n");

	sprintf(sCode,"%s\nusing namespace std;\n",sCode);

	sprintf(sCode,"%s\nutype* %s(const utype * inParam,TCtrlInfo *errInfo)\n",sCode,funcName);
	sprintf(sCode,"%s{\n",sCode);
	sprintf(sCode, "%s    LOG_FUNC_BC();\n", sCode);
	return 0;
}

int genBusi(char *funcName,char * sqlText,char* parseText,int INMROW,int OUTMROW,char * sCode,char * sParam,int SUFFIX)
{
	int i;
	int ivars,ovars;
	char smFuncName[40];
	char CMD;
	int otlBuff;

	otl_nocommit_stream sm_parse(10,parseText,db);
	CMD=parseCmd(parseText);
	otl_nocommit_stream sm_ibusiparam;
	
	if(has_dict)
		sm_ibusiparam.open(1,"Insert into BS_MODPARAM_INFO \
						   (MOD_NAME, IN_OUT, POS_CODE, DATA_TYPE, DATA_NAME, DATA_DESC, DATA_LEN) \
						 Values \
						   (:MOD_NAME<char[255+1>, :IO<char[1+1]>, :POS<int>, :DATA_TYPE<char[20+1]>, \
						   :DATA_NAME<char[255+1]>, :DATA_DESC<char[255+1]>, :LEN<int>)"
					   ,db_dict);

	sprintf(sCode,"%s\tL4C_TRACE(\"------==INPUT BEGIN==-------\");\n",sCode);
	sprintf(sCode,"%s\tLogUtype(inParam);\n",sCode);
	sprintf(sCode,"%s\tL4C_TRACE(\"------==INPUT END==-------\");\n",sCode);
	sprintf(sCode,"%s\tif(errInfo){\n\t\tmemset(errInfo,0,sizeof(TCtrlInfo));\n\t}\n",sCode);

	otl_var_desc* vdesc;
	int vdesc_len;

	vdesc=sm_parse.describe_in_vars(vdesc_len);

	otl_column_desc* cdesc;
	int cdesc_len;

	cdesc=sm_parse.describe_select(cdesc_len);

	sprintf(smFuncName,"sm_%s",funcName);


	if(cdesc_len>0)
		sprintf(sCode,"%s\n\tuAutoPtr uap(uInit(0));\n\n",sCode);


	sprintf(sCode,"%s\tint rpcRows=0;\n",sCode);
	sprintf(sCode,"%s\totl_nocommit_stream %s;\n\n",sCode,smFuncName);
	sprintf(sCode,"%s\n\t%s.set_flush(false);\n",sCode,smFuncName);


	if(INMROW && (sm_parse.get_stream_type()!=otl_select_stream_type)
		|| OUTMROW && (sm_parse.get_stream_type()==otl_select_stream_type))
		otlBuff=10;
	else
		otlBuff=1;
	if(SUFFIX){
		sprintf(sCode,"%s\tchar sqlStatement[4096];\n",sCode);
		sprintf(sCode,"%s\tsprintf(sqlStatement,\"%s\"",sCode,sqlText);
		for(int sxhi=0;sxhi<SUFFIX;++sxhi) strcat(sCode,"\n\t\t\t\t,utGetStr(inParam,\"SUFFIX\")");
		sprintf(sCode,"%s);\n\t%s.open(%d,sqlStatement,GETDB(errInfo));\n\n",sCode,smFuncName,otlBuff);
	}
	else{
		sprintf(sCode,"%s\t%s.open(%d,\"%s\",GETDB(errInfo));\n\n",sCode,smFuncName,otlBuff,sqlText);
	}

	sprintf(sParam,"///////////////// Input parameters ////////////////\n");
	if(INMROW){
		if(vdesc_len>0 || SUFFIX){
			sprintf(sParam,"%s// @\tARRAY\n",sParam);
			if(SUFFIX)
				sprintf(sParam,"%s// -@0\tSTRING\tSUFFIX\n",sParam);
		}

		if(vdesc_len>0){
			sprintf(sCode,"%s\tconst utype* rp;\n\n",sCode);
			sprintf(sCode,"%s\tchar inDataName[U_MAXNAMELEN];\n",sCode);
			sprintf(sCode,"%s\tstrcpy(inDataName,utGetStr(inParam,\"INDATANAME\"));\n",sCode);
			sprintf(sCode,"%s\tfor(UPOS pos=utFind(inParam,inDataName) ; pos!=UPOS_END ; pos=utNext(inParam,pos)){\n",sCode);
			sprintf(sCode,"%s\t\trp=utGetStruct(inParam,inDataName,pos);\n\n",sCode);
			sprintf(sParam,"%s// -@*\tSTRUCT\n",sParam);
		}

		for(i=0;i<vdesc_len;++i){
			sprintf(sCode,"%s\n\t\tif(utGetEmpty(rp,\"%s\"))\n",sCode,vdesc[i].name+1);
			sprintf(sCode,"%s\t\t\t%s<<otl_null();\n",sCode,smFuncName);
			sprintf(sCode,"%s\t\telse\n",sCode);
			switch(vdesc[i].ftype){
				case 1:
				sprintf(sParam,"%s// --@%d\t%s\t%s\n",sParam,i,"STRING",vdesc[i].name+1);
				sprintf(sCode,"%s\t\t\t%s<<utGetStr(rp,\"%s\");\n",sCode,smFuncName,vdesc[i].name+1);
				if(has_dict) sm_ibusiparam<<funcName<<"i"<<i<<"String"<<(vdesc[i].name+1)<<(vdesc[i].name+1)<<(vdesc[i].elem_size);
				break;
				case 2:
				case 3:
				sprintf(sParam,"%s// --@%d\t%s\t%s\n",sParam,i,"DOUBLE",vdesc[i].name+1);
				sprintf(sCode,"%s\t\t\t%s<<utGetDouble(rp,\"%s\");\n",sCode,smFuncName,vdesc[i].name+1);
				if(has_dict) sm_ibusiparam<<funcName<<"i"<<i<<"Double"<<(vdesc[i].name+1)<<(vdesc[i].name+1)<<(vdesc[i].elem_size);
				break;
				case 4:
				sprintf(sParam,"%s// --@%d\t%s\t%s\n",sParam,i,"INT",vdesc[i].name+1);
				sprintf(sCode,"%s\t\t\t%s<<utGetInt(rp,\"%s\");\n",sCode,smFuncName,vdesc[i].name+1);
				if(has_dict) sm_ibusiparam<<funcName<<"i"<<i<<"Int"<<(vdesc[i].name+1)<<(vdesc[i].name+1)<<(vdesc[i].elem_size);
				break;
				case 7:
				sprintf(sParam,"%s// --@%d\t%s\t%s\n",sParam,i,"LONG",vdesc[i].name+1);
				sprintf(sCode,"%s\t\t\t%s<<utGetLong(rp,\"%s\");\n",sCode,smFuncName,vdesc[i].name+1);
				if(has_dict) sm_ibusiparam<<funcName<<"i"<<i<<"Long"<<(vdesc[i].name+1)<<(vdesc[i].name+1)<<(vdesc[i].elem_size);
				break;
			}
		}
		if(i>0){
			sprintf(sCode,"%s\t}\n",sCode);
		}
	}
	else{
		if(vdesc_len>0 || SUFFIX){
			sprintf(sParam,"%s// @\tSTRUCT\n",sParam);
			if(SUFFIX)
				sprintf(sParam,"%s// -@0\tSTRING\tSUFFIX\n",sParam);
		}
		for(i=0;i<vdesc_len;++i){
			int ii;
			if(SUFFIX)
				ii=i+1;
			else
				ii=i;

			sprintf(sCode,"%s\n\tif(utGetEmpty(inParam,\"%s\"))\n",sCode,vdesc[i].name+1);
			sprintf(sCode,"%s\t\t%s<<otl_null();\n",sCode,smFuncName);
			sprintf(sCode,"%s\telse\n",sCode);
			switch(vdesc[i].ftype){
				case 1:
				sprintf(sParam,"%s// -@%d\t%s\t%s\n",sParam,ii,"STRING",vdesc[i].name+1);
				sprintf(sCode,"%s\t\t%s<<utGetStr(inParam,\"%s\");\n",sCode,smFuncName,vdesc[i].name+1);
				if(has_dict) sm_ibusiparam<<funcName<<"i"<<i<<"String"<<(vdesc[i].name+1)<<(vdesc[i].name+1)<<(vdesc[i].elem_size);
				break;
				case 2:
				case 3:
				sprintf(sParam,"%s// -@%d\t%s\t%s\n",sParam,ii,"DOUBLE",vdesc[i].name+1);
				sprintf(sCode,"%s\t\t%s<<utGetDouble(inParam,\"%s\");\n",sCode,smFuncName,vdesc[i].name+1);
				if(has_dict) sm_ibusiparam<<funcName<<"i"<<i<<"Double"<<(vdesc[i].name+1)<<(vdesc[i].name+1)<<(vdesc[i].elem_size);
				break;
				case 4:
				sprintf(sParam,"%s// -@%d\t%s\t%s\n",sParam,ii,"INT",vdesc[i].name+1);
				sprintf(sCode,"%s\t\t%s<<utGetInt(inParam,\"%s\");\n",sCode,smFuncName,vdesc[i].name+1);
				if(has_dict) sm_ibusiparam<<funcName<<"i"<<i<<"Int"<<(vdesc[i].name+1)<<(vdesc[i].name+1)<<(vdesc[i].elem_size);
				break;
				case 7:
				sprintf(sParam,"%s// -@%d\t%s\t%s\n",sParam,ii,"LONG",vdesc[i].name+1);
				sprintf(sCode,"%s\t\t%s<<utGetLong(inParam,\"%s\");\n",sCode,smFuncName,vdesc[i].name+1);
				if(has_dict) sm_ibusiparam<<funcName<<"i"<<i<<"Long"<<(vdesc[i].name+1)<<(vdesc[i].name+1)<<(vdesc[i].elem_size);
				break;
			}
		}
	}

	sprintf(sCode,"%s\n\t%s.flush();\n",sCode,smFuncName);

	if(cdesc_len==0){

		sprintf(sCode,"%s\n\trpcRows+=%s.get_rpc();\n",sCode,smFuncName);
		sprintf(sCode,"%s\tif(errInfo){\n\t\terrInfo->iSqlRows = rpcRows;\n\t}\n",sCode);

		sprintf(sCode,"%s\tL4C_TRACE(\"------==OUTPUT BEGIN==-------\");\n",sCode);
		sprintf(sCode,"%s\tL4C_TRACE(\"此构件无输出\");\n",sCode);
		sprintf(sCode,"%s\tL4C_TRACE(\"------==OUTPUT END==-------\");\n",sCode);
		sprintf(sCode,"%s\treturn NULL;\n",sCode);
		sprintf(sCode,"%s}\n",sCode);

		return 0;
	}

	sprintf(sParam,"%s////////////////////////////////////////////////////\n",sParam);

	if(cdesc_len>0){
		if(OUTMROW){
			sprintf(sCode,"%s\tchar outDataName[U_MAXNAMELEN];\n",sCode);
			sprintf(sCode,"%s\tstrcpy(outDataName,utGetStr(inParam,\"OUTDATANAME\"));\n",sCode);
		}
	}

	sprintf(sCode,"%s\n\twhile(!%s.eof()){\n",sCode,smFuncName);

	for(i=0;i<cdesc_len;++i){
		switch(cdesc[i].otl_var_dbtype){
			case 1:
			sprintf(sCode,"%s\t\tchar f%d[%d+1];\n",sCode,i,cdesc[i].dbsize);
			if(has_dict) sm_ibusiparam<<funcName<<"o"<<i<<"String"<<(cdesc[i].name)<<(cdesc[i].name)<<(cdesc[i].dbsize);
			break;
			case 2:
			case 3:
			if(cdesc[i].scale==0)
				if(cdesc[i].prec>9){
					sprintf(sCode,"%s\t\tlong f%d;\n",sCode,i);
					if(has_dict) sm_ibusiparam<<funcName<<"o"<<i<<"Long"<<(cdesc[i].name)<<(cdesc[i].name)<<(cdesc[i].prec);
				}
				else{
					sprintf(sCode,"%s\t\tint f%d;\n",sCode,i);
					if(has_dict) sm_ibusiparam<<funcName<<"o"<<i<<"Int"<<(cdesc[i].name)<<(cdesc[i].name)<<(cdesc[i].prec);
				}
			else {
				sprintf(sCode,"%s\t\tdouble f%d;\n",sCode,i);
				if(has_dict) sm_ibusiparam<<funcName<<"o"<<i<<"Double"<<(cdesc[i].name)<<(cdesc[i].name)<<(cdesc[i].prec);
			}
			break;
			case 4:
			sprintf(sCode,"%s\t\tint f%d;\n",sCode,i);
			if(has_dict) sm_ibusiparam<<funcName<<"o"<<i<<"Int"<<(cdesc[i].name)<<(cdesc[i].name)<<(cdesc[i].prec);
			break;
			case 7:
			sprintf(sCode,"%s\t\tlong f%d;\n",sCode,i);
			if(has_dict) sm_ibusiparam<<funcName<<"o"<<i<<"Long"<<(cdesc[i].name)<<(cdesc[i].name)<<(cdesc[i].prec);
			break;
		}

	}

	sprintf(sCode,"%s\n",sCode);

	sprintf(sParam,"%s///////////////// Output parameters ////////////////\n",sParam);

	if(OUTMROW){
		if(cdesc_len>0){
			sprintf(sCode,"%s\n\t\tutype* rp=uInit(%d);\n",sCode,cdesc_len);
			sprintf(sCode,"%s\t\tuAutoPtr ap(rp);\n",sCode);
			sprintf(sCode,"%s\t\tutAddStruct(uap,outDataName,rp);\n",sCode);
			sprintf(sCode,"%s\t\tap.release();\n",sCode,cdesc_len);
			sprintf(sParam,"%s// @\tARRAY\n",sParam);
			sprintf(sParam,"%s// -@*\tSTRUCT\n",sParam);
		}
		for(i=0;i<cdesc_len;++i){
			sprintf(sCode,"%s\n\t\t%s>>f%d;\n",sCode,smFuncName,i);
			sprintf(sCode,"%s\t\tif(%s.is_null())\n",sCode,smFuncName);
			if(cdesc[i].otl_var_dbtype==1)
				sprintf(sCode,"%s\t\t\tutAddStr(rp,\"%s\",\"\");\n",sCode,cdesc[i].name);
			else
				sprintf(sCode,"%s\t\t\tutAddEmpty(rp,\"%s\");\n",sCode,cdesc[i].name);
			sprintf(sCode,"%s\t\telse\n",sCode);

			switch(cdesc[i].otl_var_dbtype){
				case 1:
				sprintf(sParam,"%s// --@%d\t%s\t%s\n",sParam,i,"STRING",cdesc[i].name);
				sprintf(sCode,"%s\t\t\tutAddStr(rp,\"%s\",Rtrim(f%d));\n",sCode,cdesc[i].name,i);
				break;
				case 2:
				case 3:
				if(cdesc[i].scale==0){
					if(cdesc[i].prec>9){
						sprintf(sParam,"%s// --@%d\t%s\t%s\n",sParam,i,"LONG",cdesc[i].name);
						sprintf(sCode,"%s\t\t\tutAddLong(rp,\"%s\",f%d);\n",sCode,cdesc[i].name,i);
					}
					else{
						sprintf(sParam,"%s// --@%d\t%s\t%s\n",sParam,i,"INT",cdesc[i].name);
						sprintf(sCode,"%s\t\t\tutAddInt(rp,\"%s\",f%d);\n",sCode,cdesc[i].name,i);
					}
				}
				else{
					sprintf(sParam,"%s// --@%d\t%s\t%s\n",sParam,i,"DOUBLE",cdesc[i].name);
					sprintf(sCode,"%s\t\t\tutAddDouble(rp,\"%s\",f%d);\n",sCode,cdesc[i].name,i);
				}
				break;
				case 4:
				sprintf(sParam,"%s// --@%d\t%s\t%s\n",sParam,i,"INT",cdesc[i].name);
				sprintf(sCode,"%s\t\t\tutAddInt(rp,\"%s\",f%d);\n",sCode,cdesc[i].name,i);
				break;
				case 7:
				sprintf(sParam,"%s// @%d.*\t%s\t%s\n",sParam,i,"LONG",cdesc[i].name);
				sprintf(sCode,"%s\t\t\tutAddLong(rp,\"%s\",f%d);\n",sCode,cdesc[i].name,i);
				break;
			}
		}

		sprintf(sCode,"%s\n\t\trpcRows++;\n",sCode);
	}
	else{
		if(cdesc_len>0)
			sprintf(sParam,"%s// @\tSTRUCT\n",sParam);
		for(i=0;i<cdesc_len;++i){
			sprintf(sCode,"%s\n\t\t%s>>f%d;\n",sCode,smFuncName,i);
			sprintf(sCode,"%s\t\tif(%s.is_null())\n",sCode,smFuncName);
			if(cdesc[i].otl_var_dbtype==1)
				sprintf(sCode,"%s\t\t\tutAddStr(uap,\"%s\",\"\");\n",sCode,cdesc[i].name);
			else
				sprintf(sCode,"%s\t\t\tutAddEmpty(uap,\"%s\");\n",sCode,cdesc[i].name);
			sprintf(sCode,"%s\t\telse\n",sCode);

			switch(cdesc[i].otl_var_dbtype){
				case 1:
				sprintf(sParam,"%s// -@%d\t%s\tSTRING\n",sParam,i,cdesc[i].name);
				sprintf(sCode,"%s\t\t\tutAddStr(uap,\"%s\",Rtrim(f%d));\n",sCode,cdesc[i].name,i);
				break;
				case 2:
				case 3:
				if(cdesc[i].scale==0){
					if(cdesc[i].prec>9){
						sprintf(sParam,"%s// -@%d\t%s\tLONG\n",sParam,i,cdesc[i].name);
						sprintf(sCode,"%s\t\t\tutAddLong(uap,\"%s\",f%d);\n",sCode,cdesc[i].name,i);
					}
					else{
						sprintf(sParam,"%s// -@%d\t%s\tINT\n",sParam,i,cdesc[i].name);
						sprintf(sCode,"%s\t\t\tutAddInt(uap,\"%s\",f%d);\n",sCode,cdesc[i].name,i);
					}
				}
				else{
					sprintf(sParam,"%s// -@%d\t%s\tDOUBLE\n",sParam,i,cdesc[i].name);
					sprintf(sCode,"%s\t\t\tutAddDouble(uap,\"%s\",f%d);\n",sCode,cdesc[i].name,i);
				}
				break;
				case 4:
				sprintf(sParam,"%s// -@%d\t%s\tINT\n",sParam,i,cdesc[i].name);
				sprintf(sCode,"%s\t\t\tutAddInt(uap,\"%s\",f%d);\n",sCode,cdesc[i].name,i);
				break;
				case 7:
				sprintf(sParam,"%s// -@%d\t%s\tLONG\n",sParam,i,cdesc[i].name);
				sprintf(sCode,"%s\t\t\tutSetLong(uap,\"%s\",f%d);\t//%s\n",sCode,cdesc[i].name,i);
				break;
			}
		}
		sprintf(sCode,"%s\n\t\trpcRows++;\n",sCode);
		sprintf(sCode,"%s\t\tbreak;\n",sCode);
	}

	sprintf(sParam,"%s////////////////////////////////////////////////////\n",sParam);
	sprintf(sCode,"%s\t}\n",sCode);

	sprintf(sCode,"%s\tif(errInfo){\n\t\terrInfo->iSqlRows = rpcRows;\n\t}\n",sCode,smFuncName);
	sprintf(sCode,"%s\tL4C_TRACE(\"------==OUTPUT BEGIN==-------\");\n",sCode);
	sprintf(sCode,"%s\tLogUtype(uap);\n",sCode);
	sprintf(sCode,"%s\tL4C_TRACE(\"------==OUTPUT END==-------\");\n",sCode);
	sprintf(sCode,"%s\treturn(uap.release());\n",sCode);


	sprintf(sCode,"%s}\n",sCode);

	return 0;
}




int main(int argc,char **argv)
{
	char initCode[1024];
	char sCode[40960];
	char sParam[4096];
	int SUFFIX;
    bool iscfgsql = false;

    int in_mrows, out_mrows;
    char bc_name[50], bc_outfile[128], bc_desc[128], tbl_suffix[30];
    char *sql_file;

    char sqlText[10240];
    char parseText[10240];
    char ll[256];
    int lastLine=0;
    
    if(argc == 3){
        //按照参数都在sql文件中处理
        iscfgsql = true;
    }else if(argc<8){
		fprintf(stderr, "Usage: \n    abc user/passwd@db[:user2/passwd2@cfgdb] bc_name in_mrows out_mrows sql_file  bc_file bc_desc [suffix]\n");
		fprintf(stderr, "    or abc user/passwd@db[:user2/passwd2@cfgdb] sql_file\n");
		exit(1);
	}
	/*if(argc<8){
		fprintf(stderr, "Usage: autoBC user/passwd@db:user2/passwd2@db2 bc_name in_mrows out_mrows sql_file  bc_file bc_desc [suffix]\n");
		exit(1);
	}*/
    map<string, string> params, fields; //保存配置数据的map
    map<string, string>::iterator it;
    if(iscfgsql){
        char buf[1024];

        sql_file = argv[2];

        cfg_get_keys(sql_file, "params", &params);
        //fprintf(stderr, "params.size=%d\n", params.size());
        strcpy(bc_name, params.find("bc_name")->second.c_str());
        in_mrows  = atoi(params.find("in_mrows")->second.c_str());
        out_mrows = atoi(params.find("out_mrows")->second.c_str());
        strcpy(bc_outfile, params.find("bc_outfile")->second.c_str());
        strcpy(bc_desc, params.find("bc_desc")->second.c_str());
        it = params.find("tbl_suffix");
        if(it == params.end())
        	SUFFIX = 0;
        else{
        	strcpy(tbl_suffix, it->second.c_str());
        	if(tbl_suffix[0] == 0)
        		SUFFIX = 0;
        	else
        		SUFFIX = 1;
        }
    }else{
        if(argc > 8){
            strcpy(tbl_suffix, argv[8]);
            SUFFIX=1;
        }else {
            SUFFIX=0;
            tbl_suffix[0] = 0;
        }
        strcpy(bc_name, argv[2]);
        in_mrows = atoi(argv[3]);
        out_mrows = atoi(argv[4]);
        sql_file = argv[5];
        strcpy(bc_outfile, argv[6]);
        strcpy(bc_desc, argv[7]);
    }

	try{
		otl_connect::otl_initialize();
		char* s=strchr(argv[1],':');

		if(s!=NULL){
			s[0]=0;
			++s;
			db.rlogon(argv[1]); // connect to Oracle
			db_dict.rlogon(s);
			has_dict = true;
		}else{
			has_dict = false;
			db.rlogon(argv[1]);
		}



		if(has_dict){
			otl_nocommit_stream sm_dbusimod;
			sm_dbusimod.open(1,"delete from  BS_BUSIMOD_INFO where MOD_NAME=:mod_name<char[255+1]>",db_dict);
			sm_dbusimod<<bc_name;
			otl_nocommit_stream sm_dmtr;
			sm_dmtr.open(1,"delete from  BS_MODTABRLT_INFO where MOD_NAME=:mod_name<char[255+1]>",db_dict);
			sm_dmtr<<bc_name;
			otl_nocommit_stream sm_dbusiparam;
			sm_dbusiparam.open(1,"delete from  BS_MODPARAM_INFO where MOD_NAME=:mod_name<char[255+1]>",db_dict);
			sm_dbusiparam<<bc_name;
			otl_nocommit_stream sm_ibusimod;
			sm_ibusimod.open(1,"Insert into BS_BUSIMOD_INFO \
							   (MOD_NAME, MOD_TYPE, MOD_DESC, FILE_NAME, MOD_VER, CREATE_TIME, MODIFY_TIME, RELEASE_FLAG) \
							 Values \
							   (:MOD_NAME<char[255+1]>, 'BC', :MOD_DESC<char[255+1]>, :FILE_NAME<char[255+1]>, '1.0', sysdate, sysdate, 'Y')"
							   ,db_dict);

			sm_ibusimod<<bc_name<<bc_desc<<bc_outfile;
		}

		memset(initCode,0,sizeof(initCode));
		memset(sCode,0,sizeof(sCode));
		memset(sParam,0,sizeof(sParam));

		genInit(bc_name,initCode);

		char sqlText[10240];
		char parseText[10240];
		char ll[256];
		int lastLine=0;

		memset(sqlText,0,sizeof(sqlText));
		memset(parseText,0,sizeof(parseText));
		memset(ll,0,sizeof(ll));
		int lines=0;

		FILE* fp;
		if((fp=fopen(sql_file,"r"))==NULL){
			fprintf(stderr, "打开文件 %s 失败\n",sql_file);
			exit(1);
		}
		while(fgets(ll,sizeof(ll),fp)!=NULL){
            if(ll[0] == '[')
                break; //读到配置参数部分了
            strcat(parseText,ll);
			if(ll[strlen(ll)-1]=='\n') ll[strlen(ll)-1]=' ';
			lastLine=sqlcat(sqlText, ll, strlen(ll), lastLine);

			lines++;
			if(ferror(stdin)){
				fprintf(stderr, "读取文件 %s 失败\n", sql_file);
				exit(1);
			}
		}

		fclose(fp);

		if(SUFFIX){
			char ppText[4096];
			strcpy(ppText,parseText);
			SUFFIX=parseSuffix(sqlText,ppText, parseText, tbl_suffix);
		}
		genBusi(bc_name, sqlText, parseText, in_mrows, out_mrows, sCode,sParam,SUFFIX);


		ansy_sql(parseText, inner_trim(parseText));
		
		if(has_dict)
		{
			map<string, int> sp;
			for(int j=0;j<sufx;++j){
				int flag=0;
				char* s=(char*)(&flag);
				if(sp.count(ta[j].tbname)==0){
					sp[ta[j].tbname]=0;
				}
				s[ta[j].op-1]=1;
				sp[ta[j].tbname]|=flag;
			}

			otl_nocommit_stream sm_imtr;
			sm_imtr.open(10,"Insert into BS_MODTABRLT_INFO \
							   (MOD_NAME, TAB_NAME, C, R, U, D) \
							 Values \
							(:MOD_NAME<char[255+1]>, :TAB_NAME<char[31+1]>, :C<char[1+1]>, :R<char[1+1]>, :U<char[1+1]>, :D<char[1+1]>) "
							   ,db_dict);
			for(map<string,int>::iterator it = sp.begin(); it != sp.end(); ++it){
				char ay[4][2]={"0","0","0","0"};
				char* s=(char*)(&it->second);
				if(s[0]) ay[0][0]='1';
				if(s[1]) ay[1][0]='1';
				if(s[2]) ay[2][0]='1';
				if(s[3]) ay[3][0]='1';
				sm_imtr<< bc_name << it->first.c_str() << ay[0]<< ay[1] << ay[2] << ay[3];
			}
			db_dict.commit();
		}

		db.rollback();
	}

	catch(otl_exception& p){// intercept OTL exceptions
		db.rollback();
		if(has_dict) db_dict.rollback();
		fprintf(stderr, "%s : %s : %s\n",p.msg,p.stm_text,p.var_info);
		exit(1);
	}

	printf("%s",sParam);
	printf("%s",initCode);
	printf("%s",sCode);
	return 0;
}
