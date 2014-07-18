// collection of helpers for TTC software

#ifndef _ttc_utils_Utils_hh_
#define _ttc_utils_Utils_hh_


#include "xoap/MessageReference.h"
#include "log4cplus/logger.h"

#include <stdint.h>
#include <string>
#include <vector>
#include <sstream>
#include <ostream>
#include <ctime>
#include <sys/time.h>


// Number of clocks in one orbit.
#define NCLK_PER_ORBIT 3564

#define STRINGIZE(s) STRINGIZE_HELPER(s)
#define STRINGIZE_HELPER(s) #s

#define DEFAULT_LTC_BTC 99
#define DEFAULT_TTCCI_BTC 100
#define DEFAULT_TTCCI_DT2 3


// forward declarations

namespace HAL
{
class VMEBusAdapterInterface;
class VME64xDummyBusAdapter;
}


// utility functions and classes in namespace ttc

namespace ttc
{

log4cplus::Logger getUtilsLogger();

timeval operator-(const timeval& lhs, const timeval& rhs);

uint64_t microseconds(const timeval& t);

void wait(uint32_t millis);

void SetBit_on(uint32_t & data, int ibit);

void SetBit_off(uint32_t & data, int ibit);

//! Sets bit at position @ibit, in word @param data to the value given by @param ON
void SetBit(uint32_t & data, int ibit, bool ON);

/**
 * Sets the bits maskoffset+maskwidth-1..maskoffset from newdata
 * and the remaining bits from originalwd
 * and returns the resulting value
 * (in other words: pastes newdata into originalwd at offset maskoffset).
 */
uint32_t MaskIn(
    const uint32_t originalwd,
    const uint32_t newdata,
    const uint32_t maskwidth,
    const uint32_t maskoffset);

/**
 * Returns 'data' shifted left by 'maskoffset' anded
 * with a sequence of 1 bits (from bit 0 to bis maskwidth-1).
 * Example:
 *       <pre>
 *         maskwidth = 3
 *         masoffset = 5
 *         data = abcdefghij
 *       </pre>
 *       where a..j are the individual bit of 'data', then the return value is:
 *       <pre>
 *             abcde & 111 = cde
 *       </pre>
 */
uint32_t MaskOut(
    const uint32_t data,
    const uint32_t maskwidth,
    const uint32_t maskoffset);

std::string GetNthWord(const size_t n, const std::string& line);

/**
 * Finds a string in @param line.
 * @param result is the word AFTER the string @param variable .
 * @return true if the string was found, false if not.
 */
bool FindString(
    const std::string line,
    const std::string variable,
    std::string &result);

/**
 * Finds a string in @param line.
 * @param result is a vector of strings resulting from splitting the word
 *   after string @param variable, if found.
 * @return true if the string was found, false if not.
 */
bool FindStringVector(
    const std::string line,
    const std::string variable,
    std::vector<std::string>& result);

bool GetDouble(
    const std::string line,
    const std::string variable,
    double& result);

bool GetUnsignedLong(
    const std::string line,
    const std::string variable,
    uint32_t& result);

std::string CurrentTime();

size_t NumberOfWords(const std::string& line);

uint32_t RollOver(const int32_t val, const uint32_t max = NCLK_PER_ORBIT);

int FlipOrbit(const int32_t val, const uint32_t max = NCLK_PER_ORBIT);

std::vector<std::string> filelist(
    const std::string& path = "",
    const std::string& match_at_beginning = "",
    const std::string& match_at_end = "");

uint32_t NClocksPerOrbit();

//! Random returns a pseudo-random real number uniformly distributed between 0.0 and 1.0.
double Random(void);

//! generates random trigger patterns (for LTC and TTCci ram triggers) with mean 'm'.
uint32_t RandomTrigger(double m);

/**
 * Parses string var, ignores initial or trailing white space,
 * looks for an integer and puts it in @param result.
 * The integer can be written in decimal or hexadecimal format (starting with '0x').
 */
bool String2Long(std::string var, int32_t& result);

//! Same as String2Long but for unsigned integers.
bool String2UnsignedLong(std::string var, uint32_t& result);

std::string UnsignedLong2String(const uint32_t val);

std::string Long2String(const int32_t val);

std::string Long2HexString(const int32_t val);

std::string to_lower(const std::string & s);

template<typename T>
std::string to_string(const T& t, bool usehex = false)
{
  std::ostringstream s;
  if (usehex)
    s << std::hex;
  s << t;
  return s.str();
}

int32_t getint(const std::string& s);

void hex2bytes(const std::string& str, char* buf);

//! struct holding a number to be printed in a hexadecimal or decimal format
struct hexdec
{
  hexdec(uint32_t val, unsigned digits = 0, bool _print_dec = true);

  std::string toString() const;

  //! The value to be printed.
  uint32_t val;

  //! The number of digits to which the printout should be zero-padded.
  unsigned digits;

  /**
   * If this is set to true, the decimal value is printed in
   * parentheses behind the hex value.
   */
  bool print_dec;
};

//! output operator for printing a hexdec
std::ostream & operator<<(std::ostream& out, const hexdec& v);

//! struct holding a number to be printed in binary or decimal format
struct bindec
{
  /**
   * constructor:
   * @param group_size if this is > 0, every 'group_size' digits,
   *   a quote character is inserted (counting from the left).
   * @param digits does NOT include the spacing characters!
   */
  bindec(uint32_t val, unsigned digits = 0, unsigned _group_size = 0);

  std::string toString() const;

  //! the value to be printed
  uint32_t val;

  //! the number of digits to which the printout should be zero-padded
  unsigned digits;

  unsigned group_size;
};

//! output operator for printing a bindec
std::ostream & operator<<(std::ostream& out, const bindec& v);

//! class for handling timeval objects (containg s and ms values)
struct SimpleTime : timeval
{
  SimpleTime();

  void setNow();

  SimpleTime& operator-=(const timeval& rhs);

  SimpleTime operator-(const timeval& rhs);

  SimpleTime operator-(const SimpleTime& rhs);

  //! Convert to number of seconds (including fraction).
  operator double() const;

  operator std::string() const;
};

//! returns value of environment variable @param varname, or, if not defined, @param default_value
std::string getEnvWithDefault(const std::string& varname, const std::string& default_value);

//! Expands the filename with environment variables.
std::string expandFileName(const std::string& pathname);

/**
 * Returns the 'number of the PCI board' in the busadapter specification,
 * i.e. the x of the string 'CAENPCI:x.y'.
 * @param adapter_spec is the string following the colon e.g. in the string 'CAENPCI:0.0'.
 */
int getCaenBusAdapterUnitNumberFromString(const std::string& adapter_spec);

/**
 * Returns the 'number of the VMEBus controller' in the busadapter specification,
 * i.e. the y of the string 'CAENPCI:x.y'.
 * @param adapter_spec is the string following the colon e.g. in the string 'CAENPCI:0.0'.
 * (This is useful if one has more than one VMEbus controller connected to one PCI card.)
 */
int getCaenBusAdapterChainNumberFromString(const std::string& adapter_spec);

//! returns pointer to newly created HAL::VMEBusAdapterInterface (caller takes ownership)
HAL::VMEBusAdapterInterface* getBusAdapter(std::string const inName = "$VMEBUSADAPTER");

//! returns pointer to newly created HAL::VME64xDummyBusAdapter (caller takes ownership)
HAL::VME64xDummyBusAdapter* getDummyBusAdapter(const std::string& params);

/**
 * Returns attribute-value pairs from a DOMnode.
 * Assumes that each attribute does not appear more than once.
 * Prefixes and local names are concatenated with a colon in between. TODO clarify
 */
std::map<std::string, std::string> getAllAttributesOfNode(DOMNode* node);

//! returns current time as string
std::string GetCurrentTime();

/**
 * Creates a SOAP message for a TTC command @param commandname,
 * passing a map @param variables with name-value pairs.
 */
xoap::MessageReference createSOAPMessageCommand(
    const std::string& commandname,
    const std::map<std::string, std::string>& params);

//! Creates a SOAP reply message for an exception, with @param e used for the SOAP fault and details.
xoap::MessageReference createSOAPReplyException(xcept::Exception& e);

//! Creates a SOAP reply message for an FSM state query
xoap::MessageReference createSOAPReplyFSMState(
    const std::string& actionResponse,
    const std::string& stateResponse);

//! Creates a SOAP reply message for an FSM state transition request
xoap::MessageReference createSOAPReplyFSMTransition(
    const std::string& actionResponse,
    const std::string& stateResponse);

//! Creates a SOAP reply message for a generic TTC command, with @param commandResponse as the main tag
xoap::MessageReference createSOAPReplyCommand(const std::string& commandResponse);

//! Creates a SOAP reply message containing the current configuration string @param configStr
xoap::MessageReference createSOAPReplyGetCurrentConfiguration(const std::string& configStr);

}


#endif
