// $Id: ImagePicker.h,v 1.2 2008/07/18 15:28:44 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xgi_ImagePicker_h_
#define _xgi_ImagePicker_h_

#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include "xgi/exception/Exception.h"

namespace xgi
{	
	class ImagePicker
	{
		public:

		ImagePicker
		(
			const std::string& id, 
			const std::string& httpRoot, 
			const std::string& fileFilter,
			const std::string& inputFieldId 
		);
		
		~ImagePicker();
			
		void render (std::ostream& out);
				
		private:
		
		// Create a temporary file called imageset.js in the 
		// root of the Web server (must be writable for this application
		//
		void createImageSet(const std::string& filefilter)
			throw (xgi::exception::Exception);
		
		std::string id_; 
		std::string httpRoot_;
		std::string fileFilter_;
		std::string inputFieldId_;
	};

	std::ostream& operator<<(std::ostream& out, ImagePicker& ob);
}


#endif
