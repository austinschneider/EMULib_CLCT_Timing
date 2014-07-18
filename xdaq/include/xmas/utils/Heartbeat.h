// $Id: Heartbeat.h,v 1.3 2008/07/18 15:28:36 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xmas_utils_Heartbeat_h_
#define _xmas_utils_Heartbeat_h_ 

#include <string>
#include "toolbox/Properties.h"
#include "xoap/MessageReference.h"
#include "ws/addressing/Headers.h"
#include "xmas/exception/Exception.h"
#include "xmas/utils/Request.h"
#include "xdaq/ApplicationDescriptor.h"

namespace xmas
{
namespace utils
{
	class Heartbeat: public xmas::utils::Request
	{
		public:
		
		Heartbeat(xdaq::ApplicationDescriptor &  descriptor);
		
		Heartbeat(xoap::MessageReference& msg) throw (xmas::exception::Exception);
        
		virtual ~Heartbeat();
				
		xoap::MessageReference toSOAP();
			
		toolbox::Properties & getProperties();

		std::string getURL();

		private:
		
		std::string url_;
		toolbox::Properties p_;

			
	};
}}

#endif
