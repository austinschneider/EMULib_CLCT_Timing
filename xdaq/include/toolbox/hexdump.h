// $Id: hexdump.h,v 1.4 2008/07/18 15:27:32 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini                                    *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/

#include <string>
#include <sstream>

namespace toolbox
{
	/* dumps size bytes of *data to stdout. Looks like:
 		[0000] 75 6E 6B 6E 6F 77 6E 20   30 FF 00 00 00 00 39 00 unknown 0.....9.
 	*/
	void hexdump(void *data, size_t size);


	/*! Dumps the data at location \param data of size \param size into the stream \param out
            Two formats are supported: fmt=[text|html] for text and html rendering.
	    This function is not yet implemented
        */
	void hexdump(std::ostream& out, std::string fmt, void* data, size_t size);
}
