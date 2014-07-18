// $Id: Crypt.h,v 1.2 2008/07/18 15:27:56 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xaccess_Crypt_h_
#define _xaccess_Crypt_h_

#include <string>

namespace xaccess {

	class Crypt {

		public: 
 		//! The crypt() function performs password encryption, based on the NBS Data
     		/*! Encryption Standard (DES). 
		*/
		static std::string crypt(const std::string  & key, const std::string & salt);

		protected: 
		Crypt();


	};

}


#endif
