#include <alloca.h>
#include "utype.h"

/** $$$ ADD BY LGZ BEGIN**/
int iUtypeMallocTimes=0;

static bool g_bIsDebugStatus = false;

static TUtypeInnerDebugLink *g_ptUtypeInnerDebugLink = NULL;

void SetDebugStatus(bool bIsDebugStatus)
{
	g_bIsDebugStatus = bIsDebugStatus;
}

TUtypeInnerDebugLink *GetUtypeInnerDebugLink()
{
	return g_ptUtypeInnerDebugLink;
}

static void* Malloc(size_t _Size)
{
	if (g_bIsDebugStatus)
	{
/*
		TUtypeInnerDebugLink *ptNewUtypeInnerDebugLink = (TUtypeInnerDebugLink *)malloc(sizeof(TUtypeInnerDebugLink));
		ptNewUtypeInnerDebugLink->pPtr = malloc(_Size);
		ptNewUtypeInnerDebugLink->next = NULL;
		
		if (g_ptUtypeInnerDebugLink == NULL)
		{
			g_ptUtypeInnerDebugLink = ptNewUtypeInnerDebugLink;
		}
		else
		{
			//往头上追加
			ptNewUtypeInnerDebugLink->next = g_ptUtypeInnerDebugLink;
			g_ptUtypeInnerDebugLink = ptNewUtypeInnerDebugLink;
		}
		iUtypeMallocTimes++;
		
		return g_ptUtypeInnerDebugLink->pPtr;
*/
		iUtypeMallocTimes++;
		return malloc(_Size);
	}
	else
	{
		return malloc(_Size);
	}
}

static void Free(void *ptr)
{
	if (g_bIsDebugStatus)
	{
/*
		TUtypeInnerDebugLink *ptPre = g_ptUtypeInnerDebugLink, *ptCur = NULL;
		
		if (g_ptUtypeInnerDebugLink == NULL)
		{
			//不应该到这里
		}
		else
		{
			if (g_ptUtypeInnerDebugLink->pPtr == ptr)
			{
				ptCur = g_ptUtypeInnerDebugLink;
				g_ptUtypeInnerDebugLink = g_ptUtypeInnerDebugLink->next;
				free(ptCur);
			}
			else
			{
				ptCur = g_ptUtypeInnerDebugLink->next;
				while(ptCur)
				{
					if ((ptCur->pPtr == ptr) && (ptr != (void*) NULL))
					{
						ptPre->next = ptCur->next;
						free(ptCur);
						break;
					}
					else
					{
						ptPre = ptCur;
						ptCur = ptCur->next;
					}
				}
			}
		}
*/
		iUtypeMallocTimes--;
	}
	free(ptr);
}

static void *Realloc(void *ptr,int iSize)
{
	if (g_bIsDebugStatus)
	{
/*
		TUtypeInnerDebugLink *ptCur = g_ptUtypeInnerDebugLink;
		while(ptCur)
		{
			if (ptCur->pPtr == ptr)
			{
				ptCur->pPtr = realloc(ptr, iSize);
				return ptCur->pPtr;
			}
			else
			{
				ptCur = ptCur->next;
			}
		}
*/
		return realloc(ptr, iSize);
	}
	else
	{
		return realloc(ptr, iSize);
	}
}

/** $$$ ADD BY LGZ END **/

#define init0(a) memset(a, 0, sizeof(a))

#define COUNT_LEV(tpu,iterator,ind,param,end)	\
	int level;	\
	level=0;	\
	ind[level]=param##0;	\
	\
	if(param##1!=end){	\
		level++;	\
		ind[level]=param##1;	\
	}	\
	if(param##2!=end){	\
		level++;	\
		ind[level]=param##2;	\
	}	\
	if(param##3!=end){	\
		level++;	\
		ind[level]=param##3;	\
	}	\
	if(param##4!=end){	\
		level++;	\
		ind[level]=param##4;	\
	}	\
	if(param##5!=end){	\
		level++;	\
		ind[level]=param##5;	\
	}	\
	if(param##6!=end){	\
		level++;	\
		ind[level]=param##6;	\
	}	\
	if(param##7!=end){	\
		level++;	\
		ind[level]=param##7;	\
	}	\
	if(param##8!=end){	\
		level++;	\
		ind[level]=param##8;	\
	}	\
	if(param##9!=end){	\
		level++;	\
		ind[level]=param##9;	\
	}	\
	iterator=0;\
	while(iterator<level){	\
		tpu=(utype*)utGetStruct(tpu,ind[iterator]);	\
		iterator++;	\
	}

long u_errno=0;

/* Calc hashvalue for a key */

static unsigned int hash_func(const char *key)
{
	register unsigned int nr=1, nr2=4;
	register unsigned int length;
	length=strlen(key);

	while (length--)
	{
		nr^= (((nr & 63)+nr2)*((unsigned int) (unsigned char) *key++))+ (nr << 8);
		nr2+=3;
	}

	return ((unsigned int) nr)%U_HASHMOD;
}



/*不成功返回NULL*/
utype* uInit(int capacity)
{
	return _uInit(capacity, &u_errno);
}

utype* _uInit(int capacity, long *plRet)
{
	int i,noMem=0;
	utype *pu;

	*plRet = 0;

	if(capacity<1)
		capacity=1;

	pu=(utype*)Malloc(sizeof(utype));
	if (!pu)
	{
		*plRet = U_ERR_NOMEM;
		return NULL;
	}
	memset(pu,0,sizeof(utype));
	pu->capacity=capacity;
	pu->cnt=0;
	pu->ppe=(ue**)Malloc(sizeof(ue*)*capacity);
	if (!(pu->ppe))
	{
		Free(pu);
		*plRet = U_ERR_NOMEM;
		pu = NULL;
	}
	memset(pu->ppe, 0, sizeof(sizeof(ue*)*capacity));

	for(i=0;i<capacity;i++)
	{
		pu->ppe[i]=(ue*)Malloc(sizeof(ue));
		if (pu->ppe[i] == NULL)
		{
			noMem = i+1;
			break;
		}
		memset(pu->ppe[i],0,sizeof(ue));
		pu->ppe[i]->namePos=-1;
		pu->ppe[i]->nameListPre=-1;
		pu->ppe[i]->nameListNext=-1;
	}
	if (noMem != 0)
	{
		for(i=0;i<noMem-1;i++)
		{
			Free(pu->ppe[i]);
		}
		Free(pu->ppe);
		Free(pu);
		*plRet = U_ERR_NOMEM;
		pu = NULL;
	}

/*********** 20090312 *********/
	memset(pu->idxKey,U_HASHNULL,sizeof(pu->idxKey));
/******************************/
	pu->idxName=(idxNameItem*)Malloc(sizeof(idxNameItem)*capacity);
	pu->nameCap=capacity;
	pu->idxNameFree=0;
	for(i=0;i<capacity;i++){
		memset(pu->idxName[i].name,0,U_MAXNAMELEN);
		pu->idxName[i].idxNameFree=i+1;
		pu->idxName[i].nameListFirst=-1;
	}
	pu->idxName[i-1].idxNameFree=-1;

	return pu;
}

/*不成功返回NULL*/
utype* uAlloc(utype *pu,int occ, long *plRet)
{
	int i,noMem=0,new_cap;
	ue** tmp;

	*plRet = 0;
	if(occ<pu->cnt)
	{
		ueFree(pu->ppe[occ]);
	}
	else if(occ>=pu->cnt && occ<pu->capacity)
	{
		pu->cnt=occ+1;
	}
	else if(occ>=pu->capacity)
	{
		if(occ>pu->capacity+pu->capacity/2)
			new_cap=occ+1;
		else
			new_cap=pu->capacity+pu->capacity/2+1;

		tmp =(ue**)Realloc(pu->ppe,sizeof(ue*)*new_cap);
		if (!tmp)
		{
			*plRet = U_ERR_NOMEM;
			return NULL;
		}
		pu->ppe=tmp;
		memset(pu->ppe+pu->capacity,0,sizeof(ue*)*(new_cap-pu->capacity));
		for(i=0;i<new_cap-pu->capacity;i++)
		{
			pu->ppe[pu->capacity+i]=(ue*)Malloc(sizeof(ue));
			if (!(pu->ppe[pu->capacity+i]))
			{
				noMem = i+1;
				break;
			}
			memset(pu->ppe[pu->capacity+i],0,sizeof(ue));
			pu->ppe[pu->capacity+i]->namePos=-1;
			pu->ppe[pu->capacity+i]->nameListPre=-1;
			pu->ppe[pu->capacity+i]->nameListNext=-1;
		}

		if (noMem != 0)
		{
			for(i=0;i<noMem-1;i++)
			{
				Free(pu->ppe[pu->capacity+i]);
			}
			*plRet = U_ERR_NOMEM;
			return NULL;
		}
		pu->capacity=new_cap;
		pu->cnt=occ+1;
	}
	return pu;
}

/*不成功返回NULL*/
utype * uSetInt(utype *pu,int occ,int iv)
{
	return _uSetInt(pu,occ,iv, &u_errno);
}

utype * _uSetInt(utype *pu,int occ,int iv, long *plRet)
{
	*plRet = 0;
	if (uAlloc(pu,occ,plRet) == NULL)
	{
		return NULL;
	}

	(*(pu->ppe+occ))->type=U_INT;
	(*(pu->ppe+occ))->value.v_int=iv;
	return pu;
}

utype * uSetChar(utype *pu,int occ,char iv)
{
	return _uSetChar(pu,occ,iv, &u_errno);
}
utype * _uSetChar(utype *pu,int occ,char iv, long *plRet)
{
	*plRet = 0;
	if (uAlloc(pu,occ,plRet) == NULL)
	{
		return NULL;
	}

	pu->ppe[occ]->type=U_CHAR;
	pu->ppe[occ]->value.v_char=iv;
	return pu;
}

/*不成功返回NULL*/
utype * uSetLong(utype *pu,int occ,long iv)
{
	return _uSetLong(pu,occ,iv, &u_errno);
}
utype * _uSetLong(utype *pu,int occ,long iv, long *plRet)
{
	*plRet = 0;
	if (uAlloc(pu,occ,plRet) == NULL)
	{
		return NULL;
	}

	(*(pu->ppe+occ))->type=U_LONG;
	(*(pu->ppe+occ))->value.v_long=iv;
	return pu;
}

/*不成功返回NULL*/
utype * uSetDouble(utype *pu,int occ,double iv)
{
	return _uSetDouble(pu,occ,iv, &u_errno);
}
utype * _uSetDouble(utype *pu,int occ,double iv, long *plRet)
{
	*plRet = 0;
	if (uAlloc(pu,occ,plRet) == NULL)
	{
		return NULL;
	}
	(*(pu->ppe+occ))->type=U_DOUBLE;
	(*(pu->ppe+occ))->value.v_double=iv;
	return pu;
}

char uGetChar(const utype *pu,int occ)
{
	return _uGetChar(pu,occ,&u_errno);
}
char _uGetChar(const utype *pu,int occ, long *plRet)
{
	*plRet = 0;

	if(occ>=pu->cnt){
		*plRet = U_ERR_NOOCC;
		return 0;
	}
	switch(pu->ppe[occ]->type){
	case U_CHAR:
		return pu->ppe[occ]->value.v_char;
	case U_INT:
		return (char)pu->ppe[occ]->value.v_int;
	case U_LONG:
		return (char)pu->ppe[occ]->value.v_long;
	case U_DOUBLE:
		return (char)pu->ppe[occ]->value.v_double;
	case U_STRING:
		return pu->ppe[occ]->value.p_char[0];
	case U_EMPTY:
		*plRet = U_ERR_EMPTY;
		return 0;
	default:
		*plRet = U_ERR_WRONGTYPE;
		return 0;
	}
}

int uGetInt(const utype *pu,int occ)
{
	return _uGetInt(pu,occ,&u_errno);
}
int _uGetInt(const utype *pu,int occ, long *plRet)
{
	*plRet = 0;
	if(occ>=pu->cnt){
		*plRet = U_ERR_NOOCC;
		return 0;
	}
	switch(pu->ppe[occ]->type){
	case U_CHAR:
		return (int)pu->ppe[occ]->value.v_char;
	case U_INT:
		return pu->ppe[occ]->value.v_int;
	case U_LONG:
		return (int)pu->ppe[occ]->value.v_long;
	case U_DOUBLE:
		return (int)pu->ppe[occ]->value.v_double;
	case U_STRING:
		return atoi(pu->ppe[occ]->value.p_char);
	case U_EMPTY:
		*plRet = U_ERR_EMPTY;
		return 0;
	default:
		*plRet = U_ERR_WRONGTYPE;
		return 0;
	}
}

long uGetLong(const utype *pu,int occ)
{
	return _uGetLong(pu,occ,&u_errno);
}
long _uGetLong(const utype *pu,int occ, long *plRet)
{
	*plRet = 0;
	if(occ>=pu->cnt){
		*plRet = U_ERR_NOOCC;
		return 0;
	}
	switch(pu->ppe[occ]->type){
	case U_CHAR:
		return (long)pu->ppe[occ]->value.v_char;
	case U_INT:
		return (long)pu->ppe[occ]->value.v_int;
	case U_LONG:
		return pu->ppe[occ]->value.v_long;
	case U_DOUBLE:
		return (long)pu->ppe[occ]->value.v_double;
	case U_STRING:
		return atol(pu->ppe[occ]->value.p_char);
	case U_EMPTY:
		*plRet = U_ERR_EMPTY;
		return 0;
	default:
		*plRet = U_ERR_WRONGTYPE;
		return 0;
	}
}

double uGetDouble(const utype *pu,int occ)
{
	return _uGetDouble(pu,occ,&u_errno);
}
double _uGetDouble(const utype *pu,int occ, long *plRet)
{
	*plRet = 0;
	if(occ>=pu->cnt){
		*plRet = U_ERR_NOOCC;
		return 0;
	}
	switch(pu->ppe[occ]->type){
	case U_CHAR:
		return (double)pu->ppe[occ]->value.v_char;
	case U_INT:
		return (double)pu->ppe[occ]->value.v_int;
	case U_LONG:
		return (double)pu->ppe[occ]->value.v_long;
	case U_DOUBLE:
		return pu->ppe[occ]->value.v_double;
	case U_STRING:
		return atof(pu->ppe[occ]->value.p_char);
	case U_EMPTY:
		*plRet = U_ERR_EMPTY;
		return 0;
	default:
		*plRet = U_ERR_WRONGTYPE;
		return 0;
	}
}

/*不成功返回NULL*/
utype *uSetStr(utype *pu,int occ,const char * iv)
{
	return _uSetStr(pu,occ,iv, &u_errno);
}
utype *_uSetStr(utype *pu,int occ,const char * iv, long *plRet)
{
	*plRet = 0;
	if (uAlloc(pu,occ,plRet) == NULL)
	{
		return NULL;
	}
	(*(pu->ppe+occ))->type=U_STRING;
	(*(pu->ppe+occ))->value.p_char=(char*)Malloc(strlen(iv)+1);
	if ((*(pu->ppe+occ))->value.p_char == NULL)
	{
		return NULL;
	}
	strcpy((*(pu->ppe+occ))->value.p_char,iv);
	return pu;
}

char * uGetStr(const utype *pu,int occ)
{
	return _uGetStr(pu,occ,&u_errno);
}

char * _uGetStr(const utype *pu,int occ, long *plRet)
{
	*plRet = 0;

	if(occ>=pu->cnt){
		*plRet = U_ERR_NOOCC;
		return NULL;
	}
	else if(pu->ppe[occ]->type!=U_STRING){
		*plRet = U_ERR_WRONGTYPE;
		return NULL;
	}
	else if(pu->ppe[occ]->type==U_EMPTY){
		*plRet = U_ERR_EMPTY;
		return NULL;
	}

	return(pu->ppe[occ]->value.p_char);
}

/*不成功返回NULL*/
utype *uSetArray(utype *pu,int occ,utype * iv)
{
	return _uSetArray(pu,occ,iv, &u_errno);
}
utype * _uSetArray(utype *pu,int occ,utype * iv, long *plRet)
{
	*plRet = 0;
	if (uAlloc(pu,occ,plRet) == NULL)
	{
		return NULL;
	}
	if (iv)
	{

		(*(pu->ppe+occ))->type=U_ARRAY;
		(*(pu->ppe+occ))->value.p_utype=iv;
	}
	else
	{
		//(*(pu->ppe+occ))->type=U_EMPTY;
		(*(pu->ppe+occ))->type=U_ARRAY;
		(*(pu->ppe+occ))->value.p_utype=uInit(1);
	}
	return pu;
}

const utype * uGetArray(const utype *pu,int occ)
{
	return _uGetArray(pu,occ,&u_errno);
}
const utype* _uGetArray(const utype *pu,int occ, long *plRet)
{
	*plRet = 0;
	if(occ>=pu->cnt){
		*plRet = U_ERR_NOOCC;
		return NULL;
	}
	else if(pu->ppe[occ]->type!=U_ARRAY){
		*plRet = U_ERR_WRONGTYPE;
		return NULL;
	}
	else if(pu->ppe[occ]->type==U_EMPTY){
		*plRet = U_ERR_EMPTY;
		return NULL;
	}
	return(pu->ppe[occ]->value.p_utype);
}

/*不成功返回NULL*/
utype *uSetStruct(utype *pu,int occ,utype * iv)
{
	return _uSetStruct(pu,occ,iv, &u_errno);
}
utype * _uSetStruct(utype *pu,int occ,utype * iv, long *plRet)
{
	*plRet = 0;
	if (uAlloc(pu,occ,plRet) == NULL)
	{
		return NULL;
	}
	if (iv)
	{
		(*(pu->ppe+occ))->type=U_STRUCT;
		(*(pu->ppe+occ))->value.p_utype=iv;
	}
	else
	{
		//(*(pu->ppe+occ))->type=U_EMPTY;
		(*(pu->ppe+occ))->type=U_STRUCT;
		(*(pu->ppe+occ))->value.p_utype=uInit(1);
	}
	return pu;
}

const utype * uGetStruct(const utype *pu,int occ)
{
	return _uGetStruct(pu,occ,&u_errno);
}
const utype* _uGetStruct(const utype *pu,int occ, long *plRet)
{
	*plRet = 0;
	if(occ>=pu->cnt){
		*plRet = U_ERR_NOOCC;
		return NULL;
	}
	else if(pu->ppe[occ]->type!=U_STRUCT){
		*plRet = U_ERR_WRONGTYPE;
		return NULL;
	}
	else if(pu->ppe[occ]->type==U_EMPTY){
		*plRet = U_ERR_EMPTY;
		return NULL;
	}

	return(pu->ppe[occ]->value.p_utype);
}

utype *uSetEmpty(utype *pu,int occ)
{
	return _uSetEmpty(pu,occ,&u_errno);
}
utype * _uSetEmpty(utype *pu,int occ,long *plRet)
{
	*plRet = 0;
	if (uAlloc(pu,occ,plRet) == NULL)
	{
		return NULL;
	}
	(*(pu->ppe+occ))->type=U_EMPTY;
	return pu;
}

int uGetEmpty(const utype *pu,int occ)
{
	return _uGetEmpty(pu,occ,&u_errno);
}
int _uGetEmpty(const utype *pu,int occ, long *plRet)
{
	*plRet = 0;
	if(occ>=pu->cnt){
		*plRet = U_ERR_NOOCC;
		return 0;
	}
	if(pu->ppe[occ]->type==U_EMPTY)
		return 1;
	else
		return 0;
}
/*******
void uMove(utype *tpu,int tocc,utype * fpu,int focc)
{
	if(tpu==NULL || fpu==NULL)
		return ;
	uAlloc(tpu,tocc,&u_errno);
	ueFree(tpu->ppe[tocc]);
	tpu->ppe[tocc]=fpu->ppe[focc];
	fpu->ppe[focc]=NULL;

	unsigned int hashKey;
	int hashPos;
	if(_utSearch(fpu,fpu->ppe[focc]->name,&hashKey,&hashPos)!=-1)
		_utEraseName(fpu,hashKey,hashPos);
}
**********/

utype * uClone(const utype *pu)
{
	int i;
	utype * pou=NULL;

	if(pu==NULL)
		return NULL;

	pou=uInit(pu->cnt);
	for(i=0;i<pu->cnt;i++){

		switch(pu->ppe[i]->type){

			case U_EMPTY:
				uSetEmpty(pou,i);
				break;
			case U_CHAR:
				uSetChar(pou,i,uGetChar(pu,i));
				break;
			case U_INT:
				uSetInt(pou,i,uGetInt(pu,i));
				break;
			case U_LONG:
				uSetLong(pou,i,uGetLong(pu,i));
				break;
			case U_DOUBLE:
				uSetDouble(pou,i,uGetDouble(pu,i));
				break;
			case U_STRING:
				uSetStr(pou,i,uGetStr(pu,i));
				break;
			case U_ARRAY:
				uSetArray(pou,i,uClone(uGetArray(pu,i)));
				break;
			case U_STRUCT:
				uSetStruct(pou,i,uClone(uGetStruct(pu,i)));
				break;
               }

       }

       return(pou);
}

void uFree(utype *pu)
{
	int i;

	u_errno=0;
	if (pu)
	{
		for(i=0;i<pu->capacity;i++)
		{
			if( pu->ppe[i]->type==U_STRING){
				Free(pu->ppe[i]->value.p_char);
				pu->ppe[i]->value.p_char=NULL;
			}
			else if( pu->ppe[i]->type==U_ARRAY || pu->ppe[i]->type==U_STRUCT ){
				uFree(pu->ppe[i]->value.p_utype);
				pu->ppe[i]->value.p_utype = NULL;
			}
			Free(pu->ppe[i]);
			pu->ppe[i]=NULL;
		}
		Free(pu->ppe);
		pu->ppe = NULL;
		Free(pu->idxName);
		pu->idxName = NULL;
		Free(pu);
	}
}

void ueFree(ue * pue)
{
	u_errno=0;

	if (pue)
	{
		if(pue->type==U_STRING)
		{
			Free(pue->value.p_char);
			pue->value.p_char = NULL;
		}
		else if(pue->type==U_ARRAY || pue->type==U_STRUCT)
		{
			uFree(pue->value.p_utype);
			pue->value.p_utype = NULL;
		}
	}
}

#ifdef __cplusplus
int uPackLen(const utype *pu)
{
	int i;
	int ul;
	char tmpStr[40];

	ul=0;

	if(pu==NULL)
		return 0;

	for(i=0;i<pu->cnt;i++){
		ul+=2;	//U_NEXT和数据类型占两位
		ul+=((int)strlen(utGetName(pu,i))+1);	//20090223 增加名字
		switch(pu->ppe[i]->type){
			case U_EMPTY:	//只设类型
				break;
			case U_CHAR:	//设置类型和值
				ul++;
				break;
			case U_INT:	//设置类型和值
				sprintf(tmpStr,"%d",pu->ppe[i]->value.v_int);
				ul+=((int)strlen(tmpStr)+1);
				break;
			case U_LONG:
				sprintf(tmpStr,"%ld",pu->ppe[i]->value.v_long);
				ul+=((int)strlen(tmpStr)+1);
				break;
			case U_DOUBLE:
				sprintf(tmpStr,"%f",pu->ppe[i]->value.v_double);
				ul+=((int)strlen(tmpStr)+1);
				break;
			case U_STRING:
				ul+=((int)strlen(pu->ppe[i]->value.p_char)+1);
				break;
			case U_ARRAY:
			case U_STRUCT:
				ul+=uPackLen(pu->ppe[i]->value.p_utype);
				break;

		}
	}
	ul++;	//U_END
	return ul;
}

int _uPack(const utype *pu,char **upack)
{
	int i;

	for(i=0;i<pu->cnt;i++){
		**upack=U_NEXT;	//设置ue开始标志
		(*upack)++;

		**upack=pu->ppe[i]->type;	//设置数据类型
		(*upack)++;

		switch(pu->ppe[i]->type){	//设置数据类型和值

			case U_EMPTY:	//只设类型
				break;
			case U_CHAR:	//设置类型和值
				**upack=pu->ppe[i]->value.v_char;
				(*upack)++;
				break;
			case U_INT:	//设置类型和值
				sprintf(*upack,"%d",pu->ppe[i]->value.v_int);
				(*upack)+=(strlen(*upack)+1);
				break;
			case U_LONG:
				sprintf(*upack,"%ld",pu->ppe[i]->value.v_long);
				(*upack)+=(strlen(*upack)+1);
				break;
			case U_DOUBLE:
				sprintf(*upack,"%f",pu->ppe[i]->value.v_double);
				(*upack)+=(strlen(*upack)+1);
				break;
			case U_STRING:
				strcpy(*upack,pu->ppe[i]->value.p_char);
				(*upack)+=(strlen(*upack)+1);
				break;
			case U_ARRAY:
			case U_STRUCT:
				_uPack(pu->ppe[i]->value.p_utype,upack);
				break;

		}
		strcpy(*upack,utGetName(pu,i));	//20090223 增加名字
		(*upack)+=(strlen(*upack)+1);

	}

	**upack=U_END;
	(*upack)++;

	return 0;

}
int uPack(utype *pu,char *upack)
{
	char * tp;

	if(pu==NULL)
		return 0;

	tp=upack;
	return _uPack(pu,&tp);
}

int _uUnpack(char **upack,utype **upp)
{
	int occ;
	utype * tpu;
	char* pv;

	if(**upack==U_END){
		*upp=NULL;
		(*upack)++;	//20090204
		return 0;
	}
	else if(**upack==U_NEXT){
		*upp=uInit(5);
		occ=0;
	}
	else{
		return -1;
	}
	while(**upack==U_NEXT){
		(*upack)++;
		char tmpT;
		tmpT=**upack;
		(*upack)++;

		switch(tmpT){
			case U_EMPTY:
				//uSetStruct(*upp,occ,NULL);
				utAddEmpty(*upp,*upack);
				break;
			case U_CHAR:
				pv=*upack;
				(*upack)++;	//20090223
				utAddChar(*upp,*upack,*pv);
				break;
			case U_INT:
				pv=*upack;
				(*upack)+=(strlen(*upack)+1);
				utAddInt(*upp,*upack,atoi(pv));
				break;
			case U_LONG:
				pv=*upack;
				(*upack)+=(strlen(*upack)+1);
				utAddLong(*upp,*upack,atol(pv));
				break;
			case U_DOUBLE:
				pv=*upack;
				(*upack)+=(strlen(*upack)+1);
				utAddDouble(*upp,*upack,atof(pv));
				break;
			case U_STRING:
				pv=*upack;
				(*upack)+=(strlen(*upack)+1);
				utAddStr(*upp,*upack,pv);
				break;
			case U_ARRAY:
				_uUnpack(upack,&tpu);
				//if(tpu!=NULL)
					utAddArray(*upp,*upack,tpu);
				break;
			case U_STRUCT:
				_uUnpack(upack,&tpu);
				//if(tpu!=NULL)
					utAddStruct(*upp,*upack,tpu);
				break;
			default:
				uFree(*upp);
				*upp = NULL;
				return -1;

		}
		//strcpy((*upp)->ppe[occ]->name,*upack);	//20090223 增加名字
		(*upack)+=(strlen(*upack)+1);

		occ++;
	}
	(*upack)++;
	return 0;
}

int uUnpack(char *upack,utype **upp)
{
	char * tp;

	if(upack==NULL)
		return 0;

	tp=upack;
	return _uUnpack(&tp,upp);
}


void PrintLevel(int iLevel)
{
	int i;
	for(i = 0; i < iLevel; i ++)
	{
		printf("-");
	}
}

static void PrintUtype(const utype *pu, int iLevel)
{
	int i;

	u_errno=0;
	for(i=0;i<pu->cnt;i++)
	{
		switch(pu->ppe[i]->type)
		{
			case U_EMPTY:
			{
				PrintLevel(iLevel);
				printf("empty %s\n",utGetName(pu,i));
				break;
			}
			case U_CHAR:
			{
				PrintLevel(iLevel);
				printf("%s\tchar\t%c\n",utGetName(pu,i), pu->ppe[i]->value.v_char);
				break;
			}
			case U_INT:
			{
				PrintLevel(iLevel);
				printf("%s\tint\t%d\n",utGetName(pu,i), pu->ppe[i]->value.v_int);
				break;
			}
			case U_LONG:
			{
				PrintLevel(iLevel);
				printf("%s\tlong\t%ld\n",utGetName(pu,i), pu->ppe[i]->value.v_long);
				break;
			}
			case U_DOUBLE:
			{
				PrintLevel(iLevel);
				printf("%s\tdouble\t%lf\n",utGetName(pu,i), pu->ppe[i]->value.v_double);
				break;
			}
			case U_STRING:
			{
				PrintLevel(iLevel);
				printf("%s\tstring\t%s\n",utGetName(pu,i), pu->ppe[i]->value.p_char);
				break;
			}
			case U_ARRAY:
			case U_STRUCT:
			{
				PrintLevel(iLevel);
				printf("%s\tutype\n",utGetName(pu,i));
				PrintUtype(pu->ppe[i]->value.p_utype,iLevel+1);
				break;
			}
			default:
			{
				break;
			}
		}
	}
}




//验证名字，格式要求与c变量名相同
int uValidName(const char* s1)
{
	int i=0, isStart=0;
	for(i=0;i<1024*1024;i++){
		if(s1[i]==0) return 1;
		if((s1[i]<='Z'&&s1[i]>='A')||(s1[i]<='z'&&s1[i]>='a')||s1[i]=='_'){
			isStart=1;
			continue;
		}else if(s1[i]<='9'&&s1[i]>='0'){
			if(isStart==0) return 0;
			continue;
		}
		return 0;
	}
	return 1;
}

size_t uChgValue(char* s, size_t maxlen, const char* src)
{
	size_t i=0, j=0;
	for(i=0;j<maxlen-1-6;i++){//减去\0和替换后的最大可能长度
		if(src[i]==0) break ;
		switch(src[i]){
			case '<':s[j++]='&';s[j++]='l';s[j++]='t';s[j++]=';';break;
			case '>':s[j++]='&';s[j++]='g';s[j++]='t';s[j++]=';';break;
			case '&':s[j++]='&';s[j++]='a';s[j++]='m';s[j++]='p';s[j++]=';';break;
			case '\'':s[j++]='&';s[j++]='a';s[j++]='p';s[j++]='o';s[j++]='s';s[j++]=';';break;
			case '"':s[j++]='&';s[j++]='q';s[j++]='u';s[j++]='o';s[j++]='t';s[j++]=';';break;
			default :s[j++]=src[i];
		}
	}
	s[j]=0;
	return j;
}

size_t uStrcat(char** s1,size_t curlen, size_t* maxlen, const char* s2, int isChg)
{
	size_t s2len=strlen(s2);
	if(s2len==0) return 0;
	if((2*s2len+curlen+1>*maxlen)||s2len+curlen>=*maxlen-128){
		char* s=(char*)Realloc(*s1, (*maxlen+s2len)*2);
		if(s==NULL) return 0;
		*s1=s;
		*maxlen=(*maxlen+s2len)*2;
	}
	if(isChg)
		return uChgValue(*s1+curlen, *maxlen-curlen, s2);
	else{
		if(s2len==1){
			(*s1)[curlen]=s2[0];
			(*s1)[curlen+1]=0;
		}
		else if(s2len==2){
			(*s1)[curlen]=s2[0];
			(*s1)[curlen+1]=s2[1];
			(*s1)[curlen+2]=0;
		}
		else
			strcpy((*s1)+curlen, s2);
	}
	return s2len;
}



char uTypeArray[][10]={"empty", "char", "int", "long", "double", "string", "node", "node"};

size_t addnv(char** s1, size_t curlen, size_t* maxlen, const char* name, const char* value, int type)
{
	size_t le=0;
	le+=uStrcat(s1, curlen+le, maxlen, "<", 0);
	le+=uStrcat(s1, curlen+le, maxlen, name, 0);
	le+=uStrcat(s1, curlen+le, maxlen, " type=\"", 0);
	le+=uStrcat(s1, curlen+le, maxlen, uTypeArray[type], 0);
	le+=uStrcat(s1, curlen+le, maxlen, "\">", 0);
	le+=uStrcat(s1, curlen+le, maxlen, value, 1);
	le+=uStrcat(s1, curlen+le, maxlen, "</", 0);
	le+=uStrcat(s1, curlen+le, maxlen, name, 0);
	le+=uStrcat(s1, curlen+le, maxlen, ">", 0);
	return le;
}

size_t u2x(const utype *pu, char** buf, size_t curlen, size_t* maxlen)
{
	int i=0;
	for(i=0;i<pu->cnt;i++){
		if(uValidName(utGetName(pu,i))==0){
			snprintf(*buf, 2048, "<%s>无法作为合法的XML节点名", utGetName(pu,i));
			throw(uException(U_ERR_NAMENULL, *buf));
		}
		switch(pu->ppe[i]->type){
			case U_EMPTY:{

				curlen+=addnv(buf, curlen, maxlen, utGetName(pu,i), "", U_EMPTY);
				break;
			}
			case U_CHAR:
			{
				char s[2];
				s[0]=pu->ppe[i]->value.v_char;
				s[1]=0;
				curlen+=addnv(buf, curlen, maxlen, utGetName(pu,i), s, U_CHAR);
				break;
			}
			case U_INT:
			{
				char s[20];
				sprintf(s, "%d", pu->ppe[i]->value.v_int);
				curlen+=addnv(buf, curlen, maxlen, utGetName(pu,i), s, U_INT);
				break;
			}
			case U_LONG:
			{
				char s[20];
				sprintf(s, "%ld", pu->ppe[i]->value.v_long);
				curlen+=addnv(buf, curlen, maxlen, utGetName(pu,i), s, U_LONG);
				break;
			}
			case U_DOUBLE:
			{
				char s[25];
				sprintf(s, "%lf", pu->ppe[i]->value.v_double);
				curlen+=addnv(buf, curlen, maxlen, utGetName(pu,i), s, U_DOUBLE);
				break;
			}
			case U_STRING:
			{
				curlen+=addnv(buf, curlen, maxlen, utGetName(pu,i), pu->ppe[i]->value.p_char, U_STRING);
				break;
			}
			case U_ARRAY:
			case U_STRUCT:
			{
				curlen+=uStrcat(buf, curlen, maxlen, "<", 0);
				curlen+=uStrcat(buf, curlen, maxlen, utGetName(pu,i), 0);

				curlen+=uStrcat(buf, curlen, maxlen, ">", 0);
				curlen=u2x(pu->ppe[i]->value.p_utype, buf, curlen, maxlen);
				curlen+=uStrcat(buf, curlen, maxlen, "</", 0);
				curlen+=uStrcat(buf, curlen, maxlen, utGetName(pu,i), 0);
				curlen+=uStrcat(buf, curlen, maxlen, ">", 0);
				break;
			}
			default:
			{
				break;
			}
		}
	}
	return curlen;
}


char* uUType2Xml(const utype *pu, const char* rootName)
{	
	size_t maxlen=2048;
	size_t curlen;
	char* sbf=(char*)malloc(maxlen);
	if(sbf==NULL) return NULL;
	HandPtr p((void**)&sbf);
	if(uValidName(rootName)==0){
		snprintf(sbf, 2048, "<%s>无法作为合法的XML节点名", rootName);
		throw(uException(U_ERR_NAMENULL, sbf));
	}
	snprintf(sbf, 2048, "<?xml version=\"1.0\" encoding=\"GBK\" standalone=\"no\" ?><%s>", rootName);
	curlen=u2x(pu, &sbf, strlen(sbf), &maxlen);
	curlen+=uStrcat(&sbf, curlen, &maxlen, "</", 0);
	curlen+=uStrcat(&sbf, curlen, &maxlen, rootName, 0);
	curlen+=uStrcat(&sbf, curlen, &maxlen, ">", 0);
	return (char*)p.GetPtr();
}


int trans (char* u_type)
{
	int type;
	if(strcmp(u_type,"empty")==0)
	{
		type = 0;
	}
	if(strcmp(u_type,"char")==0)
	{
		type = 1;
	}
	if(strcmp(u_type,"int")==0)
	{
		type = 2;
	}
	if(strcmp(u_type,"long")==0)
	{
		type = 3;
	}
	if(strcmp(u_type,"double")==0)
	{
		type = 4;
	}
	if(strcmp(u_type,"string")==0)
	{
		type = 5;
	}
	if(strcmp(u_type,"node")==0)
	{
		type = 7;
	}
	return type;
}




typedef struct ut{
	utype* pu;
	int occ;
	int type;
} tut;

int head_hook(void* data, void* load, void** save, int level,
							const char* tagname, size_t len,
							const char* attname, size_t len2,
							const char* attvalue, size_t len3)
{
	return 0;
}
int attrib_hook(void* data, void* load, void** save, int level,
							const char* tagname, size_t len,
							const char* attname, size_t len2,
							const char* attvalue, size_t len3)
{
	tut* tp=(tut*)data;
	utype* fath=(utype*)load;
	char* tname=(char*)alloca(len+128);
	char* u_name=(char*)alloca(len2+128);
	char* u_value=(char*)alloca(len3+128);

	if(level==0) return 0;//默认认为根节点只能是复合类型
	if(tname==NULL||u_name==NULL||u_value==NULL) throw(uException(U_ERR_TYPE, "", "xml节点名/属性名/属性值过大以致内存分配失败"));
	memcpy(tname, tagname, len);
	tname[len]=0;
	if(load==NULL) throw(uException(U_ERR_TYPE, tname, "非node类型节点下包含有其他节点!"));
	memcpy(u_name, attname, len2);
	u_name[len2]=0;
	memcpy(u_value, attvalue, len3);
	u_value[len3]=0;
	if(strcmp(u_name, "type")) return 0;
	if(tp->type!=-1) throw(uException(U_ERR_MORE_TYPE, tname, "节点存在多个类型属性"));
	tp->type=trans(u_value);
	if(tp->type!=U_STRUCT&&tp->type!=U_ARRAY){
		*save=NULL;
	}

	return 0;
	
}
int value_hook(void* data, void* load, void** save, int level,
							const char* tagname, size_t len,
							const char* value, size_t len2)
{
	tut* tp=(tut*)data;
	utype* pou=(utype*)load;
	char* tname=(char*)alloca(len+128);
	char* u_value=(char*)alloca(len2+128);
	
	if(tname==NULL||u_value==NULL) throw(uException(U_ERR_TYPE, "", "xml节点名/值过大以致内存分配失败"));
	memcpy(tname, tagname, len);
	tname[len]=0;
	if(level==0) return 0;//默认认为根节点只能是复合类型
	if(load==NULL) throw(uException(U_ERR_TYPE, tname, "非node类型节点下包含有其他节点."));
	
	
	xs_speccpy(u_value, len2+128, value, len2);

	switch(tp->type){
		case U_EMPTY:{
			utSetEmpty(pou,tp->occ);
			break;
		}
		case U_CHAR:{

			utSetChar(pou,tp->occ,u_value[0]);
			break;
		}
		case U_INT:{
			if(!len2)
				utSetInt(pou,tp->occ,0);
			else
				utSetInt(pou,tp->occ,atoi(u_value));
			break;
		}
		case U_LONG:{
			if(!len2)
				utSetLong(pou,tp->occ,0);
			else
				utSetLong(pou,tp->occ,atol(u_value));
			break;
		}
		case U_DOUBLE:{
			if(!len2)
				utSetDouble(pou,tp->occ,0);
			else
				utSetDouble(pou,tp->occ,atof(u_value));

			break;
		}
		//case -1:
		case U_STRING:{
			utSetStr(pou,tp->occ,u_value);
			break;
		}
		default:{
			break;
		}
	}
	return 0;
	
}
int enter_hook(void* data, void* load, void** save, int level, const char* tagname, size_t len)
{
	tut* tp=(tut*)data;
	char* tname=(char*)alloca(len+128);
	utype* fath=(utype*)load;
	utype* pu=uInit(1);
	uAutoPtr p(pu);

	tp->type=-1;
	if(tname==NULL) throw(uException(U_ERR_TYPE, "", "xml节点名过大以致内存分配失败"));
	memcpy(tname, tagname, len);
	if(load==NULL&&level!=0) throw(uException(U_ERR_TYPE, tname, "非node类型节点下包含有其他节点"));
	tname[len]=0;
	if(level==0){
		uFree(pu);
		pu=tp->pu;
		tp->occ=0;
	}
	else{
		tp->occ=utAddStruct(fath, tname, pu);
	}
	*save=pu;
	p.release();
	return 0;
}



int leave_hook(void* data, void* load, void** save, int level,
							const char* tagname, size_t len)
{

	return 0;
}

utype* uXml2Utype(const char* xmlbuf)
{
	int rt;
	tut p;
	p.pu=uInit(INIT_LENGTH);
	uAutoPtr hand(p.pu);
	p.type=-1;
	rt=xs_engine(xmlbuf, strlen(xmlbuf), &p, head_hook,enter_hook,leave_hook, attrib_hook, value_hook);
	if(rt){
		throw(uException(rt+10000, xs_strerr(rt)));
	}
	return hand.release();
}


/*********** 20090318 *************
找到元素返回UPOS；pHashPos返回名字在hash表的位置
未找到返回UPOS_END；pHashPos返回在hash表中的空位
*********************************/

UPOS _utSearch(const utype* pu,const char* name,unsigned int* pHashKey,int* pHashPos)
{
	if(pu == NULL || name==NULL || name[0]==0)
		return UPOS_END;

	unsigned int hashKey;
	int namePos;
	int hashPos=0;

	hashKey=hash_func(name);
	while(pu->idxKey[hashKey][hashPos]!=U_HASHNULL){
		namePos=pu->idxKey[hashKey][hashPos];
		if(strcmp(pu->idxName[namePos].name,name)==0){
			if(pHashKey)
				*pHashKey=hashKey;
			if(pHashPos)
				*pHashPos=hashPos;
			return pu->idxName[namePos].nameListFirst;
		}
		hashPos++;
		if(hashPos>=U_MAXHASHLEV){
			char errMsg[80];
			sprintf(errMsg,"%s错误,HASH数组越界！",__FUNCTION__);
			throw(uException(U_ERR_HASHOVER,errMsg));
		}
	}
	if(pHashKey)
		*pHashKey=hashKey;
	if(pHashPos)
		*pHashPos=hashPos;
	return UPOS_END;
}

idxNameItem* _utNameAlloc(utype* pu)
{
	int i;
	if(pu->idxNameFree!=-1)
		return pu->idxName;
	int newCap;
	newCap=pu->nameCap+pu->nameCap/2+1;
	pu->idxName=(idxNameItem*)Realloc(pu->idxName,sizeof(idxNameItem)*newCap);
	pu->idxNameFree=pu->nameCap;
	for(i=pu->nameCap;i<newCap;i++){
		memset(pu->idxName[i].name,0,U_MAXNAMELEN);
		pu->idxName[i].idxNameFree=i+1;
		pu->idxName[i].nameListFirst=-1;
	}
	pu->idxName[i-1].idxNameFree=-1;
	pu->nameCap=newCap;
	return pu->idxName;
}

void _utAddName(utype* pu,const char* name,UPOS pos,int occ,unsigned int hashKey,int hashPos)
{
	if(name==NULL || name[0]==0)
		return;
	if(strlen(name)>=U_MAXNAMELEN){
		char errMsg[80];
		sprintf(errMsg,"%s错误,[%d]元素名字超长！",__FUNCTION__,occ);
		throw(uException(U_ERR_NAMELEN,errMsg));
	}
	int namePos;
	if(pos==UPOS_END){
		if(pu->idxNameFree==-1)
			pu->idxName=_utNameAlloc(pu);
		namePos=pu->idxNameFree;
		pu->idxKey[hashKey][hashPos]=namePos;
		strcpy(pu->idxName[namePos].name,name);
		pu->idxNameFree=pu->idxName[namePos].idxNameFree;
		pu->idxName[namePos].idxNameFree=-1;
		pu->idxName[namePos].nameListFirst=occ;
		pu->ppe[occ]->namePos=namePos;
		pu->ppe[occ]->nameListPre=-1;
		pu->ppe[occ]->nameListNext=-1;
	}
	else{
		int focc;
		namePos=pu->idxKey[hashKey][hashPos];
		focc=pu->idxName[namePos].nameListFirst;
		pu->ppe[focc]->nameListPre=occ;
		pu->ppe[occ]->nameListPre=-1;
		pu->ppe[occ]->nameListNext=focc;
		pu->ppe[occ]->namePos=namePos;
		pu->idxName[namePos].nameListFirst=occ;
	}
}

void _utEraseName(utype* pu,int occ,unsigned int hashKey,int hashPos)
{
//清nameList
	int singleFlag;
	int namePos;

	namePos=pu->ppe[occ]->namePos;
	if(namePos==-1)
		return;
	if(pu->ppe[occ]->nameListPre!=-1)
		pu->ppe[pu->ppe[occ]->nameListPre]->nameListNext=pu->ppe[occ]->nameListNext;
	if(pu->ppe[occ]->nameListNext!=-1)
		pu->ppe[pu->ppe[occ]->nameListNext]->nameListPre=pu->ppe[occ]->nameListPre;
	if(pu->idxName[namePos].nameListFirst==occ)
		pu->idxName[namePos].nameListFirst=pu->ppe[occ]->nameListNext;
//清idxName,回收idxName空间
//清idxKey
	if(pu->idxName[namePos].nameListFirst!=-1)
		return;

	pu->ppe[occ]->namePos=-1;
	memset(pu->idxName[namePos].name,0,U_MAXNAMELEN);
	pu->idxName[namePos].idxNameFree=pu->idxNameFree;
	pu->idxNameFree=namePos;

	unsigned char lastPos;
	lastPos=hashPos;
	while(pu->idxKey[hashKey][lastPos+1]!=U_HASHNULL){
		lastPos++;
	}
	if(lastPos==hashPos)
		pu->idxKey[hashKey][lastPos]=U_HASHNULL;
	else{
		pu->idxKey[hashKey][hashPos]=pu->idxKey[hashKey][lastPos];
		pu->idxKey[hashKey][lastPos]=U_HASHNULL;
	}
}

UPOS utFind(const utype* pu,const char* name)
{
	UPOS pos;
	if(pu == NULL || name == NULL)
		return UPOS_END;
	pos=_utSearch(pu,name,NULL,NULL);
	if(pos==UPOS_END)
		return pos;
	while(pu->ppe[pos]->nameListNext!=-1)
		pos=pu->ppe[pos]->nameListNext;
	return pos;
}

UPOS utNext(const utype* pu,UPOS beginPos)
{
	return(pu->ppe[beginPos]->nameListPre);
}

void utSetInt(utype* pu,int occ,int iv){
	char errMsg[80];
	if(pu==NULL){
		sprintf(errMsg,"%s错误,输入空utype指针！",__FUNCTION__);
		throw(uException(U_ERR_UPNULL,errMsg));
	}
	if(uSetInt(pu,occ,iv)==NULL){
		sprintf(errMsg,"%s错误,分配[%d]元素失败！",__FUNCTION__,occ);
		throw(uException(U_ERR_NOMEM,errMsg));
	}
}

int utGetInt(const utype* pu,int occ,char* name){
	char errMsg[80];

	if(pu==NULL){
		sprintf(errMsg,"%s错误,输入空utype指针！",__FUNCTION__);
		throw(uException(U_ERR_UPNULL,errMsg));
	}
	if(occ>=pu->cnt){
		sprintf(errMsg,"%s错误,读取[%d]元素不存在！",__FUNCTION__,occ);
		throw(uException(U_ERR_NOOCC,errMsg));
	}
    /*else if(pu->ppe[occ]->type!=U_INT){
		sprintf(errMsg,"%s错误,读取[%d]元素类型不匹配！",__FUNCTION__,occ);
		throw(uException(U_ERR_WRONGTYPE,errMsg));
	}*/
	else if(pu->ppe[occ]->type==U_EMPTY){
		sprintf(errMsg,"%s错误,读取[%d]元素为空值！",__FUNCTION__,occ);
		throw(uException(U_ERR_EMPTY,errMsg));
	}
	if(name){
		strcpy(name,utGetName(pu,occ));
	}
	return(uGetInt(pu,occ));
}

void utSetChar(utype* pu,int occ,char iv){
	char errMsg[80];
	if(pu==NULL){
		sprintf(errMsg,"%s错误,输入空utype指针！",__FUNCTION__);
		throw(uException(U_ERR_UPNULL,errMsg));
	}
	if(uSetChar(pu,occ,iv)==NULL){
		sprintf(errMsg,"%s错误,分配[%d]元素失败！",__FUNCTION__,occ);
		throw(uException(U_ERR_NOMEM,errMsg));
	}
}

char utGetChar(const utype* pu,int occ,char* name){
	char errMsg[80];

	if(pu==NULL){
		sprintf(errMsg,"%s错误,输入空utype指针！",__FUNCTION__);
		throw(uException(U_ERR_UPNULL,errMsg));
	}
	if(occ>=pu->cnt){
		sprintf(errMsg,"%s错误,读取[%d]元素不存在！",__FUNCTION__,occ);
		throw(uException(U_ERR_NOOCC,errMsg));
	}
    /*   	else if(pu->ppe[occ]->type!=U_CHAR){
		sprintf(errMsg,"%s错误,读取[%d]元素类型不匹配！",__FUNCTION__,occ);
		throw(uException(U_ERR_WRONGTYPE,errMsg));
	} */
	else if(pu->ppe[occ]->type==U_EMPTY){
		sprintf(errMsg,"%s错误,读取[%d]元素为空值！",__FUNCTION__,occ);
		throw(uException(U_ERR_EMPTY,errMsg));
	}
        if(name){
                strcpy(name,utGetName(pu,occ));
        }
	return(uGetChar(pu,occ));
}

void utSetLong(utype* pu,int occ,long iv){
	char errMsg[80];
	if(pu==NULL){
		sprintf(errMsg,"%s错误,输入空utype指针！",__FUNCTION__);
		throw(uException(U_ERR_UPNULL,errMsg));
	}
	if(uSetLong(pu,occ,iv)==NULL){
		sprintf(errMsg,"%s错误,分配[%d]元素失败！",__FUNCTION__,occ);
		throw(uException(U_ERR_NOMEM,errMsg));
	}
}

long utGetLong(const utype* pu,int occ,char* name){
	char errMsg[80];

	if(pu==NULL){
		sprintf(errMsg,"%s错误,输入空utype指针！",__FUNCTION__);
		throw(uException(U_ERR_UPNULL,errMsg));
	}
	if(occ>=pu->cnt){
		sprintf(errMsg,"%s错误,读取[%d]元素不存在！",__FUNCTION__,occ);
		throw(uException(U_ERR_NOOCC,errMsg));
	}
    /*  	else if(pu->ppe[occ]->type!=U_LONG){
		sprintf(errMsg,"%s错误,读取[%d]元素类型不匹配！",__FUNCTION__,occ);
		throw(uException(U_ERR_WRONGTYPE,errMsg));
	} */
	else if(pu->ppe[occ]->type==U_EMPTY){
		sprintf(errMsg,"%s错误,读取[%d]元素为空值！",__FUNCTION__,occ);
		throw(uException(U_ERR_EMPTY,errMsg));
	}
        if(name){
                strcpy(name,utGetName(pu,occ));
        }
	return(uGetLong(pu,occ));
}

void utSetDouble(utype* pu,int occ,double iv){
	char errMsg[80];
	if(pu==NULL){
		sprintf(errMsg,"%s错误,输入空utype指针！",__FUNCTION__);
		throw(uException(U_ERR_UPNULL,errMsg));
	}
	if(uSetDouble(pu,occ,iv)==NULL){
		sprintf(errMsg,"%s错误,分配[%d]元素失败！",__FUNCTION__,occ);
		throw(uException(U_ERR_NOMEM,errMsg));
	}
}

double utGetDouble(const utype* pu,int occ,char* name){
	char errMsg[80];

	if(pu==NULL){
		sprintf(errMsg,"%s错误,输入空utype指针！",__FUNCTION__);
		throw(uException(U_ERR_UPNULL,errMsg));
	}
	if(occ>=pu->cnt){
		sprintf(errMsg,"%s错误,读取[%d]元素不存在！",__FUNCTION__,occ);
		throw(uException(U_ERR_NOOCC,errMsg));
	}
    /*   	else if(pu->ppe[occ]->type!=U_DOUBLE){
		sprintf(errMsg,"%s错误,读取[%d]元素类型不匹配！",__FUNCTION__,occ);
		throw(uException(U_ERR_WRONGTYPE,errMsg));
	} */
	else if(pu->ppe[occ]->type==U_EMPTY){
		sprintf(errMsg,"%s错误,读取[%d]元素为空值！",__FUNCTION__,occ);
		throw(uException(U_ERR_EMPTY,errMsg));
	}
        if(name){
                strcpy(name,utGetName(pu,occ));
        }
	return(uGetDouble(pu,occ));
}

void utSetStr(utype* pu,int occ,const char * iv){
	char errMsg[80];
	if(pu==NULL){
		sprintf(errMsg,"%s错误,输入空utype指针！",__FUNCTION__);
		throw(uException(U_ERR_UPNULL,errMsg));
	}
	if(uSetStr(pu,occ,iv)==NULL){
		sprintf(errMsg,"%s错误,分配[%d]元素失败！",__FUNCTION__,occ);
		throw(uException(U_ERR_NOMEM,errMsg));
	}
}

char * utGetStr(const utype* pu,int occ,char* name){
	char errMsg[80];

	if(pu==NULL){
		sprintf(errMsg,"%s错误,输入空utype指针！",__FUNCTION__);
		throw(uException(U_ERR_UPNULL,errMsg));
	}
	if(occ>=pu->cnt){
		sprintf(errMsg,"%s错误,读取[%d]元素不存在！",__FUNCTION__,occ);
		throw(uException(U_ERR_NOOCC,errMsg));
	}
       	else if(pu->ppe[occ]->type!=U_STRING){
		sprintf(errMsg,"%s错误,读取[%d]元素类型不匹配！",__FUNCTION__,occ);
		throw(uException(U_ERR_WRONGTYPE,errMsg));
	}
	else if(pu->ppe[occ]->type==U_EMPTY){
		sprintf(errMsg,"%s错误,读取[%d]元素为空值！",__FUNCTION__,occ);
		throw(uException(U_ERR_EMPTY,errMsg));
	}
        if(name){
                strcpy(name,utGetName(pu,occ));
        }
	return(uGetStr(pu,occ));
}

void utSetArray(utype* pu,int occ,utype * iv){
	char errMsg[80];
	if(pu==NULL){
		sprintf(errMsg,"%s错误,输入空utype指针！",__FUNCTION__);
		throw(uException(U_ERR_UPNULL,errMsg));
	}
	if(uSetArray(pu,occ,iv)==NULL){
		sprintf(errMsg,"%s错误,分配[%d]元素失败！",__FUNCTION__,occ);
		throw(uException(U_ERR_NOMEM,errMsg));
	}
}

const utype* utGetArray(const utype* pu,int occ,char* name){
	char errMsg[80];

	if(pu==NULL){
		sprintf(errMsg,"%s错误,输入空utype指针！",__FUNCTION__);
		throw(uException(U_ERR_UPNULL,errMsg));
	}
	if(occ>=pu->cnt){
		sprintf(errMsg,"%s错误,读取[%d]元素不存在！",__FUNCTION__,occ);
		throw(uException(U_ERR_NOOCC,errMsg));
	}
       	else if(pu->ppe[occ]->type!=U_ARRAY){
		sprintf(errMsg,"%s错误,读取[%d]元素类型不匹配！",__FUNCTION__,occ);
		throw(uException(U_ERR_WRONGTYPE,errMsg));
	}
	else if(pu->ppe[occ]->type==U_EMPTY){
		sprintf(errMsg,"%s错误,读取[%d]元素为空值！",__FUNCTION__,occ);
		throw(uException(U_ERR_EMPTY,errMsg));
	}
        if(name){
                strcpy(name,utGetName(pu,occ));
        }
	return(uGetArray(pu,occ));
}

void utSetStruct(utype* pu,int occ,utype * iv){
	char errMsg[80];
	if(pu==NULL){
		sprintf(errMsg,"%s错误,输入空utype指针！",__FUNCTION__);
		throw(uException(U_ERR_UPNULL,errMsg));
	}
	if(uSetStruct(pu,occ,iv)==NULL){
		sprintf(errMsg,"%s错误,分配[%d]元素失败！",__FUNCTION__,occ);
		throw(uException(U_ERR_NOMEM,errMsg));
	}
}

const utype* utGetStruct(const utype *pu,int occ,char* name){
	char errMsg[80];

	if(pu==NULL){
		sprintf(errMsg,"%s错误,输入空utype指针！",__FUNCTION__);
		throw(uException(U_ERR_UPNULL,errMsg));
	}
	if(occ>=pu->cnt){
		sprintf(errMsg,"%s错误,读取[%d]元素不存在！",__FUNCTION__,occ);
		throw(uException(U_ERR_NOOCC,errMsg));
	}
       	else if(pu->ppe[occ]->type!=U_STRUCT){
		sprintf(errMsg,"%s错误,读取[%d]元素类型不匹配！",__FUNCTION__,occ);
		throw(uException(U_ERR_WRONGTYPE,errMsg));
	}
	else if(pu->ppe[occ]->type==U_EMPTY){
		sprintf(errMsg,"%s错误,读取[%d]元素为空值！",__FUNCTION__,occ);
		throw(uException(U_ERR_EMPTY,errMsg));
	}
        if(name){
                strcpy(name,utGetName(pu,occ));
        }
	return(uGetStruct(pu,occ));
}

void utSetEmpty(utype* pu,int occ){
	char errMsg[80];
	if(pu==NULL){
		sprintf(errMsg,"%s错误,输入空utype指针！",__FUNCTION__);
		throw(uException(U_ERR_UPNULL,errMsg));
	}
	if(uSetEmpty(pu,occ)==NULL){
		sprintf(errMsg,"%s错误,分配[%d]元素失败！",__FUNCTION__,occ);
		throw(uException(U_ERR_NOMEM,errMsg));
	}
}

int utGetEmpty(const utype* pu,int occ,char* name){
	char errMsg[80];

	if(pu==NULL){
		sprintf(errMsg,"%s错误,输入空utype指针！",__FUNCTION__);
		throw(uException(U_ERR_UPNULL,errMsg));
	}
	if(occ>=pu->cnt){
		sprintf(errMsg,"%s错误,读取[%d]元素不存在！",__FUNCTION__,occ);
		throw(uException(U_ERR_NOOCC,errMsg));
	}
        if(name){
                strcpy(name,utGetName(pu,occ));
        }
	return(uGetEmpty(pu,occ));
}

utype * utClone(const utype *pu)
{
	int i;
	utype * pou=NULL;

	if(pu==NULL)
		return NULL;

	pou=uInit(pu->cnt);
	for(i=0;i<pu->cnt;i++){

		switch(pu->ppe[i]->type){

			case U_EMPTY:
				utAddEmpty(pou,utGetName(pu,i));
				break;
			case U_CHAR:
				utAddChar(pou,utGetName(pu,i),utGetChar(pu,i));
				break;
			case U_INT:
				utAddInt(pou,utGetName(pu,i),utGetInt(pu,i));
				break;
			case U_LONG:
				utAddLong(pou,utGetName(pu,i),utGetLong(pu,i));
				break;
			case U_DOUBLE:
				utAddDouble(pou,utGetName(pu,i),utGetDouble(pu,i));
				break;
			case U_STRING:
				utAddStr(pou,utGetName(pu,i),utGetStr(pu,i));
				break;
			case U_ARRAY:
				utAddArray(pou,utGetName(pu,i),utClone(utGetArray(pu,i)));
				break;
			case U_STRUCT:
				utAddStruct(pou,utGetName(pu,i),utClone(utGetStruct(pu,i)));
				break;
               }

       }

       return(pou);
}
//
//void utMove(utype *tpu,int tocc,utype* fpu,int focc){
//	char errMsg[80];
//
//	if(tpu==NULL || fpu==NULL){
//		sprintf(errMsg,"%s错误,输入空utype指针！",__FUNCTION__);
//		throw(uException(U_ERR_UPNULL,errMsg));
//	}
//	if(focc>=fpu->cnt){
//		sprintf(errMsg,"%s错误,读取[%d]元素不存在！",__FUNCTION__,focc);
//		throw(uException(U_ERR_NOOCC,errMsg));
//	}
//       	else if(fpu->ppe[focc]->type!=U_ARRAY && fpu->ppe[focc]->type!=U_STRUCT){
//		sprintf(errMsg,"%s错误,读取[%d]元素类型不匹配！",__FUNCTION__,focc);
//		throw(uException(U_ERR_WRONGTYPE,errMsg));
//	}
//	else if(fpu->ppe[focc]->type==U_EMPTY){
//		sprintf(errMsg,"%s错误,读取[%d]元素为空值！",__FUNCTION__,focc);
//		throw(uException(U_ERR_EMPTY,errMsg));
//	}
//
//	return(uMove(tpu,tocc,fpu,focc));
//}


//分离指定位置的节点，并返回该节点的指针。
//
//utype* utApart(utype *pu, int occ)
//{
//	char errMsg[80];
//	if(pu==NULL){
//		sprintf(errMsg,"%s错误,输入空utype指针！",__FUNCTION__);
//		throw(uException(U_ERR_UPNULL,errMsg));
//	}
//	if(occ>=pu->cnt)
//	{
//		sprintf(errMsg,"%s错误,读取[%d]元素不存在！",__FUNCTION__,occ);
//		throw(uException(U_ERR_NOOCC,errMsg));
//	}
//    else if ((pu->ppe[occ]->type != U_STRUCT) && (pu->ppe[occ]->type != U_STRUCT))
//	{
//		sprintf(errMsg,"%s错误,读取[%d]元素类型不匹配！",__FUNCTION__,occ);
//		throw(uException(U_ERR_WRONGTYPE,errMsg));
//	}
//	utype *ptCurUtype = pu->ppe[occ]->value.p_utype;
//
//	pu->ppe[occ]->value.p_utype = NULL;
//	pu->ppe[occ]->type = U_EMPTY;
//
//	unsigned int hashKey;
//	int hashPos;
//	if(_utSearch(pu,pu->ppe[occ]->name,&hashKey,&hashPos)!=-1)
//		_utEraseName(pu,hashKey,hashPos);
//
//	return ptCurUtype;
//}

int utAddInt(utype* pu,const char* name,int iv)
{
	int occ;
	UPOS pos;
	unsigned int hashKey;
	int hashPos;

	occ=pu->cnt;
	utSetInt(pu,occ,iv);
	pos=_utSearch(pu,name,&hashKey,&hashPos);
	_utAddName(pu,name,pos,occ,hashKey,hashPos);
	return occ;
}

void utSetInt(utype* pu,const char* name,UPOS pos,int iv)
{
	int pos2;
	if (pos == UPOS_END){
		pos2 = _utSearch(pu,name,NULL,NULL);
		if (pos2 != UPOS_END){
			utSetInt(pu, pos2, iv);
		} else {
			utAddInt(pu, name, iv);
		}
	}	else {
		utSetInt(pu,pos,iv);
	}
}

int utGetInt(const utype* pu,const char* name,int* pocc)
{
	int occ;
	occ=_utSearch(pu,name,NULL,NULL);
	if(occ==UPOS_END){
		char errMsg[80];
		sprintf(errMsg,"%s错误,[%s]元素不存在！",__FUNCTION__,name);
		throw(uException(U_ERR_UNFIND,errMsg));
	}
	if(pocc)
		*pocc=occ;
	return(utGetInt(pu,occ));
}
int utGetInt(const utype* pu,const char* name,UPOS pos,int* pocc)
{
	if(pos==UPOS_END){
		char errMsg[80];
		sprintf(errMsg,"%s错误,[%s]元素不存在！",__FUNCTION__,name);
		throw(uException(U_ERR_UNFIND,errMsg));
	}
	int occ;
	occ=pos;
	return(utGetInt(pu,occ));
}

int utAddChar(utype* pu,const char* name,char iv)
{
	int occ;
	UPOS pos;
	unsigned int hashKey;
	int hashPos;

	occ=pu->cnt;
	utSetChar(pu,occ,iv);
	pos=_utSearch(pu,name,&hashKey,&hashPos);
	_utAddName(pu,name,pos,occ,hashKey,hashPos);
	return occ;
}

void utSetChar(utype* pu,const char* name,UPOS pos,char iv)
{
	int pos2;
	if (pos == UPOS_END){
		pos2 = _utSearch(pu, name,NULL,NULL);
		if (pos2 != UPOS_END){
			utSetChar(pu, pos2, iv);
		} else {
			utAddChar(pu, name, iv);
		}
	}	else {
		utSetChar(pu,pos,iv);
	}
}

char utGetChar(const utype* pu,const char* name,int* pocc)
{
	int occ;
	occ=_utSearch(pu,name,NULL,NULL);
	if(occ==UPOS_END){
		char errMsg[80];
		sprintf(errMsg,"%s错误,[%s]元素不存在！",__FUNCTION__,name);
		throw(uException(U_ERR_UNFIND,errMsg));
	}
	if(pocc)
		*pocc=occ;
	return(utGetChar(pu,occ));
}
char utGetChar(const utype* pu,const char* name,UPOS pos,int* pocc)
{
	if(pos==UPOS_END){
		char errMsg[80];
		sprintf(errMsg,"%s错误,[%s]元素不存在！",__FUNCTION__,name);
		throw(uException(U_ERR_UNFIND,errMsg));
	}
	int occ;
	occ=pos;
	return(utGetChar(pu,occ));
}

int utAddLong(utype* pu,const char* name,long iv)
{
	int occ;
	UPOS pos;
	unsigned int hashKey;
	int hashPos;

	occ=pu->cnt;
	utSetLong(pu,occ,iv);
	pos=_utSearch(pu,name,&hashKey,&hashPos);
	_utAddName(pu,name,pos,occ,hashKey,hashPos);
	return occ;
}

void utSetLong(utype* pu,const char* name,UPOS pos,long iv)
{
	int pos2;
	if (pos == UPOS_END){
		pos2 = _utSearch(pu, name,NULL,NULL);
		if (pos2 != UPOS_END){
			utSetLong(pu, pos2, iv);
		} else {
			utAddLong(pu, name, iv);
		}
	}	else {
		utSetLong(pu,pos,iv);
	}
}

long utGetLong(const utype* pu,const char* name,int* pocc)
{
	int occ;
	occ=_utSearch(pu,name,NULL,NULL);
	if(occ==UPOS_END){
		char errMsg[80];
		sprintf(errMsg,"%s错误,[%s]元素不存在！",__FUNCTION__,name);
		throw(uException(U_ERR_UNFIND,errMsg));
	}
	if(pocc)
		*pocc=occ;
	return(utGetLong(pu,occ));
}
long utGetLong(const utype* pu,const char* name,UPOS pos,int* pocc)
{
	if(pos==UPOS_END){
		char errMsg[80];
		sprintf(errMsg,"%s错误,[%s]元素不存在！",__FUNCTION__,name);
		throw(uException(U_ERR_UNFIND,errMsg));
	}
	int occ;
	occ=pos;
	return(utGetLong(pu,occ));
}

int utAddDouble(utype* pu,const char* name,double iv)
{
	int occ;
	UPOS pos;
	unsigned int hashKey;
	int hashPos;

	occ=pu->cnt;
	utSetDouble(pu,occ,iv);
	pos=_utSearch(pu,name,&hashKey,&hashPos);
	_utAddName(pu,name,pos,occ,hashKey,hashPos);
	return occ;
}

void utSetDouble(utype* pu,const char* name,UPOS pos,double iv)
{
	int pos2;
	if (pos == UPOS_END){
		pos2 = _utSearch(pu, name,NULL,NULL);
		if (pos2 != UPOS_END){
			utSetDouble(pu, pos2, iv);
		} else {
			utAddDouble(pu, name, iv);
		}
	}	else {
		utSetDouble(pu,pos,iv);
	}
}

double utGetDouble(const utype* pu,const char* name,int* pocc)
{
	int occ;
	occ=_utSearch(pu,name,NULL,NULL);
	if(occ==UPOS_END){
		char errMsg[80];
		sprintf(errMsg,"%s错误,[%s]元素不存在！",__FUNCTION__,name);
		throw(uException(U_ERR_UNFIND,errMsg));
	}
	if(pocc)
		*pocc=occ;
	return(utGetDouble(pu,occ));
}
double utGetDouble(const utype* pu,const char* name,UPOS pos,int* pocc)
{
	if(pos==UPOS_END){
		char errMsg[80];
		sprintf(errMsg,"%s错误,[%s]元素不存在！",__FUNCTION__,name);
		throw(uException(U_ERR_UNFIND,errMsg));
	}
	int occ;
	occ=pos;
	return(utGetDouble(pu,occ));
}

int utAddStr(utype* pu,const char* name,const char* iv)
{
	int occ;
	UPOS pos;
	unsigned int hashKey;
	int hashPos;

	occ=pu->cnt;
	utSetStr(pu,occ,iv);
	pos=_utSearch(pu,name,&hashKey,&hashPos);
	_utAddName(pu,name,pos,occ,hashKey,hashPos);
	return occ;
}

void utSetStr(utype* pu,const char* name,UPOS pos,const char* iv)
{
	int pos2;
	if (pos == UPOS_END){
		pos2 = _utSearch(pu, name,NULL,NULL);
		if (pos2 != UPOS_END){
			utSetStr(pu, pos2, iv);
		} else {
			utAddStr(pu, name, iv);
		}
	}	else {
		utSetStr(pu,pos,iv);
	}
}


char* utGetStr(const utype* pu,const char* name,int* pocc)
{
	int occ;
	occ=_utSearch(pu,name,NULL,NULL);
	if(occ==UPOS_END){
		char errMsg[80];
		sprintf(errMsg,"%s错误,[%s]元素不存在！",__FUNCTION__,name);
		throw(uException(U_ERR_UNFIND,errMsg));
	}
	if(pocc)
		*pocc=occ;
	return(utGetStr(pu,occ));
}
char* utGetStr(const utype* pu,const char* name,UPOS pos,int* pocc)
{
	if(pos==UPOS_END){
		char errMsg[80];
		sprintf(errMsg,"%s错误,[%s]元素不存在！",__FUNCTION__,name);
		throw(uException(U_ERR_UNFIND,errMsg));
	}
	int occ;
	occ=pos;
	return(utGetStr(pu,occ));
}

int utAddArray(utype* pu,const char* name,utype* iv)
{
	int occ;
	UPOS pos;
	unsigned int hashKey;
	int hashPos;

	occ=pu->cnt;
	utSetArray(pu,occ,iv);
	pos=_utSearch(pu,name,&hashKey,&hashPos);
	_utAddName(pu,name,pos,occ,hashKey,hashPos);
	return occ;
}

void utSetArray(utype* pu,const char* name,UPOS pos,utype* iv)
{
	int pos2;
	if (pos == UPOS_END){
		pos2 = _utSearch(pu, name,NULL,NULL);
		if (pos2 != UPOS_END){
			utSetArray(pu, pos2, iv);
		} else {
			utAddArray(pu, name, iv);
		}
	}	else {
		utSetArray(pu,pos,iv);
	}
}

const utype* utGetArray(const utype* pu,const char* name,int* pocc)
{
	int occ;
	occ=_utSearch(pu,name,NULL,NULL);
	if(occ==UPOS_END){
		char errMsg[80];
		sprintf(errMsg,"%s错误,[%s]元素不存在！",__FUNCTION__,name);
		throw(uException(U_ERR_UNFIND,errMsg));
	}
	if(pocc)
		*pocc=occ;
	return(utGetArray(pu,occ));
}
const utype* utGetArray(const utype* pu,const char* name,UPOS pos,int* pocc)
{
	if(pos==UPOS_END){
		char errMsg[80];
		sprintf(errMsg,"%s错误,[%s]元素不存在！",__FUNCTION__,name);
		throw(uException(U_ERR_UNFIND,errMsg));
	}
	int occ;
	occ=pos;
	return(utGetArray(pu,occ));
}

int utAddStruct(utype* pu,const char* name,utype* iv)
{
	int occ;
	UPOS pos;
	unsigned int hashKey;
	int hashPos;

	occ=pu->cnt;
	utSetStruct(pu,occ,iv);
	pos=_utSearch(pu,name,&hashKey,&hashPos);
	_utAddName(pu,name,pos,occ,hashKey,hashPos);
	return occ;
}

void utSetStruct(utype* pu,const char* name,UPOS pos,utype* iv)
{
	int pos2;
	if (pos == UPOS_END){
		pos2 = _utSearch(pu, name,NULL,NULL);
		if (pos2 != UPOS_END){
			utSetStruct(pu, pos2, iv);
		} else {
			utAddStruct(pu, name, iv);
		}
	}	else {
		utSetStruct(pu,pos,iv);
	}
}

const utype* utGetStruct(const utype* pu,const char* name,int* pocc)
{
	int occ;
	occ=_utSearch(pu,name,NULL,NULL);
	if(occ==UPOS_END){
		char errMsg[80];
		sprintf(errMsg,"%s错误,[%s]元素不存在！",__FUNCTION__,name);
		throw(uException(U_ERR_UNFIND,errMsg));
	}
	if(pocc)
		*pocc=occ;
	return(utGetStruct(pu,occ));
}
const utype* utGetStruct(const utype* pu,const char* name,UPOS pos,int* pocc)
{
	if(pos==UPOS_END){
		char errMsg[80];
		sprintf(errMsg,"%s错误,[%s]元素不存在！",__FUNCTION__,name);
		throw(uException(U_ERR_UNFIND,errMsg));
	}
	int occ;
	occ=pos;
	return(utGetStruct(pu,occ));
}

int utAddEmpty(utype* pu,const char* name)
{
	int occ;
	UPOS pos;
	unsigned int hashKey;
	int hashPos;

	occ=pu->cnt;
	utSetEmpty(pu,occ);
	pos=_utSearch(pu,name,&hashKey,&hashPos);
	_utAddName(pu,name,pos,occ,hashKey,hashPos);
	return occ;
}

void utSetEmpty(utype* pu,const char* name,UPOS pos)
{
	int pos2;
	if (pos == UPOS_END){
		pos2 = _utSearch(pu, name,NULL,NULL);
		if (pos2 != UPOS_END){
			utSetEmpty(pu,pos2);
		} else {
			utAddEmpty(pu,name);
		}
	}	else {
		utSetEmpty(pu,pos);
	}
}

int utGetEmpty(const utype* pu,const char* name,int* pocc)
{
	int occ;
	occ=_utSearch(pu,name,NULL,NULL);
	if(occ==UPOS_END){
		char errMsg[80];
		sprintf(errMsg,"%s错误,[%s]元素不存在！",__FUNCTION__,name);
		throw(uException(U_ERR_UNFIND,errMsg));
	}
	if(pocc)
		*pocc=occ;
	return(utGetEmpty(pu,occ));
}
int utGetEmpty(const utype* pu,const char* name,UPOS pos,int* pocc)
{
	if(pos==UPOS_END){
		char errMsg[80];
		sprintf(errMsg,"%s错误,[%s]元素不存在！",__FUNCTION__,name);
		throw(uException(U_ERR_UNFIND,errMsg));
	}
	int occ;
	occ=pos;
	return(utGetEmpty(pu,occ));
}
//
//utype* utApart(utype *pu, const char* name)
//{
//	char errMsg[80];
//	int occ;
//	occ=_utSearch(pu,name,NULL,NULL);
//	if(occ==-1){
//		sprintf(errMsg,"%s错误,[%s]元素不存在！",__FUNCTION__,name);
//		throw(uException(U_ERR_UNFIND,errMsg));
//	}
//	return(utApart(pu,occ));
//}

/******************

void utRename(utype* pu,int occ,const char* nname)
{
	char errMsg[80];
	unsigned int oHashKey;
	int oHashPos;

	unsigned int nHashKey;
	int nHashPos;
	int nOcc;

	if(occ>=pu->cnt){
		sprintf(errMsg,"%s错误,[%d]位置元素不存在！",__FUNCTION__,occ);
		throw(uException(U_ERR_NOOCC,errMsg));
	}
	if(nname!=NULL && nname[0]!=0){
		if(strlen(nname)>=U_MAXNAMELEN){
			sprintf(errMsg,"%s错误,[%d]元素名字超长！",__FUNCTION__,occ);
			throw(uException(U_ERR_NAMELEN,errMsg));
		}
		if((nOcc=_utSearch(pu,nname,&nHashKey,&nHashPos))!=-1 && nOcc!=occ){
			sprintf(errMsg,"%s错误,与[%d]元素名字冲突！",__FUNCTION__,nOcc);
			throw(uException(U_ERR_NAMECONFLICT,errMsg));
		}
		if(nOcc==occ)
			return;
		if(pu->ppe[occ]->name[0]!=0){
			_utSearch(pu,pu->ppe[occ]->name,&oHashKey,&oHashPos);
			_utEraseName(pu,oHashKey,oHashPos);
			_utSearch(pu,nname,&nHashKey,&nHashPos);
		}
		pu->idxKey[nHashKey][nHashPos]=occ;
		strcpy(pu->ppe[occ]->name,nname);
	}
}
*********************/

void utRename(utype* pu,const char* oname,const char* nname)
{
	char errMsg[80];
	unsigned int oHashKey;
	int oHashPos;
	UPOS oPos;

	unsigned int nHashKey;
	int nHashPos;
	UPOS nPos;

	if(oname==NULL || oname[0]==0){
		sprintf(errMsg,"%s错误,未提供元素名字！",__FUNCTION__);
		throw(uException(U_ERR_NAMENULL,errMsg));
	}
	if(strcmp(oname,nname)==0)
		return;

	oPos=_utSearch(pu,oname,&oHashKey,&oHashPos);
	if(oPos==UPOS_END){
		sprintf(errMsg,"%s错误,[%s]元素不存在！",__FUNCTION__,oname);
		throw(uException(U_ERR_UNFIND,errMsg));
	}

	if(nname!=NULL && nname[0]!=0){
		if(strlen(nname)>=U_MAXNAMELEN){
			sprintf(errMsg,"%s错误,[%s]元素名字超长！",__FUNCTION__,nname);
			throw(uException(U_ERR_NAMELEN,errMsg));
		}
		if((nPos=_utSearch(pu,nname,&nHashKey,&nHashPos))!=UPOS_END){
			sprintf(errMsg,"%s错误,与[%s]元素名字冲突！",__FUNCTION__,nname);
			throw(uException(U_ERR_NAMECONFLICT,errMsg));
		}
		int namePos;
		namePos=pu->idxKey[oHashKey][oHashPos];

		int lastPos;
		lastPos=oHashPos;
		while(pu->idxKey[oHashKey][lastPos+1]!=U_HASHNULL){
			lastPos++;
		}
		if(lastPos==oHashPos)
			pu->idxKey[oHashKey][lastPos]=U_HASHNULL;
		else{
			pu->idxKey[oHashKey][oHashPos]=pu->idxKey[oHashKey][lastPos];
			pu->idxKey[oHashKey][lastPos]=U_HASHNULL;
		}

		_utSearch(pu,nname,&nHashKey,&nHashPos);
		pu->idxKey[nHashKey][nHashPos]=namePos;
		strcpy(pu->idxName[namePos].name,nname);
	}
}

const char* utGetName(const utype* pu,int occ)
{
	if(occ>=pu->cnt){
		char errMsg[80];
		sprintf(errMsg,"%s错误,[%d]位置元素不存在！",__FUNCTION__,occ);
		throw(uException(U_ERR_NOOCC,errMsg));
	}
	int namePos=pu->ppe[occ]->namePos;
	if(namePos==-1)
		return NULL;
	else
		return(pu->idxName[namePos].name);
}

int utGetType(const utype* pu,const char* name)
{
	int occ;
	occ=_utSearch(pu,name,NULL,NULL);
	if(occ==UPOS_END){
		char errMsg[80];
		sprintf(errMsg,"%s错误,[%s]元素不存在！",__FUNCTION__,name);
		throw(uException(U_ERR_UNFIND,errMsg));
	}
	return(pu->ppe[occ]->type);
}

int utGetIntByDir(const utype* pu,int occ0,int occ1,int occ2,int occ3,int occ4,int occ5,int occ6,int occ7,int occ8,int occ9)
{
	const utype* tpu=pu;
	int i=0;
	int occs[10];
	COUNT_LEV(tpu,i,occs,occ,-1)
	return utGetInt(tpu,occs[i]);
}

int utGetIntByDir(const utype* pu,const char* name0,const char* name1,const char* name2,const char* name3,const char* name4,const char* name5,const char* name6,const char* name7,const char* name8,const char* name9)
{
	const utype* tpu=pu;
	int i=0;
	const char* names[10];
	COUNT_LEV(tpu,i,names,name,NULL)
	return utGetInt(tpu,names[i]);
}

char utGetCharByDir(const utype* pu,int occ0,int occ1,int occ2,int occ3,int occ4,int occ5,int occ6,int occ7,int occ8,int occ9)
{
	const utype* tpu=pu;
	int i=0;
	int occs[10];
	COUNT_LEV(tpu,i,occs,occ,-1)
	return utGetChar(tpu,occs[i]);
}

char utGetCharByDir(const utype* pu,const char* name0,const char* name1,const char* name2,const char* name3,const char* name4,const char* name5,const char* name6,const char* name7,const char* name8,const char* name9)
{
	const utype* tpu=pu;
	int i=0;
	const char* names[10];
	COUNT_LEV(tpu,i,names,name,NULL)
	return utGetChar(tpu,names[i]);
}

long utGetLongByDir(const utype* pu,int occ0,int occ1,int occ2,int occ3,int occ4,int occ5,int occ6,int occ7,int occ8,int occ9)
{
	const utype* tpu=pu;
	int i=0;
	int occs[10];
	COUNT_LEV(tpu,i,occs,occ,-1)
	return utGetLong(tpu,occs[i]);
}

long utGetLongByDir(const utype* pu,const char* name0,const char* name1,const char* name2,const char* name3,const char* name4,const char* name5,const char* name6,const char* name7,const char* name8,const char* name9)
{
	const utype* tpu=pu;
	int i=0;
	const char* names[10];
	COUNT_LEV(tpu,i,names,name,NULL)
	return utGetLong(tpu,names[i]);
}

double utGetDoubleByDir(const utype* pu,int occ0,int occ1,int occ2,int occ3,int occ4,int occ5,int occ6,int occ7,int occ8,int occ9)
{
	const utype* tpu=pu;
	int i=0;
	int occs[10];
	COUNT_LEV(tpu,i,occs,occ,-1)
	return utGetDouble(tpu,occs[i]);
}

double utGetDoubleByDir(const utype* pu,const char* name0,const char* name1,const char* name2,const char* name3,const char* name4,const char* name5,const char* name6,const char* name7,const char* name8,const char* name9)
{
	const utype* tpu=pu;
	int i=0;
	const char* names[10];
	COUNT_LEV(tpu,i,names,name,NULL)
	return utGetDouble(tpu,names[i]);
}

char* utGetStrByDir(const utype* pu,int occ0,int occ1,int occ2,int occ3,int occ4,int occ5,int occ6,int occ7,int occ8,int occ9)
{
	const utype* tpu=pu;
	int i=0;
	int occs[10];
	COUNT_LEV(tpu,i,occs,occ,-1)
	return utGetStr(tpu,occs[i]);
}

char* utGetStrByDir(const utype* pu,const char* name0,const char* name1,const char* name2,const char* name3,const char* name4,const char* name5,const char* name6,const char* name7,const char* name8,const char* name9)
{
	const utype* tpu=pu;
	int i=0;
	const char* names[10];
	COUNT_LEV(tpu,i,names,name,NULL)
	return utGetStr(tpu,names[i]);
}

const utype* utGetArrayByDir(const utype* pu,int occ0,int occ1,int occ2,int occ3,int occ4,int occ5,int occ6,int occ7,int occ8,int occ9)
{
	const utype* tpu=pu;
	int i=0;
	int occs[10];
	COUNT_LEV(tpu,i,occs,occ,-1)
	return utGetArray(tpu,occs[i]);
}

const utype* utGetArrayByDir(const utype* pu,const char* name0,const char* name1,const char* name2,const char* name3,const char* name4,const char* name5,const char* name6,const char* name7,const char* name8,const char* name9)
{
	const utype* tpu=pu;
	int i=0;
	const char* names[10];
	COUNT_LEV(tpu,i,names,name,NULL)
	return utGetArray(tpu,names[i]);
}

const utype* utGetStructByDir(const utype* pu,int occ0,int occ1,int occ2,int occ3,int occ4,int occ5,int occ6,int occ7,int occ8,int occ9)
{
	const utype* tpu=pu;
	int i=0;
	int occs[10];
	COUNT_LEV(tpu,i,occs,occ,-1)
	return utGetStruct(tpu,occs[i]);
}

const utype* utGetStructByDir(const utype* pu,const char* name0,const char* name1,const char* name2,const char* name3,const char* name4,const char* name5,const char* name6,const char* name7,const char* name8,const char* name9)
{
	const utype* tpu=pu;
	int i=0;
	const char* names[10];
	COUNT_LEV(tpu,i,names,name,NULL)
	return utGetStruct(tpu,names[i]);
}

int utGetEmptyByDir(const utype* pu,int occ0,int occ1,int occ2,int occ3,int occ4,int occ5,int occ6,int occ7,int occ8,int occ9)
{
	const utype* tpu=pu;
	int i=0;
	int occs[10];
	COUNT_LEV(tpu,i,occs,occ,-1)
	return utGetEmpty(tpu,occs[i]);
}

int utGetEmptyByDir(const utype* pu,const char* name0,const char* name1,const char* name2,const char* name3,const char* name4,const char* name5,const char* name6,const char* name7,const char* name8,const char* name9)
{
	const utype* tpu=pu;
	int i=0;
	const char* names[10];
	COUNT_LEV(tpu,i,names,name,NULL)
	return utGetEmpty(tpu,names[i]);
}

const utype* getUtypeByPath(const utype* pu, const char* xpath, char* name)
{
	const utype* tpu = pu;
	char* token;
	const char* ptr;
	char path[100];

	memset(path, 0, sizeof(path));

	ptr = strrchr(xpath, '.');
	if(ptr==NULL){
		strcpy(name, xpath);
		return pu;
	}
	strncpy(path, xpath, ptr-xpath);
	path[ptr-xpath]='\0';
	strcpy(name, ptr+1);

	if (strcmp(path, "0") != 0){
		token = strtok(path, ".");
		while (token != NULL){
			tpu = utGetStruct(tpu, token);
	  	token = strtok(NULL, ".");
		}
	}

	return tpu;
}

int utGetIntByPath(const utype *pu, const char *xpath)
{
	const utype* tpu=pu;
	char name[30];

	tpu = getUtypeByPath(tpu, xpath, name);
	return utGetInt(tpu, name);
}

char utGetCharByPath(const utype *pu, const char *xpath)
{
	const utype* tpu=pu;
	char name[30];

	tpu = getUtypeByPath(tpu, xpath, name);
	return utGetChar(tpu, name);
}

long utGetLongByPath(const utype *pu, const char *xpath)
{
	const utype* tpu=pu;
	char name[30];

	tpu = getUtypeByPath(tpu, xpath, name);
	return utGetLong(tpu, name);
}

double utGetDoubleByPath(const utype *pu, const char *xpath)
{
	const utype* tpu=pu;
	char name[30];

	tpu = getUtypeByPath(tpu, xpath, name);
	return utGetDouble(tpu, name);
}

char* utGetStrByPath(const utype *pu, const char *xpath)
{
	const utype* tpu=pu;
	char name[30];

	tpu = getUtypeByPath(tpu, xpath, name);
	return utGetStr(tpu, name);
}

const utype* utGetStructByPath(const utype *pu, const char *xpath)
{
	const utype* tpu=pu;
	char name[30];

	tpu = getUtypeByPath(tpu, xpath, name);
	return utGetStruct(tpu, name);
}

const utype* utGetArrayByPath(const utype *pu, const char *xpath)
{
	const utype* tpu=pu;
	char name[30];

	tpu = getUtypeByPath(tpu, xpath, name);
	return utGetArray(tpu, name);
}

void utSetIntByDir(utype* pu,int val,int occ0,int occ1,int occ2,int occ3,int occ4,int occ5,int occ6,int occ7,int occ8,int occ9)
{
	utype* tpu=pu;
	int i=0;
	int occs[10];
	COUNT_LEV(tpu,i,occs,occ,-1)
	utSetInt(tpu,occs[i],val);
}
void utSetIntByDir(utype* pu,int val,const char* name0,const char* name1,const char* name2,const char* name3,const char* name4,const char* name5,const char* name6,const char* name7,const char* name8,const char* name9)
{
	utype* tpu=pu;
	int i=0;
	const char* names[10];
	COUNT_LEV(tpu,i,names,name,NULL)
	utSetInt(tpu,names[i],UPOS_END,val);
}
void utAddIntByDir(utype* pu,int val,const char* name0,const char* name1,const char* name2,const char* name3,const char* name4,const char* name5,const char* name6,const char* name7,const char* name8,const char* name9)
{
	utype* tpu=pu;
	int i=0;
	const char* names[10];
	COUNT_LEV(tpu,i,names,name,NULL)
	utAddInt(tpu,names[i],val);
}

void utSetCharByDir(utype* pu,char val,int occ0,int occ1,int occ2,int occ3,int occ4,int occ5,int occ6,int occ7,int occ8,int occ9)
{
	utype* tpu=pu;
	int i=0;
	int occs[10];
	COUNT_LEV(tpu,i,occs,occ,-1)
	utSetChar(tpu,occs[i],val);
}
void utSetCharByDir(utype* pu,char val,const char* name0,const char* name1,const char* name2,const char* name3,const char* name4,const char* name5,const char* name6,const char* name7,const char* name8,const char* name9)
{
	utype* tpu=pu;
	int i=0;
	const char* names[10];
	COUNT_LEV(tpu,i,names,name,NULL)
	utSetChar(tpu,names[i],UPOS_END,val);
}
void utAddCharByDir(utype* pu,char val,const char* name0,const char* name1,const char* name2,const char* name3,const char* name4,const char* name5,const char* name6,const char* name7,const char* name8,const char* name9)
{
	utype* tpu=pu;
	int i=0;
	const char* names[10];
	COUNT_LEV(tpu,i,names,name,NULL)
	utAddChar(tpu,names[i],val);
}

void utSetLongByDir(utype* pu,long val,int occ0,int occ1,int occ2,int occ3,int occ4,int occ5,int occ6,int occ7,int occ8,int occ9)
{
	utype* tpu=pu;
	int i=0;
	int occs[10];
	COUNT_LEV(tpu,i,occs,occ,-1)
	utSetLong(tpu,occs[i],val);
}
void utSetLongByDir(utype* pu,long val,const char* name0,const char* name1,const char* name2,const char* name3,const char* name4,const char* name5,const char* name6,const char* name7,const char* name8,const char* name9)
{
	utype* tpu=pu;
	int i=0;
	const char* names[10];
	COUNT_LEV(tpu,i,names,name,NULL)
	utSetLong(tpu,names[i],UPOS_END,val);
}
void utAddLongByDir(utype* pu,long val,const char* name0,const char* name1,const char* name2,const char* name3,const char* name4,const char* name5,const char* name6,const char* name7,const char* name8,const char* name9)
{
	utype* tpu=pu;
	int i=0;
	const char* names[10];
	COUNT_LEV(tpu,i,names,name,NULL)
	utAddLong(tpu,names[i],val);
}

void utSetDoubleByDir(utype* pu,double val,int occ0,int occ1,int occ2,int occ3,int occ4,int occ5,int occ6,int occ7,int occ8,int occ9)
{
	utype* tpu=pu;
	int i=0;
	int occs[10];
	COUNT_LEV(tpu,i,occs,occ,-1)
	utSetDouble(tpu,occs[i],val);
}
void utSetDoubleByDir(utype* pu,double val,const char* name0,const char* name1,const char* name2,const char* name3,const char* name4,const char* name5,const char* name6,const char* name7,const char* name8,const char* name9)
{
	utype* tpu=pu;
	int i=0;
	const char* names[10];
	COUNT_LEV(tpu,i,names,name,NULL)
	utSetDouble(tpu,names[i],UPOS_END,val);
}
void utAddDoubleByDir(utype* pu,double val,const char* name0,const char* name1,const char* name2,const char* name3,const char* name4,const char* name5,const char* name6,const char* name7,const char* name8,const char* name9)
{
	utype* tpu=pu;
	int i=0;
	const char* names[10];
	COUNT_LEV(tpu,i,names,name,NULL)
	utAddDouble(tpu,names[i],val);
}

void utSetStrByDir(utype* pu,const char* val,int occ0,int occ1,int occ2,int occ3,int occ4,int occ5,int occ6,int occ7,int occ8,int occ9)
{
	utype* tpu=pu;
	int i=0;
	int occs[10];
	COUNT_LEV(tpu,i,occs,occ,-1)
	utSetStr(tpu,occs[i],val);
}
void utSetStrByDir(utype* pu,const char* val,const char* name0,const char* name1,const char* name2,const char* name3,const char* name4,const char* name5,const char* name6,const char* name7,const char* name8,const char* name9)
{
	utype* tpu=pu;
	int i=0;
	const char* names[10];
	COUNT_LEV(tpu,i,names,name,NULL)
	utSetStr(tpu,names[i],UPOS_END,val);
}
void utAddStrByDir(utype* pu,const char* val,const char* name0,const char* name1,const char* name2,const char* name3,const char* name4,const char* name5,const char* name6,const char* name7,const char* name8,const char* name9)
{
	utype* tpu=pu;
	int i=0;
	const char* names[10];
	COUNT_LEV(tpu,i,names,name,NULL)
	utAddStr(tpu,names[i],val);
}

void utSetArrayByDir(utype* pu,utype* val,int occ0,int occ1,int occ2,int occ3,int occ4,int occ5,int occ6,int occ7,int occ8,int occ9)
{
	utype* tpu=pu;
	int i=0;
	int occs[10];
	COUNT_LEV(tpu,i,occs,occ,-1)
	utSetArray(tpu,occs[i],val);
}
void utSetArrayByDir(utype* pu,utype* val,const char* name0,const char* name1,const char* name2,const char* name3,const char* name4,const char* name5,const char* name6,const char* name7,const char* name8,const char* name9)
{
	utype* tpu=pu;
	int i=0;
	const char* names[10];
	COUNT_LEV(tpu,i,names,name,NULL)
	utSetArray(tpu,names[i],UPOS_END,val);
}
void utAddArrayByDir(utype* pu,utype* val,const char* name0,const char* name1,const char* name2,const char* name3,const char* name4,const char* name5,const char* name6,const char* name7,const char* name8,const char* name9)
{
	utype* tpu=pu;
	int i=0;
	const char* names[10];
	COUNT_LEV(tpu,i,names,name,NULL)
	utAddArray(tpu,names[i],val);
}

void utSetStructByDir(utype* pu,utype* val,int occ0,int occ1,int occ2,int occ3,int occ4,int occ5,int occ6,int occ7,int occ8,int occ9)
{
	utype* tpu=pu;
	int i=0;
	int occs[10];
	COUNT_LEV(tpu,i,occs,occ,-1)
	utSetStruct(tpu,occs[i],val);
}
void utSetStructByDir(utype* pu,utype* val,const char* name0,const char* name1,const char* name2,const char* name3,const char* name4,const char* name5,const char* name6,const char* name7,const char* name8,const char* name9)
{
	utype* tpu=pu;
	int i=0;
	const char* names[10];
	COUNT_LEV(tpu,i,names,name,NULL)
	utSetStruct(tpu,names[i],UPOS_END,val);
}
void utAddStructByDir(utype* pu,utype* val,const char* name0,const char* name1,const char* name2,const char* name3,const char* name4,const char* name5,const char* name6,const char* name7,const char* name8,const char* name9)
{
	utype* tpu=pu;
	int i=0;
	const char* names[10];
	COUNT_LEV(tpu,i,names,name,NULL)
	utAddStruct(tpu,names[i],val);
}

void utSetEmptyByDir(utype* pu,int occ0,int occ1,int occ2,int occ3,int occ4,int occ5,int occ6,int occ7,int occ8,int occ9)
{
	utype* tpu=pu;
	int i=0;
	int occs[10];
	COUNT_LEV(tpu,i,occs,occ,-1)
	utSetEmpty(tpu,occs[i]);
}

void utSetEmptyByDir(utype* pu,const char* name0,const char* name1,const char* name2,const char* name3,const char* name4,const char* name5,const char* name6,const char* name7,const char* name8,const char* name9)
{
	utype* tpu=pu;
	int i=0;
	const char* names[10];
	COUNT_LEV(tpu,i,names,name,NULL)
	utSetEmpty(tpu,names[i], UPOS_END);
}

void utAddEmptyByDir(utype* pu,const char* name0,const char* name1,const char* name2,const char* name3,const char* name4,const char* name5,const char* name6,const char* name7,const char* name8,const char* name9)
{
	utype* tpu=pu;
	int i=0;
	const char* names[10];
	COUNT_LEV(tpu,i,names,name,NULL)
	utAddEmpty(tpu,names[i]);
}


void utAddIntByPath(utype *pu, int val,const char *xpath)
{
	utype* tpu=pu;
	char name[30];

	tpu = (utype*)getUtypeByPath(tpu, xpath, name);
	utAddInt(tpu, name,val);
}

void utAddCharByPath(utype *pu, char val,const char *xpath)
{
	utype* tpu=pu;
	char name[30];

	tpu = (utype*)getUtypeByPath(tpu, xpath, name);
	utAddChar(tpu, name,val);
}

void utAddLongByPath(utype *pu, long val,const char *xpath)
{
	utype* tpu=pu;
	char name[30];

	tpu = (utype*)getUtypeByPath(tpu, xpath, name);
	utAddLong(tpu, name,val);
}

void utAddDoubleByPath(utype *pu, double val,const char *xpath)
{
	utype* tpu=pu;
	char name[30];

	tpu = (utype*)getUtypeByPath(tpu, xpath, name);
	utAddDouble(tpu, name,val);
}

void utAddStrByPath(utype *pu, const char* val,const char *xpath)
{
	utype* tpu=pu;
	char name[30];

	tpu = (utype*)getUtypeByPath(tpu, xpath, name);
	utAddStr(tpu, name,val);
}

void utAddStructByPath(utype *pu,utype *val, const char *xpath)
{
	utype* tpu=pu;
	char name[30];

	tpu = (utype*)getUtypeByPath(tpu, xpath, name);
	utAddStruct(tpu, name,val);
}

void utAddArrayByPath(utype *pu, utype *val,const char *xpath)
{
	utype* tpu=pu;
	char name[30];

	tpu = (utype*)getUtypeByPath(tpu, xpath, name);
	utAddArray(tpu, name,val);
}


void utSetIntByPath(utype *pu, int val,const char *xpath)
{
	utype* tpu=pu;
	char name[30];

	tpu = (utype*)getUtypeByPath(tpu, xpath, name);
	utSetInt(tpu, name,UPOS_END,val);
}

void utSetCharByPath(utype *pu, char val,const char *xpath)
{
	utype* tpu=pu;
	char name[30];

	tpu = (utype*)getUtypeByPath(tpu, xpath, name);
	utSetChar(tpu, name,UPOS_END,val);
}

void utSetLongByPath(utype *pu, long val,const char *xpath)
{
	utype* tpu=pu;
	char name[30];

	tpu = (utype*)getUtypeByPath(tpu, xpath, name);
	utSetLong(tpu, name,UPOS_END,val);
}

void utSetDoubleByPath(utype *pu, double val,const char *xpath)
{
	utype* tpu=pu;
	char name[30];

	tpu = (utype*)getUtypeByPath(tpu, xpath, name);
	utSetDouble(tpu, name,UPOS_END,val);
}

void utSetStrByPath(utype *pu, const char* val,const char *xpath)
{
	utype* tpu=pu;
	char name[30];

	tpu = (utype*)getUtypeByPath(tpu, xpath, name);
	utSetStr(tpu, name,UPOS_END,val);
}

void utSetStructByPath(utype *pu,utype *val, const char *xpath)
{
	utype* tpu=pu;
	char name[30];

	tpu = (utype*)getUtypeByPath(tpu, xpath, name);
	utSetStruct(tpu, name,UPOS_END,val);
}

void utSetArrayByPath(utype *pu, utype *val,const char *xpath)
{
	utype* tpu=pu;
	char name[30];

	tpu = (utype*)getUtypeByPath(tpu, xpath, name);
	utSetArray(tpu, name,UPOS_END,val);
}
uElement tagutype::operator [] (int i)  const {
	return uElement(this,i);
}

uElement tagutype::operator [] (const char* s) const  {
	return uElement(this,s);
}


#endif

