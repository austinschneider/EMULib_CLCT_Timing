#ifndef jal_JALEXCEPTION_H
#define jal_JALEXCEPTION_H
/**
 *     @class JALException
 *
 *     @short Base class for all exceptions thrown by JAL.
 *
 *            Derived from the XDAQ xcept::Exception, which provides a mechanism 
 *            for tracing the history of exceptions.
 * 
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:59:07 $
 *
 *
**/

#include "xcept/Exception.h"

namespace jal {

  class JALException : public xcept::Exception {
    
  public:
    JALException( std::string name, std::string message, std::string module, int line, std::string function ) 
      : xcept::Exception(name, message, module, line, function) {}; 

    JALException( std::string name, std::string message, std::string module, int line, std::string function, xcept::Exception& previous ) 
      : xcept::Exception(name, message, module, line, function, previous) {}; 

  }; 

}

#endif

