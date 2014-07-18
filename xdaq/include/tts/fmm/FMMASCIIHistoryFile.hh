#ifndef _FMMASCIIHISTORYFILE_H
#define _FMMASCIIHISTORYFILE_H

/**
 *     @class FMMASCIIHistoryFile
 *
 *     @short ASCII storing the FMM transition history.
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:53:26 $
 *
 *
 **/

#include "tts/fmm/FMMHistoryFile.hh"
#include "tts/fmm/FMMHistoryItem.hh"

#include <fstream>
#include <string>

namespace tts {

  class FMMASCIIHistoryFile : public tts::FMMHistoryFile {

  public:
    /// c-tor 
    ///
    /// @param filename is the name of the history file
    FMMASCIIHistoryFile(std::string const& filename);

    /// d-tor
    virtual ~FMMASCIIHistoryFile();

    /// store a new history item
    ///
    /// @param hi is the history item to store
    /// @param trmiss indicates whether transitions were missed before/after??? this item
    virtual void save(tts::FMMHistoryItem const& hi, bool trmiss = false);

    /// close the history file
    virtual void close();

  private:
    std::ofstream _of;
  };

}



#endif
