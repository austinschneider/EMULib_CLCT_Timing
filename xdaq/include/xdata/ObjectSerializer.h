// $Id: ObjectSerializer.h,v 1.4 2008/07/18 15:28:08 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_ObjectSerializer_h_
#define _xdata_ObjectSerializer_h_


namespace xdata {


class ObjectSerializer {
	public:	
	virtual ~ObjectSerializer()
	{
	}

	virtual std::string type() const = 0;
};


}

#endif
