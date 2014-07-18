/**
 *     @class JTAGSVFCommandFactoryState
 *
 *     @short JTAG SVF Command Factory for State Command.
 *            
 *       
 *       @see
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:59:09 $
 *
 *
**/

#ifndef jal_JTAGSVFCommandFactoryState_H
#define jal_JTAGSVFCommandFactoryState_H

#include "jal/jtagSVFSequencer/JTAGSVFCommandFactory.h"
#include "jal/jtagSVFSequencer/JTAGSVFCommand.h"

#include <vector>
#include <string>

namespace jal {

  class JTAGSVFCommandFactoryState : public JTAGSVFCommandFactory {
  public:
    /// constructor
    JTAGSVFCommandFactoryState() {};
  
    /// destructor
    virtual ~JTAGSVFCommandFactoryState() {};

    /// parse an State command and create the command object
    JTAGSVFCommand* create(std::vector<std::string> const& args)
      throw(jal::SVFSyntaxException);
  };

}
#endif
