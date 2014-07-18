/**
 *     @class JTAGSVFCommandCreator
 *
 *     @short Class that creates a JTAG SVF Command object from a 
 *            line read from the SVF file.
 *
 *            The command arguments are passed as a vector of strings.
 *            Command factory objects are used to actually create
 *            the commands making it easy to define new commands.   
 *       
 *       @see JTAGSVFCommandFactory
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:59:08 $
 *
 *
**/

#ifndef jal_JTAGSVFCommandCreator_H
#define jal_JTAGSVFCommandCreator_H

#include "jal/jtagSVFSequencer/JTAGSVFCommand.h"
#include "jal/jtagSVFSequencer/JTAGSVFCommandFactory.h"

#include <vector>
#include <string>
#include <map>

namespace jal {

  class JTAGSVFCommandCreator {
  public:
    /// constructor
    JTAGSVFCommandCreator();
  
    /// destructor
    ~JTAGSVFCommandCreator();

    /// create a command
    JTAGSVFCommand* create(std::vector<std::string> const& args) 
      throw (jal::SVFSyntaxException);

    /// reset the command creator (to start a new file)
    void reset();
 
  protected:
    std::map<std::string, JTAGSVFCommandFactory*> _factory_map;
  };

}
#endif
