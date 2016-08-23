#ifndef __CLTuxParam_h__
#define __CLTuxParam_h__

#include "CLDomErrorHandler.h"

//输入参数XML编码
#define ENCODING_IN_NAME "UTF-8"

//输出参数XML编码
#define ENCODING_OUT_NAME "UTF-8"

#ifndef MAX_PARMS_LENGTH
#	define MAX_PARMS_NUM       100
#endif

#ifndef MAX_PARMS_LENGTH
#	define MAX_PARMS_LENGTH    1023
#endif


typedef struct tagClassCodeDispTypeTwin
{
	int		iDispType;
	char	sDispType[32];
} TClassCodeDispTypeTwin;

class CLClassCodeDispType
{
public:
	static const int	DISP_TYPE_TEXT		= 0;
	static const int	DISP_TYPE_SELECT	= 1;
	static const int	DISP_TYPE_CHECKBOX	= 2;
	static const int	DISP_TYPE_RADIO		= 3;
	static const int	DISP_TYPE_TABNAME	= 4;
	static const int	DISP_TYPE_TABLE		= 5;
	static const int	DISP_TYPE_LABEL		= 6;
	static const int	DISP_TYPE_AREA		= 7;
	static const int	DISP_TYPE_HIDDEN	= 8;
	static const int	DISP_TYPE_BOOLEAN	= 9;
	static const int	DISP_TYPE_TABLEGRAPH	= 10;//组图片
public:
	static const char* GetDispTypeName(int iDispType)
	{
		for (int i = 0; i < MAX_DISPTYPE_NUM; i ++)
		{
			if (classCodeDispTypeTwin[i].iDispType == iDispType)
			{
				return classCodeDispTypeTwin[i].sDispType;
			}
		}
		return NULL;
	}
private:
	static const int MAX_DISPTYPE_NUM	= 11;
	static const TClassCodeDispTypeTwin classCodeDispTypeTwin[MAX_DISPTYPE_NUM];
};

typedef struct tagClassCodeDataTypeTwin
{
	int		iDataType;
	char	sDataType[32];
} TClassCodeDataTypeTwin;

class CLClassCodeDataType
{
public:
	static const int	DATA_TYPE_STRING	= 0;
	static const int	DATA_TYPE_INT		= 1;
	static const int	DATA_TYPE_DOUBLE	= 2;
	static const int	DATA_TYPE_COMPLEX	= 3;
	static const int	DATA_TYPE_DATATIME	= 4;
	static const int	DATA_TYPE_LONG		= 5;
public:
	static const char* GetDataTypeName(int iDataType)
	{
		for (int i = 0; i < MAX_DATATYPE_NUM; i ++)
		{
			if (classCodeDataTypeTwin[i].iDataType == iDataType)
			{
				return classCodeDataTypeTwin[i].sDataType;
			}
		}
		return NULL;
	}
private:
	static const int MAX_DATATYPE_NUM	= 6;
	static const TClassCodeDataTypeTwin classCodeDataTypeTwin[MAX_DATATYPE_NUM];
};


/*
class CLXmlToStr: public XMLFormatTarget
{
public:
	CLXmlToStr(const XMLCh* const toTranscode)
	{
		fLocalForm = NULL;
		fFormatter = new XMLFormatter(ENCODING_IN_NAME,this, XMLFormatter::NoEscapes,XMLFormatter::UnRep_CharRef);
		if (fFormatter)
		{
			*fFormatter<<toTranscode;
		}
	}

	~CLXmlToStr()
    {
		if (fLocalForm != NULL)
		{
			free(fLocalForm);
		}
		if (fFormatter)
		{
			delete fFormatter;
		}
    }

	const char* localForm() const
    {
		if (fLocalForm)
		{
			return fLocalForm;
		}
		else
		{
			return g_nullStr;
		}
    }
protected:
    virtual void writeChars(const XMLByte* const toWrite
                          , const unsigned int   count
                          , XMLFormatter* const  formatter)
	{
		DBUG_ENTER("writeChars::writeChars");
		if(fLocalForm != g_nullStr)
		{
			free(fLocalForm);
		}
		fLocalForm=NULL;
		fLocalForm=new char[count+1];
		memset(fLocalForm,0,count+1);
		memcpy(fLocalForm,(char *)toWrite,count+1);	
		DBUG_PRINT("writeChars;", ("fLocalForm=[%s]", fLocalForm));
		DBUG_VOID_RETURN;
	}
private :
	XMLFormatter *	fFormatter;
    char*   fLocalForm;
};

#define S(str) CLXmlToStr(str).localForm()
*/

class CLTuxParam
{
public:
	~CLTuxParam()
	{
		paramValues.clear();
	}
public:
	//对象编码
	const char *paramId;

	//对象类型
	const char *paramCode;

	//参数名称
	const char *paramName;

	//参数值
	vector <const ub1 *> paramValues;
};

/*
输入输出参数文档格式：
<?xml version="1.0" encoding="UTF-8" standalone="no" ?>
<mainFunc opCode="1234" funcName="操作代码名称" type="tabname">
	<inputParams order="1">
		<class classNo="10087" classCode="10087">
			<paramValue value="aaaa01"/>
		</class>
		<class classNo="10092" classCode="10092">
			<paramValue value="CODCDOJHGECIFONG"/>
		</class>
		<class classNo="10114" classCode="10114">
			<paramValue value="1500"/>
		</class>
	</inputParams>
	<outputParams order="2">
		<class classNo="1" classCode="1" className="" dataLength="-1" dataType="int" order="1" readOnly="F" type="text">
			<paramValue order="1" value="xyz1"/>
			<paramValue order="2" value="xyz2"/>
			<paramValue order="3" value="xyz3"/>
		</class>
		<class classNo="2" classCode="2" className="" dataLength="-1" dataType="int" order="2" readOnly="F" type="text">
			<paramValue order="1" value="xyz1"/>
			<paramValue order="2" value="xyz2"/>
			<class classNo="3" classCode="3" className="" dataLength="-1" dataType="int" order="1" readOnly="F" type="text">
				<paramValue order="1" value="xyz1"/>
				<paramValue order="2" value="xyz2"/>
				<paramValue order="3" value="xyz3"/>
			</class>
		</class>
	</outputParams>
	<relaFuncs>
		<relaFunc opCode="1111" funcName="" type="tabname"/>
		<relaFunc opCode="2222" funcName="" type="tabname"/>
	</relaFuncs>
</mainFunc>
*/
class CLTuxParams
{
public:
};

class CLTuxInParams : public CLTuxParams
{
public:
	CLTuxInParams(FBFR32 *transIN);
	~CLTuxInParams();
public:

	bool IsInitialize()
	{
		return m_initialize;
	}

	//没有取到值返回NULL。
	char *GetPubFirstValueByCode(ub4 paramCode, char* value) throw();

	//没有取到值返回NULL。
	const XMLCh* GetFirstValueByCode(ub4 paramCode) throw();

	//是否返回功能关系信息
	bool IsDisplayRelaFunc() throw();

private:
	ETYPE Initialize(FBFR32 *transIN) throw();
	
	//不成功返回NULL。
	DOMElement *GetClassElement(const char* paramCode) throw(); 

	//不成功返回NULL。
	DOMElement *GetPubClassElement(const char* paramCode) throw();
private:
	bool m_initialize;
	char *m_xmlTuxParam;

	static const char*  m_MemBufId;

	//生成DOM解析对象
	XercesDOMParser *parser;

	MemBufInputSource* memBufIS;

	//XML根标签ROOT_TAG_NAME
	DOMElement *rootEl;
	DOMElement *inputParamsEl;
	DOMElement *pubParamsEl;
};


class CLTuxOutParams : public CLTuxParams
{
public:
	CLTuxOutParams(const char*opCode, const char *funcName);
	~CLTuxOutParams();
public:
	//得到输出参数的根节点
	DOMElement* GetOutParamsElemnt()
	{
		return m_parametersEl;
	}

	//是否初始化成功
	bool IsInitialize()
	{
		return m_initialize;
	}

	//追加一个参数值
	ETYPE AppendParam(DOMElement* curEl, DOMElement** newEl, const char *classNo,
						const char*classCode, const char *className, const char* paramValue,
								  int iDataLength, int iDataType, int iOrder, bool bReadOnly, int iDisplayType,
								  bool bIsInParam, int iInParamCtrl, int iRuleCode, int iGroupOrder,
								  int iColCount, int iRowCount, int iDisplayCtrl,int iDisplayCol) throw();

	//追加一个参数节点
	ETYPE AppendElement(DOMElement* curEl, DOMElement** newEl, const char *classNo,
						const char*classCode, const char *className, int iDataLength,
						int iDataType, int iOrder, bool bReadOnly, int iDisplayType,
						bool bIsInParam, int iInParamCtrl, int iRuleCode, int iGroupOrder,
						int iColCount, int iRowCount, int iDisplayCtrl,int iDisplayCol) throw();

	//追加一个图形元素节点
	ETYPE AppendGraphEl(DOMElement* curEl, DOMElement** newEl, const char *sGraphType,
						int iChartDepth, int iDimCategories, int iDimValueDirection,
						const char *sGraphTitleCaption, int iDataBeginPos, int iDataEndPos,
						const char *sStyle) throw();
	//追加一个图形元素节点值
	ETYPE AppendGraphValue(DOMElement* curEl, DOMElement** newEl, int iDimValue) throw();

	//增加一个值节点
	ETYPE AppendValue(DOMElement* curEl, int iOrder, const char* paramValue) throw();

	//增加一个下拉节点
	ETYPE AppendSelectNode(DOMElement* curEl, int iOrder, const char* code, const char*name) throw();

	//增加一个下拉节点的关联节点
	ETYPE AppendSelectRelaClassNo(DOMElement* curEl, int iOrder, ub4 iClassNo) throw();

	//追加一个关联操作代码值
	ETYPE AppendFunc(DOMElement** newEl, const char *sOpCode, const char *sFuncName, const char *sParentFuncName, int iDisplayType, int iOrder) throw();

	//设置当前节点的行数
	//并且把当前节点的行数，赋值给iPreRowCount变量。
	ETYPE SetRowCount(DOMElement* curEl, int iRowCount, int* iPreRowCount) throw();

	//失败返回空
	const char * ParamToXml() throw();
private:
	//初始化
	ETYPE Initialize(const char*opCode, const char *funcName) throw();
private:
	bool m_initialize;

	//XML DOM实现类
	DOMImplementation* impl;

	//XML DOM文档
	DOMDocument*        doc;

	//根节点
	DOMElement*  rootNode;

	//XML_ELTAG_OUTPARAMS节点
	DOMElement*  m_parametersEl;

	//XML_ELTAG_RELAFUNCS节点
	DOMElement*  m_relaFuncEl;

	//DOMWriter
	DOMWriter *dw;

	//MemBufFormatTarget
	MemBufFormatTarget *xmlbuf;
};

#endif//__CLTuxParam_h__
