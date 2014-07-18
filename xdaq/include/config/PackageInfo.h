// $Id: PackageInfo.h,v 1.4 2008/07/18 15:26:43 gutleber Exp $

/*************************************************************************
 * XDAQ Components for Distributed Data Acquisition                      *
 * Copyright (C) 2000-2009, CERN.			                 *
 * All rights reserved.                                                  *
 * Authors: J. Gutleber and L. Orsini					 *
 *                                                                       *
 * For the licensing terms see LICENSE.		                         *
 * For the list of contributors see CREDITS.   			         *
 *************************************************************************/

#ifndef _config_PackageInfo_h_
#define _config_PackageInfo_h_ 

#include <string>
#include <set>
#include <exception>
#include <iostream>
#include <sstream>
#include <algorithm>

#define GETPACKAGEINFO(SCOPE) \
   config::PackageInfo SCOPE::getPackageInfo() \
  {\
            return config::PackageInfo(SCOPE::package, SCOPE::versions, SCOPE::description, SCOPE::link, SCOPE::authors, SCOPE::summary, __DATE__, __TIME__);\
  }
  
//
// The following Macro works as follows:
// in a module file ModuleV.cc, the version definitions
// of other modules are included, e.g. OtherModule::versions.
// The function OtherModule::getPackageInfo() is however not
// included. If called, it will return the package info of
// the linked OtherModule. The parameter OtherModule::versions
// passed in the ckeckVersions however comes from the object
// file of ModuleV.cc and that includes a OtherModule::versions
// definition that may be different.
//
#define CHECKDEPENDENCY(SCOPE)\
    SCOPE::getPackageInfo().checkVersions(SCOPE::versions);
  
#define ADDDEPENDENCY(VARIABLE,SCOPE)\
   VARIABLE.insert(SCOPE::getPackageInfo().getName());
  
 /*
 	Usage:
	#if CORETOOLS_VERSION_CODE >= CORETOOLS_VERSION(3,7,2)
	...
	#endif
 */
#define CORETOOLS_VERSION(a,b,c) (((a) << 16) + ((b) << 8) + (c))

 /*
 	Usage:
	#if OS_VERSION_CODE >= OS_VERSION(2,4,0)
	...
	#endif
 */
#define OS_VERSION(a,b,c) (((a) << 16) + ((b) << 8) + (c))


 /*
 	Usage:
	#if <PACKAGE>_VERSION_CODE >= PACKAGE_VERSION_CODE(2,4,0)
	...
	#endif
	
	Usage for definition of package version:
	#define MYPACKAGE_VERSION_CODE PACKAGE_VERSION_CODE(3,9,0)
	
 */
#define PACKAGE_VERSION_CODE(a,b,c) (((a) << 16) + ((b) << 8) + (c))
#define PACKAGE_VERSION_STRING(a,b,c) CONFIG_QUOTE(a) "." CONFIG_QUOTE(b) "." CONFIG_QUOTE(c)
#define CONFIG_QUOTE(a) #a


namespace config 
{

class PackageInfo
{
        public:
	
        class VersionException : public std::exception 
        {
            public: 
	    
            VersionException(const std::string& what)
            {
		what_ = what;            
            }
	    
	    virtual ~VersionException () throw ()
	    {
	    }
            
            virtual const char * what() const throw() 
            {
                return what_.c_str();
            }
            
	    protected:
            
            std::string what_;
        };
        
        class ImplementationTooOldException : public VersionException
        {
            public:
            
            ImplementationTooOldException(const std::string& what):VersionException(what)
            {
            }
        };
        
        class ImplementationNewerException : public VersionException
        {
            public:
            
            ImplementationNewerException(const std::string& what):VersionException(what)
            {
            }
            
        };
    
        
        
        /*! Constructor: Provide the package name and a set of
            versions supported by this package in the following format:
	    x.y, x.y.z, x.y, .... where x and y are numbers
        */ 
        PackageInfo(const  std::string & name, const  std::string & vset, const std::string & description, const std::string& link, 
			const std::string & authors, const std::string& summary,const std::string& date, const std::string& time );
	
	/*! Return the package description text string */
	std::string getDescription();
	
	/*! Provide a description of the package, e.g. what the package implements. */
	void setDescription (const std::string & description);

	/*! Return a hyperlink for this module in string format */
	std::string getLink();
	
	/*! Provide a hyperlink for this module, e.g. a link to documentation */
	void setLink (const std::string & link);
	
	/*! Return the latest supported version of this package as a text string, e.g. 3.1 */
	std::string getLatestVersion();
	
	/*! Return an STL set of all supported versions */
	std::set<std::string, std::less<std::string> > getSupportedVersions();
	
	/*! Return the name of the package provided in the constructor as a string */
	std::string getName();
	
	/*! Return the name of the authors for this package */
	std::string getAuthors();
	
	/*! Return the name of the authors for this package */
	std::string getSummary();
	
	
	/*! Return the compile date */
	std::string getDate();
	
	/*! Return the compile time */
	std::string getTime();
 
	/*! Compare the currently supported versions of the package against
	    a set of versions offered by another environment in vset as a
	    list: "x.y, x.y, x.y.z, ...".
            If the two version sets overlap totally or partially the function simply returns.
            If the two sets are disjoint or if no matching version numbers can be found, one
            of two exceptions is raised. ImplementationTooOldException is raised, if the
 	    current implementation versions are older than the ones provided in vset. 
            ImplementationNewerException is raised if the current versions of the package are
            newer than the one provided in vset.
        */ 
        void checkVersions(const std::string& vset) throw (ImplementationTooOldException,ImplementationNewerException);
        
        protected:
        
	// Helper function to convert a comma separated list of items into a set
        std::set<std::string, std::less<std::string> > stringToVersionSet(const std::string & vset );
        
        std::string vset_; // list of versions supported by this package
        std::string name_; // name of the package
	std::string description_; // a description of the package
	std::string link_;
	std::string date_;
	std::string time_;
	std::string authors_;
	std::string summary_;
};	

}
#endif
