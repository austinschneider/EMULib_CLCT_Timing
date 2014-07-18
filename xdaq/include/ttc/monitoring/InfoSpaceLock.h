#ifndef _ttc_monitoring_infospacelock_h_
#define _ttc_monitoring_infospacelock_h_


namespace xdata
{
class InfoSpace;
}


namespace ttc
{

class InfoSpaceLock
{
friend class MonitoringListener;
public:
  void lock();
  void unlock();
private:
  InfoSpaceLock();
  InfoSpaceLock(xdata::InfoSpace* infoSpace);
  xdata::InfoSpace* infoSpace_;
};


class InfoSpaceLockHandler
{
public:
  InfoSpaceLockHandler(const ttc::InfoSpaceLock& infoSpaceLock);
  ~InfoSpaceLockHandler();
private:
  InfoSpaceLock infoSpaceLock_;
};

}


#endif
