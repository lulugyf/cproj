#include "CLTux.h"

#ifndef WIN32
const int	CLClassCodeDataType::DATA_TYPE_STRING;
const int	CLClassCodeDataType::DATA_TYPE_INT;
const int	CLClassCodeDataType::DATA_TYPE_DOUBLE;
const int	CLClassCodeDataType::DATA_TYPE_COMPLEX;
const int	CLClassCodeDataType::DATA_TYPE_DATATIME;
const int	CLClassCodeDataType::DATA_TYPE_LONG;

const int	CLClassCodeDispType::DISP_TYPE_TEXT;
const int	CLClassCodeDispType::DISP_TYPE_SELECT;
const int	CLClassCodeDispType::DISP_TYPE_CHECKBOX;
const int	CLClassCodeDispType::DISP_TYPE_RADIO;
const int	CLClassCodeDispType::DISP_TYPE_TABNAME;
const int	CLClassCodeDispType::DISP_TYPE_TABLE;
const int	CLClassCodeDispType::DISP_TYPE_LABEL;
const int	CLClassCodeDispType::DISP_TYPE_AREA;
const int	CLClassCodeDispType::DISP_TYPE_HIDDEN;
const int	CLClassCodeDispType::DISP_TYPE_BOOLEAN;
const int	CLClassCodeDispType::DISP_TYPE_TABLEGRAPH;

const int 	CLClassCodeDispType::MAX_DISPTYPE_NUM;
const int 	CLClassCodeDataType::MAX_DATATYPE_NUM;

#endif
const TClassCodeDataTypeTwin CLClassCodeDataType::classCodeDataTypeTwin[MAX_DATATYPE_NUM] =
{
	{DATA_TYPE_STRING, "string"},
	{DATA_TYPE_INT, "int"},
	{DATA_TYPE_DOUBLE, "double"},
	{DATA_TYPE_COMPLEX, "complex"},
	{DATA_TYPE_DATATIME, "datatime"},
	{DATA_TYPE_LONG, "long"}
};

const TClassCodeDispTypeTwin CLClassCodeDispType::classCodeDispTypeTwin[MAX_DISPTYPE_NUM] =
{
	{DISP_TYPE_TEXT, "text"},
	{DISP_TYPE_SELECT, "select"},
	{DISP_TYPE_CHECKBOX, "checkbox"},
	{DISP_TYPE_RADIO, "radio"},
	{DISP_TYPE_TABNAME, "tabname"},
	{DISP_TYPE_TABLE, "table"},
	{DISP_TYPE_LABEL, "label"},
	{DISP_TYPE_AREA, "area"},
	{DISP_TYPE_HIDDEN, "hidden"},
	{DISP_TYPE_BOOLEAN, "boolean"},
	{DISP_TYPE_TABLEGRAPH, "graphInfo"}
};

const char*  CLTuxInParams::m_MemBufId = "prodInfo";
ETYPE CLTuxInParams::Initialize(FBFR32 *transIN) throw()
{
	ub4 xmlTuxParamLen=0;
	ETYPE iRet=0;

	DBUG_ENTER("CLTuxInParams::Initialize");

	if(transIN == NULL)
	{
		DBUG_RETURN(iRet);
	}
	m_xmlTuxParam = Fgetalloc32(transIN, GPARM32_0, 0, NULL);
	if (!m_xmlTuxParam)
	{
		DBUG_RETURN(CLError::E_MEMORY_LACK);
	}
	xmlTuxParamLen = (ub4)strlen(m_xmlTuxParam);
	DBUG_PRINT("Initialize", ("xmlTuxParamLen=[%d][%s]", xmlTuxParamLen,m_xmlTuxParam));

	try
	{
		XMLPlatformUtils::Initialize();
	}
	catch(...)
	{
		DBUG_PRINT("CLTuxInParams::Initialize",("XMLPlatformUtils::Initialize() Error"));
		DBUG_RETURN(CLError::E_XML_INIT);
	}
	//生成DOM解析对象
	parser = new XercesDOMParser();
	if (!parser)
	{
		DBUG_PRINT("CLTuxInParams::Initialize",("new XercesDOMParser Error"));
		DBUG_RETURN(CLError::E_XML_INIT);
	}
	
	//设置是否校验模式：Val_Never, Val_Always,Val_Auto
	parser->setValidationScheme(XercesDOMParser::Val_Auto);

	//设置是否校执行命名空间的校验
	parser->setDoNamespaces(false);

	//设置是否解析模式（Schema）。
	parser->setDoSchema(false);

	//设置是否全模式解析
	parser->setValidationSchemaFullChecking(false);

	//是否创建实体参考节点
	parser->setCreateEntityReferenceNodes(false);

	CLDomErrorHandler *errHandler = new CLDomErrorHandler();
	parser->setErrorHandler(errHandler);

	memBufIS = new MemBufInputSource((const XMLByte *)m_xmlTuxParam, xmlTuxParamLen, m_MemBufId, false);

	if (!memBufIS)
	{
		DBUG_PRINT("CLTuxInParams::Initialize",("new memBufIS Error"));
		DBUG_RETURN(CLError::E_XML_INIT);
	}

	DOMDocument *doc = 0;
	DOMNode* paramNode = NULL, *attributeNode = NULL;
	DOMNode* valueNode = NULL;
	DOMNamedNodeMap* namedNodeMap = NULL;
	CLTuxParam *tuxParam = NULL;

	try
	{
		parser->parse(*memBufIS);
	}
	catch (...)
	{
		DBUG_RETURN(CLError::E_XML_PARSE);
	}

	doc = parser->getDocument();
	if (doc == NULL)
	{
		DBUG_RETURN(CLError::E_XML_PARSE);
	}
	doc->setEncoding(X(ENCODING_IN_NAME));
	doc->setActualEncoding(X(ENCODING_IN_NAME));
	rootEl = doc->getDocumentElement();

	if (!rootEl)
	{
		DBUG_PRINT("CLTuxInParams", ("CLTuxInParams::Initialize rootEl=[NULL]"));
		DBUG_RETURN(CLError::E_XML_TAG_ROOT);
	}

	inputParamsEl = (DOMElement *)rootEl->getFirstChild();
	while(inputParamsEl)
	{
		if (strcmp(S((inputParamsEl)->getNodeName()), XML_ELTAG_INPARAMS) == 0)
		{
			break;
		}
		inputParamsEl = (DOMElement *)inputParamsEl->getNextSibling();
	}
	if (inputParamsEl == NULL)
	{
		DBUG_RETURN(CLError::E_XML_ELTAG_INPARAMS);
	}

	pubParamsEl = (DOMElement *)rootEl->getFirstChild();
	while(pubParamsEl)
	{
		if (strcmp(S((pubParamsEl)->getNodeName()), XML_ELTAG_PUBPARAMS) == 0)
		{
			break;
		}
		pubParamsEl = (DOMElement *)pubParamsEl->getNextSibling();
	}
	if (pubParamsEl == NULL)
	{
		DBUG_RETURN(CLError::E_XML_ELTAG_PUBPARAMS);
	}

	m_initialize = true;
	DBUG_RETURN(0);
}

CLTuxInParams::CLTuxInParams(FBFR32 *transIN)
{
	DBUG_ENTER("CLTuxInParams::CLTuxInParams");
	m_initialize = false;
	parser = NULL;
	memBufIS = NULL;
	m_xmlTuxParam = NULL;
	rootEl = NULL;
	inputParamsEl = NULL;
	pubParamsEl = NULL;
	ub4 iRet = Initialize(transIN);
	DBUG_PRINT("CLTuxInParams", ("CLTuxInParams::Initialize=[%ld]", iRet));
	DBUG_VOID_RETURN;
}

CLTuxInParams::~CLTuxInParams()
{
	if (m_xmlTuxParam)
	{
		free(m_xmlTuxParam);
		m_xmlTuxParam=NULL;
	}
	if (parser)
	{
		delete parser;
		parser = NULL;
	}
	if (memBufIS)
	{
		delete memBufIS;
		memBufIS = NULL;
	}
	XMLPlatformUtils::Terminate();
}

//不成功返回NULL。
inline DOMElement *CLTuxInParams::GetClassElement(const char* paramCode) throw()
{
	DBUG_ENTER("CLTuxInParams::GetClassElement");
	DOMNodeList* nodeList= inputParamsEl->getElementsByTagName(X(XML_ELTAG_CLASS));
	if (!nodeList)
	{
		DBUG_PRINT("GetClassElement", ("GetClassElement 无输入参数"));
		DBUG_RETURN(NULL);
	}
	DOMAttr* attr = NULL;
	
	for(XMLSize_t i = 0; i < nodeList->getLength(); i ++)
	{
		attr = ((DOMElement*)nodeList->item(i))->getAttributeNode(X(XML_ATTRTAG_CLASSCODE));
		DBUG_PRINT("GetClassElement", ("S(attr->getValue())[%s][%s]",S(attr->getValue()), paramCode));
		if (strcmp(S(attr->getValue()), paramCode) == 0)
		{
			DBUG_RETURN((DOMElement*)nodeList->item(i));
		}
	}
	DBUG_RETURN(NULL);
}

//不成功返回NULL。
inline DOMElement *CLTuxInParams::GetPubClassElement(const char* paramCode) throw()
{
	DBUG_ENTER("CLTuxInParams::GetPubClassElement");
	DOMNodeList* nodeList= pubParamsEl->getElementsByTagName(X(XML_ELTAG_CLASS));
	if (!nodeList)
	{
		DBUG_PRINT("GetPubClassElement", ("GetClassElement 无输入参数"));
		DBUG_RETURN(NULL);
	}
	DOMAttr* attr = NULL;
	
	for(XMLSize_t i = 0; i < nodeList->getLength(); i ++)
	{
		attr = ((DOMElement*)nodeList->item(i))->getAttributeNode(X(XML_ATTRTAG_CLASSCODE));
		DBUG_PRINT("GetPubClassElement", ("S(attr->getValue())[%s][%s]",S(attr->getValue()), paramCode));
		if (strcmp(S(attr->getValue()), paramCode) == 0)
		{
			DBUG_RETURN((DOMElement*)nodeList->item(i));
		}
	}
	DBUG_RETURN(NULL);
}

//是否返回功能关系信息
bool CLTuxInParams::IsDisplayRelaFunc() throw()
{
	static char value[10+1];

	DBUG_ENTER("CLTuxInParams::IsDisplayRelaFunc");
	DOMAttr* valueAttr = rootEl->getAttributeNode(X(XML_ATTRTAG_ISDISPRELA));
	if (!valueAttr)
	{
		DBUG_RETURN(true);
	}

	strcpy(value, S(valueAttr->getValue()));
	if (value[0] == 'F')
	{
		DBUG_RETURN(false);
	}
	DBUG_RETURN(true);
}

char *CLTuxInParams::GetPubFirstValueByCode(ub4 paramCode, char* value) throw()
{
	static char s[10+1];

	DBUG_ENTER("CLTuxInParams::GetPubFirstValueByCode");
	memset(s, 0, sizeof(s));
	sprintf(s, "%d", paramCode);
	DOMElement* el= NULL;
	if ( (el = GetPubClassElement(s)) == NULL)
	{
		DBUG_RETURN(NULL);
	}
	else
	{
		DOMElement* valueEl = (DOMElement*)el->getFirstChild();
		DBUG_PRINT("GetPubFirstValueByCode", ("valueEl[%ld]",valueEl));
		while(valueEl)
		{
			DBUG_PRINT("GetPubFirstValueByCode", ("S(valueEl->getTagName())[%s][%s]",
				S(valueEl->getTagName()), XML_ELTAG_PARAMVALUE));
			if (strcmp(S(valueEl->getTagName()), XML_ELTAG_PARAMVALUE)== 0)
			{
				DOMAttr* valueAttr = valueEl->getAttributeNode(X(XML_ATTRTAG_VALUE));
				if (valueAttr != NULL)
				{
					strcpy(value, S(valueAttr->getValue()));
					DBUG_PRINT("GetPubFirstValueByCode",("GetPubFirstValueByCode valueAttr->getValue()=[%s]", value));
					DBUG_RETURN(value);
				}
				else
				{
					DBUG_RETURN(NULL);
				}
			}
			valueEl = (DOMElement*)valueEl->getNextSibling();
		}
	}
	DBUG_RETURN(NULL);
}

const XMLCh* CLTuxInParams::GetFirstValueByCode(ub4 paramCode) throw()
{
	static char s[10+1];

	DBUG_ENTER("CLTuxInParams::GetFirstValueByCode");
	memset(s, 0, sizeof(s));
	sprintf(s, "%d", paramCode);
	DOMElement* el= NULL;
	if ( (el = GetClassElement(s)) == NULL)
	{
		DBUG_RETURN(NULL);
	}
	else
	{
		DOMElement* valueEl = (DOMElement*)el->getFirstChild();
		while(valueEl)
		{
			if (strcmp(S(valueEl->getTagName()), XML_ELTAG_PARAMVALUE)== 0)
			{
				DOMAttr* valueAttr = valueEl->getAttributeNode(X(XML_ATTRTAG_VALUE));
				if (valueAttr != NULL)
				{
					DBUG_RETURN(valueAttr->getValue());
				}
				else
				{
					DBUG_RETURN(NULL);
				}
			}
			valueEl = (DOMElement*)valueEl->getNextSibling();
		}
	}
	DBUG_RETURN(NULL);
}

CLTuxOutParams::CLTuxOutParams(const char*opCode, const char *funcName)
{
	m_initialize = false;

	dw = NULL;
	xmlbuf = NULL;
	doc = NULL;

	Initialize(opCode,funcName);
}

CLTuxOutParams::~CLTuxOutParams()
{
	DBUG_ENTER("CLTuxOutParams::CLTuxOutParams");
	
	DBUG_PRINT("CLTuxOutParams", ("delete xmlbuf[%ld]", xmlbuf));
	if (xmlbuf)
	{
		delete xmlbuf;
		xmlbuf = NULL;
	}
	DBUG_PRINT("CLTuxOutParams", ("delete dw[%ld]", xmlbuf));
	if (dw)
	{
		dw->release();
		dw = NULL;
	}
	DBUG_PRINT("CLTuxOutParams", ("delete doc[%ld]", doc));
	if (doc)
	{
		doc->release();
		doc = NULL;
	}
	DBUG_PRINT("CLTuxOutParams", ("Terminate"));
	XMLPlatformUtils::Terminate();
	DBUG_VOID_RETURN;
}

ETYPE CLTuxOutParams::Initialize(const char*opCode, const char *funcName) throw()
{
	DBUG_ENTER("CLTuxOutParams::Initialize");
	try
	{
		XMLPlatformUtils::Initialize();
	}
	catch(...)
	{
		DBUG_PRINT("CLTuxOutParams::Initialize",("XMLPlatformUtils::Initialize() Error"));
		DBUG_RETURN(CLError::E_XML_INIT);
	}

	impl = DOMImplementationRegistry::getDOMImplementation(X("Core"));
	if (!impl)
	{
		DBUG_PRINT("CLTuxOutParams::Initialize",("DOMImplementationRegistry::getDOMImplementation() Error"));
		DBUG_RETURN(CLError::E_XML_INIT);
	}

	doc = impl->createDocument(NULL, X(ROOT_TAG_NAME),0);
	if (!doc)
	{
		DBUG_PRINT("CLTuxOutParams::Initialize",("impl->createDocument ROOT_TAG_NAME Error"));
		DBUG_RETURN(CLError::E_XML_INIT);
	}

	//根节点
	rootNode = doc->getDocumentElement();
	if (!rootNode)
	{
		DBUG_PRINT("CLTuxOutParams::Initialize",("doc->getDocumentElement Error"));
		DBUG_RETURN(CLError::E_XML_INIT);
	}
	rootNode->setAttribute(X(XML_ATTRTAG_OPCODE), X(opCode));
	rootNode->setAttribute(X(XML_ATTRTAG_FUNCNAME), X(funcName));
	rootNode->setAttribute(X(XML_ATTRTAG_TYPE), X(CLClassCodeDispType::GetDispTypeName(CLClassCodeDispType::DISP_TYPE_TABNAME)));

	//PARAMS_TAG_NAME节点
	m_parametersEl = doc->createElement(X(XML_ELTAG_OUTPARAMS));
	if (!m_parametersEl)
	{
		DBUG_PRINT("CLTuxOutParams::Initialize",("doc->createElement XML_ELTAG_OUTPARAMS Error"));
		DBUG_RETURN(CLError::E_XML_INIT);
	}
	m_parametersEl->setAttribute(X(XML_ATTRTAG_ORDER), X("2"));
	m_parametersEl->setAttribute(X(XML_ATTRTAG_ROWCOUNT), X("0"));
	m_parametersEl->setAttribute(X(XML_ATTRTAG_COLCOUNT), X("0"));

	rootNode->appendChild(m_parametersEl);

	//PARAMS_TAG_NAME节点
	m_relaFuncEl = doc->createElement(X(XML_ELTAG_RELAFUNCS));
	if (!m_relaFuncEl)
	{
		DBUG_PRINT("CLTuxOutParams::Initialize",("doc->createElement XML_ELTAG_RELAFUNCS Error"));
		DBUG_RETURN(CLError::E_XML_INIT);
	}
	m_relaFuncEl->setAttribute(X(XML_ATTRTAG_ORDER), X("3"));
	rootNode->appendChild(m_relaFuncEl);

	m_initialize = true;
	DBUG_RETURN(0);
}

ETYPE CLTuxOutParams::AppendParam(DOMElement* curEl, DOMElement** newEl, const char *classNo,
								const char*classCode, const char *className, const char* paramValue,
								int iDataLength, int iDataType, int iOrder, bool bReadOnly, int iDisplayType,
								bool bIsInParam, int iInParamCtrl, int iRuleCode, int iGroupOrder,
								int iColCount, int iRowCount, int iDisplayCtrl,int iDisplayCol) throw()
{
	DOMNode *curNode=NULL;
	ETYPE iRet = 0;


	DBUG_ENTER("CLTuxOutParams::AppendParam");
	if (CLClassCodeDataType::GetDataTypeName(iDataType) == NULL)
	{
		DBUG_RETURN(CLError::EB_UNIFY_NOSUPPORT_DISPDATATYPE);
	}
	if (CLClassCodeDispType::GetDispTypeName(iDisplayType) == NULL)
	{
		DBUG_RETURN(CLError::EB_UNIFY_NOSUPPORT_DISPLAYTYPE);
	}

	*newEl = NULL;
	if ((iRet = AppendElement(curEl, newEl, classNo, classCode, className, iDataLength,
		iDataType, iOrder, bReadOnly, iDisplayType,bIsInParam,iInParamCtrl,iRuleCode,
		iGroupOrder, iColCount, iRowCount,iDisplayCtrl, iDisplayCol)) != 0)
	{
		DBUG_RETURN(iRet);
	}

	if ( (iRet = AppendValue(*newEl, 0, paramValue)) != 0)
	{
		DBUG_RETURN(iRet);
	}

	DBUG_RETURN(iRet);
}

ETYPE CLTuxOutParams::AppendValue(DOMElement* curEl, int iOrder, const char* paramValue) throw()
{
	DOMElement *newEl=NULL;
	char tmpBuf[32];

	DBUG_ENTER("CLTuxOutParams::AppendValue");
	try
	{
		newEl = doc->createElement(X(XML_ELTAG_PARAMVALUE));
		sprintf(tmpBuf, "%d", iOrder);
		newEl ->setAttribute(X(XML_ATTRTAG_ORDER), X(tmpBuf));
		newEl ->setAttribute(X(XML_ATTRTAG_VALUE), X(paramValue));
		curEl->appendChild(newEl);
	}
	catch(...)
	{
		DBUG_RETURN(CLError::E_MEMORY_LACK);
	}
	DBUG_RETURN(0);
}

//增加一个下拉节点
ETYPE CLTuxOutParams::AppendSelectNode(DOMElement* curEl, int iOrder, const char* code, const char*name) throw()
{
	DOMElement *newEl=NULL;
	char tmpBuf[32];

	DBUG_ENTER("CLTuxOutParams::AppendSelectNode");
	try
	{
		newEl = doc->createElement(X(XML_ELTAG_CODEVALUE));
		sprintf(tmpBuf, "%d", iOrder);
		newEl ->setAttribute(X(XML_ATTRTAG_ORDER), X(tmpBuf));
		newEl ->setAttribute(X(XML_ATTRTAG_CODE), X(code));
		newEl ->setAttribute(X(XML_ATTRTAG_NAME), X(name));
		curEl->appendChild(newEl);
	}
	catch(...)
	{
		DBUG_RETURN(CLError::E_MEMORY_LACK);
	}
	DBUG_RETURN(0);
}

//增加一个下拉节点的关联节点
ETYPE CLTuxOutParams::AppendSelectRelaClassNo(DOMElement* curEl, int iOrder, ub4 iClassNo) throw()
{
	DOMElement *newEl=NULL;
	char tmpBuf[32];

	DBUG_ENTER("CLTuxOutParams::AppendSelectRelaClassNo");
	try
	{
		newEl = doc->createElement(X(XML_ELTAG_RELACLASSNO));
		sprintf(tmpBuf, "%d", iOrder);
		newEl ->setAttribute(X(XML_ATTRTAG_ORDER), X(tmpBuf));
		sprintf(tmpBuf, "%d", iClassNo);
		newEl ->setAttribute(X(XML_ATTRTAG_CLASSNO), X(tmpBuf));
		curEl->appendChild(newEl);
	}
	catch(...)
	{
		DBUG_RETURN(CLError::E_MEMORY_LACK);
	}
	DBUG_RETURN(0);
}

ETYPE CLTuxOutParams::AppendElement(DOMElement* curEl, DOMElement** newEl, const char *classNo,
									const char*classCode, const char *className, int iDataLength,
									int iDataType, int iOrder, bool bReadOnly, int iDisplayType,
									bool bIsInParam, int iInParamCtrl, int iRuleCode, int iGroupOrder,
									int iColCount, int iRowCount, int iDisplayCtrl,int iDisplayCol) throw()
{
	ETYPE iRet = 0;
	char tmpBuf[32];

	DBUG_ENTER("CLTuxOutParams::AppendElement");
	if (CLClassCodeDataType::GetDataTypeName(iDataType) == NULL)
	{
		DBUG_RETURN(CLError::EB_UNIFY_NOSUPPORT_DISPDATATYPE);
	}
	if (CLClassCodeDispType::GetDispTypeName(iDisplayType) == NULL)
	{
		DBUG_RETURN(CLError::EB_UNIFY_NOSUPPORT_DISPLAYTYPE);
	}
	try
	{
		*newEl = doc->createElement(X(XML_ELTAG_CLASS));
		memset(tmpBuf,0, sizeof(tmpBuf));
		sprintf(tmpBuf, "%d", iOrder);
		(*newEl)->setAttribute(X(XML_ATTRTAG_ORDER), X(tmpBuf));
		
		(*newEl)->setAttribute(X(XML_ATTRTAG_CLASSNO), X(classNo));
		(*newEl)->setAttribute(X(XML_ATTRTAG_CLASSCODE), X(classCode));
		(*newEl)->setAttribute(X(XML_ATTRTAG_CLASSNAME), X(className));

		memset(tmpBuf,0, sizeof(tmpBuf));
		sprintf(tmpBuf, "%d", iDataLength);
		(*newEl)->setAttribute(X(XML_ATTRTAG_DATALENGTH), X(tmpBuf));

		(*newEl)->setAttribute(X(XML_ATTRTAG_DATATYPE), X(CLClassCodeDataType::GetDataTypeName(iDataType)));
		if (bReadOnly)
		{
			(*newEl)->setAttribute(X(XML_ATTRTAG_READONLY), X("T"));
		}
		else
		{
			(*newEl)->setAttribute(X(XML_ATTRTAG_READONLY), X("F"));
		}
		(*newEl)->setAttribute(X(XML_ATTRTAG_TYPE), X(CLClassCodeDispType::GetDispTypeName(iDisplayType)));
		
		if (bIsInParam)
		{
			(*newEl)->setAttribute(X(XML_ATTRTAG_ISINPARAM), X("T"));
		}
		else
		{
			(*newEl)->setAttribute(X(XML_ATTRTAG_ISINPARAM), X("F"));
		}
		memset(tmpBuf,0, sizeof(tmpBuf));
		sprintf(tmpBuf, "%d", iInParamCtrl);
		(*newEl)->setAttribute(X(XML_ATTRTAG_INPARAMCTRL), X(tmpBuf));

		memset(tmpBuf,0, sizeof(tmpBuf));
		sprintf(tmpBuf, "%d", iRuleCode);
		(*newEl)->setAttribute(X(XML_ATTRTAG_RULECODE), X(tmpBuf));

		memset(tmpBuf,0, sizeof(tmpBuf));
		sprintf(tmpBuf, "%d", iGroupOrder);
		(*newEl)->setAttribute(X(XML_ATTRTAG_GRROUPORDER), X(tmpBuf));

		memset(tmpBuf,0, sizeof(tmpBuf));
		sprintf(tmpBuf, "%d", iColCount);
		(*newEl)->setAttribute(X(XML_ATTRTAG_COLCOUNT), X(tmpBuf));

		memset(tmpBuf,0, sizeof(tmpBuf));
		sprintf(tmpBuf, "%d", iRowCount);
		(*newEl)->setAttribute(X(XML_ATTRTAG_ROWCOUNT), X(tmpBuf));

		memset(tmpBuf,0, sizeof(tmpBuf));
		sprintf(tmpBuf, "%d", iDisplayCtrl);
		(*newEl)->setAttribute(X(XML_ATTRTAG_DISPLAYCTRL), X(tmpBuf));

		memset(tmpBuf,0, sizeof(tmpBuf));
		sprintf(tmpBuf, "%d", iDisplayCol);
		(*newEl)->setAttribute(X(XML_ATTRTAG_DISPLAYCOL), X(tmpBuf));

		/*按照iOrder排序*/
		DOMElement* refChild = (DOMElement*)curEl->getFirstChild();
		DOMAttr* valueAttr = NULL;
		while(refChild)
		{
			valueAttr = refChild->getAttributeNode(X(XML_ATTRTAG_ORDER));
			if (valueAttr == NULL)
			{
				break;
			}
			if (atoi(S(valueAttr->getValue())) > iOrder)
			{
				break;
			}
			refChild = (DOMElement*)refChild->getNextSibling();
		}
		curEl->insertBefore((*newEl), refChild);
		//curEl->appendChild(*newEl);
	}
	catch(...)
	{
		DBUG_RETURN(CLError::E_MEMORY_LACK);
	}
	DBUG_RETURN(iRet);
}
//追加一个图形元素节点
ETYPE CLTuxOutParams::AppendGraphEl(DOMElement* curEl, DOMElement** newEl, const char *sGraphType,
					int iChartDepth, int iDimCategories, int iDimValueDirection,
					const char *sGraphTitleCaption, int iDataBeginPos, int iDataEndPos,
					const char *sStyle) throw()
{
	ETYPE iRet = 0;
	char tmpBuf[32];

	DBUG_ENTER("CLTuxOutParams::AppendGraphEl");
	try
	{
		*newEl = doc->createElement(X(XML_GRAPH_INFO));
		(*newEl)->setAttribute(X(XML_GRAPH_TYPE), X(sGraphType));

		memset(tmpBuf,0, sizeof(tmpBuf));
		sprintf(tmpBuf, "%d", iChartDepth);
		(*newEl)->setAttribute(X(XML_GRAPH_DEPTH), X(tmpBuf));
		
		memset(tmpBuf,0, sizeof(tmpBuf));
		sprintf(tmpBuf, "%d", iDimCategories);
		(*newEl)->setAttribute(X(XML_GRAPH_DIM_CATEGORIES), X(tmpBuf));

		memset(tmpBuf,0, sizeof(tmpBuf));
		sprintf(tmpBuf, "%d", iDimValueDirection);
		(*newEl)->setAttribute(X(XML_GRAPH_DIM_VALUE_DIRECTION), X(tmpBuf));

		(*newEl)->setAttribute(X(XML_GRAPH_TITLE_CAPTION), X(sGraphTitleCaption));

		memset(tmpBuf,0, sizeof(tmpBuf));
		sprintf(tmpBuf, "%d", iDataBeginPos);
		(*newEl)->setAttribute(X(XML_GRAPH_DATA_BEGIN_POS), X(tmpBuf));

		memset(tmpBuf,0, sizeof(tmpBuf));
		sprintf(tmpBuf, "%d", iDataEndPos);
		(*newEl)->setAttribute(X(XML_GRAPH_DATA_END_POS), X(tmpBuf));

		(*newEl)->setAttribute(X(XML_GRAPH_STYLE), X(sStyle));

		curEl->appendChild(*newEl);
	}
	catch(...)
	{
		DBUG_RETURN(CLError::E_MEMORY_LACK);
	}

	DBUG_RETURN(iRet);
}

//追加一个图形元素节点值
ETYPE CLTuxOutParams::AppendGraphValue(DOMElement* curEl, DOMElement** newEl, int iDimValue) throw()
{
	ETYPE iRet = 0;
	char tmpBuf[32];

	DBUG_ENTER("CLTuxOutParams::AppendGraphValue");
	try
	{
		*newEl = doc->createElement(X(XML_GRAPH_DIM_VALUE));

		memset(tmpBuf,0, sizeof(tmpBuf));
		sprintf(tmpBuf, "%d", iDimValue);
		(*newEl)->setAttribute(X(XML_ATTRTAG_VALUE), X(tmpBuf));

		curEl->appendChild(*newEl);
	}
	catch(...)
	{
		DBUG_RETURN(CLError::E_MEMORY_LACK);
	}

	DBUG_RETURN(iRet);
}

//追加一个关联操作代码值
ETYPE CLTuxOutParams::AppendFunc(DOMElement** newEl, const char *sOpCode, const char *sFuncName, const char *sParentFuncName, int iDisplayType, int iOrder) throw()
{
	char tmpBuf[32];

	DBUG_ENTER("CLTuxOutParams::AppendFunc");
	if (CLClassCodeDispType::GetDispTypeName(iDisplayType) == NULL)
	{
		DBUG_RETURN(CLError::EB_UNIFY_NOSUPPORT_DISPLAYTYPE);
	}
	try
	{
		*newEl = doc->createElement(X(XML_ELTAG_RELAFUNC));
		(*newEl)->setAttribute(X(XML_ATTRTAG_OPCODE), X(sOpCode));
		(*newEl)->setAttribute(X(XML_ATTRTAG_FUNCNAME), X(sFuncName));
		(*newEl)->setAttribute(X(XML_ATTRTAG_PARENTFUNCNAME), X(sParentFuncName));
		(*newEl)->setAttribute(X(XML_ATTRTAG_TYPE), X(CLClassCodeDispType::GetDispTypeName(iDisplayType)));
		memset(tmpBuf,0, sizeof(tmpBuf));
		sprintf(tmpBuf, "%d", iOrder);
		(*newEl)->setAttribute(X(XML_ATTRTAG_ORDER), X(tmpBuf));
		m_relaFuncEl->appendChild((*newEl));
	}
	catch(...)
	{
		DBUG_RETURN(CLError::E_MEMORY_LACK);
	}
	DBUG_RETURN(0);
}


const char * CLTuxOutParams::ParamToXml() throw()
{
	DBUG_ENTER("CLTuxOutParams::ParamToXml");
	if (!m_initialize)
	{
		DBUG_RETURN(NULL);
	}

	if (dw)
	{
		dw->release();
		dw = NULL;
	}
	if (xmlbuf)
	{
		delete xmlbuf;
		xmlbuf = NULL;
	}
	dw = ((DOMImplementationLS*)impl)->createDOMWriter();
	dw->setEncoding(X(ENCODING_OUT_NAME));

	//为了加快页面对XML的处理速度，输出的XML流不包含空白元素。
	//if (dw->canSetFeature(XMLUni::fgDOMWRTFormatPrettyPrint, true))
	//	dw->setFeature(XMLUni::fgDOMWRTFormatPrettyPrint, true);

	xmlbuf=new MemBufFormatTarget();
	DBUG_PRINT("ParamToXml", ("xmlbuf address[%ld]", xmlbuf));
	dw->writeNode(xmlbuf, *doc);

	DBUG_RETURN((const char *)xmlbuf->getRawBuffer());
}
