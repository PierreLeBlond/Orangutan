#
# Try to find gli header file.
# Once done this will define
#
# GLI_INCLUDE_DIR

if(NOT GLI_FOUND)

  FIND_PATH(GLI_INCLUDE_DIR gli/gli.hpp
      PATHS
      ${PROJECT_SOURCE_DIR}/ext/gli
      /usr/local/include/
      NO_DEFAULT_PATH
    )

  SET(GLI_FOUND "NO")

  IF (GLI_INCLUDE_DIR)
    SET(GLI_FOUND "YES")
  ENDIF (GLI_INCLUDE_DIR)

  if(GLI_FOUND)
    message(STATUS "Found GLI: ${GLI_INCLUDE_DIR}")
  else(GLI_FOUND)
    if (NOT GLI_FIND_QUIETLY)
      message(FATAL_ERROR "could NOT find GLI")
    endif (NOT GLI_FIND_QUIETLY)
  endif(GLI_FOUND)

endif(NOT GLI_FOUND)
