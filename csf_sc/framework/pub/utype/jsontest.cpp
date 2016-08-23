/*
 * jsontest.cpp
 *
 *  Created on: 2013-1-15
 *      Author: guanyf
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern "C" {
  #include "jsonc/json.h"
}


int main1(int argc, char *argv[])
{
	json_object *jo = NULL;

	jo = json_tokener_parse(argv[1]);

	printf("is_error(%d)  isnull %d\n", is_error(jo), jo==NULL);
	if(jo == NULL)
		return 1;

	printf("json_type:%d is_int:%d\n", json_object_get_type(jo),
			json_object_get_type(jo) == json_type_int);

	if(json_object_get_type(jo) == json_type_object){
		char *key; struct json_object *val;
		struct lh_table *tbl = json_object_get_object(jo);
		if(tbl == NULL){
			printf("table is NULL\n");
		}else{
			struct lh_entry *entry = tbl->head;
			if(entry) {
				key = (char*)entry->k;
				val = (struct json_object*)entry->v;
				printf("key[%s] val_type:%d\n", key,
						json_object_get_type(val));
			}else{
				printf("entry is NULL\n");
			}
		}
	}

	if(jo != NULL)
		json_object_put(jo);

	return 0;

}

int splitc(char *string, char *fields[], int  nfields, char sep )
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


int main(int argc, char *argv[])
{
	json_object *jo = NULL;

	jo = json_tokener_parse(argv[1]);
	printf("parse succ!!!!!!!\n");

	jsonChkArr(jo, argc-2, &argv[2]);

	printf("%s\n", json_object_to_json_string_ext(jo, JSON_C_TO_STRING_PRETTY));

	if(jo != NULL)
		json_object_put(jo);

	return 0;
}


/*
 * g++ -o t t.cpp -L/tp/esb/csf/run/solib -lutype -I.

./jsontest '{
        "ROOT":{
                "DETAIL_MSG":"OK!",
                "OUT_DATA":{
                        "OUTMSG":{
                                "PAY_INFO":{
                                        "BACK_FLAG":"0",
                                        "CONTRACT_NO":24104060019021,
                                        "LOGIN_NO":"nfGH01",
                                        "OP_CODE":"8000",
                                        "OP_TIME":"20130201 09:21:08",
                                        "PAY_MONEY":2000,
                                        "PAY_NAME":"现金",
                                        "PAY_NOTE":"用户[18284354915] 快速缴费[20]",
                                        "PAY_PATH":"01",
                                        "PAY_SN":109607842516,
                                        "PAY_TYPE":"0",
                                        "TOWN_NAME":"未知"
                                }
                        },
                        "PAY_FEE":2000,
                        "RECORD_COUNT":1
                },
                "PROMPT_MSG":"",
                "RETURN_CODE":0,
                "RETURN_MSG":"ok!",
                "USER_MSG":"ok!"
        }
}' 'ROOT/OUT_DATA/OUTMSG/PAY_INFO'



./jsontest '{
        "ROOT":{
                "DETAIL_MSG":"OK!",
                "OUT_DATA":{
                        "ACCOUNT_TYPE":"1",
                        "CONTRACT_NAME":"威远县奉龙煤",
                        "CONTRACT_NO":22004023646800,
                        "CONTRACT_NUM":0,
                        "CON_OWE":10003,
                        "CURRENT_POINT":777,
                        "CUST_TYPE_NAME":"普通",
                        "GROUP_NAME":"内江",
                        "LIMIT_OWE":0,
                        "ODD_FEE":0,
                        "OUTMSG":
                                {
                                        "OWEFEEINFO":
                                                {
                                                        "DELAY_FEE":260,
                                                        "FAVOUR_FEE":0,
                                                        "ID_NO":22904014957989,
                                                        "OWE_FEE":500,
                                                        "PAYED_LATER":0,
                                                        "PAYED_PREPAY":0,
                                                        "PHONE_NO":"18728143267",
                                                        "RUN_NAME":"正常",
                                                        "SHOULD_PAY":500,
                                                        "YEAR_MONTH":201301
                                                }

                                },
                        "PAY_CODE_NAME":"预付费",
                        "PREPAY_FEE":0,
                        "PRODUCT_NAME":"神州行家园卡201103",
                        "REMONTH_FEE":0,
                        "RUN_NAME":"正常",
                        "SM_NAME":"数字普通",
                        "TOP_CON_FLAG":0,
                        "TYPE_NAME":"集团后付费账户",
                        "USER_NAME":"×××奉龙煤",
                        "USER_NUM":9
                },
                "PROMPT_MSG":"",
                "RETURN_CODE":0,
                "RETURN_MSG":"ok!",
                "USER_MSG":"ok!"
        }
}' 'ROOT/OUT_DATA/OUTMSG' 'ROOT/OUT_DATA/OUTMSG/OWEFEEINFO'
 */
