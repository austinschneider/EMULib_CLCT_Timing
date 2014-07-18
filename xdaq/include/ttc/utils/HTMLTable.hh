#ifndef _ttc_utils_HTMLTable_hh_
#define _ttc_utils_HTMLTable_hh_


#include <string>
#include <iostream>


namespace ttc
{

//! class to handle generation of HTML table output
class HTMLTable
{
public:

  HTMLTable(
      std::ostream& outstream,
      const int border = 1,
      const int cellpadding = 2,
      const int cellspacing = 2,
      const std::string& bgdcolor = "",
      const std::string& align = "",
      const int widthpercentage = 0);

  HTMLTable(std::ostream& outstream, const std::string& style);

  ~HTMLTable();

  void Set(
      const int border = 1,
      const int cellpadding = 2,
      const int cellspacing = 2,
      const std::string& bgdcolor = "",
      const std::string& align = "",
      const int widthpercentage = 0);

  void SetCellStyle(const std::string &style);

  void NewCell(const std::string &style = "", const size_t colspan = 1, const size_t rowspan = 1);

  /**
   * Starts a new row (i.e. prints the <tr> opening tag).
   * If a cell is still open this will print the closing tag for the cell (</td>).
   * If a row is still open, this will print the closing tag for the row (</tr>).
   */
  void NewRow();

  void CloseRow();

  //! 'Opens' the html table, i.e. writes the corresponding opening HTML tag to the output stream.
  void Open();

  //! 'Closes' the html table, i.e. writes the corresponding closing HTML tag to the output stream.
  void Close();

private:

  bool _inrow;
  bool _incell;
  bool _isopen;

  std::ostream &out;

  //! The table border (width ?).
  std::string _border;

  //! The table's cell padding.
  std::string _padding;

  //! The table's cell spacing.
  std::string _spacing;

  //! The table's background color.
  std::string _bgdcolor;

  //! Alignment of the table itself (used in the table tag).
  std::string _align;

  //! The table width.
  size_t _widthpercentage;

  std::string _cell_vertical;

  //! Cell horizontal text alignment.
  std::string _cell_align;

  //! Bold or normal text in the cells.
  bool _cell_bold;

  //! Cell background color.
  std::string _cell_bgdcolor;

  //! Cell colspan (how many columns should cells span).
  size_t _cell_colspan;

  //! Cell rowspan (how many rows should cells span).
  size_t _cell_rowspan;

  //! Recognizes certain keywords in 'style' and sets the corresponding flag.
  void Set(const std::string &style);

  void ClearCellStyle();

  /**
   * Returns true if str1 or str2 or str3 occur in basestr
   * (empty strings in strx do not count as occurence).
   */
  bool FindString(
      const std::string& basestr,
      const std::string& str1,
      const std::string& str2 = "",
      const std::string& str3 = "") const;
};

}


#endif
