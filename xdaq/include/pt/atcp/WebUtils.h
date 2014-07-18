#ifndef _pt_atcp_WebUtils_h_
#define _pt_atcp_WebUtils_h_

#include "xgi/Output.h"
#include "xgi/exception/Exception.h"
#include "xdata/Serializable.h"


#include <string>
#include <vector>


namespace  pt { namespace atcp { // namespace pt::atcp

/**
 * Prints a nagivation icon.
 */
void printWebPageIcon
(
    xgi::Output       *out,
    const std::string imgSrc,
    const std::string label,
    const std::string href
)
throw (xgi::exception::Exception);

/**
 * Prints the standard web page title bar for a RU builder application.
 *
 * Note: If there is no RU builder tester application then set
 * rubuilderTesterUrl to empty string ("").
 */
void printWebPageTitleBar
(
    xgi::Output        *out,
    const std::string  pageIconSrc,
    const std::string  pageIconAlt,
    const std::string  appClass,
    const unsigned int appInstance,
    const std::string  appState,
    const std::string  appUrn,
    const std::string  appIconSrc,
    const std::string  dbgIconSrc,
    const std::string  fsmIconSrc
)
throw (xgi::exception::Exception);

/**
 * Prints the specified parameters as an HTML table with the specified name.
 */
void printParamsTable
(
    xgi::Output                                                 *out,
    const std::string                                           name,
    std::vector< std::pair<std::string, xdata::Serializable*> > &params
)
throw (xgi::exception::Exception);

} } // namespace rubuilder::utils

#endif
