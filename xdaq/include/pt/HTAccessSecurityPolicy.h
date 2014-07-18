// $Id: HTAccessSecurityPolicy.h,v 1.3 2008/07/18 15:27:18 gutleber Exp $
/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pt_HTAccess_h_
#define _pt_HTAccess_h_

#include <string>

#include "pt/SecurityPolicy.h"

namespace pt {

	class HTAccessSecurityPolicy: public pt::SecurityPolicy {

		public: 
		
		virtual std::string getPolicyName() = 0;
		
		virtual std::string getName() = 0;

		virtual std::string getType() = 0;

		virtual bool checkAccess(const std::string & host, const std::string & ip) = 0;

		virtual bool checkAuth(const std::string & userpass) = 0;

		virtual bool isAccessLimited(const std::string & method) = 0;

		virtual bool isAuthLimited(const std::string & method) = 0;
	};

}


#endif
