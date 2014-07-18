#ifndef STANDALONEROUTINE_H
#define STANDALONEROUTINE_H

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for memset
#include <iomanip>
#include <cmath>
#include <unistd.h>
#include <string>
#include <vector>
#include <algorithm>

#include "emu/pc/VMEModule.h"
#include "emu/pc/Crate.h"

// Don't forget to set the board pointers after creating the class object

// CFEBTiming_DMBDebug is the primary method to call, it will scan for the l1a window and then begin the actual test if it finds one
// L1AWindowScan searches for the l1a window needed to read out the data
// Sometimes the TMB doesn't see the l1a (we've been trying to debug this as well), just retry the scan until it does, it will either work for the whole test or none of it

// Some of these don't have preprocessor tags (who knows why...) but do need to be included
// Uncomment them as needed
/*
#include "emu/pc/DAQMB.h"
#include "emu/pc/TMB.h"
#include "emu/pc/CCB.h"
#include "emu/pc/MPC.h"
#include "emu/pc/RAT.h"
#include "emu/pc/TMB_constants.h"
#include "emu/pc/ALCTController.h"
#include "emu/pc/VMEController.h"
*/


namespace emu {
	namespace pc {

class StandAloneRoutine {

public:

int debug_;
bool comparing_with_clct_;
int me11_pulsing_;
int CFEBPatterns[9][6];
TMB * thisTMB_ ;
DAQMB * thisDMB_ ;
CCB * thisCCB_ ;
MPC * thisMPC_ ;
std::ostream * MyOutput_ ;

inline StandAloneRoutine() {
	debug_ = 1;
	MyOutput_ = &std::cout;
	thisTMB_ = NULL;
	thisDMB_ = NULL;
	thisCCB_ = NULL;
	thisMPC_ = NULL;

	int patterns[9][6] = {
		{5, 2, 0, -2, -4, -5},
		{-5, -2, 0, 2, 4, 5},
		{4, 2, 0, -2, -4, -4},
		{-4, -2, 0, 2, 4, 4},
		{3, 1, 0, -1, -2, -3},
		{-3, -1, 0, 1, 2, 3},
		{2, 1, 0, -1, -2, -2},
		{-2, -1, 0, 1, 2, 2},
		{0, 0, 0, 0, 0, 0}
	};

	for(int i=0; i<9; ++i) {
		for(int j=0; j<6; ++j) {
			CFEBPatterns[i][j] = patterns[i][j];
		}
	}
}

virtual ~StandAloneRoutine();

inline void RedirectOutput(std::ostream * Output) {
    //
    thisTMB_->RedirectOutput(Output);
    thisDMB_->RedirectOutput(Output);
    thisCCB_->RedirectOutput(Output);
    thisMPC_->RedirectOutput(Output);
    MyOutput_ = Output ;

    ;
}

inline void LoadCFEB(int HalfStrip = -1, int CLCTInputs = 0x1f, bool enableL1aEmulator = 0){
	//
	if ( enableL1aEmulator ) thisTMB_->EnableInternalL1aSequencer();
	thisTMB_->DisableCLCTInputs();
	thisTMB_->SetCLCTPatternTrigger();
	//
	thisDMB_->set_comp_thresh(0.1);
	thisDMB_->set_dac(0.5,0);
	//
	if (HalfStrip == -1 ) HalfStrip = int(rand()*31./(RAND_MAX+1.0));
	//
	if (debug_) std::cout << " -- Injecting CFEB in halfstrip = " << std::dec << HalfStrip
			<< " into CLCT inputs = 0x" << std::hex << CLCTInputs << std::endl;
	//
	//thisTMB->DiStripHCMask(HalfStrip/4-1); // counting from 0; //Bad...requests L1a....
	//
	int hp[6]; memset(hp, 0, sizeof(hp));
	//
	if (comparing_with_clct_) {
		//
		// The CLCT key-layer has been moved from layer 3 to layer 2.
		// As a result, for a staggered, non-bending pattern, the key 1/2-strip
		// determined by the CLCT is changed by 1.
		//
		for (int layer = 0; layer < 6; layer++ ) {
			// make a very slanted road.  In addition, for ME1/1, need to "unstagger" the strips...
			if (layer == 0) hp[layer] = HalfStrip + 4 + me11_pulsing_;
			if (layer == 1) hp[layer] = HalfStrip + 2;
			if (layer == 2) hp[layer] = HalfStrip     + me11_pulsing_;
			if (layer == 3) hp[layer] = HalfStrip - 2;
			if (layer == 4) hp[layer] = HalfStrip - 4 + me11_pulsing_;
			if (layer == 5) hp[layer] = HalfStrip - 5;
			//
			// The following is needed for NON me11 chambers
			if (me11_pulsing_ == 0) hp[layer]++;
		}
		//
	} else{
		//
		for (int layer = 0; layer < 6; layer++ )
			hp[layer] = HalfStrip;
	}
	//
	// Set the pattern
	//
	thisDMB_->trigsetx(hp,CLCTInputs);
	//
	thisTMB_->EnableCLCTInputs(CLCTInputs);
	//
	// Inject it (pulse the CFEBs)
	//
	thisCCB_->setCCBMode(CCB::VMEFPGA);
	thisCCB_->WriteRegister(0x28,0x7878);  //4Aug05 DM changed 0x789b to 0x7862
	//
	return;
}
//
inline void LoadCFEB(int * hs, int CLCTInputs, bool enableL1aEmulator = 0){
	//
	if ( enableL1aEmulator ) thisTMB_->EnableInternalL1aSequencer();
	thisTMB_->DisableCLCTInputs();
	thisTMB_->SetCLCTPatternTrigger();
	//
	thisDMB_->set_comp_thresh(0.1);
	thisDMB_->set_dac(0.5,0);
	//
	thisDMB_->trigsetx(hs,CLCTInputs);
	//
	thisTMB_->EnableCLCTInputs(CLCTInputs);
	//
	// Inject it (pulse the CFEBs)
	//
	thisCCB_->setCCBMode(CCB::VMEFPGA);
	thisCCB_->WriteRegister(0x28,0x7878);  //4Aug05 DM changed 0x789b to 0x7862
	//
	return;
}
//
inline void PulseCFEB(int HalfStrip = -1, int CLCTInputs = 0x1f, bool enableL1aEmulator = 0){
	//
	LoadCFEB(HalfStrip, CLCTInputs, enableL1aEmulator);
	//
	thisDMB_->inject(1,0x4f);
	//
	// Decode the TMB CLCTs (0 and 1)
	//
	thisTMB_->DecodeCLCT();
	//
	if (debug_>10) {
		thisTMB_->PrintCLCT();
		thisDMB_->PrintCounters();
	}
	//
	return;
}
//
inline void PulseCFEB(int * HalfStrips, int CLCTInputs, bool enableL1aEmulator = 0){
	//
	LoadCFEB(HalfStrips, CLCTInputs, enableL1aEmulator);
	//
	thisDMB_->inject(1,0x4f);
	//
	// Decode the TMB CLCTs (0 and 1)
	//
	thisTMB_->DecodeCLCT();
	//
	if (debug_>10) {
		thisTMB_->PrintCLCT();
		thisDMB_->PrintCounters();
	}
	//
	return;
}

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

inline void SetTMBInternalL1A(int delay) {
	//thisTMB_->ReadRegister(ccb_trig_adr);
	//thisTMB_->SetInternalL1aDelay(delay);
	//thisTMB_->WriteRegister(ccb_trig_adr);
	thisTMB_->ReadRegister(seq_l1a_adr);
	thisTMB_->SetInternalL1a(delay);
	thisTMB_->WriteRegister(seq_l1a_adr);
}

inline void SetTMBL1ADelay(int delay) {
	thisTMB_->ReadRegister(seq_l1a_adr);
	thisTMB_->SetL1aDelay(delay);
	thisTMB_->WriteRegister(seq_l1a_adr);
}

inline void SetCfebRxPosNeg(int posneg) {
	thisTMB_->SetCfeb0RxPosNeg(posneg);
	thisTMB_->SetCfeb1RxPosNeg(posneg);
	thisTMB_->SetCfeb2RxPosNeg(posneg);
	thisTMB_->SetCfeb3RxPosNeg(posneg);
	thisTMB_->SetCfeb4RxPosNeg(posneg);
}

inline void SetCfebRxClockDelay(int delay) {
	thisTMB_->SetCfeb0RxClockDelay(delay); 		// Set delay in TMB object
	thisTMB_->WriteRegister(phaser_cfeb0_rxd_adr);	// Write delay to hardware
	thisTMB_->FirePhaser(phaser_cfeb0_rxd_adr);		// Load delay
	//
	thisTMB_->SetCfeb1RxClockDelay(delay);
	thisTMB_->WriteRegister(phaser_cfeb1_rxd_adr);
	thisTMB_->FirePhaser(phaser_cfeb1_rxd_adr);
	//
	thisTMB_->SetCfeb2RxClockDelay(delay);
	thisTMB_->WriteRegister(phaser_cfeb2_rxd_adr);
	thisTMB_->FirePhaser(phaser_cfeb2_rxd_adr);
	//
	thisTMB_->SetCfeb3RxClockDelay(delay);
	thisTMB_->WriteRegister(phaser_cfeb3_rxd_adr);
	thisTMB_->FirePhaser(phaser_cfeb3_rxd_adr);
	//
	thisTMB_->SetCfeb4RxClockDelay(delay);
	thisTMB_->WriteRegister(phaser_cfeb4_rxd_adr);
	thisTMB_->FirePhaser(phaser_cfeb4_rxd_adr);
}

inline void ResyncDCFEBs() {
	char rcv[2];
	unsigned int addr;
	unsigned short int data;
	int irdwr;
	int slot_number;

	if(thisDMB_->GetHardwareVersion() == 2) {
		slot_number = thisDMB_->slot();

		unsigned int fw_version = thisDMB_->odmb_firmware_version();
		if(fw_version < 265) {
			//continue; // 265 == 0x0109

			// Resync ODMB and DCFEB L1A Counters
			irdwr = 3;
			if((thisDMB_->odmb_firmware_version() / 0x100) >= 3) {
				addr = 0x003014 | (slot_number << 19);
				data = 0x0001;
			}
			else {
				addr = 0x003010 | (slot_number << 19);
				data = 0x0002;
			}
			thisDMB_->getCrate()->vmeController()->vme_controller(irdwr, addr, &data, rcv);
		}
		std::cout << " Calling Resync " << std::endl;
	} // ODMB only
}

inline void SetDCFEBsPipelineDepth(int depth) {
	if(thisDMB_->cfebs().at(0).GetHardwareVersion() != 2)
			return; // All CFEBs should have the same HW version; get it from the first.

	if(thisDMB_->GetHardwareVersion() == 2) { // reprogram DCFEBs
		char rcv[2];
		unsigned int addr;
		unsigned short int data;
		int irdwr;
		int slot = thisDMB_->slot();
		irdwr = 3;
		addr = 0x003010 | (slot << 19);
		data = 0x0001;
		thisDMB_->getCrate()->vmeController()->vme_controller(irdwr, addr, &data, rcv);
		usleep(300000);
	}

	std::vector<emu::pc::CFEB> cfebs = thisDMB_->cfebs();
	for(std::vector<emu::pc::CFEB>::reverse_iterator cfeb = cfebs.rbegin(); cfeb != cfebs.rend(); ++cfeb) {

		short int pipelineDepth = depth;

		thisDMB_->dcfeb_set_PipelineDepth(*cfeb, pipelineDepth); // set the pipeline depth
		usleep(100000);
		thisDMB_->Pipeline_Restart(*cfeb); // and then restart the pipeline
		usleep(100000);

		if(thisDMB_->GetHardwareVersion() != 2) {
			// set DCFEBs to behave like CFEBs and send data on any L1A, required when not using ODMB
			thisDMB_->dcfeb_Set_ReadAnyL1a(*cfeb);
		}

		thisDMB_->shift_all(NORM_RUN);
		thisDMB_->buck_shift();
		usleep(100000);
	}

	if(thisDMB_->getCrate()) {
		thisDMB_->getCrate()->ccb()->l1aReset(); // need to do this after restarting DCFEB pipelines
		usleep(1000);
		//resyncDCFEBs(thisDMB_->getCrate()); // TODO: remove once firmware takes care of it
		ResyncDCFEBs();
		usleep(1000);
	}
}

inline void CFEBTiming_ConfigureODMB() {
	if(thisDMB_->GetHardwareVersion() == 2) {
		int slot_number = thisDMB_->slot();

		char rcv[2];
		unsigned int addr;
		unsigned short int data;
		int irdwr;

		// ODMB Reset
		irdwr = 3;
		int odmb_fw_vers = (thisDMB_->odmb_firmware_version() / 0x100);
		addr = (odmb_fw_vers >= 3)?0x003004:0x003000;
		addr = addr | slot_number << 19;
		data = (odmb_fw_vers >= 3)?0x01:0x100;
		thisDMB_->getTheController()->vme_controller(irdwr, addr, &data, rcv);
		usleep(300000);

		// Kill No Boards
		irdwr = 3;
		addr = (0x00401c) | slot_number << 19;
		data = 0x0000; // Kill None
		thisDMB_->getTheController()->vme_controller(irdwr, addr, &data, rcv);

		//  Set LCT_L1A_DLY
		irdwr = 3;
		addr = (0x004000) | slot_number << 19;
		data = 0x001a; // P5 // 0x001a; B904
		thisDMB_->getTheController()->vme_controller(irdwr, addr, &data, rcv);

		// Set OTMB_DLY
		//irdwr = 3; addr = (0x004004)| slot_number<<19; data = 0x0001;
		irdwr = 3;
		addr = (0x004004) | slot_number << 19;
		data = 0x0002;
		thisDMB_->getTheController()->vme_controller(irdwr, addr, &data, rcv);

		//    Set ALCT_DLY
		//  irdwr = 3; addr = (0x00400c)| slot_number<<19; data = 0x001e; // ME+1/1/34
		irdwr = 3;
		addr = (0x00400c) | slot_number << 19;
		data = 0x001f; // ME+1/1/35
		thisDMB_->getTheController()->vme_controller(irdwr, addr, &data, rcv);

		//    Set INJ_DLY
		// Set it to 0 explicitly as in some older firmware versions its default value is nonzero.
		irdwr = 3;
		addr = (0x004010) | slot_number << 19;
		data = 0x0000;
		thisDMB_->getTheController()->vme_controller(irdwr, addr, &data, rcv);

		// ODMB configured to accept real triggers
		irdwr = 3;
		addr = (0x003000) | slot_number << 19;
		data = 0x0000;
		thisDMB_->getTheController()->vme_controller(irdwr, addr, &data, rcv);
		if(odmb_fw_vers >= 3) {
			addr = (0x003300) | slot_number << 19;
			thisDMB_->getTheController()->vme_controller(irdwr, addr, &data, rcv);
			addr = (0x003304) | slot_number << 19;
			thisDMB_->getTheController()->vme_controller(irdwr, addr, &data, rcv);
			addr = (0x003308) | slot_number << 19;
			thisDMB_->getTheController()->vme_controller(irdwr, addr, &data, rcv);
			addr = (0x003400) | slot_number << 19;
			thisDMB_->getTheController()->vme_controller(irdwr, addr, &data, rcv);
			addr = (0x003404) | slot_number << 19;
			thisDMB_->getTheController()->vme_controller(irdwr, addr, &data, rcv);
		}

		// Temporary fix to explicitly set crate id in ODMB
		irdwr = 3;
		addr = (0x004020) | slot_number << 19;
		data = thisTMB_->getCrate()->CrateID();
		thisDMB_->getTheController()->vme_controller(irdwr, addr, &data, rcv);
	}
}

inline void SetODMBPedestalMode() {
	if(thisDMB_->GetHardwareVersion() < 2)
		return;

	int slot_number = thisDMB_->slot();
	char rcv[2];
	unsigned int addr;
	unsigned short int data;
	int irdwr;

	int othisDMB__fw_vers = (thisDMB_->odmb_firmware_version() / 0x100);
	printf("othisDMB_ fw vers read from othisDMB_: %4x\n", thisDMB_->odmb_firmware_version());
	printf("othisDMB_ fw vers: %d\n", othisDMB__fw_vers);
	// set OthisDMB_ to Pedestal mode
	irdwr = 3;
	addr = (othisDMB__fw_vers >= 3)?0x003400:0x003000;
	addr = addr | slot_number << 19;
	data = (othisDMB__fw_vers >= 3)?0x01:0x2000;
	std::cout << "Pulsing: addr =" << addr << "  data = " << data << std::endl;
	thisDMB_->getCrate()->vmeController()->vme_controller(irdwr, addr, &data, rcv);
	// Set OTMB_DLY
	//irdwr = 3; addr = (0x004004)| slot_number<<19; data = 0x0001;
	irdwr = 3;
	addr = (0x004004) | slot_number << 19;
	data = 0x0002;
	thisDMB_->getCrate()->vmeController()->vme_controller(irdwr, addr, &data, rcv);
	//    Set ALCT_DLY
	irdwr = 3;
	addr = (0x00400c) | slot_number << 19;
	data = 0x001f;
	// Kill OthisDMB_ inputs
	irdwr = 3;
	addr = (0x00401c) | slot_number << 19;
	data = 0x0100; // Kill ALCT
	thisDMB_->getCrate()->vmeController()->vme_controller(irdwr, addr, &data, rcv);
	//  Set LCT_L1A_DLY
	irdwr = 3;
	addr = (0x004000) | slot_number << 19;
	data = 0x000e; //5;
	thisDMB_->getCrate()->vmeController()->vme_controller(irdwr, addr, &data, rcv);
	//    Set INJ_DLY
	// Set it to 0 explicitly as in some older firmware versions its default value is nonzero.
	irdwr = 3;
	addr = (0x004010) | slot_number << 19;
	data = 0x0000;
	thisDMB_->getCrate()->vmeController()->vme_controller(irdwr, addr, &data, rcv);
	// Set EXT_DLY
	irdwr = 3;
	addr = (0x004014) | slot_number << 19;
	data = 0x0000;
	thisDMB_->getCrate()->vmeController()->vme_controller(irdwr, addr, &data, rcv);
	// Set CAL_LCT_DLY
	irdwr = 3;
	addr = (0x004018) | slot_number << 19;
	data = 0x000f;
	thisDMB_->getCrate()->vmeController()->vme_controller(irdwr, addr, &data, rcv);
}

inline void ConfigureTMB(const CFEBTiming_Configuration & config) {
	thisCCB_->setCCBMode(CCB::DLOG);

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

	thisTMB_->SetCfeb0TOFDelay(test_cfeb_tof_delay[0]);
	thisTMB_->SetCfeb1TOFDelay(test_cfeb_tof_delay[1]);
	thisTMB_->SetCfeb2TOFDelay(test_cfeb_tof_delay[2]);
	thisTMB_->SetCfeb3TOFDelay(test_cfeb_tof_delay[3]);
	thisTMB_->SetCfeb4TOFDelay(test_cfeb_tof_delay[4]);
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
	// End new lines from Stan's code


	thisTMB_->FireDDDStateMachine();
	//
	comparing_with_clct_ = true;
	thisTMB_->StartTTC();
	::sleep(1);
	usleep(1000);
}

inline void PulseInject(bool is_inject_scan, int cfeb, unsigned int layer_mask, unsigned int pattern, unsigned int halfstrip, unsigned int n_pulses = 1, unsigned int pulse_delay = 0x4f) {
	std::cout << "Start: " << __PRETTY_FUNCTION__  << std::endl;
	const int MaxCFEB = 5;
	const int MaxTimeDelay=25;
	const bool is_cfeb_scan = cfeb < 0;

	char test_hs[6]; memset(test_hs, 0, sizeof(test_hs));// hs[0-6] is 1-32 have strips in layers 0-6
	int test_hs_int[6]; memset(test_hs_int, 0, sizeof(test_hs_int));

	// Build half strip array (specify a half strip to pulse for each layer)
	for(int layer=0; layer<6; ++layer){
		int val = halfstrip+CFEBPatterns[pattern-0x2][layer];
		if(val<0 || val>31) continue;
		test_hs[layer] = val & 0x1f;
		test_hs_int[layer] = val & 0x1f;
	}
	//
	if(is_inject_scan){
		thisDMB_->Set_TMB_TX_MODE(cfeb, 5); // Set the mode of the CFEB in question
		usleep(1000);
		thisDMB_->Set_TMB_TX_MODE_Layer_Mask(cfeb, layer_mask); // Set the layer mask
		usleep(1000);
		thisDMB_->Set_TMB_TX_MODE_ShiftLayers(cfeb, test_hs); // Set the half strip for each layer
		usleep(1000);
		thisCCB_->inject(n_pulses, pulse_delay); // Inject the pattern of half strips to the CFEB
		usleep(1000);
		thisDMB_->Set_TMB_TX_MODE(cfeb, 0); // Return mode to original state
		usleep(1000);
	}
	else {
		PulseCFEB(test_hs_int,0x1<<cfeb);
	}
	std::cout << "End: " << __PRETTY_FUNCTION__  << std::endl;
}

inline void CFEBTiming_PrintConfiguration(CFEBTiming_Configuration & config) {
	(*MyOutput_) << std::setw(21) << "tmb_internal_l1a: " << std::setw(4) << config.tmb_internal_l1a << std::endl;
	(*MyOutput_) << std::setw(21) << "clct_pattern_trig_en: " << std::setw(4) << config.clct_pattern_trig_en << std::endl;
	(*MyOutput_) << std::setw(21) << "clct_ext_trig_en: " << std::setw(4) << config.clct_ext_trig_en << std::endl;
	(*MyOutput_) << std::setw(21) << "tmb_allow_clct: " << std::setw(4) << config.tmb_allow_clct << std::endl;
	(*MyOutput_) << std::setw(21) << "hs_pretrig_hit_thresh: " << std::setw(4) << config.hs_pretrig_hit_thresh << std::endl;
	(*MyOutput_) << std::setw(21) << "min_hits_pattern: " << std::setw(4) << config.min_hits_pattern << std::endl;
	(*MyOutput_) << std::setw(21) << "ignore_ccb_startstop: " << std::setw(4) << config.ignore_ccb_startstop << std::endl;
	(*MyOutput_) << std::setw(21) << "layer_trigger_en: " << std::setw(4) << config.layer_trigger_en << std::endl;
	(*MyOutput_) << std::setw(21) << "fifo_mode: " << std::setw(4) << config.fifo_mode << std::endl;
	(*MyOutput_) << std::setw(21) << "fifo_tbins: " << std::setw(4) << config.fifo_tbins << std::endl;
	(*MyOutput_) << std::setw(21) << "fifo_pretrig: " << std::setw(4) << config.fifo_pretrig << std::endl;
	(*MyOutput_) << std::setw(21) << "fifo_no_hits_raw: " << std::setw(4) << config.fifo_no_hits_raw << std::endl;
	(*MyOutput_) << std::setw(21) << "ccb_ext_trig_delay: " << std::setw(4) << config.ccb_ext_trig_delay << std::endl;
	(*MyOutput_) << std::setw(21) << "tmb_l1a_delay: " << std::setw(4) << config.tmb_l1a_delay << std::endl;
	(*MyOutput_) << std::setw(21) << "cfeb_rx_posneg: " << std::setw(4) << config.cfeb_rx_posneg << std::endl;
	(*MyOutput_) << std::setw(21) << "cfeb_rx_clock_delay: " << std::setw(4) << config.cfeb_rx_clock_delay << std::endl;
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
	if(read.tmb_internal_l1a != orig.tmb_internal_l1a) {
		(*MyOutput_) << std::setw(35) << "BAD tmb_internal_l1a: EXPECTED: " << std::setw(4) << orig.tmb_internal_l1a << " | READ: " << std::setw(4) << read.tmb_internal_l1a << std::endl;
		same = false;
	}
	if(read.clct_pattern_trig_en != orig.clct_pattern_trig_en) {
		(*MyOutput_) << std::setw(35) << "BAD clct_pattern_trig_en: EXPECTED: " << std::setw(4) << orig.clct_pattern_trig_en << " | READ: " << std::setw(4) << read.clct_pattern_trig_en << std::endl;
		same = false;
	}
	if(read.clct_ext_trig_en != orig.clct_ext_trig_en) {
		(*MyOutput_) << std::setw(35) << "BAD clct_ext_trig_en: EXPECTED: " << std::setw(4) << orig.clct_ext_trig_en << " | READ: " << std::setw(4) << read.clct_ext_trig_en << std::endl;
		same = false;
	}
	if(read.tmb_allow_clct != orig.tmb_allow_clct) {
		(*MyOutput_) << std::setw(35) << "BAD tmb_allow_clct: EXPECTED: " << std::setw(4) << orig.tmb_allow_clct << " | READ: " << std::setw(4) << read.tmb_allow_clct << std::endl;
		same = false;
	}
	if(read.hs_pretrig_hit_thresh != orig.hs_pretrig_hit_thresh) {
		(*MyOutput_) << std::setw(35) << "BAD hs_pretrig_hit_thresh: EXPECTED: " << std::setw(4) << orig.hs_pretrig_hit_thresh << " | READ: " << std::setw(4) << read.hs_pretrig_hit_thresh << std::endl;
		same = false;
	}
	if(read.min_hits_pattern != orig.min_hits_pattern) {
		(*MyOutput_) << std::setw(35) << "BAD min_hits_pattern: EXPECTED: " << std::setw(4) << orig.min_hits_pattern << " | READ: " << std::setw(4) << read.min_hits_pattern << std::endl;
		same = false;
	}
	if(read.ignore_ccb_startstop != orig.ignore_ccb_startstop) {
		(*MyOutput_) << std::setw(35) << "BAD ignore_ccb_startstop: EXPECTED: " << std::setw(4) << orig.ignore_ccb_startstop << " | READ: " << std::setw(4) << read.ignore_ccb_startstop << std::endl;
		same = false;
	}
	if(read.layer_trigger_en != orig.layer_trigger_en) {
		(*MyOutput_) << std::setw(35) << "BAD layer_trigger_en: EXPECTED: " << std::setw(4) << orig.layer_trigger_en << " | READ: " << std::setw(4) << read.layer_trigger_en << std::endl;
		same = false;
	}
	if(read.fifo_mode != orig.fifo_mode) {
		(*MyOutput_) << std::setw(35) << "BAD fifo_mode: EXPECTED: " << std::setw(4) << orig.fifo_mode << " | READ: " << std::setw(4) << read.fifo_mode << std::endl;
		same = false;
	}
	if(read.fifo_tbins != orig.fifo_tbins) {
		(*MyOutput_) << std::setw(35) << "BAD fifo_tbins: EXPECTED: " << std::setw(4) << orig.fifo_tbins << " | READ: " << std::setw(4) << read.fifo_tbins << std::endl;
		same = false;
	}
	if(read.fifo_pretrig != orig.fifo_pretrig) {
		(*MyOutput_) << std::setw(35) << "BAD fifo_pretrig: EXPECTED: " << std::setw(4) << orig.fifo_pretrig << " | READ: " << std::setw(4) << read.fifo_pretrig << std::endl;
		same = false;
	}
	if(read.fifo_no_hits_raw != orig.fifo_no_hits_raw) {
		(*MyOutput_) << std::setw(35) << "BAD fifo_no_hits_raw: EXPECTED: " << std::setw(4) << orig.fifo_no_hits_raw << " | READ: " << std::setw(4) << read.fifo_no_hits_raw << std::endl;
		same = false;
	}
	if(read.ccb_ext_trig_delay != orig.ccb_ext_trig_delay) {
		(*MyOutput_) << std::setw(35) << "BAD ccb_ext_trig_delay: EXPECTED: " << std::setw(4) << orig.ccb_ext_trig_delay << " | READ: " << std::setw(4) << read.ccb_ext_trig_delay << std::endl;
		same = false;
	}
	if(read.tmb_l1a_delay != orig.tmb_l1a_delay) {
		(*MyOutput_) << std::setw(35) << "BAD tmb_l1a_delay: EXPECTED: " << std::setw(4) << orig.tmb_l1a_delay << " | READ: " << std::setw(4) << read.tmb_l1a_delay << std::endl;
		same = false;
	}
	if(read.cfeb_rx_posneg != orig.cfeb_rx_posneg) {
		(*MyOutput_) << std::setw(35) << "BAD cfeb_rx_posneg: EXPECTED: " << std::setw(4) << orig.cfeb_rx_posneg << " | READ: " << std::setw(4) << read.cfeb_rx_posneg << std::endl;
		same = false;
	}
	if(read.cfeb_rx_clock_delay != orig.cfeb_rx_clock_delay) {
		(*MyOutput_) << std::setw(35) << "BAD cfeb_rx_clock_delay: EXPECTED: " << std::setw(4) << orig.cfeb_rx_clock_delay << " | READ: " << std::setw(4) << read.cfeb_rx_clock_delay << std::endl;
		same = false;
	}
	return same;
}


inline void CFEBTiming_ConfigureLevel(CFEBTiming_Configuration & config, int level = 0) {
	(*MyOutput_) << "CFEBTiming Configure Level " << level << std::endl;
	if(level <= 0) {
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

inline void Clear_ODMB_FIFO() {
	unsigned int bad_reads = 0;
	int n_words = thisDMB_->ReadRegister(0x550C);
	int temp = 0;
	for(int i=0; i<n_words && bad_reads < 50; ++i) {
		thisDMB_->ReadRegister(0x5500);
		temp = thisDMB_->ReadRegister(0x550C);
		if(n_words == temp)
			++bad_reads;
		n_words = temp;
	}
}

inline void Print_ODMB_FIFO() {
	int n_words = thisDMB_->ReadRegister(0x550C);
	if(n_words == 0) {
		(*MyOutput_) << "\n0000\n";
	}
	for(int i=0; i<n_words; ++i) {
		(*MyOutput_) << " " << std::hex << thisDMB_->ReadRegister(0x5500);
	}
	(*MyOutput_) << std::endl << std::endl;
}

inline int * L1AWindowScan() {
	std::fstream out_file("./L1AWindowScan_Output.txt", std::ios_base::out);
	out_file << "BEGIN" << std::endl << std::flush;
	std::ostream * temp_os = MyOutput_;
	MyOutput_ = &out_file;

	const int MaxL1ADelay = 256;
	const int MaxTimeDelay=25;
	const int MaxLayer = 6;
	const int LayerCombinations = 64;
	const int MaxHalfStrip = 32;
	const int HalfStripCombinations = 256;
	const int MaxPattern = 0xa;
	const int PatternCombinations = 16;
	const int MaxPosNeg = 2;
	const int MaxDepth = 70;
	const int AllLayers = 0x3f;
	const int NTimes = 10;

	const int halfstrip = 16;
	const int cfeb = 0;
	const bool is_inject_scan = true;
	const int posneg = 0;
	const int delay = 10;
	const int depth = 45;

	const int tmb_count_min = 55;
	const int tmb_count_max = 60;

	CFEBTiming_Configuration config;
	config.cfeb_pipeline_depth = depth;
  	config.dac = (float) 160 * 5. / 4095.;
  	config.comp_thresh = (float) 50 / 1000.;
  	config.clct_pattern_trig_en = 1;
  	config.clct_ext_trig_en = 1;
  	config.tmb_allow_clct = 1;
  	config.hs_pretrig_hit_thresh = 5;
  	config.min_hits_pattern = 1;
  	config.ignore_ccb_startstop = 0;
  	config.layer_trigger_en = 0;
    config.fifo_mode = 1;
    config.fifo_tbins = 30;
    config.fifo_pretrig = 5;
    config.fifo_no_hits_raw = 0;
  	config.tmb_internal_l1a = 0;
  	config.ccb_ext_trig_delay = 0;
  	config.tmb_l1a_delay = 0;
  	config.cfeb_rx_posneg = posneg;
  	config.cfeb_rx_clock_delay = delay;

	CFEBTiming_ConfigureLevel(config);
	if(!CFEBTiming_CheckConfiguration(config))
		return NULL;

	const int increment = 1;
	const int min_l1a_ext_delay = 0;
	const int max_l1a_ext_delay = 10;
	const int n_l1a_ext_delay = max_l1a_ext_delay-min_l1a_ext_delay+1;

	int counter[n_l1a_ext_delay][MaxL1ADelay/increment]; memset(counter, 0, sizeof(counter));

	bool done = false;

	//SetTMBInternalL1A(0); // Disable the tmb's internal l1a
	//thisTMB_->EnableClctExtTrig(); // Enable l1a trigger from ccb

	const int max_windows = 10;
	int windows[max_windows][4]; memset(windows, 0, sizeof(windows));
	int n_windows = 0;
	bool in_window = false;

	for(int l1a_ext_delay=min_l1a_ext_delay; l1a_ext_delay<=max_l1a_ext_delay && (!done); ++l1a_ext_delay)  {

		config.ccb_ext_trig_delay = l1a_ext_delay;
		usleep(1000);
		CFEBTiming_ConfigureLevel(config, 2);
		//thisCCB_->SetExtTrigDelay(l1a_ext_delay); // Set external l1a delay in ccb

		for(int l1a_delay=0; l1a_delay<MaxL1ADelay && (!done); l1a_delay+=increment) {
			//std::cout << "Start: " << "PulseLoop" << std::endl;
			//SetTMBL1ADelay(l1a_delay); // Set tmb l1a delay
			config.tmb_l1a_delay = l1a_delay;
			CFEBTiming_ConfigureLevel(config, 2);
			usleep(1000);
			std::cout << "Before" << std::endl;

			CFEBTiming_CheckConfiguration(config);

			thisCCB_->bc0(); // Start triggering

			PulseInject(is_inject_scan, cfeb, AllLayers, MaxPattern, halfstrip); // Inject a pattern

			usleep(1000);
			std::cout << "After" << std::endl;
			CFEBTiming_CheckConfiguration(config);

			thisTMB_->GetCounters(); // Get back the counts

			int pulses = thisTMB_->GetCounter(56);
			if(pulses > 0) {
				if(!in_window) {
					windows[n_windows][0] = l1a_ext_delay;
					windows[n_windows][1] = l1a_delay;
					in_window = true;
				}
			}
			else if (in_window) {
				windows[n_windows][2] = l1a_ext_delay;
				windows[n_windows][3] = l1a_delay;
				++n_windows;
				in_window = false;
				if(n_windows == max_windows) done = true;
			}
			thisTMB_->ResetCounters();
			thisCCB_->WriteRegister(thisCCB_->L1Reset, 0);
		}
	}
	if(in_window) {
		windows[n_windows][2] = max_l1a_ext_delay;
		windows[n_windows][3] = MaxL1ADelay-1;
		in_window = false;
		++n_windows;
	}

	const int n_pulses = 50;
	unsigned int window_size[max_windows]; memset(window_size, 0, sizeof(window_size));
	unsigned int window_average[max_windows]; memset(window_average, 0, sizeof(window_average));
	for(int window = 0; window<n_windows; ++window) {
		int n_windows = 0;
		in_window = false;
		int e_min = windows[window][0];
		int i_min = windows[window][1];
		int e_max = windows[window][2];
		int i_max = windows[window][3];

		if(e_min != e_max) continue;
		if(e_min == 0 && i_min == 0) continue;

		(*MyOutput_) << "Window [" << e_min << "." << i_min << "]-[" << e_max << "." << i_max << "]: ";

		thisCCB_->SetExtTrigDelay(e_min); // Set external l1a delay in ccb
		for(int i = i_min; i<=i_max; ++i) {
			SetTMBL1ADelay(i); // Set tmb l1a delay
			thisCCB_->bc0(); // Start triggering
			for(int p = 0; p<n_pulses; ++p) {
				PulseInject(is_inject_scan, cfeb, AllLayers, MaxPattern, halfstrip); // Inject a pattern
			}
			thisTMB_->GetCounters(); // Get back the counts
			int pulses = thisTMB_->GetCounter(56);
			thisTMB_->ResetCounters();

			if(pulses==n_pulses) {
				if(!in_window) {
					in_window = true;
					++n_windows;
				}
				if(n_windows == 1) {
					window_average[window] += i;
					++window_size[window];
				}
			}
			else {
				if(in_window)
					in_window = false;
			}

			(*MyOutput_) << pulses;
			if(i!=i_max)
				(*MyOutput_) << ",";
			else
				(*MyOutput_) << " ";
		}
		window_average[window] = round(double(window_average[window])/double(window_size[window]));
		(*MyOutput_) << "Average: " << window_average[window] << " Size: " << window_size[window] << std::endl;
	}
	MyOutput_ = temp_os;

	int window_index = -1;
	for(int i=0; i<max_windows; ++i) {
		if(window_size[i] >= 6) {
			window_index = i;
			break;
		}
	}

	int * ret = NULL;
	if(window_index >= 0) {
		(*MyOutput_) << "External l1a delay: " << std::dec << windows[window_index][0] <<  " TMB l1a delay: " << std::dec << window_average[window_index] << std::endl;
		ret = new int[2];
		ret[0] = windows[window_index][0];
		ret[1] = window_average[window_index];
	}
	else {
		(*MyOutput_) << "No l1a delay windows found!" << std::endl;
	}
	return ret;
}

inline void CFEBTiming_DMBDebug() {

	std::fstream out_file("./DMB_Debug_Output.txt", std::ios_base::out);
	std::fstream packet_file("./packets", std::ios_base::out);
	std::ostream * temp_os = MyOutput_;
	MyOutput_ = &out_file;

	const int MaxPattern = 0xa;
	const int AllLayers = 0x3f;

	const int halfstrip = 16;
	const int cfeb = 0;
	const bool is_inject_scan = true;

	const int posneg = 0;
	const int delay = 10;
	const int depth = 58;

	CFEBTiming_Configuration config;
	config.cfeb_pipeline_depth = depth;
	config.dac = (float) 160 * 5. / 4095.;
	config.comp_thresh = (float) 50 / 1000.;

	config.clct_ext_trig_en = 1;
	config.ccb_ext_trig_delay = 0;
	config.tmb_l1a_delay = 0;
	config.cfeb_rx_posneg = posneg;
	config.cfeb_rx_clock_delay = delay;

	CFEBTiming_ConfigureLevel(config);

	int pattern = MaxPattern;
	for(int i = 0; i<1000; ++i) {
		thisCCB_->bc0(); // Start triggering

		usleep(1000);

		Clear_ODMB_FIFO();
		int n_words = thisDMB_->ReadRegister(0x550C);
		if(n_words != 0)
			(*MyOutput_) << "ERROR! n_words != 0" << std::endl;

		usleep(1000);

		PulseInject(is_inject_scan, cfeb, AllLayers, pattern, halfstrip); // Inject a pattern

		usleep(1000);

		//Read back ODMB fifo
		std::ostream * temp_os = MyOutput_;
		MyOutput_ = 	&packet_file;
		Print_ODMB_FIFO();
		MyOutput_ = temp_os;

		usleep(1000);
	}
}

}; // class

} } // namespaces

#endif
