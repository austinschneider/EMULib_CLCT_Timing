// $Id: RevokeEvent.h,v 1.1 2008/11/13 15:08:58 lorsini Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _sentinel_spotlight_RevokeEvent_h_
#define _sentinel_spotlight_RevokeEvent_h_

#include <string>
#include "toolbox/Event.h"
#include "xcept/Exception.h"

namespace sentinel
{
	namespace spotlight
	{
	/*!
		An event that encapsulates an xcept Exception.
	*/
	class RevokeEvent:  public toolbox::Event
	{
		public:

		RevokeEvent(xcept::Exception* ex, const std::string & name);

		~RevokeEvent();

		//! Obtain a copy of a reference to the underlying SOAP message
		/*!
			The underlying exception is automatically deleted when
			the last user of the event gives up using the reference to the event.
		*/
		xcept::Exception* getException();

		std::string name();

		protected:

		xcept::Exception* exception_;
		std::string name_;
	};
}}
#endif
