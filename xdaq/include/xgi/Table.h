// $Id: Table.h,v 1.2 2008/07/18 15:28:15 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xgi_Table_h_
#define _xgi_Table_h_

#include <vector>
#include <iostream>
#include <sstream>
#include <string>

namespace xgi
{	
	class Table
	{
		public:

		class Row
		{
			public:
			
			Row (const std::string& id);
			
			~Row();
			
			const std::string& getId();
			
			void addColumn(const std::string& name);
			
			std::vector<std::string>& getColumns();
			
			void render(std::ostream& out, bool even);
			
			private:
			
			std::vector<std::string> columns_;
			std::string id_;
		};

		Table(const std::string& id);
		
		~Table();
		
		std::vector<xgi::Table::Row>::iterator addRow(const std::string& id);
				
		std::vector<Row>& getRows();
		
		void addColumn (const std::string& name);
		
		std::vector<std::string>& getColumns();
		
		void render(std::ostream& out);
		
		private:
		
		std::string id_;
		std::vector<std::string> columns_;
		std::vector<Row> rows_;
	};

	std::ostream& operator<<(std::ostream& out, Table& ob);
}


#endif
