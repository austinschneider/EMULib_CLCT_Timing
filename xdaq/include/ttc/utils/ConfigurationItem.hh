#ifndef _ttc_utils_ConfigurationItem_hh_
#define _ttc_utils_ConfigurationItem_hh_


#include <iostream>
#include <string>

#include "log4cplus/logger.h"

namespace ttc
{

//! abstract base class representing a configuration item as parsed in configuration files for TTC modules
class ConfigurationItem
{
public:

  //! apply pre-parsed configuration line to GenericTTCModule
  virtual void configure(
      size_t line_number,
      const std::string& current_line,
      std::string varname,
      std::string string_val) = 0;

  //! write out configuration file string (line) corresponding to current status of GenericTTCModule
  virtual void write(std::ostream &out)
  {}

  ConfigurationItem() : logger_(log4cplus::Logger::getInstance("ConfigurationItem"))
  {}

  virtual ~ConfigurationItem()
  {}

protected:

  mutable log4cplus::Logger logger_;
};

}


#endif
