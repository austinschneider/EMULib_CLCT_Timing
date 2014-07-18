// $Id: Application.h,v 1.2 2008/07/18 15:28:38 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmem_probe_Application_h_
#define _xmem_probe_Application_h_

#include "xdaq/WebApplication.h"
#include "toolbox/mem/Pool.h"
#include "toolbox/mem/exception/Exception.h"

namespace xmem {
namespace probe {

class Application: public xdaq::WebApplication  
{
	
	public:
	
	XDAQ_INSTANTIATOR();
	
	Application(xdaq::ApplicationStub * s) throw (xdaq::exception::Exception);
	
	
	void Default(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
	void listPools(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
	void displayUsage(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
	void selfTest(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);
	
	protected:
	
	void allocateBlocks(toolbox::mem::Pool* pool) throw (toolbox::mem::exception::Exception);
	std::string qualifiedSize(size_t size);


};

}
}

#endif
