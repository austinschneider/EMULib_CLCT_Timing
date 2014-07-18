// $Id: Serializer.h,v 1.3 2008/07/18 15:28:09 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_serializer_csv_Serializer_h_
#define _xdata_serializer_csv_Serializer_h_

#include <iostream>
#include <fstream>
#include "xdata/exception/Exception.h"
#include "xdata/csv/ObjectSerializer.h"
#include "xdata/Serializer.h"

namespace xdata {
namespace csv {

class Serializer : public xdata::Serializer 
{	
	public:
	
	/*! Construct a new CSV (Comma Separated Values) serializer with a file.
	* If the given file exists, it is opened. By default the open is done
	* for an append operation. If the parameter \param append is set to fault,
	* the file is opened in overwrite mode.
	* If the file does not exists, the serializer attempts to create it.
	* if any of the outlined operations fails, an exception is raised.
	*/
	Serializer(std::string filename, bool append = true) throw (xdata::exception::Exception);

	~Serializer();

	/*! Export the data type into the file indicated in the constructor.
	* The boolean flag \param append tells, if the values should be appended
	* to the end of the file, or if the values should be written into the beginning
	* of the file.
	*/
	void exportAll(xdata::Serializable * s, bool append = true) throw (xdata::exception::Exception);

	/*! Import data from the file indicated in the constructor into the given serializable.
	* This function is not yet implemented.
	*/
	void import (xdata::Serializable * s) throw (xdata::exception::Exception);

	protected:

	std::ofstream file_;
};



}}

#endif

