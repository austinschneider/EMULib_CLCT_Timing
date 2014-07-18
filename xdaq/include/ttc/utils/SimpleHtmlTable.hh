#ifndef _ttc_utils_SimpleHtmlTable_hh_
#define _ttc_utils_SimpleHtmlTable_hh_


#include "ttc/utils/HtmlTag.hh"

#include <vector>
#include <string>


namespace ttc
{

/**
 * A class representing a simple HTML table (without cells spanning multiple rows,
 * allowing for random access to table's cells.
 */
class SimpleHtmlTable
{
// nested class

public:

  //! class encapsulating text and attributes of one cell
  class CellData : public HtmlTag
  {
  public:
    CellData() : HtmlTag("td") {}
  };

// members

public:

  //! the row offset applied when using operator() to access a table cell
  size_t row_offset;

  //! the column offset applied when using operator() to access a table cell
  size_t col_offset;

  SimpleHtmlTable();

  //! returns the number of rows of the table
  size_t GetNumRows() const;

  //! returns the number of columns for row given by @param row_number
  size_t GetNumColumns(size_t row_number) const;

  //! returns the highest number of columns encountered in any row
  size_t GetTableWidthInCells() const;

  /**
   * Returns reference to cell located at coordinates defined by @param row and @param column .
   * Expands the table if needed (increases number of rows and/or columns as due).
   */
  CellData& GetCell(size_t row, size_t column, bool apply_offset);

  //! returns the table's cell that was last accessed
  CellData& last();

  //! returns cell while applying the offset; TODO clarify
  CellData& operator()(size_t row, size_t column);

  //! inserts an empty row before @param row
  void InsertEmptyRowBefore(size_t row, bool apply_offset);

  //! inserts an empty column before @parm column
  void InsertEmptyColumnBefore(size_t column, bool apply_offset);

  //! prints table's HTML output to stream @param os
  void Print(std::ostream &os);

  /**
   * Sets an attribute for the cells in a row, up to the current width of the table,
   * i.e. this method can create additional (empty) cells.
   */
  void SetAttrForWholeRow(size_t row, const std::string &name, const std::string &value, bool apply_offset = true);

  //! stores current offset settings (pushes to the stack); TODO clarify
  void PushOffsets();

  //! recalls most recently stored offset settings (get from the stack and pop); TODO clarify
  void PopOffsets();

  /**
   * Applies alternating colors to the table's rows.
   * @param line_colors is a vector of C-style strings, where the last entry must be NULL pointer.
   */
  void ApplyAlternatingRowColors(size_t first_row, const char* line_colours[]);

private:

  HtmlTag table_tag;

  //! container holding the table's cell data (first index is row, second index is column)
  std::vector<std::vector<CellData> > cells;

  //! index of last row accessed
  size_t last_row_accessed;

  //! index of last column accessed
  size_t last_col_accessed;

  //! stack holding the history of row/column offsets
  std::vector<std::pair<size_t, size_t> > offset_stack;

  /**
   * similar to GetCell, but does not expand table if indicated cell does not exist
   * (in this case, returns empty CellData object)
   */
  const CellData& GetCellIfExisting(size_t row, size_t column, bool apply_offset) const;

  //! Fills a row with &nbsp; and removes any attributes and styles.
  void ClearRow(size_t row);

  //! fills a column with &nbsp; and removes any attributes and styles
  void ClearColumn(size_t column);

  /**
   * Pastes @param other_table at position indicated by @param row and @parm column .
   * A rectangle corresponding to the dimensions of the other table is pasted (including empty cells).
   */
  void PasteOtherTable(
      size_t row,
      size_t column,
      const SimpleHtmlTable &other_table,
      bool apply_offset = true,
      bool apply_offset_to_other = true);
};

}


#endif
