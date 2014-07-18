// $Id: endian.h,v 1.4 2008/07/18 15:26:51 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _i2o_utils_endian_h_
#define _i2o_utils_endian_h_

#include "i2o/i2o.h"

#define ALIGN_STRING32(len) ((len) + (4 - ((len) % 4)))

//
// just the opposite of htonl and htons and viceversa)
// Tell this to those guis that have defined I2O as little ENDIAN!
// good luck!
#ifdef BIG_ENDIAN__
#define i2oencodel(x)	((((x) & 0x000000ff) << 24) | \
			 (((x) & 0x0000ff00) <<  8) | \
			 (((x) & 0x00ff0000) >>  8) | \
			 (((x) & 0xff000000) >> 24))
			 
#define i2oencodes(x)	((((x) & 0x00ff) << 8) | \
			 (((x) & 0xff00) >> 8))
			 
#define i2odecodel(x)	(i2oencodel(x))
#define i2odecodes(x)	(i2oencodes(x))
inline void swapU32(U32 * buf, size_t len ) {
	assert((len % 4) == 0 );
        while ( len > 0 ) {
		*buf = i2oencodel(*buf);
		buf++;
		len -= 4;
	}	   	    
}
#else

#define i2oencodel(x) (x)
#define i2oencodes(x) (x)
#define i2odecodel(x) (x)
#define i2odecodes(x) (x)

#define swapU32(x,y)

#endif 


#endif
