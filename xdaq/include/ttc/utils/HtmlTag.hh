#ifndef _ttc_utils_HtmlTag_hh_
#define _ttc_utils_HtmlTag_hh_


#include <string>
#include <map>
#include <iostream>


namespace ttc
{

//! class representing an HTML tag with attributes
class HtmlTag
{
public:

  //! the content of the tag
  std::string content;

  HtmlTag(const std::string &_tag_name);

  //! allows to add CSS styles
  void SetStyle(const std::string &name, const std::string &value);

  //! Sets an attribute (don't set style with this, if you are using SetStyle for setting CSS styles)
  void SetAttr(const std::string &name, const std::string &value);

  //! Prints the opening part of the tag.
  void PrintOpening(std::ostream &os);

  //! Prints the closing part of the tag.
  void PrintClosing(std::ostream &os);

  //! prints the full tag (including content between opening and closing part)
  void Print(std::ostream &os);

  //! Removes all attributes
  void ClearAllAttrs();

  //! Removes all styles
  void ClearAllStyles();

private:

  //! map containing attribute-value pairs
  std::map<std::string, std::string> attributes;

  //! map containing CSS styles (if non-empty, then 'style' must not be in attributes)
  std::map<std::string, std::string> styles;

  //! the tag's name
  std::string tag_name;

  //! Returns tag as string
  std::string toString();
};

}


#endif
