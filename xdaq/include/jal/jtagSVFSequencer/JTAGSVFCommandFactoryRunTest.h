/**
 *     @class JTAGSVFCommandFactoryRunTest
 *
 *     @short JTAG SVF Command Factory for RunTest Command.
 *            
 *       
 *       @see
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:59:09 $
 *
 *
**/

#ifndef jal_JTAGSVFCommandFactoryRunTest_H
#define jal_JTAGSVFCommandFactoryRunTest_H

#include "jal/jtagSVFSequencer/JTAGSVFCommandFactory.h"
#include "jal/jtagSVFSequencer/JTAGSVFCommand.h"

#include <vector>
#include <string>

namespace jal {

  class JTAGSVFCommandFactoryRunTest : public JTAGSVFCommandFactory {
  public:
    /// constructor
    JTAGSVFCommandFactoryRunTest() {};
  
    /// destructor
    virtual ~JTAGSVFCommandFactoryRunTest() {};

    /// parse an RunTest command and create the command object
    JTAGSVFCommand* create(std::vector<std::string> const& args)
      throw(jal::SVFSyntaxException);
  };

}
#endif
