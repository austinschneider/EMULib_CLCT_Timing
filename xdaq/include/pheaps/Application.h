// $Id: Application.h,v 1.1 2007/06/08 08:30:57 lorsini Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pheaps_Application_h_
#define _pheaps_Application_h_


#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string>


#include "memphys.h"

#include "xdata/UnsignedLong.h"
#include "xdata/String.h"
#include "xdata/Boolean.h"
#include "xdata/ActionListener.h"

#include "xdaq/Application.h"
#include "xdaq/ApplicationGroup.h"
#include "xdaq/ApplicationStub.h"
#include "xdaq/ApplicationContext.h"

#include "toolbox/mem/Reference.h"
#include "toolbox/mem/MemoryPoolFactory.h"
#include "toolbox/mem/Pool.h"
#include "toolbox/net/URN.h"
#include "toolbox/fsm/FiniteStateMachine.h"

#include "xgi/Utils.h"
#include "xgi/Method.h"
#include "xgi/Input.h"
#include "xgi/Output.h"

#include "cgicc/CgiDefs.h"
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

#include "xdata/Vector.h"
#include "xdata/Bag.h"
#include "xdata/String.h"
#include "xdata/Double.h"
#include "xdata/Event.h"

#include "pheaps/Buffer.h"

namespace  pheaps {

class Application: public xdaq::Application, xdata::ActionListener
{
	public:
	
	
	XDAQ_INSTANTIATOR();
	
	class PoolConfiguration
	{
		public:
			void registerFields(xdata::Bag<pheaps::Application::PoolConfiguration>* bag)
			{
				bag->addField("nss", &nss);
				bag->addField("type", &type);
				bag->addField("size", &size);								
			}
			
		xdata::String nss;
		xdata::String type;
		xdata::Double size;
	};
	
	Application(xdaq::ApplicationStub * s) throw (xdaq::exception::Exception);
	
	void Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
       		
	void add(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
	
	void remove(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
	
	void actionPerformed(xdata::Event& e);

	protected:
	
	bool isDriverPresent(const std::string & name);
	
	void heapSetupPage(xgi::Input * in, xgi::Output * out );
	
	void addPool (const std::string& name, const std::string& type, double size)
		throw (xdaq::exception::Exception);
	
	std::map<std::string, toolbox::mem::Pool* , std::less<std::string> > heaps_;
	
	//! This vector holds a number of pools that are pre-allocated at startup
	xdata::Vector<xdata::Bag<pheaps::Application::PoolConfiguration> > autoInstalledPools_;
};

}

#endif
