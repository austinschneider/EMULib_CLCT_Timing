
/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber, G. Lo Presti and L. Orsini                      *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _xplore_Advertisement_h
#define _xplore_Advertisement_h

#include <string>
#include <vector>

#include "toolbox/mem/CountingPtr.h"
#include "toolbox/mem/ThreadSafeReferenceCount.h"
#include "toolbox/mem/StandardObjectPolicy.h"

namespace xplore
{

//! This class wraps an advertisement and handles peer advertisements (advs), peergroup advs and pipe advs.
/*! To create an advertisement use the DiscoveryService class */
class Advertisement
{
	public:
	
    typedef toolbox::mem::CountingPtr<Advertisement, toolbox::mem::SimpleReferenceCount, toolbox::mem::StandardObjectPolicy> Reference;
	
	virtual ~Advertisement() {};
	
	//! Returns the advertisement type. 
	/* Depending on the implementation and supported technologies this can be any of
	   either "jxta:PA", "jxta:PGA", "jxta:PipeAdvertisement" or "jxta:SvcAdv" in case of JXTA or
	   slp:service in case of Service Location Protocol (SLP) 
	*/
	virtual std::string getType() = 0;
	
	//! Implementation dependent representation of the advertisement
	virtual std::string toString() = 0;
	
	//! Retrieve a list of properties that the advertisement type has
	virtual std::vector<std::string> getPropertyNames() = 0;
	
	//! Set a specific property of an advertisement
	/*! These properties vary dependening on the advertisement type and the implementation.
		Here is a list of some properties for different types and implementations:
		type - slp:service
		------------------
		servicetype, url, group, other properties that are user provided
	*/
	virtual void setProperty (const std::string& name, const std::string& value) = 0;
	
	//! Retrieve a specific property of an advertisement
	virtual std::string getProperty(const std::string& name) = 0;
	
	virtual std::string getURL() = 0;

};

}

#endif

