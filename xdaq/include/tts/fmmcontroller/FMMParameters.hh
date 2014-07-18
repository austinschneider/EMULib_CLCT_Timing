#ifndef FMMPARAMETERS_H
#define FMMPARAMETERS_H

/**
 *     @class FMMParameters
 *
 *     @short Structure for parameters of one FMM
 *
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.2 $
 *     $Date: 2007/10/22 12:04:59 $
 *
 *
 **/

// to repesent data as XDATA
#include "xdata/Bag.h"
#include "xdata/String.h"
#include "xdata/Boolean.h"
#include "xdata/UnsignedShort.h"
#include "xdata/UnsignedInteger32.h"

namespace tts {

  class FMMParameters {
  public:
    void registerFields(xdata::Bag<tts::FMMParameters>* bag) {
      bag->addField("geoslot", &geoslot);
      bag->addField("serialnumber", &serialnumber);
      bag->addField("dual", &dual);
      bag->addField("inputEnableMask", &inputEnableMask);
      bag->addField("threshold20", &threshold20);
      bag->addField("threshold10A", &threshold10A);
      bag->addField("threshold10B", &threshold10B);
      bag->addField("forceControl", &forceControl);
      bag->addField("label", &label);
      bag->addField("inputLabels", &inputLabels);
      bag->addField("outputLabels", &outputLabels);
    };

    /// c-tor: define some defaults
    FMMParameters() 
      : geoslot(999), 
	serialnumber("unused"), 
	dual(false), 
	inputEnableMask(0x0), 
	threshold20(0), 
	threshold10A(0), 
	threshold10B(0),
	forceControl(false),
	label(""),
	inputLabels(""),
	outputLabels("") {};
   
    xdata::UnsignedShort geoslot;   // if 999, instantiate by serial number
    xdata::String serialnumber;
    xdata::Boolean dual;
    xdata::UnsignedInteger32 inputEnableMask;
    xdata::UnsignedShort threshold20;
    xdata::UnsignedShort threshold10A;
    xdata::UnsignedShort threshold10B;
    xdata::Boolean forceControl;
    xdata::String label;
    xdata::String inputLabels;
    xdata::String outputLabels;
  };

}
#endif
