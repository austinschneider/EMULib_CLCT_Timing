#ifndef _ttc_utils_YuiSlider_hh_
#define _ttc_utils_YuiSlider_hh_


#include "ttc/utils/YuiWidgetWithPostRequest.hh"

#include <string>
#include <vector>


namespace ttc
{

//! class representing a YUI slider widget
class YuiSlider : public ttc::YuiWidgetWithPostRequest
{
// static
public:

  static std::string getStyleSheet();

  //! returns the include statements needed for the widget code
  static std::string getYuiIncludes();

  /**
   * Returns code to be added to the head section of the HTML page:
   *    - the code of the commonly used javascript functions for sliders;
   *    - some initialization code to create the sliders on page load.
   */
  static std::string getAllSlidersJavaScriptCode(const std::vector<YuiSlider*>& sliders);

private:

  //! returns common JavaScript code
  static std::string getCommonJavaScriptCode();


// members

public:

  //! constructor: @param _initial_value is value of the slider when the page is loaded
  YuiSlider(
      const std::string& _name,
      int _initial_value,
      int _min_value,
      int _max_value);

  //! returns the slider HTML code (div tags containing colored areas of the slider)
  std::string getSliderHtmlCode();

  //! returns HTML code for input field (for the user to enter a number)
  std::string getHtmlCodeForTextControl();

  /**
   * Returns code for the button to increment the slider value.
   * @param button_suffix for unique naming of buttons within the same slide
   */
  std::string getSliderIncrementButtonCreationCode(
      const std::string &button_suffix,
      const std::string &button_label,
      int increment);

private:

  //! value of the slider when the page is loaded
  int initial_value;

  //! minimum value for selection
  int min_value;

  //! maximum value for selection
  int max_value;

  //! returns the (global) variable name used for each slider (name defined by this function)
  std::string getSliderVariableName();
};

}


#endif
