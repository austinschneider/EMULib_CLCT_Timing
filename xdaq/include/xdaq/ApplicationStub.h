// $Id: ApplicationStub.h,v 1.4 2008/07/18 15:28:02 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_ApplicationStub_h_
#define _xdaq_ApplicationStub_h_

#include "xdata/InfoSpace.h"

namespace xdaq
{
	class ApplicationContext;
	class ApplicationDescriptor;
	
	class ApplicationStub
	{
		public:
		virtual ~ApplicationStub()
		{
		}

		virtual xdaq::ApplicationContext* getContext() = 0;
		virtual xdaq::ApplicationDescriptor* getDescriptor() = 0;

		//! Return the InfoSpace that is associated with the application (it contains the exported parameters)
		//
		virtual xdata::InfoSpace* getInfoSpace() = 0;
	};
}

#endif
