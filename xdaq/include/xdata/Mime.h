// $Id: Mime.h,v 1.3 2008/07/18 15:28:08 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_MIME_h_
#define _xdata_MIME_h_

#include <map>
#include <string>
#include <vector>

#include "toolbox/mem/CountingPtr.h"
#include "toolbox/mem/ThreadSafeReferenceCount.h"
#include "toolbox/mem/StandardObjectPolicy.h"

#include "xdata/Serializable.h"
#include "xdata/exception/Exception.h"

#include "mimetic/mimetic.h"

namespace xdata {

// typedef toolbox::mem::CountingPtr<mimetic::MimeEntity, toolbox::mem::ThreadSafeReferenceCount,toolbox::mem::StandardObjectPolicy> MimeEntityReference;

class Mime: public xdata::Serializable
{
	public:
	
	Mime() throw (xdata::exception::Exception);
	
	Mime(const Mime & m) throw (xdata::exception::Exception);
	
	virtual ~Mime();
	
	//! Assign a MimeEntity object to this object
	void setEntity(mimetic::MimeEntity* entity);
	
	Mime & operator=(const Mime & m) throw (xdata::exception::Exception);

	int operator==(const Mime & m);

	int operator!=(const Mime & m);
	
	int equals(const xdata::Serializable & s);
	
	void setValue(const xdata::Serializable & s) throw (xdata::exception::Exception);
	
	std::string type() const;
	
	std::string toString() throw (xdata::exception::Exception);

	void fromString(const std::string& value) throw (xdata::exception::Exception);
	
	//! Returns entity or 0 if not set
	mimetic::MimeEntity* getEntity();
	
	protected:

	mimetic::MimeEntity* mimeEntity_;		
};

} // end namescape xdata

#endif
