/**
 *     @class JTAGScanData
 *
 *     @short Container for JTAG scan data. 
 *
 *            The class stores the scan data byte by byte. 
 *            The extends a vector of uint8_tacters. The least
 *            significant data bits (the bits to be scanned first) are
 *            pushed into the vector first. In each byte the least significant
 *            bit is scanned first.
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:59:05 $
 *
 *
**/

#ifndef jal_JTAGSCANDATA_H
#define jal_JTAGSCANDATA_H

#include <vector>
#include <iostream>
#include <stdint.h>


namespace jal {

  class JTAGScanData : public std::vector<uint8_t> {
  public:
    /// c-tor
    ///
    JTAGScanData(int num=0, uint8_t def = 0) : std::vector<uint8_t>(num, def) {};

    /// operator <<
    ///
    friend std::ostream& operator<<(std::ostream &os, const JTAGScanData& d);

    /// Expand the JTAGScanData to a given bitcount if it has a length of zero.
    /// This method is used to expand an unspecified (stored as zero length) SVF parameter.
    /// 
    /// @param bitcount is the number of bits
    /// @param default_byte is the byte used for expanding (0 by default, 0xff is used for masks)
    ///
    void expand(uint32_t bitcount, uint8_t default_byte = 0);



    /// add to the scan data. 
    ///
    /// The additional data will be attached at the higher bits (scanned later). 
    /// If both JTAGScanData have length zero, no adding is performed. If only one of the JTAGScanData
    /// has length zero, then it is expanded to the correct number of bytes.
    /// If the initail JTAGScanData is too short, leading zero bytes are added.
    /// No zero bytes are added if the second JTAGScanData is too short (This way leading 
    /// zeros need not be present). 
    ///
    /// @param d ist a reference to the data to be added
    /// @param initial_bitcount specifies the bitcount corresponding to the JTAGScanData (*this)
    /// @param bits_to_add specifiec the bitcount of the JTAGScanData to add
    /// @param default_byte is the byte used for expanding in case one of the JTAGScanData has a length of zero 
    ///                     (0 by default, 0xff is used for masks)
    void add(JTAGScanData const& d, 
	     uint32_t initial_bitcount, 
	     uint32_t bits_to_add, 
	     uint8_t default_byte = 0);

    /// return a range from a JTAGScanData
    JTAGScanData getRange (uint32_t start_bit, 
			   uint32_t nbits);

  };


  std::ostream& operator<<(std::ostream &os, const JTAGScanData& d);

}
#endif //jal_JTAGSCANDATA_H
