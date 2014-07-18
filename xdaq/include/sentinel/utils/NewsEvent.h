// $Id: NewsEvent.h,v 1.2 2008/07/18 15:27:29 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _sentinel_utils_NewsEvent_h_
#define _sentinel_utils_NewsEvent_h_

#include "toolbox/Properties.h"
#include "xdata/Serializable.h"
#include "xdata/Event.h"
#include <string>

namespace sentinel
{
    namespace utils
    {
        class NewsEvent: public xdata::Event
        {
	        public:
	
	        /*! Constructor: Pass the \param originator of this event.	
                In order to set information to be sent, retrieve the
                contained article with \function getArticle()
	        */
	        NewsEvent(void* originator=0);

	        /*! Constructor: Pass the \param article containing the information to be sent.
                All information is copied into the event and the original article may be discarded.
                Optionally, pass the originator of the event. 
	        */
	        NewsEvent(toolbox::Properties& article, void* originator=0);
	
	        /*! Return a pointer to the serializable associated with this event */
	        toolbox::Properties& getArticle();
	
	    protected:
            toolbox::Properties article_;
        };
    }
}
#endif
