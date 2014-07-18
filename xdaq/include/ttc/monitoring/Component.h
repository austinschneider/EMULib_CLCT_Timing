#ifndef _ttc_monitoring_component_h_
#define _ttc_monitoring_component_h_


#include <string>
#include <vector>
#include <map>


namespace ttc
{


class Component
{
public:
  Component(
    const std::string& group,
    const std::string& system,
    const std::string& localID);

  std::string getGroup() const;
  std::string getSystem() const;
  std::string getLocalID() const;
  std::string getKey() const;
 
private:
  std::string group_;
  std::string system_;
  std::string localID_;
  std::string key_;

  std::string checkSpecifier(const std::string& specifier);
};


class ComponentCollection
{
public:
  std::string add(const Component& component);
  const std::vector<std::string>& getComponentKeys();
  Component getComponentByKey(const std::string& key);

private:
  std::vector<std::string> vecKeys_;
  std::map<std::string, Component> mapKeyToComponent_;
};


}


#endif
