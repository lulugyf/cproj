#include <stdio.h>
#include <unistd.h>

#include <utype.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#include <stdio.h>
#include <string.h>

#include "utype.h"

extern "C" {
#include "jsonc/json.h"
}
void LogUtype(const utype *pu);
void wf(char *file_name,char *buf, size_t len)
{
    int fd;
    fd = open( file_name,
        O_WRONLY | O_CREAT | O_TRUNC,
        S_IRUSR | S_IWUSR );
    write(fd,buf,len);
    close(fd);
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
	jo = json_tokener_parse(str);
	if(jo == NULL || is_error(jo)){
		printf("==JSONERR: json_tokener_parse failed\n");
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
        case U_CHAR:
            pj1 = json_object_new_int64(pu->ppe[i]->value.v_char);
            break;
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

char * utype2json(const utype *pu)
{
    json_object *pj;
    json_object *proot;
    char *sret;

    pj = json_object_new_object();
    /* added by liupengc */
    proot = json_object_new_object();
    json_object_object_add(proot,"ROOT",pj);
    u_errno=0;
    __utype2json((utype *)pu, pj);

    //sret = strdup(json_object_to_json_string(pj));
    sret = strdup(json_object_to_json_string(proot));
    json_object_put(proot);
    return sret;
}




char *readFile(const char *fname)
{
    struct stat st;
    char *buf;
    if(stat(fname, &st) != 0)
    return NULL;
    buf = (char *)malloc(st.st_size+1);
    buf[st.st_size] = 0;
    FILE *fp = fopen(fname, "r");
    fread(buf, 1, st.st_size, fp);
    fclose(fp);
    return buf;
}


#include <utype.h>
#include <stdio.h>

void test12()
{// utype to json
    char *uxml = readFile("a.txt");
    if(uxml == NULL){
        printf("file not found\n");
        return;
    }
    uAutoPtr  inParam(uXml2Utype((const char *)uxml));
    //LogUtype(inParam);
    free(uxml);
    char *json = utype2json(inParam);
    printf(">>>>>\n%s\n<<<<<<\n", json);
    free(json);
}

void test13()
{// json to utype
    char *jsonstr = readFile("b.txt");
    
    char *xmlstr = NULL;
    uAutoPtr uptr1(json2utype(jsonstr));
    free(jsonstr);
    xmlstr = uUType2Xml(uptr1,"ROOT");
    //wf("./c.txt", xmlstr, strlen(xmlstr));
    printf("%s\n", xmlstr);
    free(xmlstr);
    //LogUtype(uptr1);
}


int main(int argc, char** argv)
{
    
    //test12();
    test13();
    return 0;
}




static void LogLevel(int* ay, int iLevel,char* s)
{
	s[0]=0;
	for(int i=0;i<iLevel;++i){
		if(ay[i]) strcat(s,"    ");
		else  strcat(s,"鈹� ");
	}
	if(ay[iLevel]) strcat(s, "鈹斺攢");
	else strcat(s, "鈹溾攢");
}
static void LogUtypeDG(char * lp ,const utype *pu, int iLevel, int* ay)
{
	int i;
	char sl[128];
	u_errno=0;
	if(pu==NULL) return;
	
	for(i=0;i<pu->cnt;i++)
	{
		if(i==pu->cnt-1) ay[iLevel]=1;
		else ay[iLevel]=0;
		LogLevel(ay, iLevel,sl);
		switch(pu->ppe[i]->type)
		{
			case U_EMPTY:
			{
				printf( "%s%d.%s(empty)",sl, i,utGetName(pu,i));
				break;
			}
			case U_CHAR:
			{
				printf( "%s%d.%s(char):%c",sl,i,utGetName(pu,i), pu->ppe[i]->value.v_char);
				break;
			}
			case U_INT:
			{
				printf( "%s%d.%s(int):%d",sl,i,utGetName(pu,i), pu->ppe[i]->value.v_int);
				break;
			}
			case U_LONG:
			{
				printf( "%s%d.%s(long):%ld",sl,i,utGetName(pu,i), pu->ppe[i]->value.v_long);
				break;
			}
			case U_DOUBLE:
			{
				printf( "%s%d.%s(double):%lf",sl,i,utGetName(pu,i), pu->ppe[i]->value.v_double);
				break;
			}
			case U_STRING:
			{
				printf( "%s%d.%s(string):%s",sl,i,utGetName(pu,i), pu->ppe[i]->value.p_char);
				break;
			}
			
			case U_ARRAY:
			case U_STRUCT:
			{
				printf( "%s%d.%s(utype)",sl,i,utGetName(pu,i));
				LogUtypeDG(lp, pu->ppe[i]->value.p_utype,iLevel+1,ay);
				break;
			}
			default:
			{
				break;
			}
		}
	}
}

void LogUtype(const utype *pu)
{
	int ay[1024];
	memset(ay,0,sizeof(ay));
	LogUtypeDG(NULL, pu, 0, ay);
}
