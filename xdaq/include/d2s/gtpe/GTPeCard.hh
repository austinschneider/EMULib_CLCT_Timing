#ifndef _GTPECARD_H
#define _GTPECARD_H

/**
 *     @class GTPeCard
 *
 *     @short Class representing the basic functions of the GTPe
 *
 *            Higher-level classes use this class to read and write
 *            data to/from the GTPe and to perform basic functions
 *            such as a rest.
 *
 *            The GTPeCard class is using a HAL PCIDevice in order to 
 *            access the GTPe.
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.3 $
 *     $Date: 2008/05/26 09:43:45 $
 *
 *
 **/

#include "d2s/gtpe/GTPeStatus.hh"

#include "hal/PCIDevice.hh"
#include "hal/HardwareAccessException.hh"
#include "xcept/Exception.h"

#include "toolbox/BSem.h"
#include "tts/ipcutils/SemaphoreArray.hh"

#include <stdint.h>
#include <vector>
#include <string>

namespace tts {
  class TTSState;
}


DEFINE_EXCEPTION1(d2s, Timeout);
DEFINE_EXCEPTION1(d2s, OutOfRange);
DEFINE_EXCEPTION1(d2s, IncompatibleFirmware);

namespace d2s {

  class GTPeCard {
  
  public:
    enum { NCOUNTERS = 31 };

    /// c-tor
    /// 
    /// @param gtpe is a reference to the HAL PCIDevice. The GTPeCard takes ownership of this device
    ///        and deletes it in its destructor
    GTPeCard( HAL::PCIDevice* gtpe )
      throw (HAL::HardwareAccessException, 
	     ipcutils::exception::Exception,
	     d2s::exception::IncompatibleFirmware);

    /// d-tor
    virtual ~GTPeCard();

    /// read the firmware revision
    ///
    /// returns firmware revision as string YYMMDDVV
    std::string readFirmwareRevisison()
      throw (HAL::HardwareAccessException);

    /// reset the GTPe
    ///
    /// resets everything (the event, error etc. counters.
    /// partition definitions, clock mode, backpressure, ...)
    void globalReset()
      throw (HAL::HardwareAccessException);

    /// reset the GTPe counters
    ///
    /// resets the event, error etc. counters.
    void resetCounters()
      throw (HAL::HardwareAccessException);

    /// toggle if SLINK is required
    ///
    /// @param requ is true if the SLINK is required (default), false to ignore the SLINK
    void toggleSLINKRequired(bool requ)
      throw (HAL::HardwareAccessException);

    /// return if SLINK is required
    bool isSLINKRequired()
      throw (HAL::HardwareAccessException);


    /// start the SLINK
    ///
    /// has to be called before staring triggers
    void startSLINK()
      throw (HAL::HardwareAccessException);

    /// start the SLINK
    void stopSLINK()
      throw (HAL::HardwareAccessException);

    /// set the clock period (only applies in clocked mode).
    ///
    /// This clock frequency is split among the active DAQ partitions.
    ///
    /// @param n_25ns is the clock period in multiples of 25 ns
    void setClockPeriod(uint32_t n_25ns)
      throw (HAL::HardwareAccessException);

    /// read back the clock period in number of 25ns periods
    uint32_t readbackClockPeriod()
      throw (HAL::HardwareAccessException);


    /// toggle between random mode and clocked mode
    ///
    /// @param clocked is true for clocked mode, false for random mode
    void toggleClockedMode(bool clocked)
      throw (HAL::HardwareAccessException);

    /// is the GTPe in clocked mode?
    bool isClockedMode()
      throw (HAL::HardwareAccessException);

    /// start the trigger generation
    ///
    void startTriggers()
      throw (HAL::HardwareAccessException);

    /// pause the trigger generation
    ///
    /// this command can be used to stop triggers without resetting 
    /// the orbit, bx, and event counters 
    void pauseTriggers()
      throw (HAL::HardwareAccessException);

    /// resume the trigger generation
    void resumeTriggers()
      throw (HAL::HardwareAccessException);

    /// stop the trigger generation
    ///
    /// this resets the internal orbit counter, bx counter, global event counter,
    /// partition event number counters
    ///
    void stopTriggers()
      throw (HAL::HardwareAccessException);


    /// is the GTPe running?
    ///
    /// also returns true if running, but in paused mode
    bool isRunning()
      throw (HAL::HardwareAccessException);

    /// is the GTPe paused?
    bool isPaused()
      throw (HAL::HardwareAccessException);


    /// set the partition definition
    ///
    ///
    /// @param part_group_idx is the index of the partition group (0..7)
    /// @param selected_partitions is a bitfield of 8 bits selecting the partition that
    ///        should belong to the partition group
    ///        The partitions are predefined in the GTPe. Adding a partition to a 
    ///        partition group changes the trigger rules for that group.
    ///          @li Bit 0: pixel     trigger rule: 2 empty bx between triggers, empty orbit after 1s
    ///          @li Bit 1: tracker   trigger rule: 2 empty bx between triggers
    ///          @li Bit 2: preshower trigger rule; 1 empty bx between triggers, no more than 14 triggers in 5.4 microsec
    ///          @li Bit 3: ecal      trigger rule: 1 empty bx between triggers
    ///          @li Bit 4: hcal      trigger rule: 1 empty bx between triggers, no more than 22 trigger / orbit
    ///          @li Bit 5: muon csc  trigger rule: 2 empty bx between triggers
    ///          @li Bit 6: muon rpc  trigger rule: 1 empty bx between triggers
    ///          @li Bit 7: muon dt   trigger rule: 1 empty bx between triggers
    ///
    /// @param triggerrate is the trigger rate in Hz (maximum is 123.e3 Hz);
    ///
    /// the return value is the trigger rate in Hz that was actually after after rounding.
    double setPartitionDef(uint32_t part_group_idx, 
			   uint32_t selected_partitions,  
			   double triggerrate)
      throw (HAL::HardwareAccessException, d2s::exception::OutOfRange);

    /// set the partition definition
    ///
    ///
    /// @param part_group_idx is the index of the partition group (0..7)
    /// @param selected_partitions is a bitfield of 8 bits selecting the partition that
    ///        should belong to the partition group
    ///        The partitions are predefined in the GTPe. Adding a partition to a 
    ///        partition group changes the trigger rules for that group.
    ///          @li Bit 0: pixel     trigger rule: 2 empty bx between triggers, empty orbit after 1s
    ///          @li Bit 1: tracker   trigger rule: 2 empty bx between triggers
    ///          @li Bit 2: preshower trigger rule; 1 empty bx between triggers, no more than 14 triggers in 5.4 microsec
    ///          @li Bit 3: ecal      trigger rule: 1 empty bx between triggers
    ///          @li Bit 4: hcal      trigger rule: 1 empty bx between triggers, no more than 22 trigger / orbit
    ///          @li Bit 5: muon csc  trigger rule: 2 empty bx between triggers
    ///          @li Bit 6: muon rpc  trigger rule: 1 empty bx between triggers
    ///          @li Bit 7: muon dt   trigger rule: 1 empty bx between triggers
    ///
    /// @param rate_bits trigger rate as accepted by the GTPe (0 .. 0xffff);
    ///
    /// the return value is the trigger rate in Hz that was actually after after rounding.
    double setPartitionDef(uint32_t part_group_idx, 
			   uint32_t selected_partitions,  
			   uint32_t rate_bits)
      throw (HAL::HardwareAccessException, d2s::exception::OutOfRange);

    /// read back partition def
    uint32_t readbackPartitionDef(uint32_t part_group_idx)
      throw (HAL::HardwareAccessException, d2s::exception::OutOfRange);

    /// read back rate
    uint32_t readbackRate(uint32_t part_group_idx)
      throw (HAL::HardwareAccessException, d2s::exception::OutOfRange);

    /// read back rate in Hz
    double readbackRateHz(uint32_t part_group_idx)
      throw (HAL::HardwareAccessException, d2s::exception::OutOfRange);

    /// read back selected partitions
    uint32_t readbackSelectedPartitions(uint32_t part_group_idx)
      throw (HAL::HardwareAccessException, d2s::exception::OutOfRange);

    /// read back current total rate
    ///
    /// in clocked mode this is the clocked mode frequency,
    /// in random mode this is the sum of trigger rates in the partitions
    double readbackCurrentTotalRate()
      throw (HAL::HardwareAccessException);

    
    /// enable BC reset on LEMO 8; ATTN: aTTS outputs 0 and 1 become unusable
    void enableBCResetLEMO(bool enable)
      throw (HAL::HardwareAccessException);

    /// enable BC reset on LEMO 9; ATTN: aTTS outputs 0 and 1 become unusable
    void enableBunchStructureLEMO(bool enable)
      throw (HAL::HardwareAccessException);

    /// is the BCReset LEMO enabled?
    bool isBCResetLEMOEnabled()
      throw (HAL::HardwareAccessException);

    /// is the Bunch structure LEMO enabled?
    bool isBunchStructureLEMOEnabled()
      throw (HAL::HardwareAccessException);


    /// latch all counters - needs to be called before reading counters
    void latchCounters()
      throw (HAL::HardwareAccessException);

    /// read out a GTPe counter
    ///
    /// @param counter_idx is the index of the counter (0..3)
    ///        0 ... NTrig_all counter
    ///        1 ... NTrig counter (only accepted triggers)
    ///        2 ... NTrig_lost_TTS counter
    ///        3 ... NTrig_lost_EVM counter
    ///
    ///        5 ... read back of command register
    ///        6 ... read partition status
    uint32_t readCounter(uint32_t counter_idx)
      throw (HAL::HardwareAccessException, d2s::exception::OutOfRange);

    /// read a 64-bit counter
    ///
    /// 'U' and 'L' is appended to item in order to read the upper and lower part of the counter 
    uint64_t readCounter64bit(std::string item) 
      throw (HAL::HardwareAccessException);

    ///
    uint64_t readGlobalTimer() 
      throw (HAL::HardwareAccessException);

    ///
    uint64_t readCounterAcceptedTriggers() 
      throw (HAL::HardwareAccessException);

    ///
    uint64_t readCounterGeneratedTriggers() 
      throw (HAL::HardwareAccessException);

    ///
    uint64_t readCounterPartitionAcceptedTriggers(uint32_t part_idx) 
      throw (HAL::HardwareAccessException, d2s::exception::OutOfRange);

    ///
    uint64_t readLostEventsATTS(uint32_t part_idx) 
      throw (HAL::HardwareAccessException, d2s::exception::OutOfRange);

    ///
    uint64_t readLostEventsSTTS(uint32_t det_idx) 
      throw (HAL::HardwareAccessException, d2s::exception::OutOfRange);
    
    ///
    std::string getTriggerRuleName(uint32_t det_idx) 
      throw (d2s::exception::OutOfRange);

    ///
    uint64_t readLostEventsTriggerRule(uint32_t det_idx) 
      throw (HAL::HardwareAccessException, d2s::exception::OutOfRange);

    ///
    uint64_t readLostEventsSLINK() 
      throw (HAL::HardwareAccessException);

    ///
    uint64_t readLostEventsIntBuf() 
      throw (HAL::HardwareAccessException);

    /// read partition status register
    ///
    uint32_t readPartitionStatus() 
      throw (HAL::HardwareAccessException);


    /// latch and read a snapshot of the GTPe Status in a single operation
    ///
    /// this method and readCountersSnapshot() are needed in multi-threading environments since
    /// counters and status information are latched with the same latch command.
    ///
    /// the two methods use a common semaphore in order not to interrupt each other
    ///
    GTPeStatus readStatusSnapshot()
      throw (HAL::HardwareAccessException);

 
    /// simulate backpressure on aTTS ouputs
    ///
    /// @param part_group_idx is the index of the partition group (0..7)
    /// @param backpressure is true if backpressure should be set for this 
    ///        partition group. (a TTS busy signal will be sent)
    void toggleBackPressure (uint32_t part_group_idx,
			     bool backpressure)
      throw (HAL::HardwareAccessException, d2s::exception::OutOfRange);
  
 
    /// Set the aTTS output
    ///
    /// @param part_group_idx is the index of the partition group (0..7)
    /// @param force is true to simulate an output value, false to output the TCS partition status
    /// @param state is the TTSState to simulate (if simulate is true). Valid values: IDLE, WARNING, READY, BUSY       
    void forceATTSOutput (uint32_t part_group_idx,
			  bool force,
			  tts::TTSState const& state = tts::TTSState::READY)
      throw (HAL::HardwareAccessException, d2s::exception::OutOfRange);
  
    /// read back the ATTS output test value set by forceATTSOutput()
    tts::TTSState readbackATTSTestOutputState(uint32_t part_group_idx)
      throw (HAL::HardwareAccessException, d2s::exception::OutOfRange);

    /// read back the ATTS output enable mask for outputs [7..0] set by forceATTSOutput()
    ///
    /// bit = 1: use partition status; bit = 0: use test output value
    uint32_t readbackATTSOutputEnables() 
      throw (HAL::HardwareAccessException);

    /// Set the sTTS input mask
    ///
    /// @param mask[7..0] is the mask for inputs 7..0, 0 masks out the channel, 1 considers it as input  
    void setSTTSInputMask (uint32_t mask)
      throw (HAL::HardwareAccessException);

    /// Set the aTTS input mask
    ///
    /// @param mask[7..0] is the mask for inputs 7..0, 0 masks out the channel, 1 considers it as input  
    void setATTSInputMask (uint32_t mask)
      throw (HAL::HardwareAccessException);

    /// Read back the sTTS input mask
    ///
    /// the retuned mask[7..0] is the mask for inputs 7..0, 0 masks out the channel, 1 considers it as input  
    uint32_t readbackSTTSInputMask ()
      throw (HAL::HardwareAccessException);

    /// Read back the aTTS input mask
    ///
    /// the retuned mask[7..0] is the mask for inputs 7..0, 0 masks out the channel, 1 considers it as input  
    uint32_t readbackATTSInputMask ()
      throw (HAL::HardwareAccessException);


    /// get a referene to the HAL::PCIDevice
    HAL::PCIDevice& device() { return *_gtpe; };

    /// lock the GTPe master semaphore.
    /// The master semaphore protects GTPe hardware access and the semaphores used for locking DAQ and Det partitions
    ///
    /// throws a d2s::exception::Timeout exception if the operation timed out
    ///
    void lock()
      throw (ipcutils::exception::Exception,
	     d2s::exception::Timeout);

    /// un-lock the GTPe master semaphore.
    /// The master semaphore protects GTPe hardware access and the semaphores used for locking DAQ and Det partitions
    void unlock()
      throw (ipcutils::exception::Exception);

    /// lock a DAQ Partition
    ///
    /// @param i_part is the DAQ partition index (0-7)
    bool lockDAQPartition( uint32_t i_part )
      throw (ipcutils::exception::Exception,
	     ipcutils::exception::OutOfRange);


    /// un-lock a DAQ Partition
    ///
    /// @param i_part is the DAQ partition index (0-7)
    void unlockDAQPartition ( uint32_t i_part )
      throw (ipcutils::exception::Exception,
	     ipcutils::exception::OutOfRange);


    /// is a DAQ Partition lcoked?
    ///
    /// @param i_part is the DAQ partition index (0-7)
    bool isDAQPartitionLocked( uint32_t i_part )
      throw (ipcutils::exception::Exception,
	     ipcutils::exception::OutOfRange);


    /// what PID owns the DAQ Partition lock?
    ///
    /// @param i_part is the DAQ partition index (0-7)
    uint32_t getDAQPartitionLockOwnerPID( uint32_t i_part)
      throw (ipcutils::exception::Exception,
	     ipcutils::exception::OutOfRange);


    /// lock a detector partition
    ///
    /// @param i_part is the detector partition index (0-7)
    bool lockDetPartition( uint32_t i_det )
      throw (ipcutils::exception::Exception,
	     ipcutils::exception::OutOfRange);


    /// un-lock a detector partition
    ///
    /// @param i_part is the detector partition index (0-7)
    void unlockDetPartition ( uint32_t i_det )
      throw (ipcutils::exception::Exception,
	     ipcutils::exception::OutOfRange);


    /// is a detector partition locked?
    ///
    /// @param i_part is the detector partition index (0-7)
    bool isDetPartitionLocked( uint32_t i_det )
      throw (ipcutils::exception::Exception,
	     ipcutils::exception::OutOfRange);


    /// what PID owns the detector partition lock
    ///
    /// @param i_part is the detector partition index (0-7)
    uint32_t getDetPartitionLockOwnerPID( uint32_t i_det)
      throw (ipcutils::exception::Exception,
	     ipcutils::exception::OutOfRange);

    /// set the run number for a DAQ partition
    ///
    /// @param i_part is the DAQ partition index (0-7)
    /// @param runNumber is the 32-bit run number
    void setPartitionRunNumber(uint32_t i_part, uint32_t runNumber)
      throw (HAL::HardwareAccessException,
	     d2s::exception::OutOfRange);

    /// read back the partition run number
    ///
    /// @param i_part is the DAQ partition index (0-7)
    uint32_t readbackPartitionRunNumber(uint32_t i_part)
      throw (HAL::HardwareAccessException,
	     d2s::exception::OutOfRange);

    /// send resync signal to certain detector partitions
    ///
    /// @param detPartitionMask gives the detector partitions to resync (lower 8 bits)
    void resyncDetPartitions (uint32_t detPartitionMask)
      throw (HAL::HardwareAccessException);

  private: 
    std::string BCDtoString(uint32_t num, uint32_t ndigit=2);

    HAL::PCIDevice* _gtpe;

    toolbox::BSem _latch_semaphore;          // obsolete if whole GTPe is always locked.
    toolbox::BSem _semaphorearray_sema;
    ipcutils::SemaphoreArray _sa;
    bool _haveMasterLock;
  };

}
#endif
