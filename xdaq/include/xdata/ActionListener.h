// $Id: ActionListener.h,v 1.3 2008/07/18 15:28:08 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_ActionListener_h_
#define _xdata_ActionListener_h_

#include "xdata/Event.h"

namespace xdata {

class ActionListener
{
	public:
	virtual ~ActionListener()
	{
	}

	virtual void actionPerformed(xdata::Event& e) = 0;
};

}

#endif
