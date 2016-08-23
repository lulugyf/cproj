/*
 * utype_json.cpp
 *
 *  Created on: 2012-7-3
 *      Author: guanyf
utype  ==>    json
-------------------------
char           long
int            long
double         double
string         string

json   ==>     utype
--------------------------
boolean        int
long           long
double         double
string         string

utype 中同一级别上如果有相同名称的数据， 会被放入json的array中

========== SAMPLE:
==== source:
<?xml version="1.0" encoding="GBK" standalone="no" ?>
<ROOT>
 <RETURN_CODE type="long">0</RETURN_CODE>
 <RETURN_MSG type="string">ok!</RETURN_MSG>
 <USER_MSG type="string">ok!</USER_MSG>
 <DETAIL_MSG type="string">OK!</DETAIL_MSG>
 <PROMPT_MSG type="string"></PROMPT_MSG>
 <OUT_DATA>
  <ROW>
   <MID type="long">2</MID><MNAME type="string">m2</MNAME><SEX type="string">0</SEX><MNOTE type="string">test m2</MNOTE>
  </ROW>
  <ROW>
   <MID type="long">3</MID><MNAME type="string">m3</MNAME><SEX type="string">0</SEX><MNOTE type="string">test m3</MNOTE>
  </ROW>
  <ROW>
   <MID type="long">411111111</MID><MNAME type="string">m4</MNAME><SEX type="string">0</SEX><MNOTE type="string">test m4</MNOTE>
  </ROW>
 </OUT_DATA>
 <Tint type="int">789</Tint>
 <Tchar type="char">a</Tchar>
 <Tdouble type="double">12312.232322</Tdouble>
</ROOT>
 */

#include <stdio.h>
#include <string.h>

#include "utype.h"

extern "C" {
  #include "jsonc/json.h"
}

static int splitc(char *string, char *fields[], int  nfields, char sep )
{
    char *p, *p1;
    int i;

    p = string;
    fields[0] = p;
    i = 1;
    while( (p1=strchr(p,sep))!= NULL && i<nfields){
        p1[0] = 0; p1++;
        fields[i] = p1;
        p = p1; i++;
    }
    return i;
}


void __json2utype(json_object *pj, utype *pu)
{
	json_object_object_foreach(pj, key, val){
		switch(json_object_get_type(val))
		{
		case json_type_null:
			utAddEmpty(pu, key);
			break;
		case json_type_boolean:
			utAddInt(pu, key, (int)json_object_get_boolean(val));
			break;
		case json_type_double:
			utAddDouble(pu, key, json_object_get_double(val));
			break;
		case json_type_int:
			utAddLong(pu, key,  (long)json_object_get_int64(val));
			break;
		case json_type_string:
			utAddStr(pu, key, json_object_get_string(val));
			break;
		case json_type_object:
		{
			utype *pu1 = uInit(1);
			__json2utype(val, pu1);
			utAddStruct(pu, key, pu1);
			break;
		}
		case json_type_array:
		{
			int arrlen = json_object_array_length(val);
			for(int i=0; i<arrlen; i++)
			{
				json_object *pj1 = json_object_array_get_idx(val, i);

				switch(json_object_get_type(pj1))
				{
				case json_type_object:
				case json_type_array:
					{
					utype *pu1 = uInit(1);
					__json2utype(pj1, pu1);
					utAddStruct(pu, key, pu1);
					break;
					}
				case json_type_null:
					utAddEmpty(pu, key);
					break;
				case json_type_boolean:
					utAddInt(pu, key, (int)json_object_get_boolean(pj1));
					break;
				case json_type_double:
					utAddDouble(pu, key, json_object_get_double(pj1));
					break;
				case json_type_int:
					utAddLong(pu, key,  (long)json_object_get_int64(pj1));
					break;
				case json_type_string:
					utAddStr(pu, key, json_object_get_string(pj1));
					break;
				}
			}
			break;
		}
		}
	}
}

utype * json2utype(const char *str)
{
	json_object *jo = NULL;
	struct lh_entry *entry = NULL;
	json_type tp;

	utype *pu = uInit(1);
	enum json_tokener_error jerr;
	jo = json_tokener_parse_verbose(str, &jerr);
	if(is_error(jo)){
		printf("==JSONERR: json_tokener_parse failed， errcode: %d, err: %s\n",
				jerr, json_tokener_error_desc(jerr ));
		return pu;
	}
	tp = json_object_get_type(jo);
	if(tp != json_type_object){
		printf("==JSONERR: not start with a Object\n");
		return pu;
	}

	json_object *jroot = NULL;
	jroot = json_object_object_get(jo,"ROOT");
	if(jroot != NULL && json_object_get_type(jroot) != json_type_object)
	{
		printf("==JSONERR: not start with ROOT\n");
		return pu;
	}
	if(jroot == NULL){ // compatible with previous none-header input
		jroot = jo;
	}

	__json2utype(jroot, pu);

	json_object_put(jo);

	return pu;
}





void __utype2json(utype *pu, json_object *pj)
{
	int i;
	const char *key;
	json_object *pj1, *pj2;

	for(i=0;i<pu->cnt;i++)
	{
		key = utGetName(pu, i);
		switch(pu->ppe[i]->type)
		{
			case U_EMPTY:
				pj1 = json_object_new_object();
				break;
			case U_CHAR:{
				char tmpv[2];
				tmpv[1] = 0;
				tmpv[0] = pu->ppe[i]->value.v_char;
				pj1 = json_object_new_string(tmpv);
				//pj1 = json_object_new_int64(pu->ppe[i]->value.v_char);
				break;
			}
			case U_INT:
				pj1 = json_object_new_int64(pu->ppe[i]->value.v_int);
				break;
			case U_LONG:
				pj1 = json_object_new_int64(pu->ppe[i]->value.v_long);
				break;
			case U_DOUBLE:
				pj1 =  json_object_new_double(pu->ppe[i]->value.v_double);
				break;
			case U_STRING:
				pj1 = json_object_new_string(pu->ppe[i]->value.p_char);
				break;
			/*case U_ARRAY:
				STRCAT("[");
				__utype2json(pu->ppe[i]->value.p_utype, buf, pbuf, totallen);
				STRCAT("]");
				break;*/
			case U_STRUCT:
			{
				pj1 = json_object_new_object();
				__utype2json(pu->ppe[i]->value.p_utype, pj1);
				break;
			}
			default:
				printf("key[%s] not recognized\n", key);
				pj1 = NULL;
				break;
		}
		if(pj1 != NULL){
			//printf("i %d -->  %s [%d] [%s]\n", i, key, pu->ppe[i]->type, json_object_to_json_string(pj1));
			pj2 = json_object_object_get(pj, key);
			if(pj2 != NULL){
				// need to process as array
				if(json_object_get_type(pj2) == json_type_array){
					json_object_array_add(pj2, pj1);
					//printf("add new arr element for key[%s] [%s]\n", key, json_object_to_json_string(pj1));
				}else{
					json_object *pj3 = json_object_new_array();
					json_object_get(pj2); // increase the reference count
					json_object_array_add(pj3, pj2);
					json_object_array_add(pj3, pj1);
					json_object_object_add(pj, key, pj3);
					//printf("create new arr for key[%s]\n", key);
				}
			}else{
				json_object_object_add(pj, key, pj1);
			}
		}
	}
}

static void jsonChkArr(json_object *jo, int arrSize, char *arrPath[]);

char * utype2json(const utype *pu, const char *psArrPath)
{
	json_object *pj;
	json_object *proot;
	char *sret;

	pj = json_object_new_object();
	proot = json_object_new_object();
	json_object_object_add(proot, "ROOT", pj);

	u_errno=0;
	__utype2json((utype *)pu, pj);

	if(psArrPath != NULL){
		const int MAXPATH = 20;
		char *path, *arrPath[MAXPATH];
		char *paths = strdup(psArrPath);
		int arrSize = splitc(paths, arrPath, MAXPATH, ' ');
		jsonChkArr(proot, arrSize, arrPath);
		free(paths);
	}

	sret = strdup(json_object_to_json_string(proot));
	json_object_put(proot);
	return sret;
}

char * utype2json(const utype *pu)
{
	return utype2json(pu, NULL);
}









static void jsonFixArr(json_object *jo_parent, const char *keyname,
		json_object *jo, int pathSize, char *path[])
{
	printf("keyname[%s] pathsize=%d path[0]=[%s] parent is NULL[%d] jo is NULL[%d]\n",
			keyname==NULL?"NULL":keyname, pathSize, pathSize>0?path[0]:"NULL",
					jo_parent == NULL, jo==NULL);
	if(pathSize == 0 && jo_parent != NULL && jo != NULL){
		if(!json_object_is_type(jo, json_type_array)){
			json_object *ja = json_object_new_array();
			char *vkey = strdup(keyname);
			json_object_array_add(ja, json_object_get(jo));
			json_object_object_add(jo_parent, vkey, ja);
			free(vkey);
		}
		return;
	}
	if(json_object_is_type(jo, json_type_array)){
		int al = json_object_array_length(jo);
		for(int j=0; j<al; j++){
			json_object *jo1 = json_object_array_get_idx(jo, j);
			jsonFixArr(jo_parent, keyname, jo1, pathSize, path);
		}
	}else if(json_object_is_type(jo, json_type_object)){
		keyname = path[0];
		if(strchr(keyname, '*') == NULL){
			json_object *jo1 = json_object_object_get(jo, keyname);
			if(jo1 != NULL)
				jsonFixArr(jo, keyname, jo1, pathSize-1, path+1);
		}else{
			int len = strlen(keyname)-1; //只支持*在最后
			printf("foreach [%s] len=%d\n", keyname, len);
			json_object_object_foreach(jo, key, val){
				if(strncmp(key, keyname, len) == 0){
					printf("into [%s]\n", key);
					jsonFixArr(jo, key, val, pathSize-1, path+1);
				}else{
					printf("not into [%s]\n", key);
				}
			}
		}
	}
}

static void jsonChkArr(json_object *jo, int arrSize, char *arrPath[])
{
	int i, n;
	const int MAXPATH = 20;
	char *path, *patharr[MAXPATH];
	for(i=0; i<arrSize; i++){
		path = strdup(arrPath[i]);
		n = splitc(path, patharr, MAXPATH, '/');
		if(n > 0){
			jsonFixArr(NULL, NULL, jo, n, patharr);
		}
		free(path);
	}
}

