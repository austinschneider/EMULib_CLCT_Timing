// $Id: DiscoveryService.h,v 1.2 2008/07/18 15:28:50 gutleber Exp $
/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber, G. Lo Presti and L. Orsini                      *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _xslp_DiscoveryService_h
#define _xslp_DiscoveryService_h

#include "toolbox/Properties.h"
#include "xslp/exception/Exception.h"
#include "xplore/Advertisement.h"

#include "slp.h"

#include "toolbox/BSem.h"

namespace xslp {

//! This class wraps the xplore Discovery Service. 
//! This service is responsible for all discovery queries over the network.
class DiscoveryService
{
	public:
	
	DiscoveryService() throw (xslp::exception::Exception);
	
	~DiscoveryService();

	//! Remotely and asynchronously queries the network discovering advertisements.
	/*! To get the discovered advertisements use a DiscoveryListener or call getKnownAdvertisements()
	   @param std::string advType the requested advertisement type; This parameter is technology dependent.
	    To get a Service Location Protocol advertisement use "slp", for JXTA use 
	    one of DiscoveryService::PEER, DiscoveryService::GROUP, DiscoveryService::ADV
	    @return a list of advertisements, or an empty list if nothing is present in the local cache.
	    */
	void search 
	(
		const std::string& advType, 
		const std::string& filter,
		std::vector<xplore::Advertisement::Reference>& resultSet
	)
	throw (xslp::exception::Exception);
		
	void retrieveProperties
	(
		const std::string& service, toolbox::Properties& properties
	) 
	throw (xslp::exception::Exception);

	//! Publishes the given advertisement.
	void publish (xplore::Advertisement::Reference adv) 
		throw (xslp::exception::Exception);
	
	//! Create a new SLP advertisement
	/*! Advertisements are created by the technology dependent platform implementations.
	    This is the implementation provided for SLP (Service Location Protocol).
	    
	    The following general advertisement types are implemented (case sensitive specification):
	    1. Peer
	    2. PeerGroup
	    3. Endpoint
	    
	    Other application specific advertisements may be added statically or dynamically in the future
	 */
	//static xplore::Advertisement::Reference createAdvertisement(const std::string& type)
	//	throw (xslp::exception::Exception);
	
	//! Create a new SLP advertisement from an SLP service string (e.g. a result from a search)
	static xplore::Advertisement::Reference createAdvertisementFromSource(const std::string& source)
		throw (xslp::exception::Exception);
	
	
	protected:
	
	friend SLPBoolean SLPFindCallback ( SLPHandle hslp,
				const char* srvurl,
				unsigned short lifetime,
				SLPError errcode,
				void* cookie);
				
	friend SLPBoolean SLPAttributesCallback ( SLPHandle hslp,
				const char* attrlist,
				SLPError errcode,
				void* cookie);
	
	/*			
	friend SLPBoolean SLPFindTypesCallback ( SLPHandle hslp,
				const char* srvtypes,
				SLPError errcode,
				void* cookie);			
	*/
	
	/*	
	void removeAdvertisement(xplore::Advertisement::Reference adv) throw (xplore::exception::Exception);
	*/
	
	SLPHandle hslp_;
	toolbox::BSem mutex_;	
};

	SLPBoolean SLPFindCallback ( SLPHandle hslp,
				const char* srvurl,
				unsigned short lifetime,
				SLPError errcode,
				void* cookie);

	SLPBoolean SLPAttributesCallback ( SLPHandle hslp,
				const char* attrlist,
				SLPError errcode,
				void* cookie);
}


#endif
