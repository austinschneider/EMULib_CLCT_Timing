/**
 *     @class JTAGSVFCommandFactoryEndir
 *
 *     @short JTAG SVF Command Factory for Endir Command.
 *       
 *       @see
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:59:09 $
 *
 *
**/

#ifndef jal_JTAGSVFCommandFactoryEndir_H
#define jal_JTAGSVFCommandFactoryEndir_H

#include "jal/jtagSVFSequencer/JTAGSVFCommandFactory.h"
#include "jal/jtagSVFSequencer/JTAGSVFCommand.h"

#include <vector>
#include <string>

namespace jal {

  class JTAGSVFCommandFactoryEndir : public JTAGSVFCommandFactory {
  public:
    /// constructor
    JTAGSVFCommandFactoryEndir() {};
  
    /// destructor
    virtual ~JTAGSVFCommandFactoryEndir() {};

    /// parse an ENDIR command and create the command object
    JTAGSVFCommand* create(std::vector<std::string> const& args)
      throw(jal::SVFSyntaxException);
  };

}
#endif
