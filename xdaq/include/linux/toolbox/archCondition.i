// $Id: archCondition.i,v 1.2 2008/07/18 15:27:30 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

inline toolbox::Condition::Condition ()
{
	// w.b. important: existInfo_ has to be initialized to zero !
        // failing to do so , gives problems in timedwait()
	existInfo_ = 0;
	pthread_mutex_init ( &condMutex_, 0 );
	pthread_cond_init  ( &condVar_, 0 );
}

inline toolbox::Condition::~Condition ()
{
	pthread_mutex_destroy(&condMutex_);
	pthread_cond_destroy (&condVar_);
}



inline int toolbox::Condition::wait ()
{
  int r;
  pthread_mutex_lock(&condMutex_);
  
  while (existInfo_ == 0)
    r = pthread_cond_wait ( &condVar_, &condMutex_ );
  existInfo_ = 0;
  pthread_mutex_unlock(&condMutex_);
  return r;
}

inline int toolbox::Condition::signal ()
{
	int r;
	pthread_mutex_lock (&condMutex_);
	existInfo_ = 1;
	r = pthread_cond_signal ( &condVar_ );
	pthread_mutex_unlock (&condMutex_);
	return r;
}

inline int toolbox::Condition::broadcast ()
{
	int r;
	pthread_mutex_lock (&condMutex_);
	existInfo_ = 1;
	r = pthread_cond_broadcast ( &condVar_ );
	pthread_mutex_unlock (&condMutex_);
	return r;
}

// added by Wojciech BIALAS, CERN/UAT 20.01.2004
// modified 24.03.2005 for XDAQ3.1                                                                             
inline int toolbox::Condition::timedwait (time_t sec, suseconds_t usec = 0)
	throw (toolbox::exception::Timeout)
{
  int r;
  struct timeval now ;
  struct timeval interval ;
  struct timeval result ;
                                                                                
  if (sec || usec) 
  { 
  	// user has passed non zero time ...                                                                        
	  interval.tv_usec = usec ;
	  interval.tv_sec = sec ;

	  pthread_mutex_lock(&condMutex_);

	  gettimeofday(&now,0);
	  timeradd(&now,&interval,&result);

	     // WB: this does not work in std g++ compiler :
	     // TIMEVAL_TO_TIMESPEC(&result,&ttw_) ;
	     // WB: lets do it again manualy :
	     ttw_.tv_sec = result.tv_sec ;
	     ttw_.tv_nsec = result.tv_usec * 1000 ;
	     r = 0; 
	     while(existInfo_==0 && r != ETIMEDOUT) 
	     {
		r = pthread_cond_timedwait ( &condVar_, &condMutex_, &ttw_ );
		}
		
	     if (r==ETIMEDOUT) 
	     {
	     		pthread_mutex_unlock(&condMutex_);
		
			XCEPT_RAISE(toolbox::exception::Timeout, "Condition timeout");
		}                                                                                
  } 
  else 
  { 
  	// usec=0 and sec=0 , so we follow normal wait()                                                                           
	pthread_mutex_lock(&condMutex_);
	while (existInfo_ == 0)
	{
		r = pthread_cond_wait ( &condVar_, &condMutex_ );
	}
  }
  existInfo_ = 0;
  pthread_mutex_unlock(&condMutex_);
  return r;
}
