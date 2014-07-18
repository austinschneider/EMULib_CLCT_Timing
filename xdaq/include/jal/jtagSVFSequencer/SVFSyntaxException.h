#ifndef jal_SVFSYNTAXEXCEPTION_H
#define jal_SVFSYNTAXEXCEPTION_H
/**
 *     @class SVFSyntaxException
 *
 *     @short Exeption thrown when an SVF syntax error is encountered
 *
 *            Most syntax errors are discovered at SVF file load time.
 *            Some syntax errors may only be discovered at play time.
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:59:09 $
 *
 *
**/

#include "jal/jtagController/JALException.h"

namespace jal {

  class SVFSyntaxException : public jal::JALException {
    
  public:
    SVFSyntaxException( std::string name, std::string message, std::string module, int line, std::string function ) 
      : jal::JALException(name, message, module, line, function) {}; 

    SVFSyntaxException( std::string name, std::string message, std::string module, int line, std::string function, xcept::Exception& previous ) 
      : jal::JALException(name, message, module, line, function, previous) {}; 

  }; 
}

#endif
