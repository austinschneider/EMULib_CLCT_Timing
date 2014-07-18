#ifndef _ttc_ttcci_TTCciControlSoapHandler_hh_
#define _ttc_ttcci_TTCciControlSoapHandler_hh_


#include <map>
#include <string>

#include "log4cplus/logger.h"
#include "xoap/MessageReference.h"
#include "toolbox/lang/Method.h"


namespace ttc
{

class TTCciControl;

//! Class handling SOAP callbacks for TTCciControl
class TTCciControlSoapHandler
{
public:

  TTCciControlSoapHandler(TTCciControl* _ttcci_control);

  void addMethod(toolbox::lang::Method* m, std::string name);

private:

  /**
   * Callback for SOAP message having a "userCommand"-tagged element in the body.
   * Supports new-style (parameters as attributes in the "userCommand" element)
   * and old-style messages (parameters as attributes of the xdaq:Body element)
   * Calls userCommandImplementation().
   */
  xoap::MessageReference userCommand(xoap::MessageReference msg)
      throw (xoap::exception::Exception);

  /**
   * Callback for SOAP message having an "ExecuteSequence"-tagged element in the body.
   * Looks for a new-style message first, with the sequence name given via the xdaq:Param attribute.
   * If found, calls ExecuteSequenceImplementation() with the sequence name.
   * Else reverts to userCommand(), passing on the message.
   */
  xoap::MessageReference executeSequence(xoap::MessageReference msg)
      throw (xoap::exception::Exception);

  /**
   * Callback for SOAP message having a "User"-tagged element in the body.
   * Executes the special sequence "user" from the TTCci config file.
   */
  xoap::MessageReference UserAction(xoap::MessageReference msg)
      throw (xoap::exception::Exception);

  /**
   * Callback for SOAP message having a "GetCurrentConfiguration"-tagged element in the body.
   * Produces a text string out of the current configuration, and sends this as the SOAP reply.
   */
  xoap::MessageReference GetCurrentConfiguration(xoap::MessageReference msg)
      throw (xoap::exception::Exception);

  /**
   * The "executeSequence" SOAP action.
   * If the sequence executed corresponds to an state transition the FSM moves accordingly.
   */
  void ExecuteSequenceImplementation(const std::string& sequence_name);

  //! pointer to the TTCci control application
  TTCciControl* ttcci_control;

  log4cplus::Logger logger_;
};

}


#endif
