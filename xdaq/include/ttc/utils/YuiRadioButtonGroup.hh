#ifndef _ttc_utils_YuiRadioButtonGroup_hh_
#define _ttc_utils_YuiRadioButtonGroup_hh_


#include "ttc/utils/YuiWidgetWithPostRequest.hh"

#include <string>
#include <vector>


namespace ttc
{

class YuiRadioButtonGroup : public YuiWidgetWithPostRequest
{
public:

  YuiRadioButtonGroup(
      const std::string &_name,
      const std::string &_html_span_name);

  //! returns the radio button group's HTML code
  std::string getHtmlCode();

  //! adds a button to this radio button group
  void addButton(const std::string &label, const std::string &value);

  /**
   * Returns the JavaScript code which creates the radio button group.
   *
   * @param initial_value is the 'value' which is initially selected (starting from zero).
   *        An exception is thrown if this value was not given in the addButton call.
   */
  std::string getJavaScriptCreationCode(const std::string &initial_value);

protected:

  std::string html_span_name;
  std::vector<std::string> button_values, button_labels;
};

}


#endif
