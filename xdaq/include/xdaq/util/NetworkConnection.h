// $Id: NetworkConnection.h,v 1.2 2008/07/18 15:28:04 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_util_NetworkConnection_h_
#define _xdaq_util_NetworkConnection_h_

#include <string>

#include "xdaq/util/NetworkDevice.h"
#include "xdaq/util/HostDescriptor.h"


namespace xdaq 
{

namespace util
{

	class NetworkConnection
	{
		public:

		//! Create a new network  device with name.
		/*! A device is uniquely identified by its name, e.g. lxcmd112 */
                /*! E.g. of usage */
                /*! NetworkDevice("FastIron 400/800/1500", "http://www.foundrynet.com/", "atcp,tcp,udp") */
		NetworkConnection (xdaq::util::HostDescriptor * h, xdaq::util::NetworkDevice * n ): host_(h), n_(n)
		{
                }
		


		//! Retrieve the name that uniquely identifies a host 
		std::string getHostDescriptor()
		{
			return host_;
		}
		
		//! Retrieve the info that describes the device 
		std::string getNetworkDevice()
		{
			return network_;
		}
                
		private:

		xdaq::util::HostDescriptor * host_;
                xdaq::util::NetworkDevicer * network_;
	};
}	

}

#endif
// $Id: NetworkConnection.h,v 1.2 2008/07/18 15:28:04 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_util_NetworkConnection_h_
#define _xdaq_util_NetworkConnection_h_

#include <string>

#include "xdaq/util/NetworkDevice.h"
#include "xdaq/util/HostDescriptor.h"


namespace xdaq 
{

namespace util
{

	class NetworkConnection
	{
		public:

		//! Create a new network  device with name.
		/*! A device is uniquely identified by its name, e.g. lxcmd112 */
                /*! E.g. of usage */
                /*! NetworkDevice("FastIron 400/800/1500", "http://www.foundrynet.com/", "atcp,tcp,udp") */
		NetworkConnection (xdaq::util::HostDescriptor * h, xdaq::util::NetworkDevice * n ): host_(h), n_(n)
		{
                }
		


		//! Retrieve the name that uniquely identifies a host 
		std::string getHostDescriptor()
		{
			return host_;
		}
		
		//! Retrieve the info that describes the device 
		std::string getNetworkDevice()
		{
			return network_;
		}
                
		private:

		xdaq::util::HostDescriptor * host_;
                xdaq::util::NetworkDevicer * network_;
	};
}	

}

#endif
