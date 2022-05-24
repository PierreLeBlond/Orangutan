#include "core/handle.h"

namespace orangutan {

unsigned int Handle::getId() const { return _id; }
void Handle::setId(unsigned int id) { _id = id; }

}  // namespace orangutan

