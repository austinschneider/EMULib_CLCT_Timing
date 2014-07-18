// $Id: Event.h,v 1.3 2008/07/18 15:28:41 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xoap_Event_h_
#define _xoap_Event_h_

#include <string>
#include "toolbox/Event.h"
#include "xoap/MessageReference.h"

namespace xoap
{
	/*!
		An event that encapsulates a SOAP message.
		To be used for listeners to xoap message
		events in case of asynchronous dispatching.
	*/
	class Event:  public toolbox::Event
	{
		public:

		Event(xoap::MessageReference & msg, const std::string & name);

		~Event();

		//! Obtain a copy of a reference to the underlying SOAP message
		/*!
			The underlying SOAP message is automatically deleted when
			the last user of the message reference gives up using the
			reference.
		*/
		xoap::MessageReference getMessage();


		std::string name();

		protected:

		xoap::MessageReference msg_;
		std::string name_;
	};
}
#endif
