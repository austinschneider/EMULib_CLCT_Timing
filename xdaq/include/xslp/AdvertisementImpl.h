
/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber, G. Lo Presti and L. Orsini                      *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _xslp_AdvertisementImpl_h
#define _xslp_AdvertisementImpl_h

#include <string>
#include <map>

#include "xplore/Advertisement.h"
#include "xslp/exception/Exception.h"
namespace xslp
{

//! This class wraps an advertisement and handles peer advertisements (advs), peergroup advs and pipe advs.
//
class AdvertisementImpl: public xplore::Advertisement
{
	public:
	
  	AdvertisementImpl (const std::string& type, const std::string & source) throw (xslp::exception::Exception);
	
	virtual ~AdvertisementImpl ();
	
	//! Returns the advertisement type. 
	/* Depending on the implementation and supported technologies this can be any of
	   either "jxta:PA", "jxta:PGA", "jxta:PipeAdvertisement" or "jxta:SvcAdv" in case of JXTA or
	   slp:service in case of Service Location Protocol (SLP) 
	*/
	std::string getType();
	

	//! Retrieve a list of properties that the advertisement type has
	virtual std::vector<std::string> getPropertyNames();

	//! Set a specific property of an advertisement
	/*! These properties vary dependening on the advertisement type and the implementation.
		Here is a list of some properties for different types and implementations:
		type - slp:service
		------------------
		servicetype, url, group, other properties that are user provided
	*/
	void setProperty (const std::string& name, const std::string& value);
	
	//! Retrieve a specific property of an advertisement
	std::string getProperty(const std::string& name);
	
	std::string getURL();
	
	protected:
	
	std::string type_;
	std::map<std::string, std::string, std::less<std::string> > properties_;
	std::string url_;
};

}

#endif


