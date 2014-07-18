#ifndef _ttc_ltc_LTCControlSoapHandler_hh_
#define _ttc_ltc_LTCControlSoapHandler_hh_


#include "log4cplus/logger.h"
#include "xoap/MessageReference.h"
#include "toolbox/lang/Method.h"


namespace ttc
{

class LTCControl;

//! Class to handle SOAP callbacks from LTCControl application
class LTCControlSoapHandler
{
public:

  LTCControlSoapHandler(LTCControl* _ltc_control);

  void addMethod(toolbox::lang::Method* m, std::string name);

private:

  //! Processes a user command.
  xoap::MessageReference userCommand(xoap::MessageReference msg) throw (xoap::exception::Exception);

  LTCControl* ltc_control;
  log4cplus::Logger logger_;
};

}


#endif
