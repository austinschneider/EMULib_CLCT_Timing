/**
 *     @class JTAGSVFCommandFactoryEnddr
 *
 *     @short JTAG SVF Command Factory for Enddr Command.
 *       
 *       @see
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:59:08 $
 *
 *
**/

#ifndef jal_JTAGSVFCommandFactoryEnddr_H
#define jal_JTAGSVFCommandFactoryEnddr_H

#include "jal/jtagSVFSequencer/JTAGSVFCommandFactory.h"
#include "jal/jtagSVFSequencer/JTAGSVFCommand.h"

#include <vector>
#include <string>

namespace jal {

  class JTAGSVFCommandFactoryEnddr : public JTAGSVFCommandFactory {
  public:
    /// constructor
    JTAGSVFCommandFactoryEnddr() {};
  
    /// destructor
    virtual ~JTAGSVFCommandFactoryEnddr() {};

    /// parse an ENDDR command and create the command object
    JTAGSVFCommand* create(std::vector<std::string> const& args)
      throw(jal::SVFSyntaxException);
  };

}
#endif
