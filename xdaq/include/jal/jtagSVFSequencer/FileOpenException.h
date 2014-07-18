#ifndef jal_FILEOPENEXCEPTION_H
#define jal_FILEOPENEXCEPTION_H
/**
 *     @class FileOpenException
 *
 *     @short Exeption thrown when an SVF file cannot be opened
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:59:08 $
 *
 *
**/


#include "jal/jtagController/JALException.h"

namespace jal {

  class FileOpenException : public jal::JALException {
    
  public:
    FileOpenException( std::string name, std::string message, std::string module, int line, std::string function ) 
      : jal::JALException(name, message, module, line, function) {}; 

    FileOpenException( std::string name, std::string message, std::string module, int line, std::string function, xcept::Exception& previous ) 
      : jal::JALException(name, message, module, line, function, previous) {}; 

  }; 
}

#endif
