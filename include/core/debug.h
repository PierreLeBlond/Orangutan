#ifndef ORANGUTAN_CORE_DEBUG_H
#define ORANGUTAN_CORE_DEBUG_H

#include <iostream>

namespace orangutan {

class Debug {
 public:
  static void getError(std::string str = "unknown");
};

}  // namespace orangutan

#endif  // ORANGUTAN_CORE_DEBUG_H
