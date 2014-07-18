// $Id: Table.h,v 1.18 2008/07/18 15:28:08 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdata_Table_h_
#define _xdata_Table_h_

#include "toolbox/mem/CountingPtr.h"
#include "toolbox/mem/ThreadSafeReferenceCount.h"
#include "toolbox/mem/StandardObjectPolicy.h"

#include <map>
#include <string>
#include <vector>

#include "xdata/Serializable.h"
#include "xdata/exception/Exception.h"
#include "xdata/AbstractTable.h"
#include "xdata/AbstractVector.h"

namespace xdata {

class TableIterator;


class Table: public xdata::Serializable, public xdata::AbstractTable
{
	public:
	
	typedef toolbox::mem::CountingPtr<Table, toolbox::mem::ThreadSafeReferenceCount, toolbox::mem::StandardObjectPolicy> Reference;
	
	//static size_t const MaxRows = 0xFFFFFFFFU;	
	//static size_t const MaxColumns = 0xFFFFFFFFU;	
	
	enum { MaxRows = 0xFFFFFFFFU, MaxColumns = 0xFFFFFFFFU };
	
	typedef xdata::TableIterator iterator;
	
	class Row 
	{
		friend class Table;
	
		public:
		
		Row(iterator & i);
		
		Row(const Row & rhs) throw (xdata::exception::Exception);
		
		xdata::Serializable * getField(const std::string & name) throw (xdata::exception::Exception);
		
		void setField ( const std::string & name, Serializable & object ) throw (xdata::exception::Exception);
		
		Row & operator=(const Row & rhs) throw (xdata::exception::Exception);
		
		protected:
		
		iterator & i_;
	};
	// case-independent (ci) string less_than
	// returns true if s1 < s2
	struct ci_less : std::binary_function<std::string, std::string, bool>
	{
	
		// case-independent (ci) compare_less binary function
		struct nocase_compare : public std::binary_function<unsigned char,unsigned char,bool> 
		{
			bool operator() (const unsigned char& c1, const unsigned char& c2) const 
			{ 
				return tolower (c1) < tolower (c2); }
			};
			
			bool operator() (const std::string & s1, const std::string & s2) const
			{
				return lexicographical_compare (s1.begin (), s1.end (),   // source range
					s2.begin (), s2.end (),   // dest range
					nocase_compare ());  // comparison
			}
	}; // end of ci_less
	
	Table() throw (xdata::exception::Exception);
	
	//! Copy constructor creates a new table from another table with a deep copy
	//
	Table(const Table & t) throw (xdata::exception::Exception);
	
	//! Create a table from the column definition of another table, \sa getTableDefinition()
	//
	Table(std::map<std::string, std::string, ci_less> & columns);
	
	virtual ~Table();
	
	Table & operator=(const Table & b) throw (xdata::exception::Exception);

	int operator==(const Table & t);

	int operator!=(const Table & t);
	
	int equals(const xdata::Serializable & s);
	
	void setValue(const xdata::Serializable & s) throw (xdata::exception::Exception);
	
	std::string type() const;
	
	std::string toString() throw (xdata::exception::Exception);
		
	std::string getColumnType(const std::string & name) throw (xdata::exception::Exception);
	
	// Abstract Table interface
	
	size_t getRowCount();
	
	std::vector<std::string> getColumns();
	
	void clear();
	
	xdata::Serializable * getValueAt(size_t rowIndex, const std::string & name)
		throw (xdata::exception::Exception);
	
	void setValueAt(size_t rowIndex, const std::string & name, Serializable & object )
		throw (xdata::exception::Exception);
	
	void addColumn(const std::string & name, const std::string & type) throw (xdata::exception::Exception);
	void removeColumn(const std::string & name) throw (xdata::exception::Exception);
	
	//! reserve memory for entries ( number of rows is invariant )
	void reserve(size_t entries) throw (xdata::exception::Exception);
	
	std::map<std::string, std::string, ci_less >&
		getTableDefinition();

	void writeTo(std::ostream & stream);
	void readFrom(std::istream & stream);
	void fromString(const std::string& value) throw (xdata::exception::Exception);

	// ! Iterator methods

	iterator begin();
	
	iterator end();
	
	// This is similar to an STL vector iterator
	iterator erase(iterator pos);
	
	/*
	
	iterator erase(iterator first, iterator last);
	iterator insert(iterator pos, const Row & value);
	
	*/
	
	std::pair<iterator, bool> insert(Row & value) throw (xdata::exception::Exception);
	
	//! Append an uninitialized row at the end of the table and return an iterator pointing to this row
	//
	iterator append() throw (xdata::exception::Exception);
	

	/*! 
	 The result from the cartesian product of n sets, is a set of 
	 all possible ordered tuples, containing on i-th place an element from i-th set. 
	 For example, the cartesian product of {a,b,c} and {c,d,e} is 
	 {(a,c),(a,d),(a,e),(b,c),(b,d),(b,e),(c,c),(c,d),(c,e)}.
	 Formally, the cartesian product of  two sets A and B (written as A x B) is the set 
	 of tuples (a, b) with a element of A and b element of B. 
	 If any of the parameter tables is null, the function returns null
	*/
	static xdata::Table * cartesianJoin(xdata::Table * t1,  xdata::Table * t2)
		throw (xdata::exception::Exception);

	/*!
	Append the rows of table \param source to table \param destination
	The columns of the two tables must match.
	If the \param destination is null, the function raises an exception
	If the \param source is null, the function returns the unmodified destination
	*/
	static void merge(xdata::Table * destination,  xdata::Table * source)
		throw (xdata::exception::Exception);
	
	/*!
	If a table has columns of table type (nested tables), tis
	function will denormalize the nested tables and return a
	new, flattenized table.
	*/
	static xdata::Table * denormalize(xdata::Table * t) 
		throw (xdata::exception::Exception);
		
	public:

	std::map<std::string, std::string, ci_less > columnDefinitions_;
	std::map<std::string, xdata::AbstractVector *, ci_less > columnData_;
	size_t numberOfRows_; 
	size_t memorySize_; 
};

} // end namescape xdata

#endif

