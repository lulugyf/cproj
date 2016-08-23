#include "framework.h"


#define L4CDEF tmp_set(lp.ll, __LINE__, __FUNCTION__, __FILE__), l4c_logdef
static void LogLevel(int* ay, int iLevel,char* s)
{
	s[0]=0;
	for(int i=0;i<iLevel;++i){
		if(ay[i]) strcat(s,"    ");
		else  strcat(s,"©¦  ");
	}
	if(ay[iLevel]) strcat(s, "©¸©¤");
	else strcat(s, "©À©¤");
}

static void LogUtypeDG(t_logparam lp ,const utype *pu, int iLevel, int* ay)
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
				L4CDEF( "%s%d.%s(empty)",sl, i,utGetName(pu,i));
				break;
			}
			case U_CHAR:
			{
				L4CDEF( "%s%d.%s(char):%c",sl,i,utGetName(pu,i), pu->ppe[i]->value.v_char);
				break;
			}
			case U_INT:
			{
				L4CDEF( "%s%d.%s(int):%d",sl,i,utGetName(pu,i), pu->ppe[i]->value.v_int);
				break;
			}
			case U_LONG:
			{
				L4CDEF( "%s%d.%s(long):%ld",sl,i,utGetName(pu,i), pu->ppe[i]->value.v_long);
				break;
			}
			case U_DOUBLE:
			{
				L4CDEF( "%s%d.%s(double):%lf",sl,i,utGetName(pu,i), pu->ppe[i]->value.v_double);
				break;
			}
			case U_STRING:
			{
				L4CDEF( "%s%d.%s(string):%s",sl,i,utGetName(pu,i), pu->ppe[i]->value.p_char);
				break;
			}
			case U_ARRAY:
			case U_STRUCT:
			{
				L4CDEF( "%s%d.%s(utype)",sl,i,utGetName(pu,i));
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

void LogUtype(const utype *pu,int a)
{
	int ay[1024];
	memset(ay,0,sizeof(ay));
	LogUtypeDG(LVTRACE, pu, 0, ay);
}
void LogUtype(const utype *pu)
{
	int ay[1024];
	memset(ay,0,sizeof(ay));
	LogUtypeDG(LVTRACE, pu, 0, ay);
}
void LogUtype(const utype *pu, const t_logparam& lp)
{
	int ay[1024];
	memset(ay,0,sizeof(ay));
	LogUtypeDG(lp, pu, 0, ay);
}
