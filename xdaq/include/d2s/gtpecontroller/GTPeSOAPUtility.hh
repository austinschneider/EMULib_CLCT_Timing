#ifndef GTPeSOAPUTILITY_H
#define GTPeSOAPUTILITY_H

/**
 *     @class GTPeSOAPUtility
 *
 *     @short Utility to extract simple commands from SOAP messages and construct responses
 *
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/29 16:58:32 $
 *
 *
 **/

// for SOAP messaging
#include "xoap/MessageReference.h"

#include <string>

namespace d2s {

  class GTPeSOAPUtility {
  public:
    /// extracts a simple SOAP Command from a SOAP Message
    /// The command is the first element tag in the SOAP Body
    ///
    /// returns the command std::string
    static std::string extractSOAPCommand(xoap::MessageReference msg) 
      throw (xoap::exception::Exception);

    /// creates a SOAP response
    ///
    /// @param response is the the name of the response element
    /// @param state is the state passed as an sttribute in the in the response elements state child element
    static xoap::MessageReference createSOAPResponse(std::string const& response, 
						     std::string const& state)
      throw (xoap::exception::Exception);
  };

}
#endif
