#ifndef __utype_h__
#define __utype_h__

#ifndef __WIN__
#define __FUNCTION__ __func__
#endif

/** $$$ ADD BY LGZ BEGIN**/
typedef struct tagUtypeInnerDebugLink
{
	void *pPtr;
	struct tagUtypeInnerDebugLink *next;
}TUtypeInnerDebugLink;


void SetDebugStatus(bool bIsDebugStatus);
TUtypeInnerDebugLink *GetUtypeInnerDebugLink();
/** $$$ ADD BY LGZ END **/


#include "xs.h"
#include <stdio.h>
#include <string.h>

#ifndef NULL
#define NULL 0
#endif

#define INIT_LENGTH 3

#define U_EMPTY 0
#define U_CHAR 1
#define U_INT 2
#define U_LONG 3
#define U_DOUBLE 4
#define U_STRING 5
#define U_ARRAY 6
#define U_STRUCT 7

#define U_BEGIN 1
#define U_NEXT 2
#define U_END 3

#define U_HASHNULL 255

#define U_ERR_NOMEM 1
#define U_ERR_NOOCC 2
#define U_ERR_WRONGTYPE 3
#define U_ERR_EMPTY 4
#define U_ERR_UPNULL 5

#define U_ERR_NAMECONFLICT 6
#define U_ERR_NAMENULL 7
#define U_ERR_HASHOVER 8


#define U_ERR_NAMELEN 9
#define U_ERR_UNFIND 10
#define U_ERR_TYPE	 11
#define U_ERR_MORE_TYPE 12

/******* 20090223 ********/
#define U_MAXNAMELEN 30
#define U_MAXLEVEL 10
/*************************/
/******** 20090312 ********/
#define U_HASHMOD 127
#define U_MAXHASHLEV 5
/**************************/
#define UPOS_END -1
extern long u_errno;
extern int iUtypeMallocTimes;

#ifdef __cplusplus
#include <string>
#include <exception>
#endif

typedef int UPOS;
typedef struct tagutype utype;
typedef struct tague{
	unsigned char type;
	union {
		char v_char;
		int v_int;
		long v_long;
		double v_double;
		char * p_char;
		utype * p_utype;
	} value;
//	char name[U_MAXNAMELEN];	//20090223
	short namePos;
	short nameListPre;
	short nameListNext;
} ue;

typedef struct tagidxNameItem{
	char name[U_MAXNAMELEN];	//20090223
	short idxNameFree;
	short nameListFirst;
} idxNameItem;


class uElement;
struct tagutype{
	unsigned short cnt;
	unsigned short capacity;
	ue **ppe;

	unsigned char idxKey[U_HASHMOD][U_MAXHASHLEV];	//20090312

	unsigned char nameCap;
	short idxNameFree;
	idxNameItem* idxName;
uElement operator [] (int i)  const;
uElement operator [] (const char* s) const  ;
};

typedef struct tagCtrlInfo
{
	/*错误代码，错误信息*/
	char	retCode[20+1];
	char	retMsg[2048];

	/*信息代码，信息内容*/
	char	infoCode[20+1];
	char	infoMsg[2048];
	long    lErrCode;
	int     iSqlRows;

	int  cursorCtrl;
} TCtrlInfo;


/**
 * 函数成功执行返回0
 */
typedef unsigned long  (*TFuncBusiness)(utype *uInParam,utype **uOutParam,TCtrlInfo *ctrlInfo);
typedef utype* (*TUtypeFuncPtr)(const utype *uInParam, TCtrlInfo *ctrlInfo);
typedef unsigned long (*TUtypeFuncLong)(utype *uInParam, TCtrlInfo *ctrlInfo);

/*不成功返回NULL*/
utype* uInit(int capacity);	/*创建统一数据结构， capacity 初始元素个数 */
utype* _uInit(int capacity, long *plRet);	/*创建统一数据结构， capacity 初始元素个数 */

/*不成功返回NULL*/
utype * uSetInt(utype *pu,int occ,int iv);	/*存int值，pu 统一数据结构指针，occ 元素位置，iv 输入值*/
utype * _uSetInt(utype *pu,int occ,int iv, long *plRet);	/*存int值，pu 统一数据结构指针，occ 元素位置，iv 输入值*/

int uGetInt(const utype *pu,int occ);	/*读int值，pu 统一数据结构指针，occ 元素位置，返回int值*/
int _uGetInt(const utype *pu,int occ, long *plRet);	/*读int值，pu 统一数据结构指针，occ 元素位置，返回int值*/

/*不成功返回NULL*/
utype * uSetChar(utype *pu,int occ,char iv);
utype * _uSetChar(utype *pu,int occ,char iv, long *plRet);

char uGetChar(const utype *pu,int occ);
char _uGetChar(const utype *pu,int occ, long *plRet);

/*不成功返回NULL*/
utype * uSetLong(utype *pu,int occ,long iv);	/*存long值，pu 统一数据结构指针，occ 元素位置，iv 输入值*/
utype * _uSetLong(utype *pu,int occ,long iv, long *plRet);	/*存long值，pu 统一数据结构指针，occ 元素位置，iv 输入值*/

long uGetLong(const utype *pu,int occ);	/*读long值，pu 统一数据结构指针，occ 元素位置，返回long值*/
long _uGetLong(const utype *pu,int occ, long *plRet);	/*读long值，pu 统一数据结构指针，occ 元素位置，返回long值*/

/*不成功返回NULL*/
utype * uSetDouble(utype *pu,int occ,double iv);	/*存double值，pu 统一数据结构指针，occ 元素位置，iv 输入值*/
utype * _uSetDouble(utype *pu,int occ,double iv, long *plRet);	/*存double值，pu 统一数据结构指针，occ 元素位置，iv 输入值*/

double uGetDouble(const utype *pu,int occ);	/*读long值，pu 统一数据结构指针，occ 元素位置，返回long值*/
double _uGetDouble(const utype *pu,int occ, long *plRet);	/*读long值，pu 统一数据结构指针，occ 元素位置，返回long值*/

/*不成功返回NULL*/
utype * uSetStr(utype *pu,int occ,const char * iv);	/*存字符串，pu 统一数据结构指针，occ 元素位置，iv 输入值*/
utype * _uSetStr(utype *pu,int occ,const char * iv, long *plRet);	/*存字符串，pu 统一数据结构指针，occ 元素位置，iv 输入值*/

char * uGetStr(const utype *pu,int occ);	/*读字符串，pu 统一数据结构指针，occ 元素位置，返回字符串*/
char * _uGetStr(const utype *pu,int occ, long *plRet);	/*读字符串，pu 统一数据结构指针，occ 元素位置，返回字符串*/

/*不成功返回NULL*/
utype * uSetArray(utype *pu,int occ,utype * iv);	/*存数组，pu 统一数据结构指针，occ 元素位置，iv 输入值*/
utype * _uSetArray(utype *pu,int occ,utype * iv, long *plRet);	/*存数组，pu 统一数据结构指针，occ 元素位置，iv 输入值*/

/*不成功返回NULL*/
const utype * uGetArray(const utype *pu,int occ);	/*读数组，pu 统一数据结构指针，occ 元素位置，返回数组（统一数据结构指针）*/
const utype * _uGetArray(const utype *pu,int occ, long *plRet);	/*读数组，pu 统一数据结构指针，occ 元素位置，返回数组（统一数据结构指针）*/

/*不成功返回NULL*/
utype * uSetStruct(utype *pu,int occ,utype * iv);	/*存结构，pu 统一数据结构指针，occ 元素位置，iv 输入值*/
utype * _uSetStruct(utype *pu,int occ,utype * iv, long *plRet);	/*存结构，pu 统一数据结构指针，occ 元素位置，iv 输入值*/

const utype* uGetStruct(const utype *pu,int occ);	/*读结构，pu 统一数据结构指针，occ 元素位置，返回结构（统一数据结构指针）*/
const utype* _uGetStruct(const utype *pu,int occ, long *plRet);	/*读结构，pu 统一数据结构指针，occ 元素位置，返回结构（统一数据结构指针）*/

utype * uSetEmpty(utype *pu,int occ);
utype * _uSetEmpty(utype *pu,int occ, long *plRet);

int uGetEmpty(const utype *pu,int occ);
int _uGetEmpty(const utype *pu,int occ, long *plRet);

//void uMove(utype *tpu,int tocc,utype * fpu,int focc);
utype * uClone(const utype *pu);

/*不成功返回NULL*/
utype* uAlloc(utype *pu,int occ, long *plRet);
idxNameItem* uNameAlloc(utype* pu);
void uFree(utype *pu);
void ueFree(ue *pue);

#ifdef __cplusplus

int uPackLen(const utype *pu);	/* 计算utype序列化包长度 */
int _uPack(const utype *pu,char **upack); /* utype序列化组包 返回序列化包长度 */
int uPack(const utype *pu,char *upack); /* utype序列化组包 返回序列化包长度 */
int _uUnpack(char **upack,utype **upp); /* utype序列化解包 */
int uUnpack(char *upack,utype **upp); /* utype序列化解包 */

void PrintLevel(int iLevel);
//void PrintUtype(const utype *pu, int iLevel);

char* uUType2Xml(const utype *pu,const char* rootName);
char* uUType2Xml_noType(const utype *pu,const char* rootName);
utype* uXml2Utype(const char* xmlbuf);
utype* uXml2UtypeStr(const char* xmlbuf);
const utype* getUtypeByPath(const utype* pu, const char* xpath, char* name);

class appException : public std::exception{
public:
	long errCode;
	char errMsg[2047+1];

	appException(long iErrCode,const char* iErrMsg)
	:errCode(iErrCode){
		memset(errMsg, 0, sizeof(errMsg));
		strncpy(errMsg, iErrMsg, 2047);
	}
	appException(long iErrCode,const char* nodename, const char* iErrMsg)
	:errCode(iErrCode){
		memset(errMsg, 0, sizeof(errMsg));
		snprintf(errMsg, 2047, "节点[%s]处错误:%s", nodename, iErrMsg);
	}
	appException(long iErrCode,const char* fmt, const char* iErrMsg, const  char* errmsg2)
	:errCode(iErrCode){
		memset(errMsg, 0, sizeof(errMsg));
		snprintf(errMsg, 2047, fmt, iErrMsg, errmsg2);
	}
	virtual const char* what() const throw()
	{
		return errMsg;
	}
};



class uException : public appException{
public:
	uException(long iErrCode,const char* iErrMsg)
	:appException(iErrCode,iErrMsg){
	}
	uException(long iErrCode,const char* nodename, const char* iErrMsg)
	:appException(iErrCode,nodename,iErrMsg){
	}
};



struct uAutoPtrRef{
	utype* yp;
	uAutoPtrRef(utype* rhs)
	: yp(rhs) { }
};


bool utIsTrue(const utype* pu,const char* name);
bool utIsTrue(const utype* pu,const char* name,const int value);
bool utIsTrue(const utype* pu,const char* name,const char *value);
bool utIsTrue(const utype* pu,const char* name,const long value);


UPOS utFind(const utype* pu,const char* name);
UPOS utNext(const utype* pu,UPOS beginPos);

//void utSetInt(utype* pu,int occ,int iv);
void utSetInt(utype* pu,int occ,int iv);
int utAddInt(utype* pu,const char* name,int iv);
void utSetInt(utype* pu,const char* name,UPOS pos,int iv);

//int utGetInt(utype* pu,int occ);
int utGetInt(const utype* pu,int occ,char* name=NULL);
int utGetInt(const utype* pu,const char* name,int* pocc=NULL);
int utGetInt(const utype* pu,const char* name,UPOS pos,int* pocc=NULL);

int utGetIntByDir(const utype* pu,int occ0,int occ1=-1,int occ2=-1,int occ3=-1,int occ4=-1,int occ5=-1,int occ6=-1,int occ7=-1,int occ8=-1,int occ9=-1);

int utGetIntByDir(const utype* pu,const char* name0,const char* name1=NULL,const char* name2=NULL,const char* name3=NULL,const char* name4=NULL,const char* name5=NULL,const char* name6=NULL,const char* name7=NULL,const char* name8=NULL,const char* name9=NULL);

//void utSetChar(utype* pu,int occ,char iv);
void utSetChar(utype* pu,int occ,char iv);
int utAddChar(utype* pu,const char* name,char iv);
void utSetChar(utype* pu,const char* name,UPOS pos,char iv);

//char utGetChar(utype* pu,int occ);
char utGetChar(const utype* pu,int occ,char* name=NULL);
char utGetChar(const utype* pu,const char* name,int* pocc=NULL);
char utGetChar(const utype* pu,const char* name,UPOS pos,int* pocc=NULL);

char utGetCharByDir(const utype* pu,int occ0,int occ1=-1,int occ2=-1,int occ3=-1,int occ4=-1,int occ5=-1,int occ6=-1,int occ7=-1,int occ8=-1,int occ9=-1);

char utGetCharByDir(const utype* pu,const char* name0,const char* name1=NULL,const char* name2=NULL,const char* name3=NULL,const char* name4=NULL,const char* name5=NULL,const char* name6=NULL,const char* name7=NULL,const char* name8=NULL,const char* name9=NULL);

//void utSetLong(utype* pu,int occ,long iv);
void utSetLong(utype* pu,int occ,long iv);
int utAddLong(utype* pu,const char* name,long iv);
void utSetLong(utype* pu,const char* name,UPOS pos,long iv);

//long utGetLong(utype* pu,int occ);
long utGetLong(const utype* pu,int occ,char* name=NULL);
long utGetLong(const utype* pu,const char* name,int* pocc=NULL);
long utGetLong(const utype* pu,const char* name,UPOS pos,int* pocc=NULL);

long utGetLongByDir(const utype* pu,int occ0,int occ1=-1,int occ2=-1,int occ3=-1,int occ4=-1,int occ5=-1,int occ6=-1,int occ7=-1,int occ8=-1,int occ9=-1);

long utGetLongByDir(const utype* pu,const char* name0,const char* name1=NULL,const char* name2=NULL,const char* name3=NULL,const char* name4=NULL,const char* name5=NULL,const char* name6=NULL,const char* name7=NULL,const char* name8=NULL,const char* name9=NULL);

//void utSetDouble(utype* pu,int occ,double iv);
void utSetDouble(utype* pu,int occ,double iv);
int utAddDouble(utype* pu,const char* name,double iv);
void utSetDouble(utype* pu,const char* name,UPOS pos,double iv);

//double utGetDouble(utype* pu,int occ);
double utGetDouble(const utype* pu,int occ,char* name=NULL);
double utGetDouble(const utype* pu,const char* name,int* pocc=NULL);
double utGetDouble(const utype* pu,const char* name,UPOS pos,int* pocc=NULL);

double utGetDoubleByDir(const utype* pu,int occ0,int occ1=-1,int occ2=-1,int occ3=-1,int occ4=-1,int occ5=-1,int occ6=-1,int occ7=-1,int occ8=-1,int occ9=-1);

double utGetDoubleByDir(const utype* pu,const char* name0,const char* name1=NULL,const char* name2=NULL,const char* name3=NULL,const char* name4=NULL,const char* name5=NULL,const char* name6=NULL,const char* name7=NULL,const char* name8=NULL,const char* name9=NULL);

//void utSetStr(utype* pu,int occ,const char * iv);
void utSetStr(utype* pu,int occ,const char* iv);
int utAddStr(utype* pu,const char* name,const char* iv);
void utSetStr(utype* pu,const char* name,UPOS pos,const char* iv);

//char * utGetStr(utype* pu,int occ);
char* utGetStr(const utype* pu,int occ,char* name=NULL);
char* utGetStr(const utype* pu,const char* name,int* pocc=NULL);
char* utGetStr(const utype* pu,const char* name,UPOS pos,int* pocc=NULL);

char* utGetStrByDir(const utype* pu,int occ0,int occ1=-1,int occ2=-1,int occ3=-1,int occ4=-1,int occ5=-1,int occ6=-1,int occ7=-1,int occ8=-1,int occ9=-1);

char* utGetStrByDir(const utype* pu,const char* name0,const char* name1=NULL,const char* name2=NULL,const char* name3=NULL,const char* name4=NULL,const char* name5=NULL,const char* name6=NULL,const char* name7=NULL,const char* name8=NULL,const char* name9=NULL);

//void utSetArray(utype* pu,int occ,utype * iv);
void utSetArray(utype* pu,int occ,utype* iv);
int utAddArray(utype* pu,const char* name,utype* iv);
void utSetArray(utype* pu,const char* name,UPOS pos,utype* iv);

//utype* utGetArray(utype* pu,int occ);
const utype* utGetArray(const utype* pu,int occ,char* name=NULL);
const utype* utGetArray(const utype* pu,const char* name,int* pocc=NULL);
const utype* utGetArray(const utype* pu,const char* name,UPOS pos,int* pocc=NULL);

const utype* utGetArrayByDir(const utype* pu,int occ0,int occ1=-1,int occ2=-1,int occ3=-1,int occ4=-1,int occ5=-1,int occ6=-1,int occ7=-1,int occ8=-1,int occ9=-1);

const utype* utGetArrayByDir(const utype* pu,const char* name0,const char* name1=NULL,const char* name2=NULL,const char* name3=NULL,const char* name4=NULL,const char* name5=NULL,const char* name6=NULL,const char* name7=NULL,const char* name8=NULL,const char* name9=NULL);

//void utSetStruct(utype* pu,int occ,utype * iv);
void utSetStruct(utype* pu,int occ,utype* iv);
int utAddStruct(utype* pu,const char* name,utype* iv);
void utSetStruct(utype* pu,const char* name,UPOS pos,utype* iv);

//utype* utGetStruct(utype *pu,int occ);
const utype* utGetStruct(const utype* pu,int occ,char* name=NULL);
const utype* utGetStruct(const utype* pu,const char* name,int* pocc=NULL);
const utype* utGetStruct(const utype* pu,const char* name,UPOS pos,int* pocc=NULL);

const utype* utGetStructByDir(const utype* pu,int occ0,int occ1=-1,int occ2=-1,int occ3=-1,int occ4=-1,int occ5=-1,int occ6=-1,int occ7=-1,int occ8=-1,int occ9=-1);

const utype* utGetStructByDir(const utype* pu,const char* name0,const char* name1=NULL,const char* name2=NULL,const char* name3=NULL,const char* name4=NULL,const char* name5=NULL,const char* name6=NULL,const char* name7=NULL,const char* name8=NULL,const char* name9=NULL);

//void utSetEmpty(utype* pu,int occ);
void utSetEmpty(utype* pu,int occ);
int utAddEmpty(utype* pu,const char* name);
void utSetEmpty(utype* pu,const char* name,UPOS pos);

//int utGetEmpty(utype *pu,int occ);
int utGetEmpty(const utype* pu,int occ,char* name=NULL);
int utGetEmpty(const utype* pu,const char* name,int* pocc=NULL);
int utGetEmpty(const utype* pu,const char* name,UPOS pos,int* pocc=NULL);

int utGetEmptyByDir(const utype* pu,int occ0,int occ1=-1,int occ2=-1,int occ3=-1,int occ4=-1,int occ5=-1,int occ6=-1,int occ7=-1,int occ8=-1,int occ9=-1);

int utGetEmptyByDir(const utype* pu,const char* name0,const char* name1=NULL,const char* name2=NULL,const char* name3=NULL,const char* name4=NULL,const char* name5=NULL,const char* name6=NULL,const char* name7=NULL,const char* name8=NULL,const char* name9=NULL);

utype * utClone(const utype *pu);

//void utMove(utype *tpu,int tocc,utype* fpu,int focc);
//
////分离指定位置的节点，并返回该节点的指针。
//utype* utApart(utype *pu, int occ);
//utype* utApart(utype *pu, const char* name);

//void utRename(utype*,int occ,const char* nname);
void utRename(utype*,const char* oname,const char* nname);

const char* utGetName(const utype* pu,int occ);
int utGetType(const utype* pu,const char* name);

int utGetIntByPath(const utype *pu,  const char *xpath);
char utGetCharByPath(const utype *pu,  const char *xpath);
long utGetLongByPath(const utype *pu,  const char *xpath);
double utGetDoubleByPath(const utype *pu,  const char *xpath);
char* utGetStrByPath(const utype *pu, const char *xpath);


void utSetIntByDir(utype* pu,int val,int occ0,int occ1=-1,int occ2=-1,int occ3=-1,int occ4=-1,int occ5=-1,int occ6=-1,int occ7=-1,int occ8=-1,int occ9=-1);
void utAddIntByDir(utype* pu,int val,const char* name0,const char* name1=NULL,const char* name2=NULL,const char* name3=NULL,const char* name4=NULL,const char* name5=NULL,const char* name6=NULL,const char* name7=NULL,const char* name8=NULL,const char* name9=NULL);
void utSetCharByDir(utype* pu,char val,int occ0,int occ1=-1,int occ2=-1,int occ3=-1,int occ4=-1,int occ5=-1,int occ6=-1,int occ7=-1,int occ8=-1,int occ9=-1);
void utAddCharByDir(utype* pu,char val,const char* name0,const char* name1=NULL,const char* name2=NULL,const char* name3=NULL,const char* name4=NULL,const char* name5=NULL,const char* name6=NULL,const char* name7=NULL,const char* name8=NULL,const char* name9=NULL);
void utSetLongByDir(utype* pu,long val,int occ0,int occ1=-1,int occ2=-1,int occ3=-1,int occ4=-1,int occ5=-1,int occ6=-1,int occ7=-1,int occ8=-1,int occ9=-1);
void utAddLongByDir(utype* pu,long val,const char* name0,const char* name1=NULL,const char* name2=NULL,const char* name3=NULL,const char* name4=NULL,const char* name5=NULL,const char* name6=NULL,const char* name7=NULL,const char* name8=NULL,const char* name9=NULL);
void utSetDoubleByDir(utype* pu,double val,int occ0,int occ1=-1,int occ2=-1,int occ3=-1,int occ4=-1,int occ5=-1,int occ6=-1,int occ7=-1,int occ8=-1,int occ9=-1);
void utAddDoubleByDir(utype* pu,double val,const char* name0,const char* name1=NULL,const char* name2=NULL,const char* name3=NULL,const char* name4=NULL,const char* name5=NULL,const char* name6=NULL,const char* name7=NULL,const char* name8=NULL,const char* name9=NULL);
void utSetStrByDir(utype* pu,const char* val,int occ0,int occ1=-1,int occ2=-1,int occ3=-1,int occ4=-1,int occ5=-1,int occ6=-1,int occ7=-1,int occ8=-1,int occ9=-1);
void utAddStrByDir(utype* pu,const char* val,const char* name0,const char* name1=NULL,const char* name2=NULL,const char* name3=NULL,const char* name4=NULL,const char* name5=NULL,const char* name6=NULL,const char* name7=NULL,const char* name8=NULL,const char* name9=NULL);
void utSetArrayByDir(utype* pu,utype* val,int occ0,int occ1=-1,int occ2=-1,int occ3=-1,int occ4=-1,int occ5=-1,int occ6=-1,int occ7=-1,int occ8=-1,int occ9=-1);
void utAddArrayByDir(utype* pu,utype* val,const char* name0,const char* name1=NULL,const char* name2=NULL,const char* name3=NULL,const char* name4=NULL,const char* name5=NULL,const char* name6=NULL,const char* name7=NULL,const char* name8=NULL,const char* name9=NULL);
void utSetStructByDir(utype* pu,utype* val,int occ0,int occ1=-1,int occ2=-1,int occ3=-1,int occ4=-1,int occ5=-1,int occ6=-1,int occ7=-1,int occ8=-1,int occ9=-1);
void utAddStructByDir(utype* pu,utype* val,const char* name0,const char* name1=NULL,const char* name2=NULL,const char* name3=NULL,const char* name4=NULL,const char* name5=NULL,const char* name6=NULL,const char* name7=NULL,const char* name8=NULL,const char* name9=NULL);
void utSetEmptyByDir(utype* pu,int occ0,int occ1=-1,int occ2=-1,int occ3=-1,int occ4=-1,int occ5=-1,int occ6=-1,int occ7=-1,int occ8=-1,int occ9=-1);
void utAddEmptyByDir(utype* pu,const char* name0,const char* name1=NULL,const char* name2=NULL,const char* name3=NULL,const char* name4=NULL,const char* name5=NULL,const char* name6=NULL,const char* name7=NULL,const char* name8=NULL,const char* name9=NULL);
void utSetIntByDir(utype* pu,int val,const char* name0,const char* name1=NULL,const char* name2=NULL,const char* name3=NULL,const char* name4=NULL,const char* name5=NULL,const char* name6=NULL,const char* name7=NULL,const char* name8=NULL,const char* name9=NULL);
void utSetCharByDir(utype* pu,char val,const char* name0,const char* name1=NULL,const char* name2=NULL,const char* name3=NULL,const char* name4=NULL,const char* name5=NULL,const char* name6=NULL,const char* name7=NULL,const char* name8=NULL,const char* name9=NULL);
void utSetLongByDir(utype* pu,long val,const char* name0,const char* name1=NULL,const char* name2=NULL,const char* name3=NULL,const char* name4=NULL,const char* name5=NULL,const char* name6=NULL,const char* name7=NULL,const char* name8=NULL,const char* name9=NULL);
void utSetDoubleByDir(utype* pu,double val,const char* name0,const char* name1=NULL,const char* name2=NULL,const char* name3=NULL,const char* name4=NULL,const char* name5=NULL,const char* name6=NULL,const char* name7=NULL,const char* name8=NULL,const char* name9=NULL);
void utSetStrByDir(utype* pu,const char* val,const char* name0,const char* name1=NULL,const char* name2=NULL,const char* name3=NULL,const char* name4=NULL,const char* name5=NULL,const char* name6=NULL,const char* name7=NULL,const char* name8=NULL,const char* name9=NULL);
void utSetArrayByDir(utype* pu,utype* val,const char* name0,const char* name1=NULL,const char* name2=NULL,const char* name3=NULL,const char* name4=NULL,const char* name5=NULL,const char* name6=NULL,const char* name7=NULL,const char* name8=NULL,const char* name9=NULL);
void utSetStructByDir(utype* pu,utype* val,const char* name0,const char* name1=NULL,const char* name2=NULL,const char* name3=NULL,const char* name4=NULL,const char* name5=NULL,const char* name6=NULL,const char* name7=NULL,const char* name8=NULL,const char* name9=NULL);
void utSetEmptyByDir(utype* pu,const char* name0,const char* name1=NULL,const char* name2=NULL,const char* name3=NULL,const char* name4=NULL,const char* name5=NULL,const char* name6=NULL,const char* name7=NULL,const char* name8=NULL,const char* name9=NULL);

void utSetIntByPath(utype *pu, int val,const char *xpath);
void utSetCharByPath(utype *pu, char val,const char *xpath);
void utSetLongByPath(utype *pu, long val,const char *xpath);
void utSetDoubleByPath(utype *pu, double val,const char *xpath);
void utSetStrByPath(utype *pu, const char* val,const char *xpath);
void utSetStructByPath(utype *pu,utype *val, const char *xpath);
void utSetArrayByPath(utype *pu, utype *val,const char *xpath);
void utAddIntByPath(utype *pu, int val,const char *xpath);
void utAddCharByPath(utype *pu, char val,const char *xpath);
void utAddLongByPath(utype *pu, long val,const char *xpath);
void utAddDoubleByPath(utype *pu, double val,const char *xpath);
void utAddStrByPath(utype *pu, const char* val,const char *xpath);
void utAddStructByPath(utype *pu,utype *val, const char *xpath);
void utAddArrayByPath(utype *pu, utype *val,const char *xpath);
#endif

/*无参数*/
#define UT_ARG_FLAG_NULL

/*对uInit函数的封装*/
#define UT_Init(uRetValue, iCapacity, iRet, ERR_HANDLER, eArgFlag) \
{ \
	if ( (uRetValue = _uInit(iCapacity, &iRet)) == NULL) \
	{ \
		ERR_HANDLER; \
	} \
}

#define UT_SetChar(uStoreDesc, iOcc, cValue, iRet, ERR_HANDLER, eArgFlag) \
{ \
	if (_uSetChar(uStoreDesc, iOcc, cValue, &iRet)== NULL) \
	{ \
		ERR_HANDLER; \
	} \
}

#define UT_SetInt(uStoreDesc, iOcc, iValue, iRet, ERR_HANDLER, eArgFlag) \
{ \
	if (_uSetInt(uStoreDesc, iOcc, iValue, &iRet)== NULL) \
	{ \
		ERR_HANDLER; \
	} \
}

#define UT_SetLong(uStoreDesc, iOcc, lValue, iRet, ERR_HANDLER, eArgFlag) \
{ \
	if (_uSetLong(uStoreDesc, iOcc, lValue, &iRet)== NULL) \
	{ \
		ERR_HANDLER; \
	} \
}

#define UT_SetDouble(uStoreDesc, iOcc, dValue, iRet, ERR_HANDLER, eArgFlag) \
{ \
	if (_uSetDouble(uStoreDesc, iOcc, dValue, &iRet)== NULL) \
	{ \
		ERR_HANDLER; \
	} \
}

#define UT_SetStr(uStoreDesc, iOcc, psValue, iRet, ERR_HANDLER, eArgFlag) \
{ \
	if (_uSetStr(uStoreDesc, iOcc, psValue, &iRet)== NULL) \
	{ \
		ERR_HANDLER; \
	} \
}

#define UT_SetArray(uStoreDesc, iOcc, ptValue, iRet, ERR_HANDLER, eArgFlag) \
{ \
	if (_uSetArray(uStoreDesc, iOcc, ptValue, &iRet)== NULL) \
	{ \
		ERR_HANDLER; \
	} \
}

#define UT_SetStruct(uStoreDesc,iOcc, ptValue, iRet, ERR_HANDLER, eArgFlag) \
{ \
	if (_uSetStruct(uStoreDesc, iOcc, ptValue, &iRet)== NULL) \
	{ \
		ERR_HANDLER; \
	} \
}

#define UT_SetEmpty(uStoreDesc,iOcc, iRet, ERR_HANDLER, eArgFlag) \
{ \
	if (_uSetEmpty(uStoreDesc, iOcc, &iRet)== NULL) \
	{ \
		ERR_HANDLER; \
	} \
}

#define UT_GetChar(cRetValue,uStoreDesc, iOcc, iRet, ERR_HANDLER, eArgFlag) \
{ \
	cRetValue = _uGetChar(uStoreDesc, iOcc, &iRet); \
	if ((iRet != 0)) \
	{ \
		ERR_HANDLER; \
	} \
}

#define UT_GetInt(iRetValue,uStoreDesc, iOcc, iRet, ERR_HANDLER, eArgFlag) \
{ \
	iRetValue = _uGetInt(uStoreDesc, iOcc, &iRet); \
	if ((iRet != 0)) \
	{ \
		ERR_HANDLER; \
	} \
}

#define UT_GetLong(lRetValue,uStoreDesc, iOcc, iRet, ERR_HANDLER, eArgFlag) \
{ \
	lRetValue = _uGetLong(uStoreDesc, iOcc, &iRet); \
	if ((iRet != 0)) \
	{ \
		ERR_HANDLER; \
	} \
}

#define UT_GetDouble(dRetValue,uStoreDesc, iOcc, iRet, ERR_HANDLER, eArgFlag) \
{ \
	dRetValue = _uGetDouble(uStoreDesc, iOcc, &iRet); \
	if ((iRet != 0)) \
	{ \
		ERR_HANDLER; \
	} \
}

#define UT_GetStr(psRetValue,uStoreDesc, iOcc, iRet, ERR_HANDLER, eArgFlag) \
{ \
	strcpy(psRetValue,_uGetStr(uStoreDesc, iOcc, &iRet)); \
	if ((iRet != 0)) \
	{ \
		ERR_HANDLER; \
	} \
}

#define UT_GetArray(paRetValue,uStoreDesc, iOcc, iRet, ERR_HANDLER, eArgFlag) \
{ \
	paRetValue = _uGetArray(uStoreDesc, iOcc, &iRet); \
	if ((iRet != 0)) \
	{ \
		ERR_HANDLER; \
	} \
}

#define UT_GetStruct(ptRetValue,uStoreDesc, iOcc, iRet, ERR_HANDLER, eArgFlag) \
{ \
	ptRetValue = _uGetStruct(uStoreDesc, iOcc, &iRet); \
	if ((iRet != 0)) \
	{ \
		ERR_HANDLER; \
	} \
}

#define UT_GetEmpty(ptRetValue,uStoreDesc, iOcc, iRet, ERR_HANDLER, eArgFlag) \
{ \
	ptRetValue = _uGetEmpty(uStoreDesc, iOcc, &iRet); \
	if ((iRet != 0)) \
	{ \
		ERR_HANDLER; \
	} \
}




class uAutoPtr {
private:
	utype* ap;    //refers to the actual owned object (if any)

public:
	//constructor
	explicit uAutoPtr (utype* ptr = 0) throw()
	: ap(ptr) {
	}


	//copy constructors (with implicit conversion)
	//- note: nonconstant parameter
	uAutoPtr (uAutoPtr& rhs) throw()
	: ap (rhs. release()) {
	}

	//assignments (with implicit conversion)
	//- note: nonconstant parameter
	uAutoPtr& operator= (uAutoPtr& rhs) throw() {
		reset(rhs.release());
		return *this;
	}

	//destructor
	~uAutoPtr() throw() {
		uFree(ap);
	}

	//value access
	utype* get() const throw() {
		return ap;
	}
	utype& operator*() const throw() {
		return *ap;
	}
	utype* operator->() const throw() {
		return ap;
	}


	//release ownership
	utype* release() throw() {
		utype* tmp(ap);
		ap = 0;
		return tmp;
	}


	//reset value
	void reset (utype* ptr=0) throw(){
		if (ap != ptr) {
			uFree(ap);
			ap = ptr;
		}
	}


	/* special conversions with auxiliary type to enable copies and assignments
	*/

	uAutoPtr(uAutoPtrRef rhs) throw()
	: ap(rhs.yp) {
	}

	uAutoPtr& operator= (uAutoPtrRef rhs) throw() { //new
		reset(rhs.yp);
		return *this;
	}

	operator uAutoPtrRef() throw() {
		return uAutoPtrRef(release());
	}

	operator uAutoPtr() throw() {
		return uAutoPtr(release());
	}

	operator utype* () const throw() {
		return ap;
	}

};




class uElement{
	private :
		const utype* p;
		int pos;
		const char* name;
		uElement (const utype* ap, int i) throw()
		: p(ap)
		,pos(i)
		,name(NULL){
		}
		uElement (const utype* ap, const char* va) throw()
		: p(ap)
		,pos(UPOS_END)
		,name(va){
		}

	public:
	friend struct tagutype;
	uElement& operator= (uElement& value) { //new
		unsigned char type;
		if(value.name){
			type=utGetType(value.p,value.name);
		}else{
			type=value.p->ppe[value.pos]->type;
		}
		switch(type){
			case U_CHAR:
				char c;
				if(value.name) c=utGetChar(value.p,value.name);
				else c=utGetChar(value.p,value.pos);
				if(name) utAddChar((utype*)p,name,c);
				else utSetChar((utype*)p,pos,c);
				break;


			case U_INT:
				int i;
				if(value.name) i=utGetInt(value.p,value.name);
				else i=utGetInt(value.p,value.pos);
				if(name) utAddInt((utype*)p,name,i);
				else utSetInt((utype*)p,pos,i);
				break;


			case U_LONG:
				long l;
				if(value.name) l=utGetLong(value.p,value.name);
				else l=utGetLong(value.p,value.pos);
				if(name) utAddLong((utype*)p,name,l);
				else utSetLong((utype*)p,pos,l);
				break;

			case U_DOUBLE:
				double d;
				if(value.name) d=utGetDouble(value.p,value.name);
				else d=utGetDouble(value.p,value.pos);
				if(name) utAddDouble((utype*)p,name,d);
				else utSetDouble((utype*)p,pos,d);
				break;

			case U_STRING:
				const char* s;
				if(value.name) s=utGetStr(value.p,value.name);
				else s=utGetStr(value.p,value.pos);
				if(name) utAddStr((utype*)p,name,s);
				else utSetStr((utype*)p,pos,s);
				break;

			case U_ARRAY:{
				uAutoPtr u;
				if(value.name) u=uClone(utGetArray(value.p,value.name));
				else u=uClone(utGetArray(value.p,value.pos));
				if(name) utAddArray((utype*)p,name,u.release());
				else utSetArray((utype*)p,pos,u.release());
				break;
			}
			case U_STRUCT:{
				uAutoPtr up;
				if(value.name) up=uClone(utGetStruct(value.p,value.name));
				else up=uClone(utGetStruct(value.p,value.pos));
				if(name) utAddStruct((utype*)p,name,up.release());
				else utSetStruct((utype*)p,pos,up.release());
				break;
			}
			default:{
				char errMsg[80];
				sprintf(errMsg,"%s错误,读取[%s]元素类型不匹配！",__FUNCTION__,name);
				throw(uException(U_ERR_WRONGTYPE,errMsg));
				}
		}
		return *this;
	}
	uElement& operator= (int value) {
		if(name){
			utAddInt((utype*)p,name,value);
		}else{
			utSetInt((utype*)p,pos,value);
		}
		return *this;
	}
	uElement& operator= (char value) {
		if(name){
			utAddChar((utype*)p,name,value);
		}else{
			utSetChar((utype*)p,pos,value);
		}
		return *this;
	}
	uElement& operator= (long value) {
		if(name){
			utAddLong((utype*)p,name,value);
		}else{
			utSetLong((utype*)p,pos,value);
		}
		return *this;
	}
	uElement& operator= (double value) {
		if(name){
			utAddDouble((utype*)p,name,value);
		}else{
			utSetDouble((utype*)p,pos,value);
		}
		return *this;
	}
	uElement& operator= (const char* value) {
		if(name){
			utAddStr((utype*)p,name,value);
		}else{
			utSetStr((utype*)p,pos,value);
		}
		return *this;
	}
	uElement& operator= (utype* value) {
		if(name){
			utAddStruct((utype*)p,name,value);
		}else{
			utSetStruct((utype*)p,pos,value);
		}
		return *this;
	}
	uElement& operator= (utype& value) {
		if(name){
			utAddStruct((utype*)p,name,&value);
		}else{
			utSetStruct((utype*)p,pos,&value);
		}
		return *this;
	}
	uElement operator[] (const char* s) {
		if(name){
			this->p=utGetStruct(p,name);
		}else{
			this->p=utGetStruct(p,pos);
		}
		name=s;
		pos=UPOS_END;
		return *this;
	}
	uElement operator[] (int w) {
		if(name){
			this->p=utGetStruct(p,name);
		}else{
			this->p=utGetStruct(p,pos);
		}
		name=NULL;
		pos=w;
		return *this;
	}
	operator int() {
		if(name){
			return utGetInt(p,name);
		}else{
			return utGetInt(p,pos);
		}
	}
	operator long() {
		if(name){
			return utGetLong(p,name);
		}else{
			return utGetLong(p,pos);
		}
	}
	operator double() {
		if(name){
			return utGetDouble(p,name);
		}else{
			return utGetDouble(p,pos);
		}
	}
	operator char*() {
		if(name){
			return utGetStr(p,name);
		}else{
			return utGetStr(p,pos);
		}
	}
	operator const utype*() {
		if(name){
			if(utGetType(p,name)==U_STRUCT){
				return utGetStruct(p,name);
			}else{
				return utGetArray(p,name);
			}
		}else{
			if(p->ppe[pos]->type==U_STRUCT){
				return utGetStruct(p,pos);
			}else{
				return utGetArray(p,pos);
			}
		}
	}
};




typedef void (*free_t)(void* d);

class HandPtr
{
	void** b;
	free_t fre;
public:
	HandPtr(void** c, free_t f){
		b=c;
		fre=f;	
	}
	HandPtr(void** c){
		b=c;
		fre=(free_t)free;	
	}
	~HandPtr(){
		if(b)
			if(*b)
				fre(*b);	
	}
	void* GetPtr(){
		void* a=*b;
		b=NULL;
		return a;
	}
};

#endif/*__utype_h__*/
