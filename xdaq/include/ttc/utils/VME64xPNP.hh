#ifndef _ttc_utils_VME64xPNP_hh_
#define _ttc_utils_VME64xPNP_hh_


#include "ttc/utils/VME64xDeviceInfo.hh"

#include <vector>
#include <string>


namespace HAL
{
class VMEAddressTable;
class VMEBusAdapterInterface;
}


namespace ttc
{

extern HAL::VMEAddressTable& DummyAddressTable;

class VME64xPNP
{
// static

public:

  static VME64xDeviceInfo GetDevice(HAL::VMEBusAdapterInterface& bus, const VME64xDeviceInfo& tofind);

// members

public:

  VME64xPNP(HAL::VMEBusAdapterInterface& bus);

  int NumberOfDevices() const;

//  int NumberOfEnabledDevices() const;

  VME64xDeviceInfo GetDeviceInfo(const VME64xDeviceInfo& tofind) const;

  VME64xDeviceInfo GetDeviceInfo(int slot) const;

  VME64xDeviceInfo Configure(const VME64xDeviceInfo& info);

private:

  int numDevices;
  int numEnabled;
  HAL::VMEBusAdapterInterface& bus;
  std::vector<VME64xDeviceInfo> devices;

  VME64xDeviceInfo GetAndConfigure(const VME64xDeviceInfo& tofind);
};

}


#endif
