// $Id: Serializable.h,v 1.8 2008/07/18 15:28:08 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_Serializable_h_
#define _xdata_Serializable_h_

#include <string>
#include <iostream>
#include "xdata/exception/Exception.h"

namespace xdata 
{
	class Serializable 
	{
		public:

		virtual ~Serializable() {}

		virtual std::string type() const = 0;

		virtual void setValue (const Serializable& s) { std::cout << "Set value of not implemented abstract xdata::Serializable" << std::endl; };

		//static Serializable * newByName(string name);

		// Comparison operators
		virtual int equals(const xdata::Serializable & s) = 0;

		//! Print value as a string
		virtual std::string toString() throw (xdata::exception::Exception) = 0;

		virtual void fromString(const std::string& value) throw (xdata::exception::Exception) = 0;

	};
}
#endif
