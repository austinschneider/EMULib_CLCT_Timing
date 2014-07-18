// $Id: AbstractTable.h,v 1.4 2008/07/18 15:28:08 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_AbstractTable_h_
#define _xdata_AbstractTable_h_

#include "xdata/Serializable.h"

namespace xdata {

class AbstractTable { 

	public:
	virtual ~AbstractTable()
	{
	}

	virtual std::string getColumnType(const std::string & name) throw (xdata::exception::Exception) = 0;
	virtual size_t getRowCount() = 0;
	virtual std::vector<std::string> getColumns() = 0;
	virtual void clear() = 0;
	virtual Serializable * getValueAt(size_t rowIndex, const std::string & name)  = 0;
	virtual void setValueAt(size_t rowIndex, const std::string & name, Serializable & object ) = 0;
	virtual void addColumn(const std::string & name, const std::string & type) throw (xdata::exception::Exception) = 0;

};


}

#endif
