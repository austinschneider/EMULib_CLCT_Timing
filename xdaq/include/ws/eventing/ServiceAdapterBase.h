// $Id: ServiceAdapterBase.h,v 1.4 2008/07/18 15:27:50 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _ws_eventing_ServiceAdapterBase_h_
#define _ws_eventing_ServiceAdapterBase_h_

#include "toolbox/Properties.h"
#include "ws/eventing/StorageAdapter.h"

namespace ws
{
	namespace eventing
	{
		class ServiceAdapterBase
		{
			public:

			ServiceAdapterBase( StorageAdapter* sa);

			StorageAdapter* getAdapter();

			void setAdapter (StorageAdapter* ai);

			toolbox::Properties& getProperties();

			protected:

	        	toolbox::Properties properties_;
        		StorageAdapter* adapter_;
	    };
	}
}

#endif


