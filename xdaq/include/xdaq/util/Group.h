// $Id: Group.h,v 1.2 2008/07/18 15:28:04 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _xdaq_util_Group_h_
#define _xdaq_util_Group_h_

#include <string>
#include "xdaq/exception/MemberNotFound.h"
#include "xdaq/exception/DuplicateMember.h"

namespace xdaq 
{

namespace util
{

	class Group
	{
		public:

		//! Create a new group with name.
		/*! A group is uniquely identified by its name, e.g. peer */
               
		Group (const std::string & name): name_(name)
		{
		
		}
		

		//! Retrieve the name that uniquely identifies a network device 
		std::string getName()
		{
			return name_;
		}
		
                
                //! Add a supported protocol by this network device
		void addMember(const std::string & member) throw (xdaq::exception::DuplicateMember)
		{
			if ( members_.find(member) == members_.end() ) 
			{
				members_[member] = 0; // symbolic link to members (a class I believe) 
			}
			else
			{
				std::string msg = toolbox::toString("Member %s already installed", member.c_str());
				XCEPT_RAISE(xdaq::exception::DuplicateMember, msg);
			}
		}
                
                 //! Remove the module from list 
                void removeMember(const std::string & member) throw (xdaq::exception::MemberNotFound)
		{
			if (members_.find(member) != members_.end() ) 
			{
				members_.erase(member);
			}
			else
			{
				std::string msg = toolbox::toString("No member % found",member.c_str());
				XCEPT_RAISE(xdaq::exception::ProtocolNotFound, msg);
			}

		}

                
                //! Retrieve all members of this group
		vector<std::string> getMembers()
		{
			std::vector<std::string> members;

			std::map<std::string, int, std::less<std::string> >::iterator i;
			for ( i = members_.begin(); i != members_.end(); i++ )
			{
				members.push_back((*i).first);
	
			}
			return members;

		}



		private:

		std::string name_;
                std::map<std::string, int, std::less<std::string> > members_;
	};
	}	

}

#endif
