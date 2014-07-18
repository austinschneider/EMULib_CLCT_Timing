#include <iostream>
#include <iomanip>
#include <sstream>
#include "emu/pc/ALCTController.h"
#include "emu/pc/BuckeyeChip.h"
#include "emu/pc/CCB.h"
#include "emu/pc/DCFEB.h"
#include "emu/pc/Chamber.h"
#include "emu/pc/Crate.h"
#include "emu/pc/ODAQMB.h"
#include "emu/pc/EMU_CC_constants.h"
#include "emu/pc/EmuController.h"
#include "emu/pc/EmuEndcap.h"
#include "emu/pc/EMU_JTAG_constants.h"
#include "emu/pc/EMUjtag.h"
#include "emu/pc/EmuLogger.h"
#include "emu/pc/GenDATA.h"
#include "emu/pc/geom.h"
#include "emu/pc/JTAG_constants.h"
#include "emu/pc/MPC.h"
#include "emu/pc/RAT.h"
#include "emu/pc/TMB_constants.h"
#include "emu/pc/TMB.h"
#include "emu/pc/TMBTester.h"
#include "emu/pc/VMECC.h"
#include "emu/pc/vme_cmd.h"
#include "emu/pc/VMEController.h"
#include "emu/pc/VMEModule.h"
#include "math.h"

namespace emu{
  namespace pc{

  int DataSource;
  int NSAMPLE;
  emu::pc::EmuController * emuController_;
  std::vector<emu::pc::Crate*> crateVector;
  emu::pc::EmuEndcap * emuEndcap_;
  emu::pc::CCB * thisCCB_;
  emu::pc::TMB * thisTMB_;
  emu::pc::ODAQMB* thisODMB_;
  std::vector<emu::pc::TMB*>   tmbVector_;
  std::vector<emu::pc::ODAQMB*> odmbVector_;
  emu::pc::Crate *thisCrate_;
  std::vector <emu::pc::DCFEB> thisDCFEBs_;
  emu::pc::DCFEB* thisDCFEB_;
  int dcfeb_;
  int ndcfeb_; 
  char hexbrdnum_[4];

  int ibrdnum_;
  const char* cbrdnum_;
  std::string brdnum_; 
  std::string FirmwareDir_ ;
  std::string DCFEBFirmware_;
  int evt;

int main(){
  NSAMPLE=8;
  ibrdnum_=-99;
  brdnum_="";

  FirmwareDir_ = getenv("HOME");
  FirmwareDir_ += "/firmware/dcfeb/";
  evt=0;
  emuController_ = new emu::pc::EmuController();
  // emuController_ = new EmuController();
  std::string xmlFile="/home/dcfebcheck/config/pc/OSU_TestStand.xml";
  std::cout << " xmlFile " << xmlFile <<std::endl;   
  emuController_->SetConfFile(xmlFile.c_str());
  std::cout << " Mycontroller:setConfFIle " << std::endl;
  emuController_->init();
  std::cout << " Mycontroller init called " << std::endl;
  emuController_->NotInDCS();
  emuEndcap_ = emuController_->GetEmuEndcap(); 
  crateVector = emuEndcap_->crates();
  printf(" crateVector size %d \n",crateVector.size());
  /*
  thisCrate_ = crateVector[0];
  thisCCB_ = thisCrate_->ccb();
  odmbVector_=thisCrate_->odaqmbs();
  printf("  odmbVector_ size %d \n",odmbVector_.size());   
  tmbVector_ = thisCrate_->tmbs();
  if(odmbVector_.size()>0)thisODMB_ =odmbVector_[0];
  thisTMB_ = tmbVector_[0];
  printf(" after tmb \n");
  if(odmbVector_.size()>0){
   thisDCFEBs_=thisODMB_->dcfebs();
   printf("  cfeb vector size %d ",thisDCFEBs_.size());
  }
  printf(" after cfeb \n");
  thisCrate_->vmeController()->SetUseDCS(true);
  // thisDDMB_->start();
  fflush(stdout);  
  hexbrdnum_[0]=0xdc;
  hexbrdnum_[1]=0xfe;
  hexbrdnum_[2]=0xb0;
  hexbrdnum_[3]=0x01;
  dcfeb_index=-99;
  if(odmbVector_.size()>0){
    int i=0;
    typedef std::vector<emu::pc::DCFEB>::iterator DCFEBItr;
    for(DCFEBItr cfebItr = thisDCFEBs_.begin(); cfebItr != thisDCFEBs_.end(); ++cfebItr) {
      dcfeb_index = (*cfebItr).number();
      printf(" dcfeb number xxx %d \n",dcfeb_index);
      if(dcfeb_==dcfeb_index)ndcfeb_=i;
      i++;
    }
    printf(" ndcfeb %d \n",ndcfeb_);
    thisDCFEB_=&thisDCFEBs_[0];
  }
  dcfeb_=dcfeb_index;
  length=0;
  thisCrate_->vmeController()->init();
  printf(" before testroutines \n");
  thisODMB_->calctrl_global();
  usleep(10000);
  //daq->eth_reset();
  //  thisCCB_->setCCBMode(emu::pc::CCB::VMEFPGA);
  // thisCCB_->hardReset(); // load fpga 
  // usleep(2000000);
  int xonoff[5]={0x01,0x02,0x04,0x08,0x10};
  sonoff=xonoff[dcfeb_index];
  printf(" sonoff %d \n",sonoff);
  usleep(2);
  */ 
}



}}
