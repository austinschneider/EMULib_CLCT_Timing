#ifndef __WebPageMaker_hh_
#define __WebPageMaker_hh_

#include <vector>
#include <string>
#include "xgi/Utils.h"
#include "xgi/Method.h"
#include "xdata/SimpleType.h"

namespace fedbuilder
{

class WebPageMaker 
{
public:
  WebPageMaker();

  void webPageHeader( xgi::Output *out,
		      std::string title ) const;

  int registerTable( std::string title,
		     std::string preSeparator,
		     std::string postSeparator );

  int addEntry( int tableId, 
		std::string name, 
		xdata::Serializable* data = NULL );

  // if no argument is given all tables are printed
  // return value: 0  all ok
  //               -1 error ( illegal tableId );
  int printTable(  xgi::Output *out,
		   int tableId = -1 ) const;

private:
  void webTableEntry( xgi::Output *out, const std::string text ) const;
  void webTableEntry( xgi::Output *out, const std::string name, const std::string value ) const;

  typedef struct 
  {
    std::string title;
    std::string preSeparator;
    std::string postSeparator;
    int tableId;
    std::vector< std::pair< std::string, xdata::Serializable * > > data;
  } webTable;

  xgi::Output *out_;
  int tableIdCounter_;
  std::vector <webTable> tableVector_; 
};

} /* namespace fedbuilder */

#endif /* __WebPageMaker_hh_ */
