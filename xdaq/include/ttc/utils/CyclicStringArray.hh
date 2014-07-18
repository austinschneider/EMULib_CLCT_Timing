#ifndef _ttc_utils_CyclicStringArray_hh_
#define _ttc_utils_CyclicStringArray_hh_


#include <vector>
#include <string>


namespace ttc
{

/**
 * Utility class to hold list of strings and providing cyclic access via next().
 * This can e.g. be used for alternating colors in HTML tables.
 */
class CyclicStringArray
{
public:

  //! Construct by char* array
  CyclicStringArray(const char* data[]);

  //! Return next string entry
  std::string next();

protected:

  size_t cur_ptr;
  std::vector<std::string> strings;
};

}


#endif
