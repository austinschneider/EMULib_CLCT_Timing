#ifndef _ttc_utils_YuiCheckButton_hh_
#define _ttc_utils_YuiCheckButton_hh_


#include "ttc/utils/YuiWidgetWithPostRequest.hh"

#include <string>
#include <vector>


namespace ttc
{

/**
 * class representing a YUI check button, with utilities to generate
 * HTML and JavaScript code for a YUI button which can be checked
 * and unchecked (and do an HTTP POST request when its state changes).
 */
class YuiCheckButton : public YuiWidgetWithPostRequest
{
public:

  //! string which the button shows in enabled state
  std::string enabled_label;

  //! string which the button shows in disabled state
  std::string disabled_label;

  /**
   * constructor:
   * @param name is the name of the javascript variable which holds the button.
   * @param html_span_name is the name of the html span tag
   *        which represents the HTML part of the button.
   */
  YuiCheckButton(
      const std::string &_name,
      const std::string &_html_span_name,
      const std::string &_enabled_label,
      const std::string &_disabled_label);

  //! returns the check button's HTML code
  std::string getHtmlCode();

  /**
   * Returns the JavaScript code which creates the button.
   *
   * @param initial_value is the current value of the button
   *   (which is e.g. read back from the actual VME module)
   *
   * @param on_click_codes are code segments (not function names)
   *   which are executed when the button is clicked
   *   (in addition to the code which generates a HTTP request).
   *   The new value of the button is stored in the variable 'new_value'.
   */
  std::string getJavaScriptCreationCode(
      bool initial_value,
      std::vector<std::string> on_click_codes = std::vector<std::string>());

protected:

  std::string html_span_name;
};

}


#endif
