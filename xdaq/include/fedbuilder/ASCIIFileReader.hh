#ifndef __ASCIIFileReader_hh_
#define __ASCIIFileReader_hh_

#include <string>

namespace fedbuilder
{
  class ASCIIFileReader {
  public:

    ASCIIFileReader( std::string fileName,
		     std::string& errorString );
    std::string getContent() const;

  private:
    std::string fileName_;
    std::string content_;
  };
}
#endif
