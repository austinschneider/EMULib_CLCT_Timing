/**
 *     @class JTAGSVFCommandFactory
 *
 *     @short Abstract base class for a JTAG SVF Command Factory.
 *            
 *            The concrete implementations create JTAG SVF Commands
 *            from a line in the SVF file, i.e. they do the parsing
 *            and check the validity of the command.
 *       
 *       @see
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:59:08 $
 *
 *
**/

#ifndef jal_JTAGSVFCommandFactory_H
#define jal_JTAGSVFCommandFactory_H

#include "jal/jtagSVFSequencer/JTAGSVFCommand.h"
#include "jal/jtagSVFSequencer/SVFSyntaxException.h"

#include <vector>
#include <string>

namespace jal {

class JTAGSVFCommandFactory {
 public:  

  /// create a command
  virtual JTAGSVFCommand* create(std::vector<std::string> const& args) 
    throw(jal::SVFSyntaxException) = 0;
  
  /// reset the command Factory (before starting a new file)
  virtual void reset() {};

  virtual ~JTAGSVFCommandFactory() {};
};

}

#endif
