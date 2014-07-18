// $Id: NetworkDevice.h,v 1.2 2008/07/18 15:28:04 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_util_NetworkDevice_h_
#define _xdaq_util_NetworkDevice_h_

#include <string>

namespace xdaq 
{

namespace util
{

	class NetworkDevice
	{
		public:

		//! Create a new network  device with name.
		/*! A device is uniquely identified by its name, e.g. lxcmd112 */
                /*! E.g. of usage */
                /*! NetworkDevice("FastIron 400/800/1500", "http://www.foundrynet.com/", "atcp,tcp,udp") */
		NetworkDevice (const std::string & name, 
                               const std::string & info): name_(name), info_(info)
		{
		
		/*
                    std::string::const_iterator nextComma;
                    std::string::const_iterator curPos = intext.begin();

                    while (true)
                    {
                        nextComma = std::find(curPos, intext.end(), ',');
                        // strip leading spaces
                        curPos = std::find_if(curPos, nextComma, std::not1(std::ptr_fun(isspace)));
                        protocols_.push_back(string(curPos, nextComma));

                        if (nextComma == intext.end())
                            break;
                        curPos = ++nextComma;
                    }
		   */ 
		}
		

		//! Retrieve the name that uniquely identifies a network device 
		std::string getName()
		{
			return name_;
		}
		
		//! Retrieve the info that describes the device 
		std::string getInfo()
		{
			return info_;
		}
                
                //! Add a supported protocol by this network device
		void addSupportedProtocol(const std::string & protocol) throw (xdaq::exception::DuplicateProtocol)
		{
			if ( protocols_.find(protocol) == protocols_.end() ) 
			{
				protocols_[protocol] = 0; // symbolic link to ModulesTable 
			}
			else
			{
				std::string msg = toolbox::toString("Protocol %s already installed", protocol.c_str());
				XCEPT_RAISE(xdaq::exception::DuplicateProtocol, msg);
			}
		}
                
                 //! Remove the module from list 
                void removeSupportedProtocol(const std::string & protocol) throw (xdaq::exception::ProtocolNotFound)
		{
			if (protocols_.find(protocol) != protocols_.end() ) 
			{
				protocols_.erase(protocol);
			}
			else
			{
				std::string msg = toolbox::toString("No protocol % found",protocol.c_str());
				XCEPT_RAISE(xdaq::exception::ProtocolNotFound, msg);
			}

		}

                
                //! Retrieve the supported communication protocols matching with XDAQ transports (tcp, udp, gm, maze etc. )
		vector<std::string> getSupportedProtocols()
		{
			std::vector<std::string> protocols;

			std::map<std::string, int, std::less<std::string> >::iterator i;
			for ( i = protocols_.begin(); i != protocols_.end(); i++ )
			{
				protocols.push_back((*i).first);
	
			}
			return protocols;

		}



		private:

		std::string name_;
		std::string info_;
                std::map<std::string, int, std::less<std::string> > protocols_;
	};
	}	

}

#endif
