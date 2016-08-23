#include "framework.h"


#include <dlfcn.h>
#include <time.h>

/*
根据utype参数替换sql字符串中的符号参数， 下面为测试代码：
	const char *sql =
		"select 1 from table${ID_NO[-2:]}#{%Y%m} ${PHONE_NO[1:4]} ${PHONE_NO[1:-4]} ${PHONE_NO[:-2]} where rownum<2";
	uAutoPtr pp(uInit(1));
	utAddLong(pp, "ID_NO", 1234567L);
	utAddStr(pp, "PHONE_NO", "abcdefghijk");
运行结果： select 1 from table67201304 bcd bcdefg abcdefghi where rownum<2

 */
void sqlreplace(const char *sql, string &sql1, const utype *inparam)
{
	char *p0, *p1;
	char pname[128], pvalue[128];

	p0 = (char *)sql;
	while( *p0 != 0){
		if(*p0 == '#' && *(p0+1) == '{'){
			p0 += 2;
			p1 = strchr(p0, '}');
			if(p1 == NULL)
				continue;
			strncpy(pname, p0, p1-p0);
			pname[p1-p0] = 0;
			p0 = p1+1;

			time_t t;
			time(&t);
			struct tm *tm = localtime(&t);
			pvalue[0] = 0;
			strftime(pvalue, sizeof(pvalue), pname, tm);
			sql1.append(pvalue);
		}else if(*p0 == '$' && *(p0+1) == '{'){
			p0 += 2;
			p1 = strchr(p0, '}');
			if(p1 == NULL)
				continue;
			strncpy(pname, p0, p1-p0);
			pname[p1-p0] = 0;
			p0 = p1+1;

			int ibeg = 0, iend = 0;
			if((p1 = strchr(pname, '[')) != NULL){
				// format:  VARNAME[123:234]
				char *p2;
				*p1 = 0; p1++;
				p2 = strchr(p1, ':');
				if(p2 == NULL) continue;
				*p2 = 0;
				ibeg = atoi(p1);
				p1 = p2+1;
				iend = atoi(p1);
			}
			UPOS pos = utFind(inparam, pname);
			if(pos == UPOS_END)
				continue;
			switch(inparam->ppe[pos]->type){
			case U_EMPTY:
			case U_ARRAY:
			case U_STRUCT:
				pvalue[0] = 0;
				break;
			case U_CHAR:
				pvalue[0] = inparam->ppe[pos]->value.v_char;
				pvalue[1] = 0;
				break;
			case U_INT:
				sprintf(pvalue, "%d", inparam->ppe[pos]->value.v_int);
				break;
			case U_LONG:
				sprintf(pvalue, "%ld", inparam->ppe[pos]->value.v_long);
				break;
			case U_DOUBLE:
				sprintf(pvalue, "%f", inparam->ppe[pos]->value.v_double);
				break;
			case U_STRING:
				strncpy(pvalue, inparam->ppe[pos]->value.p_char, sizeof(pvalue)-1);
				pvalue[sizeof(pvalue)-1] = 0;
				break;
			}
			if(ibeg == iend && iend == 0){
				sql1.append(pvalue);
			}else{
				int vlen = strlen(pvalue);
				char *v0, *v1;
				if(ibeg >= 0){
					if(ibeg >= vlen)
						continue;
					v0 = pvalue + ibeg;
				}else{
					v0 = pvalue + (vlen + ibeg);
					if(v0 < pvalue) continue;
				}
				if(iend > 0){
					if(iend > vlen)
						continue;
					v1 = pvalue + iend;
				}else if(iend == 0){
					v1 = pvalue + vlen; // s[?:]  or s[?:0] from ? to end
				}else{
					v1 = pvalue + (vlen + iend); // s[?:-n]
				}
				if(v1 < v0) continue;
				*v1 = 0;
				sql1.append(v0);
			}
		}else{
			sql1.append(p0, 1);
			p0 ++;
		}
	}
}

static utype* doQuerySqlFix(const char* sql, const utype *inparam, TCtrlInfo *errInfo)
{
	utype* array=uInit(0);
	uAutoPtr pp(array);

	otl_column_desc* cdesc;
	otl_var_desc* vdesc;
	int i=0,bindNum=0,colunmNum=0;
	L4C_TRACE("sql is:[%s]",sql);
	otl_nocommit_stream getResult;
	if(strstr(sql, "${") != NULL || strstr(sql, "#{") != NULL){
		string sql1;
		sqlreplace(sql, sql1, inparam);
		L4C_TRACE("fixed sql:[%s]", sql1.c_str());
		getResult.open(10, sql1.c_str(), GETDB(errInfo));
	}else{
		getResult.open(10, sql, GETDB(errInfo));
	}
	vdesc=getResult.describe_in_vars(bindNum);
	for (i=0;i<bindNum;i++){
		switch(vdesc[i].ftype){
			case 1:
				getResult << utGetStr(inparam,vdesc[i].name+1,(int*)NULL);
				break;
			case 2:
			case 3:
				getResult << utGetDouble(inparam,vdesc[i].name+1,(int*)NULL);
				break;
			case 4:
				getResult << utGetInt(inparam,vdesc[i].name+1,(int*)NULL);
				break;
			case 7:
				getResult << utGetLong(inparam,vdesc[i].name+1,(int*)NULL);
				break;
		}
	}
	cdesc=getResult.describe_select(colunmNum);

	i=0;
	while(!getResult.eof()){
		utype* row=uInit(0);
		utAddStruct(array,"ROW",row);
		for(int n=0;n<colunmNum;++n){
			int k;
			long l;
			double d;
			otl_datetime tm;

			switch(cdesc[n].otl_var_dbtype){

				case 19:
				case 8:
				case 18:
					char sDateTime[20];
					char* s;
					getResult >> tm;
					sprintf(sDateTime,"%04d%02d%02d%02d%02d%02d",tm.year,tm.month,tm.day,tm.hour,tm.minute,tm.second);
					utAddStr(row,cdesc[n].name,sDateTime);
					break;

				case 1:{
					       char * s = (char *)malloc(cdesc[n].dbsize);
					       if (s != NULL) {
						       memset(s, '\0', cdesc[n].dbsize);
						       getResult >> s;
						       utAddStr(row, cdesc[n].name, s);
						       free(s);
					       } else {
						       utAddStr(row, cdesc[n].name, "");
					       }
				       }
				       break;

				case 2:
				case 3:
				       if(cdesc[n].scale==0){
					       if(cdesc[n].prec>9){
						       getResult >> l;utAddLong(row,cdesc[n].name,l);
					       }
					       else{
						       getResult >> k;utAddInt(row,cdesc[n].name,k);
					       }
				       }else {
					       getResult >> d;utAddDouble(row,cdesc[n].name,d);
				       }
				       break;

				case 7:
				       getResult >> l;utAddLong(row,cdesc[n].name,l);
				       break;
				case 4:
				       getResult >> k;utAddInt(row,cdesc[n].name,k);
				       break;
			}

		}
		i++;
	}
	getResult.close();
	errInfo->iSqlRows=i;
	L4C_TRACE("--------sql excute output-----");
	LogUtype(pp);
	L4C_TRACE("-------=sql excute output=----");
	return pp.release();
}

map<int, TUtypeFuncPtr> mFuncArray;

utype* callOther(int modid, const utype* puParamIn, TCtrlInfo* errInfo)
{
	if(modid==-1) return NULL;
	TUtypeFuncPtr func;
	char sModId[20];
	char sComponentName[255+1];
	char sComponentPath[1024];
	sprintf(sModId, "%d", modid);
	otl_nocommit_stream qRuleParamMod(1, 
		"SELECT unit_name, unit_path \
		  FROM bs_busiunit_dict \
		 WHERE unit_id = :UNIT_ID<int> ", GETDB(errInfo));
	qRuleParamMod << modid;
	if (qRuleParamMod.eof()){
		throw(appException(399000001, "构件ID[%s]未配置", sModId, NULL));
	}
	qRuleParamMod>>sComponentName>>sComponentPath;
	if(strcmp(sComponentName, "SQL") == 0){
		//如果 unit_name 配置为 "SQL", 则unit_path 保存sql语句

		uAutoPtr uret( doQuerySqlFix(sComponentPath, puParamIn, errInfo) );
		UPOS pos = utFind(uret, "ROW");
		if(pos == UPOS_END)
			return NULL;
		return utClone(utGetStruct(uret, "ROW"));
	}

	map<int, TUtypeFuncPtr>::iterator i=mFuncArray.find(modid);
	if(i==mFuncArray.end()){//加载该函数
		string spath = getenv("HOME");
		spath.append("/");
		spath.append(sComponentPath);
		void* handle=dlopen(spath.c_str(), RTLD_NOW|RTLD_LOCAL);
		if(handle==NULL){
			char sErrMsg[4096];
			sprintf(sErrMsg, "动态库[%s]加载失败:%s", sComponentPath, dlerror());
			throw(appException(399000002, sErrMsg));
		}
		func=(TUtypeFuncPtr)dlsym(handle, sComponentName);
		if(func==NULL){
			char sErrMsg[4096];
			sprintf(sErrMsg, "动态库[%s]加载函数[%s]失败:%s", sComponentPath,sComponentName, dlerror());
			dlclose(handle);
			throw(appException(399000003, sErrMsg));
		}
		mFuncArray.insert(map<int, TUtypeFuncPtr>::value_type(modid, func));
	}else{
		func=i->second;
	}
	return func(puParamIn, errInfo);
}

utype* getAllParam(int iRuleId, const utype* puParamIn, TCtrlInfo* errInfo, map<int, pair<int, string> >& m)
{
	int flag=0;
	uAutoPtr uOut(uInit(1));
	uAutoPtr uInto(uInit(1));
	otl_nocommit_stream qRuleParamFunc(10, 
		"SELECT   nvl(unit_id, -1) utid\
		    FROM bs_ruleinparam_rel a\
		   WHERE a.rule_id = :RULE_ID<int> \
		GROUP BY unit_id order by utid", GETDB(errInfo));
	qRuleParamFunc<<iRuleId; //这个结构是为了能够一个 unit_id （动态库函数）可以输出多个参数
	while (!qRuleParamFunc.eof()){
		uAutoPtr uCallOutput;
		const utype* pCallOutPut;
		int iUnitId;
		char sSqlQryParam[4096];
		qRuleParamFunc>>iUnitId;
		otl_nocommit_stream qRuleParam;
		strcpy(sSqlQryParam, "SELECT  b.param_code, ':'|| b.param_name|| DECODE (value_type,\
			        2, '<int>',3, '<long>',4, '<double>',5, '<char['||value_length||']>','<char['||value_length||']>'),\
			       value_length, utype_path, b.param_name , value_type\
			  FROM bs_ruleinparam_rel a, bs_paramcode_dict b\
			 WHERE a.param_code = b.param_code AND a.rule_id = :RULE_ID<int> ");
		
		if(iUnitId!=-1){
			if(flag==0){
				uInto=utClone(uOut);
				utAddStruct(uInto, "IN_DATA", utClone(puParamIn));
				flag=1;
			}
			strcat(sSqlQryParam, "AND unit_id=:UNIT_ID<int>");
			L4C_TRACE("-------callOther begin------");
			utype* u=callOther(iUnitId, uInto, errInfo);
			LogUtype(u);
			L4C_TRACE("-------callOther end------");
			uCallOutput=u;
			pCallOutPut=u;
			if(u==NULL) throw(appException(399000004, "指定的外部功能未能加载或者调用失败"));
			qRuleParam.open(10,  sSqlQryParam, GETDB(errInfo));
			qRuleParam<<iRuleId<<iUnitId;
		}else{
			strcat(sSqlQryParam, "AND (unit_id=-1 or unit_id is NULL)");
			pCallOutPut=puParamIn;
			qRuleParam.open(10,  sSqlQryParam, GETDB(errInfo));
			qRuleParam<<iRuleId;
		}
		while (!qRuleParam.eof()){
			
			char sTypeTxt[1024];
			char sName[U_MAXNAMELEN];
			char sParamName[255+1];
			
			int iValueLength, iParamCode;
			int iValueType;
			char sPath[255+1];
			qRuleParam>>iParamCode>>sTypeTxt>>iValueLength>>sPath>>sParamName>>iValueType;
			
			switch(iValueType){
				case 2 : utAddInt(uOut, sParamName, utGetIntByPath(pCallOutPut, sPath));break;
				case 3 : utAddLong(uOut, sParamName, utGetLongByPath(pCallOutPut, sPath));break;
				case 4 : utAddDouble(uOut, sParamName, utGetDoubleByPath(pCallOutPut, sPath));break;
				case 5 : utAddStr(uOut, sParamName, utGetStrByPath(pCallOutPut, sPath));break;
				default: throw(appException(399000005, "未知的参数类型"));
			}
			L4C_TRACE("Add ParamCode[%d]", iParamCode);
			m.insert(map<int, pair<int, string> >::value_type(iParamCode, pair<int, string>(iValueType,sParamName)));
		}

	}
	L4C_TRACE("leave getAllParam");
	return uOut.release();
}


utype* My_getAllParam(int iRuleId,
		const utype* puParamIn,
		TCtrlInfo* errInfo,
		map<int, pair<int, string> >& m)
{
	int flag=0;
	uAutoPtr uOut(uInit(1));
	uAutoPtr uInto(uInit(1));
	const utype* pCallOutPut;
	int iUnitId, iLastUtId = -1;
	char sSqlQryParam[4096];

	otl_nocommit_stream qRuleParam;
	strcpy(sSqlQryParam, "SELECT  b.param_code, \
			':'|| b.param_name|| DECODE (value_type, 2, '<int>',3, '<long>',4, '<double>',5, '<char['||value_length||']>','<char['||value_length||']>'),\
			   value_length, \
			   utype_path, \
			   b.param_name ,\
			   value_type,\
			   nvl(unit_id, -1) utid\
		  FROM bs_ruleinparam_rel a, bs_paramcode_dict b\
		 WHERE a.param_code = b.param_code \
			 AND a.rule_id = :RULE_ID<int>  order by utid");
	qRuleParam.open(10,  sSqlQryParam, GETDB(errInfo));
	qRuleParam<<iRuleId;

	while (!qRuleParam.eof())
	{
		char sTypeTxt[1024];
		char sName[U_MAXNAMELEN];
		char sParamName[255+1];
		uAutoPtr uFromCall; //使用这个来自动释放 callOther 的返回值

		int iValueLength, iParamCode;
		int iValueType;
		char sPath[255+1];

		qRuleParam
			>>iParamCode
			>>sTypeTxt
			>>iValueLength
			>>sPath
			>>sParamName
			>>iValueType
			>>iUnitId;

		if(iUnitId!=-1){
			if(flag==0){
				uInto=utClone(uOut);
				utAddStruct(uInto, "IN_DATA", utClone(puParamIn));
				flag=1;
			}
			if(iLastUtId != iUnitId){ //相同 unitid 只调用一次
				L4C_TRACE("-------callOther begin------");
				utype* u = callOther(iUnitId, uInto, errInfo);
				LogUtype(u);
				L4C_TRACE("-------callOther end------");
				if(u == NULL)
					throw(appException(399000004, "指定的外部功能未能加载或者调用失败"));
				pCallOutPut = u;
				uFromCall = u; //用于自动释放， 避免内存泄漏
				iLastUtId = iUnitId;
			}
		}else{
			pCallOutPut = puParamIn;
		}
		switch(iValueType){
			case 2 : utAddInt(uOut, sParamName, utGetIntByPath(pCallOutPut, sPath));break;
			case 3 : utAddLong(uOut, sParamName, utGetLongByPath(pCallOutPut, sPath));break;
			case 4 : utAddDouble(uOut, sParamName, utGetDoubleByPath(pCallOutPut, sPath));break;
			case 5 : utAddStr(uOut, sParamName, utGetStrByPath(pCallOutPut, sPath));break;
			default: throw(appException(399000005, "未知的参数类型"));
		}
		L4C_TRACE("Add ParamCode[%d]", iParamCode);
		m.insert(map<int, pair<int, string> >::value_type(
				iParamCode,
				pair<int, string>(iValueType, sParamName)));
	}

	L4C_TRACE("leave getAllParam");
	return uOut.release();
}



size_t fGetRealValue(const utype* pu, TCtrlInfo* errInfo, const char* sParamName, char* buf, size_t len)
{
	UPOS p=utFind(pu, sParamName);
	if(p==UPOS_END){
                buf[0]=0;
                return 0;
        }
	switch(pu->ppe[p]->type){
		case U_INT:sprintf(buf, "%d", utGetInt(pu, sParamName, p));break;
		case U_LONG:sprintf(buf, "%ld", utGetLong(pu, sParamName, p));break;
		case U_DOUBLE:sprintf(buf, "%0.2f", utGetDouble(pu, sParamName, p));break;
		case U_STRING:snprintf(buf,len, "%s", utGetStr(pu, sParamName, p));break;
		default:strncpy(buf, sParamName, len-1);buf[len-1]=0;break;
	}
	return strlen(buf);
}

void rtmsgReplace(char* s, const utype* pu, TCtrlInfo* errInfo)
{
	char tmp[255+1];
	char tar[1024];
	char* cur_beg=s, *cur_end;
	otl_nocommit_stream curParamReplace(1,
	"select replace(:SRC<char[255+1]>, '{$'||:VAR<char[256]>||'}', :TAR<char[1024]>) from dual", GETDB(errInfo));

	while(cur_beg=strchr(cur_beg,'{')){
		cur_end=strchr(cur_beg, '}');
		if(cur_end==NULL) break;
		if(cur_beg[1]=='$'&&cur_end-cur_beg>2){
			memcpy(tmp, cur_beg+2, cur_end-cur_beg-2);
			tmp[cur_end-cur_beg-2]=0;
			fGetRealValue(pu,errInfo, tmp, tar, 1024);
			curParamReplace<<s<<tmp<<tar;
			curParamReplace>>s;
		}
		++cur_beg;
	}
}



int op_in(const char *in, char *set)
{
	const char *p;

	p=strtok(set, " ");
	while(p){
		if(strcmp(in,p)==0)
			return 1;
		p=strtok(NULL, " ");
	}
	return 0;
}

bool logicJudge(int iOperateId, char* value1, char* value2, int iValueType, const char* sParamPath, const utype* puParamIn, TCtrlInfo *errInfo)
{
	L4C_TRACE("iOperateId=%d, iValueType=%d", iOperateId, iValueType);
	switch(iOperateId){
		case 0:	/*--- == ---*/
			switch(iValueType){
				case 2: /*--- int ---*/
					if (utGetIntByPath(puParamIn, sParamPath) != atoi(value1))
						return false;
					break;
				case 3: /*--- long ---*/
					if (utGetLongByPath(puParamIn, sParamPath) != atol(value1))
						return false;
					break;
				case 4: /*--- double ---*/
					if (utGetDoubleByPath(puParamIn, sParamPath) != atof(value1))
						return false;
					break;
				case 5: /*--- string ---*/
					if(strcmp(utGetStrByPath(puParamIn, sParamPath), value1)!=0)
						return false;
					break;
				default:
					return false;
			}
			break;
		case 1: /*--- != ---*/
			switch(iValueType){
				case 2: /*--- int ---*/
					if (utGetIntByPath(puParamIn, sParamPath) == atoi(value1))
						return false;
					break;
				case 3: /*--- long ---*/
					if (utGetLongByPath(puParamIn, sParamPath) == atol(value1))
						return false;
					break;
				case 4: /*--- double ---*/
					if (utGetDoubleByPath(puParamIn, sParamPath) == atof(value1))
						return false;
					break;
				case 5: /*--- string ---*/
					if(strcmp(utGetStrByPath(puParamIn, sParamPath), value1)==0)
						return false;
					break;
				default:
					return false;
			}
			break;
		case 2: /*--- > ---*/
			switch(iValueType){
				case 2: /*--- int ---*/
					if (utGetIntByPath(puParamIn, sParamPath) <= atoi(value1))
						return false;
					break;
				case 3: /*--- long ---*/
					if (utGetLongByPath(puParamIn, sParamPath) <= atol(value1))
						return false;
					break;
				case 4: /*--- double ---*/
					if (utGetDoubleByPath(puParamIn, sParamPath) <= atof(value1))
						return false;
					break;
				case 5: /*--- string ---*/
					if(strcmp(utGetStrByPath(puParamIn, sParamPath), value1)<=0)
						return false;
					break;
				default:
					return false;
			}
			break;
		case 3: /*--- < ---*/
			switch(iValueType){
				case 2: /*--- int ---*/
					if (utGetIntByPath(puParamIn, sParamPath) >= atoi(value1))
						return false;
					break;
				case 3: /*--- long ---*/
					if (utGetLongByPath(puParamIn, sParamPath) >= atol(value1))
						return false;
					break;
				case 4: /*--- double ---*/
					if (utGetDoubleByPath(puParamIn, sParamPath) >= atof(value1))
						return false;
					break;
				case 5: /*--- string ---*/
					if(strcmp(utGetStrByPath(puParamIn, sParamPath), value1)>=0)
						return false;
					break;
				default:
					return false;
			}
			break;
		case 4: /*--- >= ---*/
			switch(iValueType){
				case 2: /*--- int ---*/
					if (utGetIntByPath(puParamIn, sParamPath) < atoi(value1))
						return false;
					break;
				case 3: /*--- long ---*/
					if (utGetLongByPath(puParamIn, sParamPath) < atol(value1))
						return false;
					break;
				case 4: /*--- double ---*/
					if (utGetDoubleByPath(puParamIn, sParamPath) < atof(value1))
						return false;
					break;
				case 5: /*--- string ---*/
					if(strcmp(utGetStrByPath(puParamIn, sParamPath), value1)<0)
						return false;
					break;
				default:
					return false;
			}
			break;
		case 5: /*--- <= ---*/
			switch(iValueType){
				case 2: /*--- int ---*/
					if (utGetIntByPath(puParamIn, sParamPath) > atoi(value1))
						return false;
					break;
				case 3: /*--- long ---*/
					if (utGetLongByPath(puParamIn, sParamPath) > atol(value1))
						return false;
					break;
				case 4: /*--- double ---*/
					if (utGetDoubleByPath(puParamIn, sParamPath) > atof(value1))
						return false;
					break;
				case 5: /*--- string ---*/
					if(strcmp(utGetStrByPath(puParamIn, sParamPath), value1)>0)
						return false;
					break;
				default:
					return false;
			}
			break;
		case 6: /*--- between ---*/
			switch(iValueType){
				case 2: /*--- int ---*/
					if(utGetIntByPath(puParamIn, sParamPath) < atoi(value1) || utGetIntByPath(puParamIn, sParamPath) > atoi(value2))
						return false;
					break;
				case 3: /*--- long ---*/
					if(utGetLongByPath(puParamIn, sParamPath) < atol(value1) || utGetDoubleByPath(puParamIn, sParamPath) > atol(value2))
						return false;
					break;
				case 4: /*--- double ---*/
					if(utGetDoubleByPath(puParamIn, sParamPath) < atof(value1) || utGetDoubleByPath(puParamIn, sParamPath) > atof(value2))
						return false;
					break;
				case 5: /*--- string ---*/
					if(strcmp(utGetStrByPath(puParamIn, sParamPath), value1)<0 || strcmp(utGetStrByPath(puParamIn, sParamPath), value2)>0)
						return false;
					break;
				default:
					return false;
			}
			break;
		case 7: /*--- like ---*/
			switch(iValueType){
				case 5: /*--- string ---*/
					if(strstr(value1, utGetStrByPath(puParamIn, sParamPath)) != value1)
						return false;
					break;
				default:
					return false;
			}
			break;
		case 8:	/*--- in ---*/
			switch(iValueType){
				case 5: /*--- string ---*/
					if(op_in(utGetStrByPath(puParamIn, sParamPath), value1)!=1)
						return false;
					break;
				default:
					return false;
			}
			break;
		case 9:	/*--- not in ---*/
			switch(iValueType){
				case 5: /*--- char ---*/
					if(op_in(utGetStrByPath(puParamIn, sParamPath), value1)==1)
						return false;
					break;
				default:
					return false;
			}
			break;
		case 10:	/*--- sql ---*/
			{
			uAutoPtr u(doQuerySqlFix(value1, puParamIn, errInfo));
			if(errInfo->iSqlRows==0)
				return false;
			
			break;
		}
		default:
			return false;
	}

	return true;
}

void getRtMsg(int iRuleGroup, long& lReturnCode, char* sReturnMsg,char* sUrMsg, int &iUnitId, TCtrlInfo* errInfo)
{
	otl_nocommit_stream qRuleRtMsg(1, 
		"SELECT a.return_code, b.return_msg, nvl(unit_id, -1), CUST_CLASS_TIPS\
		  FROM bs_groupretmsg_info a, bs_returnmsg_dict b\
		 WHERE a.return_code = b.return_code  AND group_id = :RULE_GROUP<int>", 
		  GETDB(errInfo));
	qRuleRtMsg<<iRuleGroup;
	if (qRuleRtMsg.eof()) throw(appException(399000008, "指定的规则无对应的错误代码与错误信息"));
	qRuleRtMsg>>lReturnCode>>sReturnMsg>>iUnitId>>sUrMsg;	
}

utype* doBusiRule(int iRuleId, const utype* puParamIn, TCtrlInfo* errInfo)
{
	string sPromptMsg;
	map<int, pair<int, string> > mParamTxt;
	memset(errInfo, 0, sizeof(TCtrlInfo));
	
	otl_nocommit_stream qRuleID(1, "SELECT   a.rule_id\
									    FROM bs_busirule_dict a \
									   WHERE  a.rule_id =:RULE_ID<int>", GETDB(errInfo));
									   
	qRuleID<<iRuleId;
	if(qRuleID.eof()) throw(appException(399000006, "RULE_ID不存在"));
	
	uAutoPtr uRuleInput(My_getAllParam(iRuleId, puParamIn, errInfo, mParamTxt));
	int iRuleGroup, iGroupType;
	
	otl_nocommit_stream qRule(10,
			"SELECT  b.group_id, c.group_type\
		FROM  bs_rulefactorgroup_rel b, bs_factorgroup_dict c \
	   WHERE  b.group_id = c.group_id\
			 AND b.rule_id =:RULE_ID<int>\
	         ORDER BY b.group_order",
	         GETDB(errInfo));
	qRule<<iRuleId;
	while (!qRule.eof()){
		qRule>>iRuleGroup>>iGroupType;
		bool bCurGroup=true;
		otl_nocommit_stream qRuleSerial(10, 
		"SELECT   operator_id, value1, value2, NVL(param_code, -1)\
		    FROM bs_rulefactor_dict a,\
		         bs_factorgroup_dict c,\
		         bs_groupfactor_rel d\
		   WHERE c.group_id = :RULE_GROUP<int>\
		     AND d.group_id = c.group_id\
		     AND a.factor_id = d.factor_id\
		ORDER BY d.factor_order", GETDB(errInfo));
		qRuleSerial<<iRuleGroup;
		while(!qRuleSerial.eof()){
			int iOperateId, iParamCode;
			char value1[1024+1];
			char value2[1024+1];
			qRuleSerial>>iOperateId>>value1>>value2>>iParamCode;
			map<int, pair<int, string> >::iterator fi=mParamTxt.find(iParamCode);
			if(fi==mParamTxt.end()&&iOperateId!=10){
				char sParamCode[10];
				sprintf(sParamCode, "%d", iParamCode);
				throw(appException(399000007, "参数代码[%s]未配置", sParamCode, NULL));
			}
			int iValueType = -1;
			char *sParamName = NULL;
			if(fi != mParamTxt.end()){
				iValueType = fi->second.first;
				sParamName = fi->second.second.c_str();
			}
			if(!logicJudge(iOperateId, value1, value2, iValueType, sParamName, uRuleInput, errInfo)){
				bCurGroup=false;
				break;
			}
		}
		if(bCurGroup){
			long lReturnCode;
			char sReturnMsg[255+1];
			char sUsrMsg[255+1];
			int iUnitId;
			getRtMsg(iRuleGroup, lReturnCode, sReturnMsg, sUsrMsg, iUnitId, errInfo);
			rtmsgReplace(sReturnMsg, uRuleInput, errInfo);
			if(iGroupType){
				if(!sPromptMsg.empty()) sPromptMsg+=" ";
				sPromptMsg+=sReturnMsg;
			}else{
				uAutoPtr uAllOut(uInit(3));
				
				if(sUsrMsg[0]==0) strcpy(sUsrMsg,sReturnMsg);
				else rtmsgReplace(sUsrMsg, uRuleInput, errInfo);
				if(iUnitId!=-1){
					utAddStruct(uRuleInput, "IN_DATA", utClone(puParamIn));
					utAddStruct(uAllOut, "OUT_DATA",  callOther(iUnitId, uRuleInput, errInfo));
				}
				utAddStr(uAllOut, "USER_MSG", sUsrMsg);
				utAddLong(uAllOut, "RETURN_CODE", lReturnCode);
				utAddStr(uAllOut, "RETURN_MSG", sReturnMsg);
				utAddStr(uAllOut, "DETAIL_MSG", "");
				return uAllOut.release();
			}
		}
	}
	L4C_TRACE("sPromptMsg:%s", sPromptMsg.c_str());
	snprintf(errInfo->infoMsg, 2048, "%s", sPromptMsg.c_str());
	return NULL;
}

