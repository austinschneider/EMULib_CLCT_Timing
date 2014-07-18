// $Id: InfoSpace.h,v 1.18 2008/07/18 15:28:08 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_InfoSpace_h_
#define _xdata_InfoSpace_h_

#include <string>
#include <map>
#include <vector>

#include "toolbox/BSem.h"

#include "xdata/Serializable.h"
#include "xdata/Bag.h"
#include "xdata/exception/Exception.h"

#include "xdata/ItemEvent.h"
#include "xdata/EventDispatcher.h"
#include "xdata/ActionListener.h"

namespace xdata 
{

class InfoSpace :  public std::map<std::string, xdata::Serializable*, std::less<std::string> >, public xdata::Serializable , public EventDispatcher {

	public:

	
	InfoSpace(const std::string & name);
	virtual ~InfoSpace();

	//! Type of the InfoSpace serializable is "infospace"
	std::string type() const;
	
	//! Retrieve the name of the Infospace
	std::string name() const;

	//! Print value as a string
	std::string toString() throw (xdata::exception::Exception);

	void fromString(const std::string& value) throw (xdata::exception::Exception);
	
	void fireItemAvailable(const std::string & name, xdata::Serializable * serializable, void * originator = 0) throw (xdata::exception::Exception);
	
	void fireItemRevoked(const std::string & name,void * originator = 0 ) throw (xdata::exception::Exception);

	void addItemAvailableListener( xdata::ActionListener * l );
	
	void addItemRevokedListener(  xdata::ActionListener * l );
	
	void removeItemAvailableListener( xdata::ActionListener * l ) throw (xdata::exception::Exception);
	
	void removeItemRevokedListener(  xdata::ActionListener * l ) throw (xdata::exception::Exception);
	
	bool hasItem(const std::string & name);
	
	//! Find a serializable in the InfoSpace according to its name
	xdata::Serializable * find(const std::string & name) throw (xdata::exception::Exception);

	//! Return a vector of serializables with their names according to a passed regular expression
	std::map<std::string, xdata::Serializable*, std::less<std::string> > 
		match(const std::string & expr) throw (xdata::exception::Exception);
	
	// Items Methods
	//
	void fireItemValueChanged(const std::string & name, void * originator = 0) throw (xdata::exception::Exception);
	
	void fireItemValueRetrieve(const std::string & name, void * originator= 0) throw (xdata::exception::Exception);
	
	void addItemChangedListener( const std::string & name, xdata::ActionListener * l ) throw (xdata::exception::Exception);
	
	void addItemRetrieveListener( const std::string & name, xdata::ActionListener * l )throw (xdata::exception::Exception);
	
	void removeItemChangedListener( const std::string & name, xdata::ActionListener * l ) throw (xdata::exception::Exception);
	
	void removeItemRetrieveListener( const std::string & name, xdata::ActionListener * l ) throw (xdata::exception::Exception);
	
	
	// Group events
	//
	void fireItemGroupChanged(std::list<std::string> & names, void * originator) throw (xdata::exception::Exception);
	
	void fireItemGroupRetrieve(std::list<std::string> & names, void * originator) throw (xdata::exception::Exception);
	
	void addGroupChangedListener( xdata::ActionListener * l ) throw (xdata::exception::Exception);
	
	void addGroupRetrieveListener( xdata::ActionListener * l )throw (xdata::exception::Exception);
	
	void removeGroupChangedListener( xdata::ActionListener * l ) throw (xdata::exception::Exception);
	
	void removeGroupRetrieveListener( xdata::ActionListener * l ) throw (xdata::exception::Exception);
	
	
	// comparison operators
	int equals(const xdata::Serializable & s);
	
	//! Locks the InfoSpace. If it is locked, this functions blocks
	void lock();
	
	//! Unlocks the InfoSpace
	void unlock();
	
	// ! General purpose listener per event type (type defined as agreement among applications )
	void addListener(  xdata::ActionListener * l, const std::string & type);
	void removeListener( xdata::ActionListener * l,  const std::string & type) throw (xdata::exception::Exception);
	void fireEvent(xdata::Event & event) throw (xdata::exception::Exception);
	//void fireEvent(const std::string & type, void * originator) throw (xdata::exception::Exception);

	protected:
	
	std::map<std::string, xdata::EventDispatcher, std::less<std::string> > dataItems_;
	std::list<xdata::ActionListener*> itemAvailableListenerList_;
	std::list<xdata::ActionListener*> itemRevokedListenerList_;
	
	std::string name_;
	
	std::map<std::string, std::list<xdata::ActionListener*>, std::less<std::string> > listeners_;
	
 
 	private:
		
	toolbox::BSem lock_;
};


}


#endif

