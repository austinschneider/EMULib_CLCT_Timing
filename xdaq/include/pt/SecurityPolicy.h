// $Id: SecurityPolicy.h,v 1.2 2008/07/18 15:27:18 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _pt_SecurityPolicy_h_
#define _pt_SecurityPolicy_h_


namespace pt 
{
	
	class SecurityPolicy
	{
		public:
		
		//! Uniquely identify a policy with a URN as urn:xdaq-security:<unique name>
		virtual std::string getPolicyName() = 0;
		
		//! Implement virtual DTOR
		virtual ~SecurityPolicy() {}
		
		protected:
		
	};

}

#endif
