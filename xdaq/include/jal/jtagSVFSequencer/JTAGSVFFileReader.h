/**
 *     @class JTAGSVFFileReader
 *
 *     @short A JTAG SVF File Reader reads an SVF File command by command.            
 *   
 *            Comments are skipped. The commands are passed into a list
 *            of arguments. Arguments going over multiple lines are 
 *            combined.
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:59:09 $
 *
 *
**/

#ifndef jal_JTAGSVFFileReader_H
#define jal_JTAGSVFFileReader_H

#include "jal/jtagSVFSequencer/FileOpenException.h"

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

namespace jal {

  class JTAGSVFFileReader {
  public:
    /// constructor. Accepts path to the SVF file.
    JTAGSVFFileReader(std::string filename);

    /// destructor
    ~JTAGSVFFileReader();

    /// get next command
    bool nextCommand(std::vector<std::string> & args)
      throw (jal::FileOpenException);


  private:
    static int replace(std::string& input, const std::string& gone, const std::string& it, bool multiple);

    std::ifstream _filestream;
    std::string _commandline;
  };

}
#endif
