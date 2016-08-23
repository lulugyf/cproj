#include <xercesc/sax/SAXParseException.hpp>

#include "CLDomErrorHandler.h"

void CLDomErrorHandler::warning(const SAXParseException&)
{
    //
    // Ignore all warnings.
    //
}

void CLDomErrorHandler::error(const SAXParseException& toCatch)
{
    fSawErrors = true;
}

void CLDomErrorHandler::fatalError(const SAXParseException& toCatch)
{
    fSawErrors = true;
}

void CLDomErrorHandler::resetErrors()
{
    fSawErrors = false;
}
