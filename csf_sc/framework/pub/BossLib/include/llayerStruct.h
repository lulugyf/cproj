#ifndef __llayerstruct_h__
#define __llayerstruct_h__

#include "oci.h"
#include "libsys.h"

//  If the symbol SQLCA_STORAGE_CLASS is defined, then the SQLCA
//  will be defined to have this storage class.
#define SQLCA_STORAGE_CLASS extern

#if PLATFORM_TYPE == PLATFORM_TYPE_HP
#else
using namespace std; 
#endif

using NSPrime::CLString;
using NSPrime::CLDBug;

#include "ltypedef.h"

#include "province.h"
#include "CLBase.h"
#include "CLError.h"
#include "CLException.h"
#include "CLLayer.h"
#include "CLDriver.h"
#include "db.h"
#include "CLDbDriver.h"
#include "CLCommand.h"
#include "CLRecordSet.h"
#include "CLShmDriver.h"
#include "CLFile.h"
#include "CLRule.h"
#include "CLDomain.h"
#include "CLRight.h"

/*---------------------------------XML BEGIN-------------------------------------------------------*/
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/AbstractDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMErrorHandler.hpp>
#include <xercesc/dom/DOMImplementationRegistry.hpp>
#include <xercesc/dom/DOMBuilder.hpp>
#include <xercesc/dom/DOMException.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMError.hpp>
#include <xercesc/dom/DOMLocator.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>
#include <xercesc/dom/DOMAttr.hpp>
#include <xercesc/framework/MemBufFormatTarget.hpp>
#include <xercesc/util/XMLString.hpp>
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
// ---------------------------------------------------------------------------
//  This is a simple class that lets us do easy (though not terribly efficient)
//  trancoding of char* data to XMLCh data.
// ---------------------------------------------------------------------------
class XStr
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    XStr(const char* const toTranscode)
    {
        // Call the private transcoding method
        fUnicodeForm = XMLString::transcode(toTranscode);
    }

    ~XStr()
    {
        XMLString::release(&fUnicodeForm);
    }


    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    const XMLCh* unicodeForm() const
    {
        return fUnicodeForm;
    }

private :
    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fUnicodeForm
    //      This is the Unicode XMLCh format of the string.
    // -----------------------------------------------------------------------
    XMLCh*   fUnicodeForm;
};

#define X(str) XStr(str).unicodeForm()


extern const char* const g_nullStr;
// ---------------------------------------------------------------------------
//  This is a simple class that lets us do easy (though not terribly efficient)
//  trancoding of XMLCh data to local code page for display.
// ---------------------------------------------------------------------------
class StrX
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------
    StrX(const XMLCh* const toTranscode)
    {
		if (!toTranscode)
		{
			//指向一个空串。保证返回的串不为空。
			fLocalForm = (char*)g_nullStr;
		}
		else
		{
			// Call the private transcoding method
			fLocalForm = XMLString::transcode(toTranscode);
		}
    }

    ~StrX()
    {
		if (fLocalForm != g_nullStr)
		{
			XMLString::release(&fLocalForm);
		}
    }


    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    const char* localForm() const
    {
        return fLocalForm;
    }

private :
    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fLocalForm
    //      This is the local code page form of the string.
    // -----------------------------------------------------------------------
    char*   fLocalForm;
};

#define S(str) StrX(str).localForm()
/*---------------------------------XML END-------------------------------------------------------*/


#endif //
