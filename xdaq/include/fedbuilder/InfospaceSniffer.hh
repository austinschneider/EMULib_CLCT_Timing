#ifndef __InfospaceSniffer_hh_
#define __InfospaceSniffer_hh_

#include <list>

// basic xdaq stuff
#include "xdaq/WebApplication.h"
#include "xdaq/Application.h"
#include "xdaq/ApplicationGroup.h"
#include "xdaq/NamespaceURI.h"

// xdata
#include "xdata/String.h"
#include "xdata/UnsignedInteger32.h"
#include "xdata/Vector.h"
#include "xdata/Bag.h"
#include "xdata/InfoSpace.h"
#include "xdata/InfoSpaceFactory.h"
#include "xdata/ActionListener.h"

// xoap definitions
#include "xoap/MessageReference.h"
#include "xoap/MessageFactory.h"
#include "xoap/SOAPEnvelope.h"
#include "xoap/SOAPBody.h"
#include "xoap/domutils.h"
#include "xoap/Method.h"

#include "xdata/Boolean.h"
#include "xdata/UnsignedInteger32.h"
#include "xdata/Vector.h"
#include "xdata/InfoSpaceFactory.h"

// toolbox utils
#include "toolbox/task/WorkLoop.h"
#include "toolbox/task/WorkLoopFactory.h"

// hyperdaq stuff
#include "cgicc/CgiDefs.h"
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"
#include "xgi/Utils.h"
#include "xgi/Method.h"

#include "fedbuilder/InfospaceSender.hh"
	
namespace fedbuilder
{
   class InfospaceSniffer : public xdaq::WebApplication,
			    public xdata::ActionListener

   {
   public:

     XDAQ_INSTANTIATOR();

     class InfospaceRegistry
     {
     public:
       InfospaceRegistry() 
       {
	 name = "undefined";
	 fireGroupRetrieveIntervall = 0;
	 fireGroupChangedIntervall = 0;
       }
       void registerFields(xdata::Bag<fedbuilder::InfospaceSniffer::InfospaceRegistry>* bag)
       {
	 bag->addField("name",   &name);
	 bag->addField("fireGroupRetrieveIntervall", &fireGroupRetrieveIntervall);
	 bag->addField("fireGroupChangedIntervall",  &fireGroupChangedIntervall);
       }
       
       xdata::String name;
       xdata::UnsignedInteger32 fireGroupRetrieveIntervall;
       xdata::UnsignedInteger32 fireGroupChangedIntervall;
     };


     InfospaceSniffer(xdaq::ApplicationStub *s);
     ~InfospaceSniffer();

     void defaultWebPage(xgi::Input *in, xgi::Output *out) throw( xgi::exception::Exception );
     void actionPerformed ( xdata::Event& e );

     
   private:
     // do some pulsing 
     bool pulse(toolbox::task::WorkLoop *wl);

     Logger logger_;
     xdata::Vector<xdata::Bag<fedbuilder::InfospaceSniffer::InfospaceRegistry> > registeredInfospaces_;
     xdata::InfoSpaceFactory       *infofac_;
     fedbuilder::InfospaceSender   monitoringSender_;
     toolbox::BSem                 actionSem_;
     xdata::UnsignedInteger32      sendBufferSize_;
     xdata::Boolean                listenToGroupRetrieve_;
     xdata::Boolean                listenToGroupChanged_;
     bool                          needPulserThread_;
     toolbox::task::WorkLoop       *pulserWorkLoop_;
     uint32_t                      pulseSeconds_;
     toolbox::BSem                 pulserMapSem_;
     std::map< xdata::InfoSpace *, uint32_t > groupRetrieveMap_;
     std::map< xdata::InfoSpace *, uint32_t > groupChangedMap_;
   };
}
#endif 

