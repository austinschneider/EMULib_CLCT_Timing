// $Id: Listener.h,v 1.2 2008/07/18 15:27:32 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_exception_Listener_h_
#define _toolbox_exception_Listener_h_

#include <string>

#include "xcept/Exception.h"

namespace toolbox 
{
	namespace exception 
	{
		
		class Listener
		{
			public:

			//! Callback to overridden by user to react to incoming exception
			//
			virtual void onException(xcept::Exception& e) = 0;

			protected:

			// define empty virtual DTOR to make GCC happy
			//
			virtual ~Listener() {}
		};

	} 

} // end  of namespace



#endif
