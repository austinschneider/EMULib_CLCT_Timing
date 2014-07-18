// $Id: ObjectSerializer.h,v 1.5 2008/07/18 15:28:11 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_exdr_ObjectSerializer_h_
#define _xdata_exdr_ObjectSerializer_h_


#include "xdata/Serializable.h"
#include "xdata/ObjectSerializer.h"
#include "xdata/exception/Exception.h"
#include "xdata/exdr/InputStreamBuffer.h"
#include "xdata/exdr/OutputStreamBuffer.h"


namespace xdata {

namespace exdr {

class Serializer;

class ObjectSerializer : public xdata::ObjectSerializer {

	public:
	virtual ~ObjectSerializer()
	{
	}

	virtual void exportAll( xdata::exdr::Serializer * serializer,  xdata::Serializable * serializable, xdata::exdr::OutputStreamBuffer * buf) throw (xdata::exception::Exception) = 0;
					
	virtual void import (xdata::exdr::Serializer * serializer,  xdata::Serializable * serializable, xdata::exdr::InputStreamBuffer * buf ) throw (xdata::exception::Exception) = 0;
		
};

}}

#endif
