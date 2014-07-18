#ifndef jal_TIMEOUTEXCEPTION_H
#define jal_TIMEOUTEXCEPTION_H
/**
 *     @class TimeoutException
 *
 *     @short Exeption thrown when the JTAG hardware does not react within the expected time.
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:59:07 $
 *
 *
**/

#include "jal/jtagController/JALException.h"

namespace jal {

  class TimeoutException : public jal::JALException {
    
  public:
    TimeoutException( std::string name, std::string message, std::string module, int line, std::string function ) 
      : jal::JALException(name, message, module, line, function) {}; 

    TimeoutException( std::string name, std::string message, std::string module, int line, std::string function, xcept::Exception& previous ) 
      : jal::JALException(name, message, module, line, function, previous) {}; 

  }; 
}

#endif
