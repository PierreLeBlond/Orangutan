#
# Try to find GLFW library and include path.
# Once done this will define
#
# GLFW_FOUND
# GLFW_INCLUDE_DIR
# GLFW_LIBRARIES
#

if(NOT GLFW_FOUND)

FIND_PATH(GLFW_INCLUDE_DIR GLFW/glfw3.h
  PATHS
    ${PROJECT_SOURCE_DIR}/ext/glfw/include
    ${PROJECT_SOURCE_DIR}/ext/nanogui/ext/glfw/include
    /usr/local/include
    /usr/X11/include
    /usr/include
    /opt/local/include
    NO_DEFAULT_PATH
    )

if(GLFW_INCLUDE_DIR)
    set(GLFW_FOUND TRUE)
endif()


if(GLFW_FOUND)
  message(STATUS "Found GLFW: ${GLFW_INCLUDE_DIR}")
else(GLFW_FOUND)
  if (NOT GLFW_FIND_QUIETLY)
    message(FATAL_ERROR "could NOT find GLFW")
  endif (NOT GLFW_FIND_QUIETLY)
endif(GLFW_FOUND)

endif(NOT GLFW_FOUND)
