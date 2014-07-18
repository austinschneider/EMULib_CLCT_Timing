/**
 *     @class JTAGSVFData
 *
 *     @short Container for the parameters of the scan and header/trailer SVF commands.
 *
 *            Paramters are the bitcount, the data to be scanned in, 
 *            the expected response (optional), the mask when checking the 
 *            expected response, the mask (smask) when scanning in data (optional).
 *
 *            Elements that are not present are coded as zero length JTAGScanData.
 *
 *
 *       @see ---
 *    @author Hannes Sakulin
 * $Revision: 1.1 $
 *     $Date: 2007/03/27 07:59:09 $
 *
 *
**/

#ifndef jal_JTAGSVFDATA_H
#define jal_JTAGSVFDATA_H

#include "jal/jtagChain/JTAGScanData.h"
#include "jal/jtagSVFSequencer/SVFSyntaxException.h"
#include <iostream>

#include <stdint.h>

namespace jal {

  class JTAGSVFData {
  public:
    /// default constructor
    JTAGSVFData() :
      _bitcount(0), _data(), _resp(), _mask(), _smask() {};

    /// constructor, default values construct an empty object
    JTAGSVFData(uint32_t bitcount,
		JTAGScanData const& data = JTAGScanData(), 
		JTAGScanData const& response = JTAGScanData(),
		JTAGScanData const& mask = JTAGScanData(), 
		JTAGScanData const& smask = JTAGScanData()) :
      _bitcount(bitcount), _data(data), _resp(response), _mask(mask), _smask(smask) {};

    /// destructor
    ~JTAGSVFData() {};

    /// setter
    void set (uint32_t bitcount,
	      JTAGScanData const& data, 
	      JTAGScanData const& response,
	      JTAGScanData const& mask, 
	      JTAGScanData const& smask) {
      _bitcount = bitcount;
      _data = data;
      _resp = response;
      _mask = mask;
      _smask = smask;
    };
    
    void setBitcount (uint32_t bitcount) { _bitcount = bitcount; };
  
    void setData     (JTAGScanData const& data    ) { _data = data; };

    void setResponse (JTAGScanData const& response) { _resp = response; };

    void setMask     (JTAGScanData const& mask    ) { _mask = mask; };

    void setSMask    (JTAGScanData const& smask   ) { _smask = smask; };

    void setData     (std::string const& data    ) 
      throw(jal::SVFSyntaxException) { stringToScanData (data, _data); };

    void setResponse (std::string const& response) 
      throw(jal::SVFSyntaxException) { stringToScanData (response, _resp); };

    void setMask     (std::string const& mask    ) 
      throw(jal::SVFSyntaxException) { stringToScanData (mask, _mask); };

    void setSMask    (std::string const& smask   ) 
      throw(jal::SVFSyntaxException) { stringToScanData (smask, _smask); };

    /// update with new data, keep elements that are not specified according to SVF specs.
    /// if the bitcount remains the same, then data, mask and smask are sticky
    void update (JTAGSVFData const& d) 
      throw(jal::SVFSyntaxException);

    /// get bitcount
    uint32_t bitcount() const { return _bitcount; };

    /// get data vector
    JTAGScanData const& data() const { return _data; };

    /// get expected response vector
    JTAGScanData const& response() const { return _resp; };

    /// get response mask ( '1' = care, '0' = don't care ). default is all cares.
    JTAGScanData const& mask() const { return _mask; };

    /// get scan mask ( '1' = care, '0' = don't care ). default is all cares.
    JTAGScanData const& smask() const { return _smask; };

    /// print the object
    friend std::ostream& operator<<(std::ostream &os, const JTAGSVFData& d) {
    
      os << "JTAGSVFData: nbit = " << d._bitcount
	 << " data = " << d._data
	 << " response = " << d._resp
	 << " mask = " << d._mask 
	 << " smask = " << d._smask
	 << std::endl;
      return os;
    }
  
    /// Concatenate another scandata object. data, resp, mask and smask are concatenated.
    /// If both parameters of one type have size() zero, then also the result for that type has
    /// size zero. Otherwise zero length elements are expanded by the add() method.
    /// Leading zero bytes may be missing in the resulting elements.
    JTAGSVFData& operator+= (JTAGSVFData const& d2);

  private:
    /// parse an SVF style hex string and store it in a JTAGScanData vector
    void stringToScanData (std::string const& pattern, JTAGScanData& scandata)
      throw (jal::SVFSyntaxException);

    /// convect a hex character to a byte value 0 - 15 
    ///
    static uint8_t hexCharToByte(char ch) 
      throw (jal::SVFSyntaxException);

  protected:
    uint32_t _bitcount;
    JTAGScanData _data, _resp, _mask, _smask;

  };

}

/// in the header in order to inline
inline uint8_t jal::JTAGSVFData::hexCharToByte(char ch) 
  throw (jal::SVFSyntaxException) {
  
  if (ch >= '0' && ch <= '9') 
    return ch-'0';
  else if (ch >= 'a' && ch <= 'f') 
    return ch-'a'+10;
  else if (ch >= 'A' && ch <= 'F') 
    return ch-'A'+10;
  else 
    XCEPT_RAISE(jal::SVFSyntaxException, "stringToScanData(): error converting hex string to number");
 
}

#endif
