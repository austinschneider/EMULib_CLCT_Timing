// $Id: utils.h,v 1.8 2008/07/18 15:27:32 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_utils_h_
#define _toolbox_utils_h_

#include <string>
#include <time.h>

#include "toolbox/exception/Exception.h"

namespace toolbox 
{
	//! Step through the file string beginning from the end and
	//! chop off the path in the beginning.
	//
	std::string chop_path(const std::string & pathname);
	
	//! Suspend thread for \param useconds microseconds. Works on all platforms
	//
	int u_sleep (useconds_t useconds);
	
	//! Get current date and time in GMT (Web compatible) time format
	//
	std::string getDateTime();
	
	//! Safely create a file
	/*!
		Create a file \param filename. Truncate the file to zero length if
		the parameter \param truncate is set to true.
		\throws a toolbox::exception::Exception if the action fails
		\returns a low level file descriptor to the created file that can be used
		to open the file
	*/
	int createFile (const std::string& filename, bool truncate)
		throw (toolbox::exception::Exception);

	
}

#define MIN(a,b) (((a)<(b))?(a):(b))

#endif
