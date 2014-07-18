#ifndef jal_HARDWAREEXCEPTION_H
#define jal_HARDWAREEXCEPTION_H
/**
 *     @class HardwareException
 *
 *     @short Exeption thrown when there is a problem accessing or initializing the JTAG hardware.
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

  class HardwareException : public jal::JALException {
    
  public:
    HardwareException( std::string name, std::string message, std::string module, int line, std::string function ) 
      : jal::JALException(name, message, module, line, function) {}; 

    HardwareException( std::string name, std::string message, std::string module, int line, std::string function, xcept::Exception& previous ) 
      : jal::JALException(name, message, module, line, function, previous) {}; 

  }; 
}

#endif
