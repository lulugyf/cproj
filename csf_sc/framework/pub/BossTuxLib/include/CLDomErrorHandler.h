#ifndef __CLDomErrorHandler_h__
#define __CLDomErrorHandler_h__

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/sax/ErrorHandler.hpp>

XERCES_CPP_NAMESPACE_USE


class CLDomErrorHandler : public ErrorHandler
{
public:
    CLDomErrorHandler() :
       fSawErrors(false)
    {
    }

    ~CLDomErrorHandler()
    {
    }


	//实现错误句柄接口
    void warning(const SAXParseException& toCatch);
    void error(const SAXParseException& toCatch);
    void fatalError(const SAXParseException& toCatch);
    void resetErrors();

    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    bool getSawErrors() const;

    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fSawErrors
    //      This is set if we get any errors, and is queryable via a getter
    //      method. Its used by the main code to suppress output if there are
    //      errors.
    // -----------------------------------------------------------------------
    bool    fSawErrors;
};

inline bool CLDomErrorHandler::getSawErrors() const
{
    return fSawErrors;
}
#endif//__CLDomErrorHandler_h__
