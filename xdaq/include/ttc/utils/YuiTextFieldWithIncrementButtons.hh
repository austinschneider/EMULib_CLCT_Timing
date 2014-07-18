#ifndef _ttc_utils_YuiTextFieldWithIncrementButtons_hh_
#define _ttc_utils_YuiTextFieldWithIncrementButtons_hh_


#include "ttc/utils/YuiWidgetWithPostRequest.hh"

#include <string>
#include <vector>


namespace ttc
{

/**
 * A widget consisting of a text field with associated increment and decrement buttons.
 * Similar in functionality to the slider, except it lacks the slider.
 * Useful to control value ranges that are too large for a slider.
 */
class YuiTextFieldWithIncrementButtons : public YuiWidgetWithPostRequest
{
// static

public:

  //! returns the include statements needed for the widget code
  static std::string getYuiIncludes();

  //! returns common JavaScript code
  static std::string getCommonJavaScriptCode();

// members

public:

  //! constructor: @param _initial_value is value of the slider when the page is loaded
  YuiTextFieldWithIncrementButtons(
      const std::string &_name,
      int _initial_value,
      int _min_value,
      int _max_value);

  //! returns HTML code for the text input field
  std::string getTextInputHtmlCode();

  /**
   * Returns code for the button to increment value.
   * @param button_suffix for unique naming of buttons TODO clarify
   */
  std::string getIncrementButtonCreationCode(
      const std::string &button_suffix,
      const std::string &button_label,
      int increment) const;

private:

  //! initial value when page is loaded
  int initial_value;

  //! minimum value for selection
  int min_value;

  //! maximum value for selection
  int max_value;

  //! defines and returns an identifier for the JavaScript object of class TextFieldWithIncrementButtons
  std::string getJavaScriptObjectName() const;

  //! defines and returns an identifier for the text field
  std::string getTextFieldName() const;
};

}


#endif
