#ifndef _ttc_rf2ttc_RF2TTCStatusPrinterHTML_hh_
#define _ttc_rf2ttc_RF2TTCStatusPrinterHTML_hh_


#include "ttc/utils/SimpleHtmlTable.hh"
#include "ttc/rf2ttc/RF2TTC.hh"


namespace ttc
{

class RF2TTCProxy;

//! Class to generate HTML code reflecting status of the RF2TTC board.
class RF2TTCStatusPrinterHTML
{
public:

  static const std::string header_colour;

protected:

  static const char* line_colours[];

public:

  RF2TTCStatusPrinterHTML(std::ostream& _os, RF2TTCProxy& _rf2ttcProxy);

  void Print();

  //! Adds information about the bunch clock (BC) channels to the output table.
  void FillBCTable();

  void FillOrbitTable();

  void FillOrbitLegend();

  void FillOrbitColumn(RF2TTC::OrbitChannel channel, bool is_first_column);

  void FillAutomaticModeTable();

  void FillTTCrxTable();

protected:

  std::ostream &os;

  //! table for the BC information
  SimpleHtmlTable table;

  // for the orbit information
  SimpleHtmlTable orbit_table;

  SimpleHtmlTable automatic_mode_table;

  SimpleHtmlTable ttcrx_table;

  RF2TTCProxy& rf2ttcProxy;

  uint32_t machine_mode;

  void FillBCLegend();

  /**
   * Fills information about one BC signal path into the table (starting from (0,0),
   * so set your offset correctly before calling this method).
   */
  void FillBCColumn(RF2TTC::BCChannel channel, bool is_first);
};

}


#endif
