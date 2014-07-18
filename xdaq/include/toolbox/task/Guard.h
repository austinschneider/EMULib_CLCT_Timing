// $Id$

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_task_Guard_h_
#define _toolbox_task_Guard_h_



namespace toolbox 
{
	namespace task 
	{
		template<typename Mutex> class Guard
    		{

    			private:
			
        			Mutex& m;
			
        			explicit Guard(Guard&);
        			Guard& operator=(Guard&);
			
    			public:
			
        			explicit Guard(Mutex& m_): m(m_)
        			{
            				m.take();
        			}
			
        			Guard(Mutex& m_,bool adopt): m(m_)
        			{
					if ( ! adopt )
						m.take();
				}

        			~Guard()
        			{
            				m.give();
        			}
    		};
	
	} // end of namespace task

} // end  of namespace toolbox



#endif
