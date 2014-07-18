// $Id: SecurityPolicyFactory.h,v 1.2 2008/07/18 15:27:18 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber, G. Lo Presti and L. Orsini                      *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#ifndef _access_SecurityPolicyFactory_h
#define _access_SecurityPolicyFactory_h

#include <string>

#include "pt/exception/Exception.h"
#include "pt/SecurityPolicy.h"


namespace pt
{

//! This factory is used to retrieve different implementations of security policies.
/* Currently "htaccess" the .htaccess policy is supported.
   In the future also other policies may be offered.
*/
class SecurityPolicyFactory
{
	public:
	
	static SecurityPolicyFactory* getInstance();
	
	static void destroyInstance();
	
	pt::SecurityPolicy* getSecurityPolicy(const std::string& name) throw (pt::exception::Exception);
		
	void addSecurityPolicyImplementation(const std::string& name, pt::SecurityPolicy* p) throw (pt::exception::Exception);
	
	void removeSecurityPolicyImplementation(const std::string & name) throw (pt::exception::Exception);
	
	std::vector<std::string>  getSecurityPolicyNames();
	

	private:
	
	// Forbid CTOR, DTOR so that nobody can create this factory
	SecurityPolicyFactory();
	~SecurityPolicyFactory();
	
	static SecurityPolicyFactory* instance_;	
	std::map<std::string, pt::SecurityPolicy*, std::less<std::string> > policies_;
};


//! static function to get the PlatformFactory singleton.
SecurityPolicyFactory* getSecurityPolicyFactory();

}


#endif
