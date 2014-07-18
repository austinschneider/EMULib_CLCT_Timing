// $Id: TableIterator.h,v 1.2 2008/07/18 15:28:08 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_TableIterator_h_
#define _xdata_TableIterator_h_

#include <iterator>

#include "xdata/Table.h"

namespace xdata {


class TableIterator : public std::iterator < std::input_iterator_tag, xdata::Table::Row>
{

	friend class xdata::Table;
	friend class xdata::Table::Row;

public:

   // Default constructor, makes a null TableIterator, equal to xdata::Table::end()
   TableIterator() ;

   // Constructor taking pointer to container, makes a TableIterator, equal to xdata::Table::begin()
   TableIterator(xdata::Table* pCont);

   TableIterator(const TableIterator & i);

   bool operator == (const TableIterator& rhs) const;

   bool operator != (const TableIterator& rhs) const;

   TableIterator& operator ++ () ;
   
   TableIterator operator ++ (int) ;
   
   TableIterator& operator -- () ;
   
   TableIterator operator -- (int) ;
   
   TableIterator& operator = (const TableIterator& rhs);
   
   xdata::Table::Row & operator *  ();
   
   xdata::Table::Row * operator -> ();

 
private:
	
   xdata::Table::Row m_Item;    // Current item from container
   xdata::Table* m_pCont;	// Pointer to container
   unsigned long m_Pos;		// Key to item in container
   bool	 m_End;			// Flag to indicate end of container reached
};

}

#endif
