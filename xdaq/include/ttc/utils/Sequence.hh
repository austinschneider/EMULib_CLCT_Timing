#ifndef _ttc_utils_Sequence_hh_
#define _ttc_utils_Sequence_hh_


#include <vector>
#include <string>


namespace ttc
{

//! class representing a sequence as defined in configuration files of TTC modules
class Sequence
{
public:

  //! constructs unnamed empty non-permanent sequence
  Sequence();

  /**
   * constructs a Sequence:
   * @param vector is a vector containing the lines of the configuration file text defining the Sequence;
   * @param name is the name of the sequence;
   * @permanent tells if this is a "permanent" sequence; TODO clarify
   */
  Sequence(
      const std::vector<std::string>& sequence,
      const std::string& name = "",
      const bool permanent = false);

  //! returns the vector of elements of the Sequence
  std::vector<std::string> Get() const;

  //! returns the name of the Sequence
  std::string GetName() const;

  //! tells if this is a "permanent" Sequence
  bool IsPermanent() const;

  //! returns the number of elements in the Sequence
  size_t N() const;

  //! clears the vector containing the Sequence's elements
  void Clear();

  //! returns the i'th element of the Sequence
  std::string Get(size_t i) const;

  /**
   * strips off comments and white space from @param line, returns if empty; else:
   * replaces element @param i of the Sequence with @param line;
   * throws if i out of range;
   * NOTE: setting at N(), i.e. push back, is disallowed
   */
  void Set(size_t i, const std::string& line);

  //! adds an element to the Sequence (if @param line contains more than comments and whitespace)
  void PushBack(const std::string& line);

  /**
   * inserts sanitized version of @param line at position @param i of the Sequence vector, if non-empty;
   * throws if i out of range;
   * NOTE: insert at N(), i.e. push back, is disallowed
   */
  void Insert(size_t i, const std::string& line = "");

  //! deletes the i'th element from the Sequence (i=0 corresponds to the first element)
  void Delete(size_t i);

  //! returns the index of the first occurrence of @param line in the Sequence, or -1 if not found
  int GetIndex(const std::string& line) const;

  bool operator==(const Sequence& entry) const;

  bool operator!=(const Sequence& entry) const;

  bool operator==(const std::string& s) const;

  bool operator!=(const std::string& s) const;

private:

  std::vector<std::string> seq_;
  std::string name_;
  bool permanent_;

  //! removes comments (text after # token) and white space (blanks and tabs) from @param line
  std::string RemoveCommentsAndBlanks(const std::string& line) const;
};

}


#endif
