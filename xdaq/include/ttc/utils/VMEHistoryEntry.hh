#ifndef _ttc_utils_VMEHistoryEntry_hh_
#define _ttc_utils_VMEHistoryEntry_hh_


#include <string>

#include "ttc/utils/Address.hh"


namespace ttc
{

//! class representing a an entry in the VME operations history
class VMEHistoryEntry
{
public:

  VMEHistoryEntry();

  VMEHistoryEntry(
      bool DoRead,
      const Address& a,
      uint32_t data,
      const std::string& Comment = "");

  VMEHistoryEntry(
      bool DoRead,
      const Address& a,
      uint32_t index,
      uint32_t data,
      const std::string& Comment = "");

  void Print(std::ostream* outstream) const;

  std::string text() const;

  bool operator==(const VMEHistoryEntry& entry) const;

  bool operator!=(const VMEHistoryEntry& entry) const;

private:

  Address address;
  uint32_t aindex;
  bool readaccess;
  uint32_t data;
  std::string comment;

  bool IsReadAccess() const;

  bool IsWriteAccess() const;

  bool IsBlockTransfer() const;

  bool IsSingleWordTransfer() const;
};


std::ostream& operator<<(std::ostream& out, const VMEHistoryEntry& ve);

}


#endif
