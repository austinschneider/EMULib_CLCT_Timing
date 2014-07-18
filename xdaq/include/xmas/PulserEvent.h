// $Id: PulserEvent.h,v 1.5 2008/07/18 15:28:36 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_PulserEvent_h_
#define _xmas_PulserEvent_h_

#include <map>
#include <string>
#include "xmas/exception/Exception.h"
#include "toolbox/Properties.h"
#include "toolbox/net/UUID.h"
#include "toolbox/TimeVal.h"
#include "toolbox/TimeInterval.h"
#include "xoap/domutils.h"

namespace xmas
{
	class PulserEvent: public toolbox::Properties
	{
		public:
		
		PulserEvent();
		
		PulserEvent(DOMNode* node) throw (xmas::exception::Exception);
		
		~PulserEvent();		
		
		//! Return map <FlashListName, Tags>
		//
		std::map<std::string, std::string>& getSamples();		
		
		toolbox::net::UUID& getId();

		bool hasPeriod();
		
		toolbox::TimeVal getStartTime()  throw (xmas::exception::Exception);
		
		toolbox::TimeInterval getPeriod()  throw (xmas::exception::Exception);
		
		/*! Returns the last time the pulse was used (set with \function update() )
			The returned time value by be NaN if the pulse was never used
		*/
		toolbox::TimeVal& getLastPulseTime();
		
		/*! Sets the pulse time to now (when the function is called).
		    The value can be retrieved with \function getLastPulseTime()
		 */
		void update();
		
		/*! Returns, how many times the pulse event was used. The counter is
		    incremented by calling \function updatePulse()
		 */
		size_t getPulseCount();
		
		/*! Reset pulse count and last pulse time */
		void reset();
		
		protected:

		std::map<std::string, std::string> flashLists_;
		toolbox::net::UUID id_;
		toolbox::TimeVal lastPulseTime_;
		size_t pulseCount_;
	};
}

#endif
