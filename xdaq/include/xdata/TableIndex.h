// $Id: TableIndex.h,v 1.4 2008/07/18 15:28:08 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_TableIndex_h_
#define _xdata_TableIndex_h_

#include <list>
#include "xdata/Table.h"

/*
	xdata::Table t;
	
	list<std::string> unique;
	unique.push_back("a");
	
	xdata::Table::index i = t.index(unique);
	
	xdata::Table q;
	
	for each r in q
	i.insert(r);  
	
	// random access
	xdata::TableIndex::key k = i.key(r);
	i[k] = r;
	
	
	std::cout << " my name : " << i[key].getField("name"); << std::endl'
	
	

*/



namespace xdata
{
	class TableIndex
	{
		public:
			
		class Key 
		{
			public:
				Key(std::list<std::string> & key, xdata::Table::Row & r ) throw (xdata::exception::Exception);

				bool operator<(const Key& k) const;				
				bool operator>(const Key& k) const;				
				bool operator==(const Key& k) const;
				
				std::string toString();
				
			private:
				std::string key_;
		};
					
		// Constructor taking pointer to container, makes a TableIndex, equal to xdata::Table::begin()
		//
		TableIndex(xdata::Table* pCont, std::list<std::string> & key) throw (xdata::exception::Exception);			
			
		xdata::Table::Row & operator[](xdata::TableIndex::Key & k) throw (xdata::exception::Exception);			
		xdata::TableIndex::Key key(xdata::Table::Row & r) throw (xdata::exception::Exception);			
		xdata::TableIndex::Key insert( xdata::Table::Row & r) throw (xdata::exception::Exception);
						
		private:
		
		xdata::Table* m_pCont;	// Pointer to container
		std::map<xdata::TableIndex::Key, xdata::Table::iterator > index_;
		std::list<std::string>  key_;
	};
}

#endif
