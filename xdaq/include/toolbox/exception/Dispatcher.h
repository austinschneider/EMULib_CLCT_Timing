// $Id: Dispatcher.h,v 1.2 2008/07/18 15:27:32 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_ExceptionDispatcher_h_
#define _toolbox_ExceptionDispatcher_h_

#include <list>
#include "toolbox/exception/Exception.h"
#include "toolbox/exception/Listener.h"

namespace toolbox 
{
	namespace exception
	{
		class Dispatcher  
		{

			public:

			Dispatcher();

			void addListener( toolbox::exception::Listener * listener );

			void removeListener( toolbox::exception::Listener * listener ) 
				throw (toolbox::exception::Exception);

			void fire ( xcept::Exception & e );

			protected:

			std::list<toolbox::exception::Listener*> listenerList_;
		};
	}
}


#endif
