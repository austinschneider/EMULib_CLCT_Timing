#ifndef jal_OUTOFRANGEEXCEPTION_H
#define jal_OUTOFRANGEEXCEPTION_H
/**
 *     @class HardwareException
 *
 *     @short Exeption thrown when a parameter is out of range.
 *
 *            This exception usually results from incorrect usage of a class.
 *            It may also indicate an error in the internal programing logic.             
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

  class OutOfRangeException : public jal::JALException {
    
  public:
    OutOfRangeException( std::string name, std::string message, std::string module, int line, std::string function ) 
      : jal::JALException(name, message, module, line, function) {}; 

    OutOfRangeException( std::string name, std::string message, std::string module, int line, std::string function, xcept::Exception& previous ) 
      : jal::JALException(name, message, module, line, function, previous) {}; 

  }; 
}

#endif
