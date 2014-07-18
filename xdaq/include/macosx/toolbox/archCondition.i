#ifndef _toolbox_archCondition_i_
#define _toolbox_archCondition_i_

inline toolbox::Condition::Condition ()
{
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
	return pthread_cond_wait ( &condVar_, &condMutex_ );
}

inline int toolbox::Condition::signal ()
{
	return pthread_cond_signal ( &condVar_ );
}

inline int toolbox::Condition::broadcast ()
{
	return pthread_cond_broadcast ( &condVar_ );
}

#endif 
