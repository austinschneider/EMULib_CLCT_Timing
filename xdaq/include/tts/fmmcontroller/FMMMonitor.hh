#ifndef FMMMONITOR_H
#define FMMMONITOR_H

/**
 *     @class FMMMonitor
 *
 *     @short Class responsible for the monitoring inside the XDAQ Application
 *
 *            - Once started the class periodically monitors the tts::FMMCard and updates the data members (monitorables)
 *            - An update can also be triggered bu a call to update()
 *            - Monitorables can be retrieved (for example for display in the web page.
 *            - Monitorables can be registered in an xdata::InfoSpace
 *            ? the Monitor registers itself as an ItemRetrieveListener for the infospace
 *
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.6 $
 *     $Date: 2008/07/16 11:33:38 $
 *
 *
 **/

#include "tts/fmmcontroller/FMMParameters.hh"

// to repesent data as xdata
#include "xdata/Vector.h"
#include "xdata/String.h"
#include "xdata/UnsignedShort.h"
#include "xdata/Integer32.h"
#include "xdata/Integer.h"
#include "xdata/UnsignedInteger32.h"
#include "xdata/UnsignedInteger64.h"
#include "xdata/Double.h"
#include "xdata/TimeVal.h"

// for callback
#include "xdata/Event.h"
#include "xdaq/Application.h"
#include "xdaq/Object.h"

#include <string>
#include <stdint.h>

namespace tts {

  // to control the hardware
  class FMMCard;
  class FMMDeadTimeMonitor;
  class FMMTransitionAnalyzer;

  class FMMMonitor : public xdaq::Object {

  public:
    /// c-tor
    ///
    /// The constructor creates one infospace for the card and up to 20 infospaces for the 20 inputs of the FMM
    ///
    /// @param fmm is a reference to an FMMCard which has to be valid during the lifetime of the FMMMonitor
    /// @param dtmon is a reference to an FMM Dead Time Monitor which has to be valid during the lifetime of the FMMMonitor
    ///
    FMMMonitor(xdaq::Application * owner,
	       tts::FMMCard& fmm,
	       tts::FMMDeadTimeMonitor& dtmon,
	       tts::FMMTransitionAnalyzer& fmmta,
	       std::string const& inputLabels,
	       std::string const& outputLabels,
	       bool isDual);

    /// d-tor
    virtual ~FMMMonitor();

    /// resets the last time tag to 
    void start();

    /// set the state name. to be called if the application state name changes (thread safe)
    void setStateName(std::string stateName);

    /// set the Run Number (thread safe)
    void setRunNumber(uint32_t runNumber);

    /// fire ItemGroupRetrieve on all infospaces in order to push monitoring data
    void pushAllInfoSpaces()
      throw (xcept::Exception);


  private:
    void updateAllInfoSpaces()
      throw (xcept::Exception);

    void lockAllInfoSpaces();
    void unLockAllInfoSpaces();

    void fillSrcIds(std::string const& inputLabels);
    void fillPartitionNumbers(std::string const& outputLabels);

    uint32_t counterIdxBusy(uint32_t io) { return io; };
    uint32_t counterIdxWarning(uint32_t io) { return io+22; };
    uint32_t counterIdxReady(uint32_t io) { return io+44; };
    uint32_t counterIdxOOS(uint32_t io) { return io+66; };
    uint32_t counterIdxError(uint32_t io) { return io+88; };

    /// the monitorable static data
    tts::FMMCard& _fmm;
    tts::FMMDeadTimeMonitor&  _dtmon;
    tts::FMMTransitionAnalyzer& _fmmta;

    bool _isDual;

    xdata::String             _stateName;
    xdata::UnsignedInteger32  _runNumber;

    xdata::UnsignedShort _geoslot;
    xdata::String        _serialNumber;

    xdata::InfoSpace * _isStatus;
    xdata::InfoSpace * _isIO[20];
    xdata::InfoSpace * _isIOdb[20];
    xdata::InfoSpace * _isPartition[2];

    /// the monitorable dynamic data - per FMM
    xdata::UnsignedInteger32  _historyMemoryAddress;
    xdata::UnsignedInteger32  _missedTransitionCount;
    xdata::String             _outputStateA;
    xdata::String             _outputStateB;

    xdata::Vector<xdata::Integer>	    _partitionNumbers;
    bool _outputIsActive[2];

    /// the monitorable dynamic data - per FMM input
    xdata::Vector<xdata::UnsignedShort>     _io;
    xdata::Vector<xdata::Integer>	    _srcId;
    xdata::Vector<xdata::Boolean>           _isActive;
    xdata::Vector<xdata::String>            _inputstates;
    xdata::Vector<xdata::Double>            _deadTimeFractions; // also include per-FMM output dead times

    xdata::Vector<xdata::UnsignedInteger64> _integralDeadTimes; // also include per-FMM output dead times
    xdata::UnsignedInteger64                _timeTag;           // Time tag for all infospaces
    xdata::UnsignedInteger64                _deltaT;            // ticks since last push of monitor data, all infospaces
    xdata::TimeVal                          _readTimeStamp;

    xdata::Vector<xdata::Vector<xdata::UnsignedInteger64> > _transitionCounters;
    xdata::Vector<xdata::Vector<xdata::Double> > _transitionFrequencies;
    xdata::Vector<xdata::Vector<xdata::UnsignedInteger64> > _timesPerState;

    xdata::Vector<xdata::UnsignedInteger64> _timesOtherState; // not R, B, W, E, OOS

    xdata::String             _stateNameLastPush;
    xdata::Vector<xdata::UnsignedInteger64> _integralDeadTimesLastPush;
    xdata::Vector<xdata::UnsignedInteger64> _integralTimesOther;
    xdata::Vector<xdata::UnsignedInteger64> _integralTimesOtherLastPush;
    xdata::Vector<xdata::Vector<xdata::UnsignedInteger64> > _timesPerStateLastPush;
    xdata::Vector<xdata::UnsignedInteger64> _timesOtherStateLastPush; // not R, B, W, E, OOS
    xdata::UnsignedInteger64                _timeTagLastPush;           // Time tag for all infospaces

  };
}
#endif
