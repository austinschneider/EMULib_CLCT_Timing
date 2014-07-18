#ifndef _ttc_utils_Singleton_h_
#define _ttc_utils_Singleton_h_


//! class template implementing the Singleton pattern
template<class T>
class Singleton
{
public:
  Singleton() : _instance(0)
  {}

  T* instance()
  {
    if (_instance == 0)
      _instance = new T();
    return _instance;
  }

protected:
  T *_instance;
};


#endif
