#ifndef ASSET_H
#define ASSET_H

#include <string>

class Asset {
 public:
  Asset(const std::string &name = "untitled");

  [[nodiscard]] const std::string &getName() const;
  void setName(const std::string &name);

 private:
  std::string _name;
};

#endif  // ASSET_H
