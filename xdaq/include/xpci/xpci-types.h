/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2004, CERN.                                        *
 * All rights reserved.                                                  *
 * Authors: L. Orsini and A. Petrucci                                    *
 *                                                                       *
 * For the licensing terms see LICENSE.                                  *
 * For the list of contributors see CREDITS.                             *
 *************************************************************************/


#ifndef _xpci_types_h_
#define _xpci_types_h_

#ifdef __KERNEL__
  #include <linux/kernel.h>
  #include <linux/types.h>
#else
  #include <limits.h>
  #include <sys/types.h>
#endif

#if defined(__WORDSIZE)
  #define SIZEOF_VOIDP __WORDSIZE
#elif defined(BITS_PER_LONG)
  #define SIZEOF_VOIDP BITS_PER_LONG
#elif defined(INTPTR_MIN)
  #if   INTPTR_MIN == INT32_MIN
    #define SIZEOF_VOIDP 32
  #elif INTPTR_MIN == INT64_MIN
    #define SIZEOF_VOIDP 64
  #endif
#else
  #error "Unhandled size of void pointer"
#endif

#  if SIZEOF_VOIDP == 64
typedef uint64_t pciaddr_t;
#else
typedef uint32_t pciaddr_t;
#endif


#endif
