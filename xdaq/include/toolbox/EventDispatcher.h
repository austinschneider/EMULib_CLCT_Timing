// $Id: EventDispatcher.h,v 1.4 2008/07/18 15:27:32 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_EventDispatcher_h_
#define _toolbox_EventDispatcher_h_

#include <list>
#include "toolbox/ActionListener.h"
#include "toolbox/exception/Exception.h"

namespace toolbox 
{
	class EventDispatcher  
	{

		public:

		EventDispatcher();

		void addActionListener( toolbox::ActionListener * l );

		void removeActionListener( toolbox::ActionListener * l ) throw (toolbox::exception::Exception);
		
		std::list<toolbox::ActionListener*> getActionListeners();

		void fireEvent ( toolbox::Event & e );

		protected:

		std::list<toolbox::ActionListener*> actionListenerList_;
	};
}


#endif
