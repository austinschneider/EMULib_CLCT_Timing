// $Id: SOAPFSMHelper.hh,v 1.3 2009/02/18 17:16:04 cschwick Exp $
#include "toolbox/fsm/AsynchronousFiniteStateMachine.h"
#include "xdaq/Application.h"
#include "xdaq/exception/Exception.h"
#include "xoap/MessageReference.h"
#include "xdaq2rc/SOAPParameterExtractor.hh"

#include <string>
#include <map>

#ifndef _fedbuilder_SOAPFSMHelper_h_
#define _fedbuilder_SOAPFSMHelper_h_

namespace fedbuilder
{
    class SOAPFSMHelper 
    {
    public:
        //SOAPFSMHelper( toolbox::fsm::FiniteStateMachine &fsm, xdaq::Application *appl );
        SOAPFSMHelper( toolbox::fsm::AsynchronousFiniteStateMachine &fsm, xdaq::Application *appl );
        
        xoap::MessageReference makeSoapReply( const std::string command, const std::string answerString  );
        
        xoap::MessageReference makeSoapFaultReply( const std::string command, const std::string answerString  );
        
        xoap::MessageReference makeFsmSoapReply( const std::string event, const std::string state ) throw (xcept::Exception);

        xoap::MessageReference changeState( xoap::MessageReference msg, 
                                            std::string & newStateName,
                                            std::string geoSlotStr = "" )
        throw (xoap::exception::Exception);

    private:
      toolbox::fsm::AsynchronousFiniteStateMachine &fsmref_;
      xdaq::Application *appl_;
      xdaq2rc::SOAPParameterExtractor parameterExtractor_;
      std::map<std::string, std::string> lookup_map_;
    };
}

#endif /* _fedbuilder_SOAPFSMHelper_h_ */
