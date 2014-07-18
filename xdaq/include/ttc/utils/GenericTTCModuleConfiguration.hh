#ifndef _ttc_utils_GenericTTCModuleConfiguration_hh_
#define _ttc_utils_GenericTTCModuleConfiguration_hh_


#include "log4cplus/logger.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>


namespace ttc
{

class GenericTTCModule;
class ConfigurationItem;

const std::string WORD_SEQUENCE_ADDNEW = "ADDSEQUENCE";
const std::string WORD_SEQUENCE_BEGIN = "BEGINSEQUENCE";
const std::string WORD_SEQUENCE_END = "ENDSEQUENCE";

//! abstract class to manage the configuration of a generic TTC module
class GenericTTCModuleConfiguration
{
public:

  GenericTTCModuleConfiguration(GenericTTCModule* _ttc_module);

  virtual ~GenericTTCModuleConfiguration();

protected:

  //! Lines of the configuration stream
  std::vector<std::string> config;

  //! number of line currently being processed (first line is 0)
  size_t line_number;

  //! map of parsed configuration items
  std::map<std::string, ConfigurationItem*> configuration_items;

  //! the TTC module to be configured
  GenericTTCModule* ttc_module;

  mutable log4cplus::Logger logger_;

  /**
   * Registers all commands which can appear in a configuration file for this TTC module.
   * To be implemented in subclass.
   * NOTE: Must be called in constructor of subclass, for initialization.
   */
  virtual void registerConfigurationCommands() = 0;

  /**
   * Reads the configuration file stream @param in and
   * configures the TTC module (using helper methods of this abstract interface).
   * To be implemented in subclass.
   */
  virtual void Configure(std::istream &in) = 0;

  //! Reads stream given by @param in and stores lines in vector config.
  void readLinesAndJoinContinuedLines(std::istream &in);

  //! Puts lines together which have been cut by "\".
  void joinContinuedLines();

  //! processes a single line of the read configuration file stream
  void processSingleLine(const std::string &current_line);

  /**
   * Extracts sequences from configuration file stream and registers them.
   * Removes lines them from vector config.
   */
  void extractSequences();

};

}


#endif
