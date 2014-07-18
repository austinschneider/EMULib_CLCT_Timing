// $Id: HTAccess.h,v 1.3 2008/07/18 15:27:56 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xaccess_HTAccess_h_
#define _xaccess_HTAccess_h_

#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>

#include "xaccess/exception/Exception.h"
#include "pt/HTAccessSecurityPolicy.h"

namespace xaccess {

	class HTAccess: public pt::HTAccessSecurityPolicy {

		public: 

		HTAccess(const std::string & url) throw (xaccess::exception::Exception);

		std::string getPolicyName();
		
		std::string getName();

		std::string getType();

		bool checkAccess(const std::string & host, const std::string & ip);

		bool checkAuth(const std::string & userpass);

		bool isAccessLimited();
		bool isAccessLimited(const std::string & method) ;


		bool isAuthLimited() ;
		bool isAuthLimited(const std::string & method) ;

		std::string getUserCode(const std::string & user)   throw (xaccess::exception::Exception);

		std::string getUserGroups(const std::string & user) throw (xaccess::exception::Exception);

		void parse(std::istringstream & is);


		protected: 

		std::string userFile_; // The user file name.
		std::string groupFile_; // The group file name
		std::string type_; 
		std::string name_;
		std::map<std::string, bool, std::less<std::string> > methods_; // The method table.
		std::map<std::string, bool, std::less<std::string> > requireEntities_; // The require entity table
		std::string requireName_;
		int order; // The order directive.
		std::vector<std::string> allowList_ ;
		std::vector<std::string> denyList_ ;

	};

}


#endif
