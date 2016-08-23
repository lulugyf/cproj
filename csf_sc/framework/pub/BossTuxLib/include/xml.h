#ifndef __xml_h__
#define __xml_h__
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMWriter.hpp>

#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/framework/MemBufFormatTarget.hpp>


#include <xercesc/util/OutOfMemoryException.hpp>

XERCES_CPP_NAMESPACE_USE

//XML8y1jG)
#define ROOT_TAG_NAME			"mainFunc"
#define XML_ATTRTAG_ISDISPRELA	"isDispRela"

//1jG)JtPT
#define XML_ATTRTAG_OPCODE		"opCode"
#define XML_ATTRTAG_FUNCNAME	"funcName"
#define XML_ATTRTAG_PARENTFUNCNAME	"pFuncName"
#define XML_ATTRTAG_TYPE		"type"

//2NJ}PEO"
#define XML_ELTAG_PUBPARAMS		"pubParams"
#define XML_ELTAG_INPARAMS		"inputParams"
#define XML_ELTAG_OUTPARAMS		"outputParams"
#define XML_ELTAG_CLASS			"class"

#define XML_ATTRTAG_ORDER		"order"
#define XML_ATTRTAG_CLASSNO		"classNo"
#define XML_ATTRTAG_CLASSCODE	"classCode"
#define XML_ATTRTAG_CLASSNAME	"className"
#define XML_ATTRTAG_DATATYPE	"dataType"
#define XML_ATTRTAG_DATALENGTH	"dataLength"
#define XML_ATTRTAG_READONLY	"readOnly"
#define XML_ATTRTAG_ISINPARAM	"isInParam"
#define XML_ATTRTAG_INPARAMCTRL	"inParamCtrl"
#define XML_ATTRTAG_RULECODE	"ruleCode"
#define XML_ATTRTAG_ROWCOUNT	"rowCount"
#define XML_ATTRTAG_GRROUPORDER	"groupOrder"
#define XML_ATTRTAG_COLCOUNT	"colCount"
#define XML_ATTRTAG_DISPLAYCTRL	"displayCtrl"
#define XML_ATTRTAG_DISPLAYCOL	"displayCol"

#define XML_ELTAG_PARAMVALUE	"paramValue"
#define XML_ATTRTAG_VALUE		"value"

#define XML_ELTAG_RELACLASSNO	"relaClassNo"

#define XML_ELTAG_CODEVALUE		"codeValue"
#define XML_ATTRTAG_CODE		"code"
#define XML_ATTRTAG_NAME		"name"

//9XA*5D2YWwPEO"
#define XML_ELTAG_RELAFUNCS		"relaFuncs"
#define XML_ELTAG_RELAFUNC		"relaFunc"

#define PARAMS_TAG_NAME			"Parameters"
#define PARAM_TAG_NAME			"Parameter"
#define PARAM_ID_TAG_NAME		"ParamId"
#define PARAM_CODE_TAG_NAME		"ParamCode"
#define PARAM_NAME_TAG_NAME		"ParamName"
#define PARAM_VALUE_TAG_NAME	"ParamValue"

//M<1m2NJ}6(RePEO"
#define XML_GRAPH_INFO					"graphInfo"
#define XML_GRAPH_TYPE					"graphType"
#define XML_GRAPH_DEPTH					"chartDepth"
#define XML_GRAPH_DIM_CATEGORIES		"dimCategories"
#define XML_GRAPH_DIM_VALUE_DIRECTION	"dimValueDirection"
#define XML_GRAPH_TITLE_CAPTION			"graphTitleCaption"
#define XML_GRAPH_DATA_BEGIN_POS		"dataBeginPos"
#define XML_GRAPH_DATA_END_POS			"dataEndPos"
#define XML_GRAPH_STYLE					"style"
#define XML_GRAPH_DIM_VALUE				"dimValue"

#endif //__xml_h__

