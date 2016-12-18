#
# Try to find GLM include path.
# Once done this will define
#
# GLM_FOUND
# GLM_INCLUDE_DIR

if(NOT GLM_FOUND)

FIND_PATH(GLM_INCLUDE_DIR glm/glm.hpp
  PATHS
  ${PROJECT_SOURCE_DIR}/ext/GLM/
  /usr/local/include
  /usr/X11/include
  /usr/include
  /opt/local/include
  NO_DEFAULT_PATH
  )

SET(GLM_FOUND "NO")

if(GLM_INCLUDE_DIR)
    SET(GLM_FOUND "YES")
endif()

if(GLM_FOUND)
    message(STATUS "Found GLM: ${GLM_INCLUDE_DIR}")
else(GLM_FOUND)
    if (NOT GLM_FIND_QUIETLY)
        message(FATAL_ERROR "could NOT find GLM")
    endif (NOT GLM_FIND_QUIETLY)
endif()

endif(NOT GLM_FOUND)
