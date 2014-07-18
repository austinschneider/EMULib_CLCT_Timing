// $Id: EventDispatcher.h,v 1.5 2008/07/18 15:28:08 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_EventDispatcher_h_
#define _xdata_EventDispatcher_h_

#include <list>
#include "xdata/ActionListener.h"
#include "xdata/exception/Exception.h"

namespace xdata {

class Serializable;

class EventDispatcher  {

	public:
	
	EventDispatcher();
	
	EventDispatcher(Serializable * s);

	void addItemChangedListener(  xdata::ActionListener * l );
	
	void addItemRetrieveListener(  xdata::ActionListener * l );
	
	void removeItemChangedListener( xdata::ActionListener * l ) throw (xdata::exception::Exception);
	
	void removeItemRetrieveListener( xdata::ActionListener * l ) throw (xdata::exception::Exception);
	
	void fireItemChanged( xdata::Event & e );
	
	void fireItemRetrieve( xdata::Event & e );
	
	Serializable * getItem();
	void setItem(Serializable *s );
	
	protected:
	
	std::list<xdata::ActionListener*> itemChangedListenerList_;
	std::list<xdata::ActionListener*> itemRetrieveListenerList_;
	Serializable * serializable_;
};


}


#endif
