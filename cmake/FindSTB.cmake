#
# Try to find stb header file.
# Once done this will define
#
# STB_INCLUDE_DIR

if(NOT STB_FOUND)

  FIND_PATH(STB_INCLUDE_DIR stb_image.h
      PATHS
      ${PROJECT_SOURCE_DIR}/ext/stb/
      /usr/local/include/
      NO_DEFAULT_PATH
    )

  SET(STB_FOUND "NO")

  IF (STB_INCLUDE_DIR)
  SET(STB_FOUND "YES")
ENDIF (STB_INCLUDE_DIR)

if(STB_FOUND)
  message(STATUS "Found STB: ${STB_INCLUDE_DIR}")
else(STB_FOUND)
  if (NOT STB_FIND_QUIETLY)
    message(FATAL_ERROR "could NOT find STB")
  endif (NOT STB_FIND_QUIETLY)
endif(STB_FOUND)

endif(NOT STB_FOUND)
