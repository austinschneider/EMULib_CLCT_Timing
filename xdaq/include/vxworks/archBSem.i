#ifndef _archBSem_i_
#define _archBSem_i_

inline BSem::BSem (BSem::State state = BSem::FULL)
{
	if ( state == FULL )
		sem_  = semBCreate(SEM_Q_FIFO, SEM_FULL);	
	else
		sem_  = semBCreate(SEM_Q_FIFO, SEM_EMPTY);

}

inline BSem::~BSem ()
{
	semDelete (sem_);
}



inline int BSem::give ()
{	
	return semGive (sem_);
}



inline int BSem::take ()
{	
	return semTake (sem_, WAIT_FOREVER);
}

inline int  BSem::take (struct timeval * timeout) 
{
	semTake (sem_, 60 * timeout->tv_sec);

}

inline int BSem::value ()
{
  if ( semTake (sem_, NO_WAIT) == 0)
    return BSem::FULL;
  else
    return BSem::EMPTY;
}
#endif /* ifndef archSemaphores_h */
