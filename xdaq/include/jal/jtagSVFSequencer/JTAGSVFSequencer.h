/**
 *     @class JTAGSVFSequencer
 *
 *     @short Sequencer of SVF Commands.
 *            
 *            There are two ways to use the class. In the first way, an SVF file ist first
 *            loaded using the loadSVFFile() method and then sequenced using the execute() methof. 
 *            In the secon way - using the execute_from_file() method - the SVF file is read command 
 *            by command and then executed. The first way has the adavantage that the SVF file syntax
 *            is completely checked before accessing the hardware. The second way has the advantage that 
 *            the SVF file does not have to be kept in memory.
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:59:09 $
 *
 *
**/

#ifndef jal_JTAGSVFSequencer_H
#define jal_JTAGSVFSequencer_H


#include "jal/jtagController/HardwareException.h"
#include "jal/jtagController/TimeoutException.h"
#include "jal/jtagController/OutOfRangeException.h"
#include "jal/jtagSVFSequencer/SVFSyntaxException.h"
#include "jal/jtagSVFSequencer/FileOpenException.h"

#include <vector>
#include <stdint.h>

namespace jal {

  class JTAGSVFCommand;
  class JTAGChain;

  class JTAGSVFSequencer {

  public:
    /// constructor
    JTAGSVFSequencer() : _override_error(false), _progress(0) {};

    /// destructor
    ~JTAGSVFSequencer();

    /// load an SVF sequence from an SVF file and store it. Return true if parsing is successful, false if not.
    /// the method checks the syntax of the SVF file, but cannot guarantee that there will be no errors when
    /// playing the file. For example, it cannot check, if STATE transitions are valid as it does not check the
    /// endstates of previous commands.
    bool loadSVFFile(const char *fn, double default_frequency = -1.)
      throw (jal::SVFSyntaxException,
	     jal::FileOpenException);

    /// execute the stored SVF sequence on a given JTAG chain
    bool execute(jal::JTAGChain& ch)
      throw (jal::HardwareException,
	     jal::TimeoutException,
	     jal::OutOfRangeException,
	     jal::SVFSyntaxException);

    /// execute the stored SVF sequence on multiple JTAG chains
    bool executeParallel(std::vector<jal::JTAGChain* > chains)
      throw (jal::HardwareException,
	     jal::TimeoutException,
	     jal::OutOfRangeException,
	     jal::SVFSyntaxException);

    /// load and execute an SVF sequence command by command without storing the sequence
    bool execute_from_file(char *fn, jal::JTAGChain& ch) const 
      throw (jal::HardwareException,
	     jal::TimeoutException,
	     jal::OutOfRangeException,
	     jal::SVFSyntaxException,
	     jal::FileOpenException);

    /// get the progress of the current execute() call (has to be called from a different thread)
    ///
    /// does not work with execute_from_file()
    /// returns the progress in per cent (0..100)
    uint32_t getProgress() const { return _progress; };

    /// print the commands in the sequence
    void print() const; 

    /// set flag to override errors (ATTENTION: this may damage the hardware)
    void setOverrideError(bool o) { _override_error = o; }

    // get a reference to the sequence
    std::vector<jal::JTAGSVFCommand *> const& getSequence() const { return _cmds;};
  private:
    std::vector<JTAGSVFCommand *> _cmds;
    bool _override_error;
    uint32_t _progress;
  };

}
// possible extensions to save memory: checkSVF: check but do not store, playSVF: load and play, save/retrieve EVF

#endif
