/**
 *     @class JTAGSVFCommandFactoryFrequency
 *
 *     @short JTAG SVF Command Factory for Frequency Command.
 *            
 *       
 *       @see
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:59:09 $
 *
 *
**/

#ifndef jal_JTAGSVFCommandFactoryFrequency_H
#define jal_JTAGSVFCommandFactoryFrequency_H

#include "jal/jtagSVFSequencer/JTAGSVFCommandFactory.h"
#include "jal/jtagSVFSequencer/JTAGSVFCommand.h"

#include <vector>
#include <string>

namespace jal {

  class JTAGSVFCommandFactoryFrequency : public JTAGSVFCommandFactory {
  public:
    /// constructor
    JTAGSVFCommandFactoryFrequency() {};
  
    /// destructor
    virtual ~JTAGSVFCommandFactoryFrequency() {};

    /// parse an frequency command and create the command object
    JTAGSVFCommand* create(std::vector<std::string> const& args)
      throw(jal::SVFSyntaxException);
  };

}
#endif
