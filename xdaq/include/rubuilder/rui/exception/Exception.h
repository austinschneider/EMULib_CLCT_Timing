#ifndef _rubuilder_rui_exception_Exception_h_
#define _rubuilder_rui_exception_Exception_h_


#include "xcept/Exception.h"


namespace rubuilder { namespace rui { namespace exception { // namespace rubuilder::rui::exception

/**
 * Exception raised by the rui package.
 */
class Exception: public xcept::Exception
{
public:

    Exception
    (
        std::string name,
        std::string message,
        std::string module,
        int         line,
        std::string function
    ) : xcept::Exception(name, message, module, line, function)
    {
    }

    Exception
    (
        std::string      name,
        std::string      message,
        std::string      module,
        int              line,
        std::string      function,
        xcept::Exception &e
    ) : xcept::Exception(name, message, module, line, function, e)
    {
    }
};

} } }  // namespace rubuilder::rui::exception

#endif
