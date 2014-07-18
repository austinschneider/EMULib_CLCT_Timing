// $Id: StandardObjectPolicy.h,v 1.2 2008/07/18 15:27:34 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _toolbox_mem_StandardObjectPolicy_h_
#define _toolbox_mem_StandardObjectPolicy_h_

#include <iostream>

namespace toolbox {
namespace mem {

class StandardObjectPolicy 
{
  public:
    template<typename T> void dispose (T* object) 
    {
        delete object;
    }
};

}
}

#endif
