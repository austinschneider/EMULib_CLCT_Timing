// $Id: Event.h,v 1.4 2008/07/18 15:27:34 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_mem_Event_h_
#define _toolbox_mem_Event_h_

#include "toolbox/Event.h"
#include <string>

using namespace std;

namespace toolbox 
{
	namespace mem
	{
		const int up = 0;
		const int down = 1;

		class Event: public toolbox::Event
		{
			public:

			Event(const std::string& type, const std::string& name, void* originator=0);
			
			std::string getName();

			protected:
			
			std::string name_;

		};

		class PoolAvailableEvent: public toolbox::mem::Event
		{
			public:
				PoolAvailableEvent(const std::string& name, void* originator=0);
		};

		class PoolRevokedEvent: public toolbox::mem::Event
		{
			public:
				PoolRevokedEvent(const std::string& name, void* originator=0);
		};
		
		class PoolUpperThresholdCrossed: public toolbox::mem::Event
		{
			public:
				PoolUpperThresholdCrossed(int direction, void* originator=0);
				
				//! Return the direction in which the threshold was crossed
				//
				int direction();
				
			protected:
				int direction_;
		};
		
		class PoolLowerThresholdCrossed: public toolbox::mem::Event
		{
			public:
				PoolLowerThresholdCrossed(int direction, void* originator=0);
				
				//! Return the direction in which the threshold was crossed
				//
				int direction();
				
			protected:
				int direction_;
		};
	}
}

#endif
