// $Id: BSem.h,v 1.3 2008/07/18 15:27:32 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_BSem_h_
#define _toolbox_BSem_h_

#include <sys/time.h>

#include "toolbox/archBSem.h"

namespace toolbox
{
	class BSem
	{
		public:
			typedef enum 
			{
				EMPTY = 0,
				FULL  = 1
			} State;

			BSem (BSem::State state);
			BSem (BSem::State state, bool recursive);
			virtual ~BSem ();

			//! Grant access to the mutex
			inline int give ();

			//! Obtain access to the mutex, blocks if mutex locked
			//
			inline int take(); // wait forever

			//! Obtains access to the mutex, blocks if mutex locked until timeout reached
			//
			inline int take (struct timeval * timeout);

			/*! Return the value of the mutex.
			\returns BSem::FULL if unlocked
			\returns BSem::EMPTY if locked
			*/
			inline int value();

			protected:
			BSem ();
			BSem & operator = (const BSem &);
			BSem (const BSem &);

			#include "toolbox/archBSemPrivate.i"
	};
}

#include "toolbox/archBSem.i"

#endif
