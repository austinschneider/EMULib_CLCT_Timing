#ifndef _FMMHISTORYDUMPER_H
#define _FMMHISTORYDUMPER_H

/**
 *     @class FMMHistoryDumper
 *
 *     @short This class monitors the transition history memory of the FMM
 *
 *            There are 2 MB of history memory on an tts::FMM. Each hisotry entry 
 *            uses 16 bytes. There are therefore 128k entries int the history.
 *            The theoretic maximum speed at which the history memory is filled
 *            up is 4 byte / 25 ns, i.e. it could be full after 13 ms. In real
 *            operation a much lower rate of transitions is expected. To be on the
 *            save side, the online SW should check the write address at least 
 *            every 13 ms. 
 *
 *            The update method checks the write counter and the current system time 
 *            and issues a warning if more than 13 ms have passed since the last 
 *            activation. If available, new history data is read form the FMM and
 *            stored in a log file.
 *
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:53:27 $
 *
 *
 **/

#include "hal/PCIDevice.hh"
#include "tts/fmm/FMMHistoryItem.hh"

#include "toolbox/rlist.h"
#include "toolbox/task/Action.h"
#include "toolbox/lang/Class.h"

#include "xcept/Exception.h"

#include <fstream>
#include <stdint.h>

namespace toolbox {
  namespace task {	
    class WorkLoop;
  };
};

namespace tts {

  class FMMHistoryDumper : public toolbox::lang::Class {
  
  public:
    /// c-tor
    FMMHistoryDumper( HAL::PCIDevice& fmmdevice );

    /// d-tor
    virtual ~FMMHistoryDumper();

    /// start periodically monitoring the History memory
    ///
    /// this method will spawn a new thread
    void startDumper(std::string const & filename);

    /// stop periodically monitoring the history memory
    void stopDumper();

    /// update the history
    ///
    void updateHistory();

  private: 
    enum { FMMHistMemSize = 0x20000 }; // in units of 16-byte blocks

    /// update the history
    ///
    /// this method is run in an other thread
    bool autoUpdate(toolbox::task::WorkLoop* wl);


    HAL::PCIDevice& _fmm;

    /// the workloop 
    toolbox::task::WorkLoop* _wl;  
    toolbox::task::ActionSignature* _signature;

    // these vars belong to the update process
    uint64_t _t_start;

    /// last address written 
    uint32_t _lastAddress;

    std::ofstream _of;
  };

}

#endif
