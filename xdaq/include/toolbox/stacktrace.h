// $Id: stacktrace.h,v 1.4 2008/07/18 15:27:32 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_stacktrace_h_
#define _toolbox_stacktrace_h_

#include <iostream>

namespace toolbox
{
	//! Write a stacktrace of at most \param depth functions to the \param stream
	//
	void stacktrace (int depth, std::ostream& stream);
}

#endif
