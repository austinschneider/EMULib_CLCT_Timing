// $Id: Event.h,v 1.6 2008/07/18 15:28:08 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_Event_h_
#define _xdata_Event_h_

#include <string>

namespace xdata 
{

class Event
{
	public:
	
	/*! Constructor, \param type is the type of the event, \param originator is
	    an opaque pass-through parameter 
	*/
	Event(const std::string & type, void* originator = 0);
	
	/*! Virtual destructor to assure that deriving classes properly clean up their
	    members.
	*/
	virtual ~Event();
	
	/*! Retrieve the type of this event */
	virtual std::string type();
	
	/*! Retrieve the opaque pass-through parameter given in the constructor */
	virtual void* originator();
		
	protected:
	
		std::string type_;
		void* originator_;
};

}

#endif
