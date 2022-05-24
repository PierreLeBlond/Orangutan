#ifndef ORANGUTAN_OBJECT_ASSET_H
#define ORANGUTAN_OBJECT_ASSET_H

#include <string>

namespace orangutan {

class Asset {
 public:
  Asset(const std::string &name);

  [[nodiscard]] const std::string &getName() const;
  void setName(const std::string &name);

 private:
  std::string _name;
};

}  // namespace orangutan

#endif  // ORANGUTAN_OBJECT_ASSET_H
