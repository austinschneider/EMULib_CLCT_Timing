// $Id: archBSem.i,v 1.3 2009/03/06 09:45:38 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#include <errno.h>
#include <unistd.h>

inline toolbox::BSem::BSem (BSem::State state = BSem::FULL)
	: state_(state)
{
	pthread_mutexattr_init(&attr_);
	pthread_mutex_init(&mutex_, &attr_);
	if (state == BSem::EMPTY) take();
}

inline toolbox::BSem::BSem (BSem::State state, bool recursive)
	: state_(state)
{
	pthread_mutexattr_init(&attr_);
	
	if (recursive)
	{
		pthread_mutexattr_settype(&attr_, PTHREAD_MUTEX_RECURSIVE);
	}
	
	pthread_mutex_init(&mutex_, &attr_);
	if (state == BSem::EMPTY) take();
}

inline toolbox::BSem::~BSem ()
{
	pthread_mutexattr_destroy(&attr_);
	pthread_mutex_destroy(&mutex_);
}



inline int toolbox::BSem::give ()
{
	int r = pthread_mutex_unlock(&mutex_);
	state_ = BSem::FULL;
	return r;
}



inline int toolbox::BSem::take ()
{
	int r = pthread_mutex_lock(&mutex_);
	state_ = BSem::EMPTY;
	return r;
}


inline int toolbox::BSem::take (struct timeval * t)
{
	int r = EBUSY; // assume mutex locked
	useconds_t timeLeft = (t->tv_sec * 1000000) + t->tv_usec;

	for (;;)
	{
		r = pthread_mutex_trylock(&mutex_);
		if (r == EBUSY)
		{
			// Check if time is up
			if (timeLeft == 0)
			{
				return r;
			}

			// Sleep for 100 ms before trying again
			(void) usleep (100000);

			// Reduce time left
			if (timeLeft > 100000)
			{
				timeLeft -= 100000;
			}
			else
			{
				timeLeft = 0;
			}
		}
		else
		{
			// got the mutex
			state_ = BSem::EMPTY;
			return r;	
		}
	}

	return r; // make compiler happy
}



inline int toolbox::BSem::value ()
{
	return state_;
}
  
