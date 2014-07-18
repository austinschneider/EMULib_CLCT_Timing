#ifndef _FMMHISTORYFILE_H
#define _FMMHISTORYFILE_H

/**
 *     @class FMMHistoryFile
 *
 *     @short Abstract interface to a file storing the FMM transition history.
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:53:27 $
 *
 *
 **/

#include "tts/fmm/FMMHistoryItem.hh"

namespace tts {

  class FMMHistoryFile {

  public:
    /// c-tor 
    FMMHistoryFile() {};

    /// d-tor
    virtual ~FMMHistoryFile() {};

    /// store a new history item
    ///
    /// @param hi is the history item to store
    /// @param trmiss indicates whether transitions were missed before/after??? this item
    virtual void save(tts::FMMHistoryItem const& hi, bool trmiss = false) = 0;

    /// close the history file
    virtual void close() = 0;
  private:

  };

}



#endif
