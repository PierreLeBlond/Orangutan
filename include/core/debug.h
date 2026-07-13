#ifndef ORANGUTAN_CORE_DEBUG_H
#define ORANGUTAN_CORE_DEBUG_H

#include <glad/glad.h>

#include <iostream>
#include <map>
#include <sstream>

namespace orangutan {

GLenum glCheckError_(const char *cmd, const char *file, int line);

#define GL_CHECK_ERROR(cmd)                                                    \
  cmd;                                                                         \
  (void)glCheckError_(#cmd, __FILE__, __LINE__);

} // namespace orangutan

#endif // ORANGUTAN_CORE_DEBUG_H
