#ifndef ORANGUTAN_CORE_HANDLE_H
#define ORANGUTAN_CORE_HANDLE_H

#include "glad/glad.h"

namespace orangutan {

class Handle {
public:
  [[nodiscard]] unsigned int getId() const;
  void setId(unsigned int id);

private:
  unsigned int _id;
};

} // namespace orangutan

#endif // ORANGUTAN_CORE_HANDLE_H
