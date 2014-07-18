// $Id: UUID.h,v 1.7 2008/07/18 15:27:36 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_net_UUID_h_
#define _toolbox_net_UUID_h_

#include <string>
#include <stdlib.h>
#include <uuid/uuid.h>
#include <iostream>
#include "toolbox/net/exception/Exception.h"

namespace toolbox {
namespace net {

class UUID {

	public:
	
	//
	// construction & destruction 
	//
	
	/*! The standard constructor creates an empty, uninitialized identifier. It need to be set afterwards
	    by calling the function make(type)
	*/
	UUID         () throw (toolbox::net::exception::Exception);                         /* standard constructor */
	UUID         (const UUID   & obj) throw (toolbox::net::exception::Exception);       /* copy     constructor */
	UUID         (const std::string & value) throw (toolbox::net::exception::Exception);       /* import   constructor */
	virtual ~UUID();                         /* destructor */

	//
	// copying & cloning 
	//
	
	UUID         &operator=    (const UUID   &_obj) throw (toolbox::net::exception::Exception);       /* copy   assignment operator */

	
	//
	// content comparison 
	//
	bool          isnil        (void) const throw (toolbox::net::exception::Exception) ;                     /* regular method */
	int           compare      (const UUID &_obj) const throw (toolbox::net::exception::Exception) ;         /* regular method */
	int           operator==   (const UUID &_obj) const;         /* comparison operator */
	int           operator!=   (const UUID &_obj) const;         /* comparison operator */
	int           operator<    (const UUID &_obj) const;         /* comparison operator */
	int           operator<=   (const UUID &_obj) const;         /* comparison operator */
	int           operator>    (const UUID &_obj) const;         /* comparison operator */
	int           operator>=   (const UUID &_obj) const;         /* comparison operator */

	std::string toString(void) const throw (toolbox::net::exception::Exception); 
	
	friend std::ostream& operator <<(std::ostream& s, const toolbox::net::UUID& uuid);
	
    private:
        uuid_t id_;         


};

std::ostream& operator <<(std::ostream& s, const toolbox::net::UUID& uuid);

}
}


#endif
