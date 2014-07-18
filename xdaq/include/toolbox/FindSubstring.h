// $Id: FindSubstring.h,v 1.3 2008/07/18 15:27:32 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_FindSubstring_h
#define _toolbox_FindSubstring_h

#include <string>

namespace toolbox
{

class FindSubstring
{
	std::string pattern_;

	public:

	FindSubstring(const std::string& pattern)
	{
		pattern_ = pattern;
	}
	
	bool operator ()(std::string& s)
	{
		return (s.find(pattern_));	
	}

};

}

#endif
