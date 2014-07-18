#ifndef _ttc_utils_HTMLFieldElement_hh_
#define _ttc_utils_HTMLFieldElement_hh_


#include <string>
#include <iostream>
#include <vector>


namespace ttc
{

class HTMLFieldElement
{

// types

public:

  enum FieldType { DROPDOWNMENU = 0, RADIOBUTTON = 1, CHECKBOX = 2 };

// members

public:

  HTMLFieldElement();

  HTMLFieldElement(
      const FieldType type,
      const int flag,
      const std::string& name,
      const std::vector<std::string>& values,
      const std::vector<std::string>& titles,
      const std::string& Options = "");

  HTMLFieldElement(
      const FieldType type,
      const int flag,
      const std::string& name,
      const std::vector<std::string> &values,
      const std::string& Options = "");

  void Set(
      const FieldType type,
      const int flag,
      const std::string& name,
      const std::vector<std::string>& values,
      const std::vector<std::string>& titles,
      const std::string &Options = "");

  void Set(
      const FieldType type,
      const int flag,
      const std::string& name,
      const std::vector<std::string>& values,
      const std::string& Options = "");

  std::string GetName() const;

  void SetName(const std::string& Name);

  void push_back(const std::string &value, const std::string &title = "");

  bool HasValue(const std::string & value) const;

  void SetDefault(const std::string & value);

  void SetDefault(const int32_t value);

  void SetCheck(const size_t index, bool val);

  void Check(const std::string& value);

  void UnCheck(const std::string &value);

  void UnCheckAll();

  std::vector<std::string> AllVector() const;

  std::vector<std::string> CheckedVector() const;

  const std::string& GetDefault() const;

  const std::string& GetDefaultTitle() const;

  int GetDefaultInt() const;

  void Write(std::ostream &out);

  size_t size() const;

  std::string GetValue(const size_t i);

  std::string GetTitle(const size_t i);

  void SetTitle(const size_t i, const std::string &tit);

private:

  int _flag;
  std::string _name;
  std::vector<std::string> _values;
  std::vector<std::string> _titles;
  std::vector<bool> _checked;
  std::string _strdefault;
  size_t _default;
  FieldType _type;
  std::string _options;
  bool _arrangeVertically;
  bool _TitleBeforeField;
  bool _BoldSelected;
  bool _UnderlineSelected;
  bool _GreenSelected;
  bool _BlueSelected;
  bool _RedSelected;

  void SetCheck(const std::string &value, bool val);

  void Check(const size_t index);

  void UnCheck(const size_t index);

  bool IsChecked(const size_t index) const;

  bool IsChecked(const std::string &value) const;

  void SetOptions(const std::string &Options);

  size_t GetDefaultIndex() const;

  bool IsRadioButton() const;

  bool IsDropDownMenu() const;

  bool IsCheckBoxes() const;

  bool FindString(
      const std::string &basestr,
      const std::string &str1,
      const std::string &str2 = "",
      const std::string &str3 = "") const;

  std::string RemovePrefix(const std::string &value) const;
};

}


#endif
