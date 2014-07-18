#ifndef _ttc_utils_JavaScriptUtils_hh_
#define _ttc_utils_JavaScriptUtils_hh_


#include <string>


/**
 * A class encapsulating a collection of static functions producing javascript output.
 * The surrounding <script> tag is not added.
 */
class JavaScriptUtils
{
public:

  static std::string makeSubmitCommand();

  static std::string MakeSlider();

  static std::string setSliderSubmitCommand();

  static std::string makeCheckButton();

  static std::string getSliderIncrementButtonCommonCode();

  static std::string TextFieldWithIncrementButtons();
};


#endif
