// $Id: NetworkDeviceTable.h,v 1.2 2008/07/18 15:28:04 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_util_NetworkDeviceTable_h_
#define _xdaq_util_NetworkDeviceTable_h_

#include <string>
#include <map>


#include "xdaq/exception/DeviceNotFound.h"
#include "xdaq/exception/DuplicateDevice.h"

#include "xdaq/util/NetworkDevice.h"


namespace xdaq {

namespace util {

class NetworkDeviceTable
{
	public:
	
	// DTOR
	~NetworkDeviceTable()
	{
		std::map<std::string, xdaq::util::NetworkDevice*, std::less<std::string> >::iterator i;
		for ( i =  devices_.begin(); i != devices_.end(); i++ )
		{
			delete (*i).second;

		}
	}
	
	//! Create a new network  device with name.
		/*! A device is uniquely identified by its name, e.g. lxcmd112 */
                /*! E.g. of usage */
                /*! createHostDescriptor("FastIron 400/800/1500", "http://www.foundrynet.com/", "atcp,tcp,udp") */
	xdaq::util::NetworkDevice* createDevice(const std::string & name, 
                                                const std::string & info )
                                        throw  (xdaq::exception::DuplicateDevice )
	{
		if ( devices_.find(name) == devices_.end() ) 
		{
			devices_[name] = new xdaq::util::NetworkDevice(name,info);
			return devices_[name];
		}
		else
		{
			std::string msg = toolbox::toString("Device name %s already existing", name.c_str());
			XCEPT_RAISE(xdaq::exception::DuplicateDevice, msg);
		}	
	}
	
	//! Remove a device descriptor by name 
 	void removeDevice(const std::string & name) throw (xdaq::exception::DeviceNotFound)
	{
		if ( devices_.find(name) != devices_.end() ) 
		{
			xdaq::util::NetworkDevice* d = devices_[name];
			delete d;
			devices_.erase(name);
		}
		else
		{
			std::string msg = toolbox::toString("No descriptor for name %s found",name.c_str());
			XCEPT_RAISE(xdaq::exception::DeviceNotFound, msg);
		}
	}
	
	//! Retrieve a host by indicating the name 
 	xdaq::util::NetworkDevice*  getDeviceDescriptor(const std::string & name) 
		throw (xdaq::exception::DeviceNotFound)
	{
		if ( devices_.find(name) != devices_.end() ) 
		{
			return devices_[name];

		}
		else
		{
			std::string msg = toolbox::toString("No descritptor for name %s found",name.c_str());
			XCEPT_RAISE(xdaq::exception::DeviceNotFound, msg);
		}
	}
	
	std::vector<xdaq::util::NetworkDevice*>   getDevices() 
	{
		std::vector<xdaq::util::NetworkDevice*> devices;

		std::map<std::string, xdaq::util::NetworkDevice*, std::less<std::string> >::iterator i;
		for ( i =  devices_.begin(); i != devices_.end(); i++ )
		{
			devices.push_back((*i).second);

		}
		return devices;

	}
	
	private:
	
	std::map<std::string, xdaq::util::NetworkDevice*, std::less<std::string> > devices_;
	
};
}
}

#endif
