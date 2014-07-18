// $Id: InfoSpaceFactory.h,v 1.3 2008/07/18 15:28:08 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and S. Murray					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_InfoSpaceFactory_h_
#define _xdata_InfoSpaceFactory_h_

#include <string>

#include "xdata/exception/Exception.h"
#include "xdata/InfoSpace.h"

namespace xdata 
{
	class InfoSpaceFactory: public xdata::InfoSpace
	{
		public:

		static InfoSpaceFactory* getInstance();

		static void destroyInstance();
		
		xdata::InfoSpace* create (const std::string& name) throw (xdata::exception::Exception);
		
		xdata::InfoSpace* get (const std::string& name) throw (xdata::exception::Exception);
		
		void destroy (const std::string & name) throw (xdata::exception::Exception);

		private:

		InfoSpaceFactory();
		
		~InfoSpaceFactory();

		static InfoSpaceFactory* instance_;
	};

	InfoSpaceFactory* getInfoSpaceFactory();
}


#endif

