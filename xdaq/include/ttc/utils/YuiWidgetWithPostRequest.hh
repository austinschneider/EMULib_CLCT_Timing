#ifndef _ttc_utils_YuiWidgetWithPostRequest_hh_
#define _ttc_utils_YuiWidgetWithPostRequest_hh_


#include <string>
#include <map>
#include <vector>


namespace ttc
{

/**
 * Base class for implementation of YUI widgets that submit
 * an HTTP POST request when their value changes.
 */
class YuiWidgetWithPostRequest
{
// static

protected:

  //! the base URL where YUI files should be taken from, to be set by the user
  static std::string yui_base_url;

public:

  /**
   * Returns the include statements needed for the widget code.
   * The arguments in the vector are a list of relative include names
   * (everything after the 'build' directory).
   */
  static std::string getYuiIncludes(std::vector<std::string> const includes);

  static void setYuiIncludeBasePath(const std::string &new_path);

  static std::string getYuiIncludeBasePath();

// members

public:

  //! URL without arguments that is called after the widget value changed
  std::string value_changed_url;

  //! add a fixed parameter (name-value pair), which must be unique (aborts if this is violated)
  void addFixedRequestParameter(const std::string &param_name, const std::string &param_value);

protected:

  std::string name;

  YuiWidgetWithPostRequest(const std::string &_name);

  /**
   * Returns JavaScript code which represents an associative array constant
   * with the fixed parameters for the HTTP request.
   */
  std::string makeHttpRequestParametersJavascriptCode();

  /**
   * Returns JavaScript code for the submit command invocation (without trailing semicolon).
   *
   * @param get_value_function is the javascript code (or name of a function
   *        which is called to determine the value of the widget
   *        which should be included as the 'value' parameter of the POST request.
   */
  std::string makeMakeSubmitCommandInvocationCode(const std::string &get_value_function);

private:

  /**
   * map with 'fixed' arguments (those that do not change when the widget value changes);
   * these are included in the HTTP request submitted when the widget value changes.
   */
  std::map<std::string, std::string> http_request_fixed_arguments;
};

}


#endif
