// $Id: utils.h,v 1.3 2008/07/18 15:28:04 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_soap_utils_h_
#define _xdaq_soap_utils_h_

#include <string>
#include "xoap/MessageReference.h"
#include "xdaq/exception/Exception.h"

namespace xdaq {
namespace soap {

 xoap::MessageReference sendMessage(xoap::MessageReference msg,  const std::string & url, const std::string & urn) 
			throw (xdaq::exception::Exception);
}}			

#endif
