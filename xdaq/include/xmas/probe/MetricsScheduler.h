// $Id: MetricsScheduler.h,v 1.2 2008/07/18 15:28:33 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_probe_MetricsScheduler_h_
#define _xmas_probe_MetricsScheduler_h_

#include "toolbox/task/AsynchronousEventDispatcher.h"
#include "xdata/ActionListener.h"
#include "toolbox/Event.h"
#include "xmas/probe/exception/Exception.h"

namespace xmas
{
	namespace probe
	{
		class FlashListMonitorRegistry;
				
		/*! This class is the source of the monitoring data for one flashlist.
		    An object of this class is instantiated for each flashlist
		*/
		class MetricsScheduler: public toolbox::task::AsynchronousEventDispatcher, public toolbox::ActionListener
		{
			public:
						
			MetricsScheduler(FlashListMonitorRegistry* registry);
			
			virtual ~MetricsScheduler();
			
			/*! Receives an event with the table built. Look up consumers for this
			    flashlist and forward the event to the consumers synchronously
			 */
			void actionPerformed( toolbox::Event& event);
			
			private:
			
			FlashListMonitorRegistry* flashListRegistry_;	
		};
	}
}
#endif


