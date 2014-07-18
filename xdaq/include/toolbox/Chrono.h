// $Id: Chrono.h,v 1.4 2008/07/18 15:27:32 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_Chrono_h
#define _toolbox_Chrono_h

#include <sys/types.h> 
#include <sys/time.h>

namespace toolbox 
{

class Chrono
{
  public:
    
    double dsecs() ;
    suseconds_t dusecs();
    void start(size_t stamp);
    void stop(size_t stamp);
    double tstamp();

  protected:

	typedef struct timeval TimeSpec;
  
    TimeSpec start_ts_;
    TimeSpec stop_ts_;

    time_t dsecs_;
    suseconds_t dfsecs_; // Fraction of second
};

}

#endif /* ifndef Chrono */
