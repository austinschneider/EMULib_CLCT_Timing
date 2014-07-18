#ifndef _ttc_utils_CgiUtils_hh_
#define _ttc_utils_CgiUtils_hh_


#include <xgi/Output.h>

#include <string>
#include <iostream>


namespace cgicc
{
class Cgicc;
}

namespace xgi
{
class Input;
}

/**
 * An utility class for CGI callbacks.
 *
 * Instantiate it at the beginning of the callback,
 *   with reference to the ogiginal xgi::Output of the callback,
 *   and feed CGI output into it.
 * When your callback returns (naturally, via a return statement, or following an exception)
 *   it will be deleted and at this point flush the stream collected.
 * If flushIfException == false, flushing on delete is suppressed
 *   if the destruction happens as a consequence of unwinding an exception.
 */
class XgiOutputHandler : public xgi::Output
{
public:
  XgiOutputHandler(xgi::Output& xo, bool flushIfException = false);
  ~XgiOutputHandler();
private:
  xgi::Output& xo_;
  bool flushIfException_;
};


//! class collecting utilities for handling CGI parameters
class CgiUtils
{

// static

public:

  /**
   * Extract parameter in a given HTTP request.
   * Throws std::invalid_argument if parameter does not exist or is given more than once.
   */
  static std::string GetCgiParam(cgicc::Cgicc& cgi, const std::string& param_name);

  /**
   * Extract bool parameter in a given HTTP request.
   * Throws std::invalid_argument if parameter does not exist or is given more than once or is neither 'true' nor 'false'.
   */
  static bool GetBoolCgiParam(cgicc::Cgicc& cgi, const std::string& param_name);

  /**
   * Extract int parameter in a given HTTP request.
   * Throws std::invalid_argument if parameter does not exist or is given more than once or is not an int.
   */
  static int GetIntCgiParam(cgicc::Cgicc& cgi, const std::string& param_name);

  /**
   * This is a workaround around a bug in the cgicc version used in XDAQ.
   *
   * If the content-type starts with 'application/x-www-form-urlencoded',
   * possibly followed by a charset definition, this sets it to this string only.
   *
   * If there is a charset specification (such as generated with recent versions of firefox),
   * this confuses cgicc (at least with post requests) in the sense that
   * it does not find any data submitted in the request.
   */
  static void FixContentType(xgi::Input* in);

  //! Print parameter -> value pairs on the given output stream, for the given HTTP request.
  static void PrintParameters(std::ostream& os, cgicc::Cgicc& cgi);

  /**
   * checks if given @param param_name is found in incoming CGI request;
   * if yes, returns first element of vector we get from cgicc;
   * else returns given @param default_value
   */
  static std::string CgiccGetParameterWithDefault(
      cgicc::Cgicc& cgi,
      const std::string& param_name,
      const std::string& default_value = "");

  //! tells whether given @param exists in incoming CGI request
  static bool CgiccHasParameter(cgicc::Cgicc& cgi, const std::string& param_name);
};


#endif
