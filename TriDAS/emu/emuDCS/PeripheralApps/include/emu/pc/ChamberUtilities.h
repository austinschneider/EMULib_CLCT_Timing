#ifndef ChamberUtilities_h
#define ChamberUtilities_h

#include <iostream>
#include <fstream>
#include <iomanip>


#include "emu/pc/DAQMB.h"
#include "emu/pc/TMB.h"
#include "emu/pc/CCB.h"
#include "emu/pc/MPC.h"
#include "emu/pc/RAT.h"
#include "emu/pc/TMB_constants.h"
#include "emu/pc/ALCTController.h"
#include "emu/pc/VMEController.h"

#include "emu/pc/StandAloneRoutine.h"


namespace emu {
  namespace pc {

/**
   Functions specific to a chamber which may use methods from several different core classes  
 */
class ChamberUtilities {
  //
public:
  //
  ChamberUtilities();
  virtual ~ChamberUtilities();
  //
  inline void RedirectOutput(std::ostream * Output) { 
    //
    thisTMB_->RedirectOutput(Output);
    thisDMB_->RedirectOutput(Output);
    thisCCB_->RedirectOutput(Output);
    thisMPC_->RedirectOutput(Output);
    MyOutput_ = Output ;
    //
  }
  //
  ////////////////////////////////////////////////
  // determine peripheral crate timing parameters
  ////////////////////////////////////////////////
  //
  ///When measuring synchronization parameters, choose to propagate the measured values from one step to the next (or not)
  inline void PropagateMeasuredValues(bool true_or_false) { use_measured_values_ = true_or_false; }
  //
  ///Perform multiple synchronization steps sequentially:
  void FindL1ADelays();
  void FindDAVDelays();
  void FindL1AAndDAVDelays();
  void Automatic();    // should be deprecated, since its name is not descriptive at all
  //
  /// When BC0 synchronization parameters change, perform this quick scan:
  void QuickTimingScan();
  //
  // clock phases...
  ///  CFEB -> TMB communication delays
  enum CFEBTiming_scanType {normal_scan, me11b_scan, me11a_scan, normal_new_scan, me11b_new_scan, me11a_new_scan, simple_pulse_scan, simple_inject_scan};
  void CFEBTiming();                           //default is normal_scan
  void CFEBTiming(CFEBTiming_scanType);
  void CFEBTiming_with_Posnegs(CFEBTiming_scanType);
  void CFEBTiming_with_Posnegs_simple_routine(bool is_new_scan, int time_delay, int cfeb_num, unsigned int layers, unsigned int pattern, int halfstrip, bool print_data = false);
  void CFEBTiming_with_Posnegs_basic_scan();
  void CFEBTiming_without_Posnegs();
  void CFEBTiming_Configure(int * tof = NULL);
  void CFEBTiming_PulseInject(bool is_inject_scan, int cfeb, unsigned int layer_mask, unsigned int pattern, unsigned int halfstrip, unsigned int n_pulses = 1, unsigned int pulse_delay = 0x4f);
  void CFEBTiming_Debug();
  void CFEBTiming_LayerMaskScan();
  void CFEBTiming_HalfStripScan();
  void SetCfebRxPosNeg(int posneg);
  void SetCfebRxClockDelay(int delay);
  void SetTMBL1ADelay(int delay);
  int GetTMBL1ADelay();
  void SetTMBInternalL1A(int delay);
	int GetTMBInternalL1ADelay();
  void ResyncDCFEBs();
  void SetDCFEBsPipelineDepth(int depth);
  void SetODMBPedestalMode();
  void CFEBTiming_ConfigureODMB();
  void Step_21();
  void configureCrate();
  void configure_21();
  void enable_21();
  int GetExtTrigDelay();
  void Clear_ODMB_FIFO();
  void Print_ODMB_FIFO();
  void Print_CLCT0();
  void Print_CFEB_Masks();
  template <size_t XS_per_CFEB>
  int GetOutputXStrip(int cfeb, int input_xstrip) {
  	const int N_CFEB_in_non_me11 = 5;
  	const int Max_HS_in_non_me11 = N_CFEB_in_non_me11*XS_per_CFEB - 1;
  	const int Min_CFEB_in_region_a = 0;
  	const int Max_CFEB_in_region_a = 3;
  	const int Min_HS_in_region_a = Min_CFEB_in_region_a*XS_per_CFEB;
  	const int Max_HS_in_region_a = Max_CFEB_in_region_a*XS_per_CFEB - 1;
  	const int Min_CFEB_in_region_b = 4;
  	const int Max_CFEB_in_region_b = 6;
  	const int Min_HS_in_region_b = Min_CFEB_in_region_b*XS_per_CFEB;
  	const int Max_HS_in_region_b = Max_CFEB_in_region_b*XS_per_CFEB - 1;

  	int tmb_compile_type = thisTMB_->GetTMBFirmwareCompileType();
  	int output_xs = -1;
  	if(tmb_compile_type == 0xa) {
  		output_xs = XS_per_CFEB*cfeb + input_xstrip;
  	}
  	else if(tmb_compile_type == 0xb) {
  		output_xs = Max_HS_in_non_me11 - (XS_per_CFEB*cfeb + input_xstrip);
  	}
  	else if(tmb_compile_type == 0xc) {
  		if(cfeb >= Min_CFEB_in_region_a && cfeb <= Max_CFEB_in_region_a)
  			output_xs = Min_HS_in_region_a + XS_per_CFEB*cfeb + input_xstrip;
  		else if(cfeb >= Min_CFEB_in_region_b && cfeb <= Max_CFEB_in_region_b)
  			output_xs = Max_HS_in_region_b - (XS_per_CFEB*(cfeb - Min_CFEB_in_region_b) + input_xstrip);
  	}
  	else if(tmb_compile_type == 0xd) {
  		if(cfeb >= Min_CFEB_in_region_a && cfeb <= Max_CFEB_in_region_a)
  			output_xs = Max_HS_in_region_a - (XS_per_CFEB*cfeb + input_xstrip);
  		else if(cfeb >= Min_CFEB_in_region_b && cfeb <= Max_CFEB_in_region_b)
  			output_xs = Min_HS_in_region_b + XS_per_CFEB*(cfeb - Min_CFEB_in_region_b) + input_xstrip;
  	}

  	return output_xs;
  }
  inline int GetOutputHalfStrip(int cfeb, int input_halfstrip) {
    return GetOutputXStrip<32>(cfeb, input_halfstrip);
  }
  inline int GetOutputStrip(int cfeb, int input_strip) {
    return GetOutputXStrip<16>(cfeb, input_strip);
  }
  template <size_t XS_per_CFEB>
  int GetInputXStrip(int output_xstrip) {
  	const int Min_CFEB_in_region_a = 0;
  	const int Max_CFEB_in_region_a = 3;
  	const int Min_CFEB_in_region_b = 4;
  	const int Max_CFEB_in_region_b = 6;

  	int tmb_compile_type = thisTMB_->GetTMBFirmwareCompileType();
  	int region = output_xstrip / XS_per_CFEB;
  	int input_xs = output_xstrip % XS_per_CFEB;
  	if(tmb_compile_type == 0xa) {

  	}
  	else if(tmb_compile_type == 0xb) {
  		input_xs = XS_per_CFEB - input_xs;
  	}
  	else if(tmb_compile_type == 0xc) {
  		if(region >= Min_CFEB_in_region_b && region <= Max_CFEB_in_region_b) {
  			input_xs = XS_per_CFEB - input_xs;
  		}
  	}
  	else if(tmb_compile_type == 0xd) {
  		if(region >= Min_CFEB_in_region_a && region <= Max_CFEB_in_region_a) {
  			input_xs = XS_per_CFEB - input_xs;
  		}
  	}
  	return input_xs;
  }
  inline int GetInputHalfStrip(int output_halfstrip) {
  	return GetInputXStrip<32>(output_halfstrip);
  }
  inline int GetInputStrip(int output_strip) {
		return GetInputXStrip<16>(output_strip);
	}
  template <size_t XS_per_CFEB>
  int GetInputCFEBByX(int output_xstrip) {
  	const int Max_CFEB_in_non_me11 = 4;
  	const int Min_CFEB_in_region_a = 0;
  	const int Max_CFEB_in_region_a = 3;
  	const int Min_CFEB_in_region_b = 4;
  	const int Max_CFEB_in_region_b = 6;

  	int tmb_compile_type = thisTMB_->GetTMBFirmwareCompileType();
  	int region = output_xstrip / XS_per_CFEB;
  	int cfeb = -1;
  	if(tmb_compile_type == 0xa) {
  		cfeb = region;
  	}
  	else if(tmb_compile_type == 0xb) {
  		cfeb = Max_CFEB_in_non_me11 - region;
  	}
  	else if(tmb_compile_type == 0xc) {
  		if(region >= Min_CFEB_in_region_a && region <= Max_CFEB_in_region_a) {
  			cfeb = region;
  		}
  		else if(region >= Min_CFEB_in_region_b && region <= Max_CFEB_in_region_b) {
  			cfeb = Min_CFEB_in_region_b + (Max_CFEB_in_region_b - region);
  		}
  	}
  	else if(tmb_compile_type == 0xd) {
  		if(region >= Min_CFEB_in_region_a && region <= Max_CFEB_in_region_a) {
  			cfeb = Min_CFEB_in_region_a + (Max_CFEB_in_region_a - region);
  		}
  		else if(region >= Min_CFEB_in_region_b && region <= Max_CFEB_in_region_b) {
  			cfeb = region;
  		}
  	}
  	return cfeb;
  }
  int GetInputCFEBByHalfStrip(int output_halfstrip) {
  	return GetInputCFEBByX<32>(output_halfstrip);
  }
  int GetInputCFEBByStrip(int output_strip) {
		return GetInputCFEBByX<16>(output_strip);
	}
  void halfset(int icrd,int ipln,int ihalf,int chan[][6][16]);
  //void DisableCCBL1A
  void CFEBTiming_DMBDebug(bool print_data = true, bool print_clct = true);
  int * CFEBTiming_L1AWindowScan(bool print_data = true, bool print_clct = true);
  int CFEBHalfStripToTMBHalfStrip(int cfeb, int halfstrip);

  void original_routine();
  void new_routine();

  int tmb_l1a_delay;
  int ccb_l1a_delay;

  struct CFEBTiming_Configuration {
  	int cfeb_pipeline_depth;
  	float dac;
  	float comp_thresh;

  	int clct_pattern_trig_en; //
  	int clct_ext_trig_en;
  	int tmb_allow_clct; //
  	int hs_pretrig_hit_thresh; //
  	int min_hits_pattern; //
  	int ignore_ccb_startstop; //
  	int layer_trigger_en; //
    int fifo_mode; //
    int fifo_tbins; //
    int fifo_pretrig; //
    int fifo_no_hits_raw; //


  	int tmb_internal_l1a;
  	int ccb_ext_trig_delay;
  	int tmb_l1a_delay;
  	int cfeb_rx_posneg;
  	int cfeb_rx_clock_delay;
  	inline CFEBTiming_Configuration():
					cfeb_pipeline_depth(0),
					dac(0),
					comp_thresh(0),
					clct_pattern_trig_en(1),
					clct_ext_trig_en(1),
					tmb_allow_clct(1),
					hs_pretrig_hit_thresh(5),
					min_hits_pattern(1),
					ignore_ccb_startstop(0),
					layer_trigger_en(0),
          fifo_mode(1),
          fifo_tbins(30),
          fifo_pretrig(5),
          fifo_no_hits_raw(0),
					tmb_internal_l1a(0),
					ccb_ext_trig_delay(0),
					tmb_l1a_delay(0),
					cfeb_rx_posneg(0),
					cfeb_rx_clock_delay(0)
  	{};
  	inline CFEBTiming_Configuration(const CFEBTiming_Configuration & o):
			cfeb_pipeline_depth(o.cfeb_pipeline_depth),
			dac(o.dac),
			comp_thresh(o.comp_thresh),
			tmb_internal_l1a(o.tmb_internal_l1a),
			clct_pattern_trig_en(o.clct_pattern_trig_en),
			clct_ext_trig_en(o.clct_ext_trig_en),
			tmb_allow_clct(o.tmb_allow_clct),
			hs_pretrig_hit_thresh(o.hs_pretrig_hit_thresh),
			min_hits_pattern(o.min_hits_pattern),
			ignore_ccb_startstop(o.ignore_ccb_startstop),
			layer_trigger_en(o.layer_trigger_en),
      fifo_mode(o.fifo_mode),
      fifo_tbins(o.fifo_tbins),
      fifo_pretrig(o.fifo_pretrig),
      fifo_no_hits_raw(o.fifo_no_hits_raw),
			ccb_ext_trig_delay(o.ccb_ext_trig_delay),
			tmb_l1a_delay(o.tmb_l1a_delay),
			cfeb_rx_posneg(o.cfeb_rx_posneg),
			cfeb_rx_clock_delay(o.cfeb_rx_clock_delay)
  	{};
  };

  inline void CFEBTiming_PrintConfiguration(CFEBTiming_Configuration & config) {
		(*MyOutput_) << std::setw(23) << "tmb_internal_l1a: " << std::setw(4) << config.tmb_internal_l1a << std::endl;
		(*MyOutput_) << std::setw(23) << "clct_pattern_trig_en: " << std::setw(4) << config.clct_pattern_trig_en << std::endl;
		(*MyOutput_) << std::setw(23) << "clct_ext_trig_en: " << std::setw(4) << config.clct_ext_trig_en << std::endl;
		(*MyOutput_) << std::setw(23) << "tmb_allow_clct: " << std::setw(4) << config.tmb_allow_clct << std::endl;
		(*MyOutput_) << std::setw(23) << "hs_pretrig_hit_thresh: " << std::setw(4) << config.hs_pretrig_hit_thresh << std::endl;
		(*MyOutput_) << std::setw(23) << "min_hits_pattern: " << std::setw(4) << config.min_hits_pattern << std::endl;
		(*MyOutput_) << std::setw(23) << "ignore_ccb_startstop: " << std::setw(4) << config.ignore_ccb_startstop << std::endl;
    (*MyOutput_) << std::setw(23) << "layer_trigger_en: " << std::setw(4) << config.layer_trigger_en << std::endl;
    (*MyOutput_) << std::setw(23) << "fifo_mode: " << std::setw(4) << config.fifo_mode << std::endl;
    (*MyOutput_) << std::setw(23) << "fifo_tbins: " << std::setw(4) << config.fifo_tbins << std::endl;
    (*MyOutput_) << std::setw(23) << "fifo_pretrig: " << std::setw(4) << config.fifo_pretrig << std::endl;
		(*MyOutput_) << std::setw(23) << "fifo_no_hits_raw: " << std::setw(4) << config.fifo_no_hits_raw << std::endl;
		(*MyOutput_) << std::setw(23) << "ccb_ext_trig_delay: " << std::setw(4) << config.ccb_ext_trig_delay << std::endl;
		(*MyOutput_) << std::setw(23) << "tmb_l1a_delay: " << std::setw(4) << config.tmb_l1a_delay << std::endl;
		(*MyOutput_) << std::setw(23) << "cfeb_rx_posneg: " << std::setw(4) << config.cfeb_rx_posneg << std::endl;
		(*MyOutput_) << std::setw(23) << "cfeb_rx_clock_delay: " << std::setw(4) << config.cfeb_rx_clock_delay << std::endl;
  }

  inline bool CFEBTiming_CheckCLCT(int cfeb, unsigned int layer_mask, unsigned int pattern, unsigned int halfstrip) {
  	bool is_good = true;
  	unsigned int n_layers = 0;
  	for(int i=0; i<6; ++i) {
  		n_layers += (layer_mask >> i) & 0x1;
  	}
  	thisTMB_->DecodeCLCT();
  	thisTMB_->GetCLCT0keyHalfStrip();
		is_good &= thisTMB_->GetCLCT0Nhit() == n_layers;
		is_good &= thisTMB_->GetCLCT0PatternId() == pattern;
		return is_good;
  }

  inline bool CFEBTiming_CheckVMECommunicaiton() { // Doesn't work yet
  	bool good = true;
  	//good &= thisDMB_->CheckVMEFirmwareVersion();

  	unsigned int odmb_firmware_version_expected = 0x306;
  	unsigned int odmb_fpga_id_expected = 0x8424A093;


  	std::cout << "position 0" << std::endl;
  	unsigned int odmb_firmware_version_read = thisDMB_->odmb_firmware_version();
  	std::cout << "position 1" << std::endl;
  	unsigned int odmb_fpga_id_read = thisDMB_->mbfpgaid();
  	std::cout << "position 2" << std::endl;

  	bool odmb_firmware_version_good = (odmb_firmware_version_expected == odmb_firmware_version_read);
  	std::cout << "position 3" << std::endl;
  	bool odmb_fpga_id_good = (odmb_fpga_id_expected == odmb_fpga_id_read);
  	std::cout << "position 3" << std::endl;


  	if(!odmb_firmware_version_good)
  		(*MyOutput_) << "BAD odmb_firmware_version: expected " << std::hex << odmb_firmware_version_expected << " read " << std::hex << odmb_firmware_version_read << std::endl;
  	std::cout << "position 4" << std::endl;
  	if(!odmb_fpga_id_good)
  		(*MyOutput_) << "BAD odmb_fpga_id: expected " << std::hex << odmb_fpga_id_expected << " read " << std::hex << odmb_fpga_id_read << std::endl;
  	std::cout << "position 5" << std::endl;

  	good &= odmb_firmware_version_good;
  	good &= odmb_fpga_id_good;
  	std::cout << "position 6" << std::endl;
  	good &= thisCCB_->CheckFirmwareDate();
  	std::cout << "position 7" << std::endl;

  	return good;
  }

  inline void CFEBTiming_ReadConfiguration(CFEBTiming_Configuration & config) {
  	thisTMB_->ReadRegister(seq_l1a_adr);
  	config.tmb_internal_l1a = thisTMB_->GetInternalL1a();

  	thisTMB_->ReadRegister(seq_trig_en_adr);
  	config.clct_pattern_trig_en = thisTMB_->GetReadClctPatternTrigEnable();
  	config.clct_ext_trig_en = thisTMB_->GetReadClctExtTrigEnable();

  	thisTMB_->ReadRegister(tmb_trig_adr);
  	config.tmb_allow_clct = thisTMB_->GetReadTmbAllowClct();

  	thisTMB_->ReadRegister(seq_clct_adr);
  	config.hs_pretrig_hit_thresh = thisTMB_->GetReadHsPretrigThresh();
  	config.min_hits_pattern = thisTMB_->GetReadMinHitsPattern();

  	thisTMB_->ReadRegister(ccb_trig_adr);
  	config.ignore_ccb_startstop = thisTMB_->GetReadIgnoreCcbStartStop();

  	thisTMB_->ReadRegister(layer_trg_mode_adr);
  	config.layer_trigger_en = thisTMB_->GetReadEnableLayerTrigger();


    thisTMB_->ReadRegister(seq_fifo_adr);
    config.fifo_mode = thisTMB_->GetReadFifoMode();
    config.fifo_tbins = thisTMB_->GetReadFifoTbins();
    config.fifo_pretrig = thisTMB_->GetReadFifoPreTrig();
    config.fifo_no_hits_raw = thisTMB_->GetReadFifoNoRawHits();

  	unsigned csrb5 = thisCCB_->ReadRegister(CCB::CSRB5);
  	config.ccb_ext_trig_delay = (csrb5 >> 8) & 0xff;

  	thisTMB_->ReadRegister(seq_l1a_adr);
  	config.tmb_l1a_delay = thisTMB_->GetL1aDelay();

  	thisTMB_->ReadRegister(phaser_cfeb0_rxd_adr); // Get phaser information
  	config.cfeb_rx_posneg = thisTMB_->GetReadCfeb0RxPosNeg();
		config.cfeb_rx_clock_delay = thisTMB_->GetReadCfeb0RxClockDelay();
  }

  inline bool CFEBTiming_CheckConfiguration(const CFEBTiming_Configuration & orig) {
  	bool same = true;
  	CFEBTiming_Configuration read(orig);
  	CFEBTiming_ReadConfiguration(read);
  	//CFEBTiming_PrintConfiguration(read);
  	std::cout << std::dec;
  	if(read.tmb_internal_l1a != orig.tmb_internal_l1a) {
  		(*MyOutput_) << std::setw(37) << "BAD tmb_internal_l1a: EXPECTED: " << std::setw(4) << orig.tmb_internal_l1a << " | READ: " << std::setw(4) << read.tmb_internal_l1a << std::endl;
  		same = false;
  	}
  	if(read.clct_pattern_trig_en != orig.clct_pattern_trig_en) {
  		(*MyOutput_) << std::setw(37) << "BAD clct_pattern_trig_en: EXPECTED: " << std::setw(4) << orig.clct_pattern_trig_en << " | READ: " << std::setw(4) << read.clct_pattern_trig_en << std::endl;
  		same = false;
  	}
  	if(read.clct_ext_trig_en != orig.clct_ext_trig_en) {
  		(*MyOutput_) << std::setw(37) << "BAD clct_ext_trig_en: EXPECTED: " << std::setw(4) << orig.clct_ext_trig_en << " | READ: " << std::setw(4) << read.clct_ext_trig_en << std::endl;
  		same = false;
  	}
  	if(read.tmb_allow_clct != orig.tmb_allow_clct) {
  		(*MyOutput_) << std::setw(37) << "BAD tmb_allow_clct: EXPECTED: " << std::setw(4) << orig.tmb_allow_clct << " | READ: " << std::setw(4) << read.tmb_allow_clct << std::endl;
  		same = false;
  	}
  	if(read.hs_pretrig_hit_thresh != orig.hs_pretrig_hit_thresh) {
  		(*MyOutput_) << std::setw(37) << "BAD hs_pretrig_hit_thresh: EXPECTED: " << std::setw(4) << orig.hs_pretrig_hit_thresh << " | READ: " << std::setw(4) << read.hs_pretrig_hit_thresh << std::endl;
  		same = false;
  	}
  	if(read.min_hits_pattern != orig.min_hits_pattern) {
  		(*MyOutput_) << std::setw(37) << "BAD min_hits_pattern: EXPECTED: " << std::setw(4) << orig.min_hits_pattern << " | READ: " << std::setw(4) << read.min_hits_pattern << std::endl;
  		same = false;
  	}
  	if(read.ignore_ccb_startstop != orig.ignore_ccb_startstop) {
  		(*MyOutput_) << std::setw(37) << "BAD ignore_ccb_startstop: EXPECTED: " << std::setw(4) << orig.ignore_ccb_startstop << " | READ: " << std::setw(4) << read.ignore_ccb_startstop << std::endl;
  		same = false;
  	}
  	if(read.layer_trigger_en != orig.layer_trigger_en) {
      (*MyOutput_) << std::setw(37) << "BAD layer_trigger_en: EXPECTED: " << std::setw(4) << orig.layer_trigger_en << " | READ: " << std::setw(4) << read.layer_trigger_en << std::endl;
      same = false;
    }
    if(read.fifo_mode != orig.fifo_mode) {
      (*MyOutput_) << std::setw(37) << "BAD fifo_mode: EXPECTED: " << std::setw(4) << orig.fifo_mode << " | READ: " << std::setw(4) << read.fifo_mode << std::endl;
      same = false;
    }
    if(read.fifo_tbins != orig.fifo_tbins) {
      (*MyOutput_) << std::setw(37) << "BAD fifo_tbins: EXPECTED: " << std::setw(4) << orig.fifo_tbins << " | READ: " << std::setw(4) << read.fifo_tbins << std::endl;
      same = false;
    }
    if(read.fifo_pretrig != orig.fifo_pretrig) {
      (*MyOutput_) << std::setw(37) << "BAD fifo_pretrig: EXPECTED: " << std::setw(4) << orig.fifo_pretrig << " | READ: " << std::setw(4) << read.fifo_pretrig << std::endl;
      same = false;
    }
    if(read.fifo_no_hits_raw != orig.fifo_no_hits_raw) {
      (*MyOutput_) << std::setw(37) << "BAD fifo_no_hits_raw: EXPECTED: " << std::setw(4) << orig.fifo_no_hits_raw << " | READ: " << std::setw(4) << read.fifo_no_hits_raw << std::endl;
      same = false;
  	}
  	if(read.ccb_ext_trig_delay != orig.ccb_ext_trig_delay) {
  		(*MyOutput_) << std::setw(37) << "BAD ccb_ext_trig_delay: EXPECTED: " << std::setw(4) << orig.ccb_ext_trig_delay << " | READ: " << std::setw(4) << read.ccb_ext_trig_delay << std::endl;
  		same = false;
  	}
  	if(read.tmb_l1a_delay != orig.tmb_l1a_delay) {
  		(*MyOutput_) << std::setw(37) << "BAD tmb_l1a_delay: EXPECTED: " << std::setw(4) << orig.tmb_l1a_delay << " | READ: " << std::setw(4) << read.tmb_l1a_delay << std::endl;
  		same = false;
  	}
  	if(read.cfeb_rx_posneg != orig.cfeb_rx_posneg) {
  		(*MyOutput_) << std::setw(37) << "BAD cfeb_rx_posneg: EXPECTED: " << std::setw(4) << orig.cfeb_rx_posneg << " | READ: " << std::setw(4) << read.cfeb_rx_posneg << std::endl;
  		same = false;
  	}
  	if(read.cfeb_rx_clock_delay != orig.cfeb_rx_clock_delay) {
  		(*MyOutput_) << std::setw(37) << "BAD cfeb_rx_clock_delay: EXPECTED: " << std::setw(4) << orig.cfeb_rx_clock_delay << " | READ: " << std::setw(4) << read.cfeb_rx_clock_delay << std::endl;
  		same = false;
  	}
  	return same;
  }

  inline void ConfigureTMB(const CFEBTiming_Configuration & config, int * cfeb_tof_delay = NULL) {

  	usleep(1000);

  	// Set up for this test...
  	thisTMB_->SetClctPatternTrigEnable(config.clct_pattern_trig_en);
  	thisTMB_->SetClctExtTrigEnable(config.clct_ext_trig_en);
  	thisTMB_->WriteRegister(seq_trig_en_adr);

  	usleep(1000);

  	thisTMB_->SetTmbAllowClct(config.tmb_allow_clct);
  	thisTMB_->WriteRegister(tmb_trig_adr);

  	usleep(1000);

  	thisTMB_->SetHsPretrigThresh(config.hs_pretrig_hit_thresh);
  	thisTMB_->SetMinHitsPattern(config.min_hits_pattern);
  	thisTMB_->WriteRegister(seq_clct_adr);

  	usleep(1000);

  	thisTMB_->SetIgnoreCcbStartStop(config.ignore_ccb_startstop);
  	thisTMB_->WriteRegister(ccb_trig_adr);

  	usleep(1000);

  	thisTMB_->SetEnableLayerTrigger(config.layer_trigger_en);
  	thisTMB_->WriteRegister(layer_trg_mode_adr);

  	usleep(1000);

  	int test_cfeb_tof_delay[5] = { thisTMB_->GetCfeb0TOFDelay(),
  		thisTMB_->GetCfeb1TOFDelay(),
  		thisTMB_->GetCfeb2TOFDelay(),
  		thisTMB_->GetCfeb3TOFDelay(),
  		thisTMB_->GetCfeb4TOFDelay() };

  	if(cfeb_tof_delay == NULL)
  		cfeb_tof_delay = test_cfeb_tof_delay;

  	thisTMB_->SetCfeb0TOFDelay(cfeb_tof_delay[0]);
  	thisTMB_->SetCfeb1TOFDelay(cfeb_tof_delay[1]);
  	thisTMB_->SetCfeb2TOFDelay(cfeb_tof_delay[2]);
  	thisTMB_->SetCfeb3TOFDelay(cfeb_tof_delay[3]);
  	thisTMB_->SetCfeb4TOFDelay(cfeb_tof_delay[4]);
  	thisTMB_->WriteRegister(vme_ddd1_adr); // Write phase and TOF delay to hardware
  	usleep(1000);
  	thisTMB_->WriteRegister(vme_ddd2_adr); //
  	usleep(1000);

  	// Begin new lines from Stan's code
  	thisTMB_->SetFifoMode(config.fifo_mode);
  	thisTMB_->SetFifoTbins(config.fifo_tbins);
  	thisTMB_->SetFifoPreTrig(config.fifo_pretrig);
  	thisTMB_->SetFifoNoRawHits(config.fifo_no_hits_raw);
  	thisTMB_->WriteRegister(emu::pc::seq_fifo_adr);

  	usleep(1000);

  	/*
  	int TimeDelay = 8;

  	std::cout << " TimeDelay " << TimeDelay << std::endl;
  	thisTMB_->tmb_clk_delays(TimeDelay,0);
  	usleep(1000);
  	thisTMB_->tmb_clk_delays(TimeDelay,1);
  	usleep(1000);
  	thisTMB_->tmb_clk_delays(TimeDelay,2);
  	usleep(1000);
  	thisTMB_->tmb_clk_delays(TimeDelay,3);
  	usleep(1000);
  	thisTMB_->tmb_clk_delays(TimeDelay,4);
  	usleep(1000);
  	*/
  	// End new lines from Stan's code

		thisTMB_->WriteRegister(vme_dddoe_adr);

  	thisTMB_->FireDDDStateMachine();
  	//
  	comparing_with_clct_ = true;
  	thisTMB_->StartTTC();
  	::sleep(1);
  	usleep(1000);
  }

  inline void CFEBTiming_ConfigureLevel(CFEBTiming_Configuration & config, int level = 0) {
  	(*MyOutput_) << "CFEBTiming Configure Level " << level << std::endl;
  	if(level <= 0) {
  		thisCCB_->setCCBMode(CCB::VMEFPGA);
			thisCCB_->hardReset();
			thisCCB_->setCCBMode(CCB::DLOG);

  		SetDCFEBsPipelineDepth(config.cfeb_pipeline_depth); // Set pipeline depth, does not have to be exact (~60)
  		usleep(1000);
  		thisTMB_->tmb_hard_reset_tmb_fpga(); // Hard reset the tmb to return to default settings
  		usleep(1000);
  		CFEBTiming_ConfigureODMB(); // Do some odmb configuration?
  		usleep(1000);
  		thisCCB_->l1aReset(); // Send a reset?
  		usleep(1000);
  		ResyncDCFEBs(); // Resync the dcfebs, apparently this is needed after the odmb config
  		usleep(1000);
  		thisCCB_->EnableL1aFromDmbCfebCalibX(); // Enable pulsing of the dcfebs
  		usleep(1000);
  		SetODMBPedestalMode(); // Tell the odmb to always accept data, regardless of timing
  		usleep(1000);
  		thisDMB_->set_dac(config.dac, 0); // Set the pulse height
  		usleep(1000);
  		thisDMB_->set_comp_thresh(config.comp_thresh); // Set the comparator chip threshold
  		usleep(1000);
  		if(thisDMB_->GetHardwareVersion() < 2)
  			thisDMB_->settrgsrc(0); // disable DMB's own trigger, LCT
  		usleep(1000);
  	}
  	if(level <= 1) {
			thisCCB_->setCCBMode(CCB::DLOG);
  		ConfigureTMB(config);
  		usleep(1000);
  	}
  	if(level <= 2) {
  		SetTMBInternalL1A(config.tmb_internal_l1a); // Disable the tmb's internal l1a
  		usleep(1000);
  		if(config.clct_ext_trig_en)
  			thisTMB_->EnableClctExtTrig(); // Enable l1a trigger from ccb
  		usleep(1000);
  		//thisCCB_->SetExtTrigDelay(0); // Set external l1a delay in ccb
  		thisCCB_->SetExtTrigDelay(config.ccb_ext_trig_delay); // Set external l1a delay in ccb
  		usleep(1000);
  		//SetTMBL1ADelay(80); // Set tmb l1a delay
  		SetTMBL1ADelay(config.tmb_l1a_delay); // Set tmb l1a delay
  		SetTMBL1ADelay(config.tmb_l1a_delay); // Set tmb l1a delay
  		usleep(1000);
  		SetCfebRxPosNeg(config.cfeb_rx_posneg); // Set posneg
  		usleep(1000);
  		SetCfebRxClockDelay(config.cfeb_rx_clock_delay); // Set the Rx clock delay (largely doesn't matter, only 1 bad value)
  		usleep(1000);
  	}
  }
  //
  const static int CFEBPatterns[9][6];
  const static int DMBCounters[60];
  //
  /// RAT -> TMB communication delays
  int  RatTmbDelayScan();
  void RpcRatDelayScan();       //rpc=0
  void RpcRatDelayScan(int rpc);
  //
  /// Determine all the timing parameters needed to establish ALCT<->TMB communication
  void ALCT_TMB_Loopback();
  //
  /// Find a "good enough" value of the alct_rx_clock_delay with alternating 1's and 0's sent from ALCT to TMB. 
  int  Find_alct_rx_with_ALCT_to_TMB_evenodd(int number_of_passes);
  //
  /// Find a "good enough" value of the alct_tx_clock_delay with alternating 1's and 0's looped back from TMB -> ALCT -> TMB.
  int  Find_alct_tx_with_TMB_to_ALCT_evenodd(int number_of_passes);
  //
  /// Check all the conductors in the cable with walking 1's looped back from TMB -> ALCT -> TMB
  int  TMB_to_ALCT_walking_ones(int number_of_passes);
  //
  /// same as above, but with "default number of passes...
  int  Find_alct_rx_with_ALCT_to_TMB_evenodd();
  int  Find_alct_tx_with_TMB_to_ALCT_evenodd();
  int  TMB_to_ALCT_walking_ones();
  //
  /// Thoroughly check the ALCT<->TMB communication by looping back random data from TMB -> ALCT -> TMB
  int ALCT_TMB_TimingUsingRandomLoopback();
  int ALCT_TMB_TimingUsingErrorCorrectionCode();
  void ThoroughRxTxScan(int rx_posneg, int tx_posneg, int pipe_depth);
  //
  // Define the timing of the BC0 from TMB -> ALCT -> TMB
  int ALCTBC0Scan();
  //
  inline void setLocalTmbBxnOffset(int value) { local_tmb_bxn_offset_ = value; }
  inline int getLocalTmbBxnOffset() { return local_tmb_bxn_offset_; }
  //
  //-----
  /// number of microseconds to wait between data reads
  inline void setPauseBetweenDataReads(int pause) { pause_between_data_reads_ = pause; }
  inline int getPauseBetweenDataReads() { return pause_between_data_reads_; }
  //
  /// number of times to read DMB scope/counter
  inline void setNumberOfDataReads(int number) { number_of_data_reads_ = number; }
  inline int getNumberOfDataReads() { return number_of_data_reads_; }
  //
  // ALCT-CLCT match timing
  //  int FindALCTinCLCTMatchWindow();
  //
  // DMB parameters
  int MeasureAlctDavCableDelay();
  int MeasureTmbLctCableDelay();
  int MeasureCfebDavCableDelay();
  //
  //
  //-----
  /// number of seconds to wait (sec) at each delay value setting
  inline void setPauseAtEachSetting(int pause) { pause_at_each_setting_ = pause; }
  inline int getPauseAtEachSetting() { return pause_at_each_setting_; }
  //
  /// Winner bits from MPC -> TMB
  int FindWinner();                          /// Use cosmic rays/pulsing from TTC
  int FindWinner(int number_of_pulses);      /// Use local pulsing of CFEB, data sent to MPC from TMB by VME command
  //
  // L1A accept windows
  inline void setMinAlctL1aDelayValue(int value) { min_alct_l1a_delay_value_ = value; }
  inline int getMinAlctL1aDelayValue() { return min_alct_l1a_delay_value_; }
  //
  inline void setMaxAlctL1aDelayValue(int value) { max_alct_l1a_delay_value_ = value; }
  inline int getMaxAlctL1aDelayValue() { return max_alct_l1a_delay_value_; }
  //
  inline void setMinTmbL1aDelayValue(int value) { min_tmb_l1a_delay_value_ = value; }
  inline int getMinTmbL1aDelayValue() { return min_tmb_l1a_delay_value_; }
  //
  inline void setMaxTmbL1aDelayValue(int value) { max_tmb_l1a_delay_value_ = value; }
  inline int getMaxTmbL1aDelayValue() { return max_tmb_l1a_delay_value_; }
  //
  int FindTmbAndAlctL1aDelay();
  int FindTMB_L1A_delay();
  int FindALCT_L1A_delay();
  //
  int  FindTMB_L1A_delay(int min_delay, int max_delay);  //set the min/max values by arguments... should go away...
  int  FindALCT_L1A_delay(int min_delay, int max_delay); //set the min/max values by arguments... should go away...
  //
  // scans to check functionality of electronics
  void ALCTChamberScan();  
  void CFEBChamberScan();
  void FindDistripHotChannels();
  //
  // useful peripheral crate functions
  void SetupRadioactiveTriggerConditions();
  void ReturnToInitialTriggerConditions();
  //
  void InitSystem();
  void InitStartSystem();
  //
  /// Setup to pulse the chamber so that both CLCT and ALCT fire on the ADB_SYNC command
  void SetupCoincidencePulsing();
  void SetupCoincidencePulsing(int amplitude);
  void SetupCoincidencePulsing(int amplitude, int pulse_signal);
  //
  void PulseRandomALCT(int delay = 0x6868);
  void PulseAllWires();
  //
  void PulseTestStrips(int delay = 0x6868);
  void LoadCFEB(int HalfStrip = -1, int CLCTInputs = 0x1f , bool enable=0);
  void PulseCFEB(int HalfStrip = -1, int CLCTInputs = 0x1f , bool enable=0);

  void LoadCFEB(int * hs, int CLCTInputs, bool enableL1aEmulator = 0);
  void PulseCFEB(int * hs, int CLCTInputs, bool enableL1aEmulator = 0);
  void PulseHalfstrips(int * hs, bool enableL1aEmulator = 0);
  //
  void InjectMPCData() ;
  //
  void PopulateDmbHistograms();
  void ReadAllDmbValuesAndScopes();
  void PrintAllDmbValuesAndScopes();
  //
  int  AdjustL1aLctDMB();
  //
  // analysis methods
  void ZeroTmbHistograms();
  void ZeroDmbHistograms();
  void ALCT_phase_analysis(int array_to_analyze[25][25]);
  int window_analysis(int * data, const int length);
  int window_counter;
  int DelayWhichGivesDesiredValue(float * vector_of_values_with_delay_index, 
				  const int min_delay, const int max_delay, 
				  int desired_value);
  void PrintHistogram(std::string label, int * histogram, int min, int max, int average);
  void PrintHistogram(std::string label, int * histogram, int min, int max, float average);
  float AverageHistogram(int * histogram, int min_value, int max_value);
  void bit_to_array(int data, int * array, const int size) ;
  inline int RoundOff(float RealNumber) { return ( (int) (RealNumber + 0.5) ); }
  inline int RoundOffForEvenWindowWidths(float RealNumber) { return ((int) RealNumber); }
  bool inSpecialRegion(int cfeb0tof,int cfeb1tof,int cfeb2tof,int cfeb3tof,int cfeb4tof,
		       int cfeb0rx ,int cfeb1rx ,int cfeb2rx ,int cfeb3rx ,int cfeb4rx ,
		       int cfeb0pn ,int cfeb1pn ,int cfeb2pn ,int cfeb3pn ,int cfeb4pn ,
		       CFEBTiming_scanType scanType);
  float determine_average_with_wraparound(int val1, int val2, int val3, int val4, int val5, const int max_val);
  float determine_average_with_wraparound(int val1, int val2, int val3, int val4, const int max_val);
  float special_region_function(float signed_rx);
  //
  //
  // Following should be deprecated?
  void ALCTScanDelays();
  //
  // Get and Set peripheral crate instances:
  inline void SetTMB(TMB * myTMB) {
      thisTMB_ = myTMB;
      thisALCT_ = myTMB->alctController();
      thisRAT_ = myTMB->getRAT();
      is_me11_ = ([] (bool b) {return b==0xc || b==0xd;})(thisTMB_->GetTMBFirmwareCompileType());
  }
  inline TMB * GetTMB() { return thisTMB_; }
  //
  inline void SetDMB(DAQMB * myDMB) {thisDMB_ = myDMB; }
  inline DAQMB * GetDMB() {return thisDMB_; }
  //
  inline void SetCCB(CCB * myCCB)   {thisCCB_ = myCCB; }
  inline CCB * GetCCB()   {return thisCCB_;}
  //
  inline void SetMPC(MPC * myMPC)   {thisMPC_ = myMPC; }
  //
  // Get xml values:
  inline int  GetCfebRxClockDelay(int CFEB)      { return thisTMB_->GetCfebRxClockDelay(CFEB); }
  inline int  GetAlctRxClockDelay()              { return thisTMB_->GetAlctRxClockDelay(); }
  inline int  GetAlctTxClockDelay()              { return thisTMB_->GetAlctTxClockDelay(); }
  inline int  GetAlctRxPosNeg()                  { return thisTMB_->GetAlctRxPosNeg(); }
  inline int  GetAlctTxPosNeg()                  { return thisTMB_->GetAlctTxPosNeg(); }
  inline int  GetRatTmbDelay()                   { return thisTMB_->GetRatTmbDelay() ; }
  inline int  GetRpcRatDelay()                   { return thisTMB_->GetRpc0RatDelay(); }
  inline int  GetMPCdelay()                      { return thisTMB_->GetMpcRxDelay(); }
  inline int  GetMPCTxDelay_configvalue()        { return thisTMB_->GetMpcTxDelay(); }
  inline int  GetAlctDavCableDelay_configvalue() { return thisDMB_->GetAlctDavCableDelay(); }
  inline int  GetTmbLctCableDelay_configvalue()  { return thisDMB_->GetTmbLctCableDelay(); }
  inline int  GetCfebDavCableDelay_configvalue() { return thisDMB_->GetCfebDavCableDelay(); }
  inline int  GetCfebCableDelay_configvalue()    { return thisDMB_->GetCfebCableDelay(); }
  inline int  GetTMBL1aTiming_configvalue()      { return thisTMB_->GetL1aDelay(); }
  inline int  GetALCTvpf_configvalue()           { return thisTMB_->GetAlctVpfDelay(); }
  inline int  GetALCTL1aDelay_configvalue()      { return thisTMB_->alctController()->GetWriteL1aDelay(); }
  inline int  GetAlctBx0Delay()                  { return thisTMB_->GetAlctBx0Delay(); }
  //
  // Get parameters from test summary results (not xml parameters):
  inline int  GetCFEBrxPhaseTest(int CFEB) { return CFEBrxPhase_[CFEB] ; }
  inline int  GetCFEBrxPosnegTest(int CFEB){ return CFEBrxPosneg_[CFEB] ; }
  inline int  GetCFEBrxdIntDelayTest(int CFEB) { return cfeb_rxd_int_delay[CFEB] ; }
  inline int  GetALCTrxPhaseTest()         { return ALCTrxPhase_ ; }
  inline int  GetALCTtxPhaseTest()         { return ALCTtxPhase_ ; }
  inline int  GetAlctRxPosNegTest()        { return ALCTrxPosNeg_ ; }
  inline int  GetAlctTxPosNegTest()        { return ALCTtxPosNeg_ ; }
  inline int  GetRatTmbDelayTest()         { return RatTmbDelay_ ; }
  inline int  GetRpcRatDelayTest()         { return GetRpcRatDelayTest(0); }
  inline int  GetRpcRatDelayTest(int rpc)  { return RpcRatDelay_[rpc] ; }
  inline int  GetMatchTrigAlctDelayTest()  { return match_trig_alct_delay_; }
  inline int  GetTmbBxnOffsetTest()        { return tmb_bxn_offset_used_; }
  inline int  GetMpcRxDelayTest()          { return MPCdelay_ ; }
  inline int  GetAlctDavCableDelayTest()   { return AlctDavCableDelay_; }
  inline int  GetTmbLctCableDelayTest()    { return TmbLctCableDelay_; }
  inline int  GetCfebDavCableDelayTest()   { return CfebDavCableDelay_; }
  inline int  GetTmbL1aDelayTest()         { return TMBL1aTiming_; }
  inline int  GetAlctL1aDelayTest()        { return ALCTL1aDelay_; }
  inline int  GetAlctBx0DelayTest()        { return ALCT_bx0_delay_; }
  //
  // Get measured values (not parameters)
  inline float GetActiveFebFlagToL1aAtDMB() { return AffToL1aAverageValue_; }
  inline float GetTmbDavValue()             { return TmbDavAverageValue_; }
  inline float GetCfebDavValue()            { return CfebDavAverageValue_; }
  inline float GetAlctDavValue()            { return AlctDavAverageValue_; }
  inline float GetActiveFebFlagToL1aScope() { return AffToL1aScopeAverageValue_; }
  inline float GetTmbDavScopeValue()        { return TmbDavScopeAverageValue_; }
  inline float GetCfebDavScopeValue()       { return CfebDavScopeAverageValue_; }
  inline float GetAlctDavScopeValue()       { return AlctDavScopeAverageValue_; }
  //
  inline float GetBestAverageAFFtoL1A()     { return best_average_aff_to_l1a_counter_; } 
  inline float GetBestAverageALCTDAVScope() { return best_average_alct_dav_scope_; } 
  inline float GetBestAverageCFEBDAVScope() { return best_average_cfeb_dav_scope_; } 
  //
  inline int  GetCFEBStripScan(int CFEB, int Strip) { return CFEBStripScan_[CFEB][Strip]; }
  inline int  GetALCTWireScan(int Wire)             { return ALCTWireScan_[Wire]; }
  //
  // Set the parameters from test summary file (not xml):
  inline void SetCFEBrxPhaseTest(int CFEB, int value) { CFEBrxPhase_[CFEB] = value ; }
  inline void SetALCTrxPhaseTest(int value)           { ALCTrxPhase_ = value ; }
  inline void SetALCTtxPhaseTest(int value)           { ALCTtxPhase_ = value ; }
  inline void SetAlctRxPosNegTest(int value)          { ALCTrxPosNeg_ = value ; }
  inline void SetAlctTxPosNegTest(int value)          { ALCTtxPosNeg_ = value ; }
  inline void SetRatTmbDelayTest(int value)           { RatTmbDelay_ = value ; }
  inline void SetRpcRatDelayTest(int rpc, int value)  { RpcRatDelay_[rpc] = value ; }
  inline void SetMatchTrigAlctDelayTest(int value)    { match_trig_alct_delay_ = value; }
  inline void SetMpcRxDelayTest(int value)            { MPCdelay_ = value; }
  inline void SetAlctDavCableDelayTest(int value)     { AlctDavCableDelay_ = value; }
  inline void SetTmbLctCableDelayTest(int value)      { TmbLctCableDelay_ = value; }
  inline void SetCfebDavCableDelayTest(int value)     { CfebDavCableDelay_ = value; }
  inline void SetTmbL1aDelayTest(int value)           { TMBL1aTiming_ = value; }
  inline void SetAlctL1aDelayTest(int value)          { ALCTL1aDelay_ = value; }
  //
  inline void SetCFEBStripScan(int CFEB, int Strip, int value) { CFEBStripScan_[CFEB][Strip] = value; }
  inline void SetALCTWireScan(int Wire, int value)             { ALCTWireScan_[Wire] = value; }
  //
  int BestCCBDelaySetting ;
  float CFEBMean[5];
  int TMB_L1a_timing ;
  int Find_ALCT_L1a_delay;
  int ALCT_L1a_delay ;
  int ALCTvpf;
  int beginning;
  //
private:
  //
  std::ostream * MyOutput_ ;
  int debug_;
  //
  bool use_measured_values_;
  int min_alct_l1a_delay_value_;
  int max_alct_l1a_delay_value_;
  int min_tmb_l1a_delay_value_; 
  int max_tmb_l1a_delay_value_; 
  int pause_at_each_setting_;
  int pause_between_data_reads_;
  int number_of_data_reads_;
  //
  int Npulses_;
  bool comparing_with_clct_;
  int me11_pulsing_;
  bool is_me11_;
  //
  bool UsePulsing_;
  //
  TMB * thisTMB_ ;
  DAQMB * thisDMB_ ;
  CCB * thisCCB_ ;
  ALCTController *thisALCT_ ;
  MPC * thisMPC_;
  RAT * thisRAT_;
  //
  int CFEBrxPhase_[5];
  int CFEBrxPosneg_[5];
  int cfeb_rxd_int_delay[5];
  int ALCTtxPhase_;
  int ALCTrxPhase_;
  int ALCTrxPosNeg_;
  int ALCTtxPosNeg_;
  int RatTmbDelay_;
  int RpcRatDelay_[2];
  int ALCTvpf_;
  int match_trig_alct_delay_;
  int MPCdelay_;
  int AlctDavCableDelay_;
  int TmbLctCableDelay_;
  int CfebDavCableDelay_;
  int TMBL1aTiming_;
  int BestALCTL1aDelay_;
  int ALCTL1aDelay_;
  //
  int local_tmb_bxn_offset_;
  int ALCT_bx0_delay_;
  int tmb_bxn_offset_used_;
  //
  int ScopeMin_;
  int ScopeMax_;
  int AffToL1aValueMin_;
  int AffToL1aValueMax_;
  int CfebDavValueMin_;
  int CfebDavValueMax_;
  int TmbDavValueMin_;
  int TmbDavValueMax_;
  int AlctDavValueMin_;
  int AlctDavValueMax_;
  //
  float AffToL1aAverageValue_;
  float CfebDavAverageValue_;
  float TmbDavAverageValue_;
  float AlctDavAverageValue_;
  float AffToL1aScopeAverageValue_;
  float CfebDavScopeAverageValue_;
  float TmbDavScopeAverageValue_;
  float AlctDavScopeAverageValue_;
  //
  float best_average_aff_to_l1a_counter_;
  float best_average_alct_dav_scope_;
  float best_average_cfeb_dav_scope_;
  //
  int CFEBStripScan_[5][32];
  int ALCTWireScan_[112];
  //
  int AlctInClctMatchWindowHisto_[16];
  //
  int AffToL1aScopeHisto_[5];
  int CfebDavScopeHisto_[5];
  int TmbDavScopeHisto_[5];
  int AlctDavScopeHisto_[5];
  int AffToL1aValueHisto_[255];
  int CfebDavValueHisto_[255];
  int TmbDavValueHisto_[255];
  int AlctDavValueHisto_[255];
  //
  int initial_clct_pretrig_thresh_;
  int initial_clct_pattern_thresh_;
  int initial_alct_pretrig_thresh_;
  int initial_alct_pattern_thresh_;
};

  } // namespace emu::pc
  } // namespace emu
#endif
