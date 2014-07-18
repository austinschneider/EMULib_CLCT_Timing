// $Id: PeerTransportNotFound.h,v 1.4 2008/07/18 15:27:18 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pt_exception_PeerTransportNotFound_h_
#define _pt_exception_PeerTransportNotFound_h_

#include "pt/exception/Exception.h"

namespace pt {
	namespace exception { 
		class PeerTransportNotFound: public pt::exception::Exception 
		{
			public: 
			PeerTransportNotFound( std::string name, std::string message, std::string module, int line, std::string function ): 
					pt::exception::Exception(name, message, module, line, function) 
			{} 
			
			PeerTransportNotFound( std::string name, std::string message, std::string module, int line, std::string function,
				xcept::Exception& e ): 
					pt::exception::Exception(name, message, module, line, function, e) 
			{} 
		}; 
	} 
}

#endif
