// $Id: memSearch.h,v 1.2 2008/07/18 15:28:41 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef xoap_memSearch_h
#define xoap_memSearch_h

#include <string.h>

namespace xoap
{
	void *memSearch(const void *buf, const void *pattern, size_t buflen, size_t len);
}

#endif
