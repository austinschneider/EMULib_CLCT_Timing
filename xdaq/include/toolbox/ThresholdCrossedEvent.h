// $Id: ThresholdCrossedEvent.h,v 1.2 2008/07/18 15:27:32 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and S. Murray					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_ThresholdCrossedEvent_h_
#define _toolbox_ThresholdCrossedEvent_h_

#include "toolbox/Event.h"
#include <string>

namespace toolbox 
{
	class ThresholdCrossedEvent: public toolbox::Event
	{
		public:

		ThresholdCrossedEvent(			
			const std::string& name, 
			const std::string& threshold, 
			double from,
			double to,
			void* originator=0);
			
		std::string getName();
		
		std::string getThreshold();

		double getFromValue();

		double getToValue();

		protected:

		std::string name_;
		std::string threshold_;
		double from_;
		double to_;

	};

	class ThresholdCrossedUpEvent: public toolbox::ThresholdCrossedEvent
	{
		public:
			ThresholdCrossedUpEvent(				
				const std::string& name, 
				double from,
				double to,
				void* originator=0);
	};

	class ThresholdCrossedDownEvent: public toolbox::ThresholdCrossedEvent
	{
		public:
			ThresholdCrossedDownEvent(				
				const std::string& name, 
				double from,
				double to,
				void* originator=0);
	};
}

#endif
