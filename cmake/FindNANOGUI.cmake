#
# Try to find NANOGUI library and include path.
# Once done this will define
#
# NANOGUI_FOUND
# NANOGUI_INCLUDE_DIR
# NANOGUI_INCLUDE_DIRS
# NANOGUI_LIBRARY
# NANOGUI_LIB_DIRS

if(NOT NANOGUI_FOUND)

FIND_PATH(NANOGUI_INCLUDE_DIR nanogui/nanogui.h
  PATHS
    ${PROJECT_SOURCE_DIR}/ext/nanogui/include
    /usr/local/include
    /usr/X11/include
    /usr/include
    /opt/local/include
    NO_DEFAULT_PATH
    )

FIND_PATH( NANOGUI_LIB_DIRS nanogui.lib
  PATHS
    ${PROJECT_SOURCE_DIR}/ext/nanogui/build
    /usr/local
    /usr/X11
    /usr
    NO_DEFAULT_PATH
    )

FIND_LIBRARY( NANOGUI_LIBRARY NAMES nanogui
  PATHS
    ${PROJECT_SOURCE_DIR}/ext/nanogui/build
    /usr/local
    /usr/X11
    /usr
    NO_DEFAULT_PATH
    )

SET(NANOGUI_FOUND "NO")

IF (NANOGUI_INCLUDE_DIR AND NANOGUI_LIBRARY)
    SET(NANOGUI_FOUND "YES")
    SET(NANOGUI_INCLUDE_DIRS
        ${NANOGUI_INCLUDE_DIR}/../include
        ${NANOGUI_INCLUDE_DIR}/../src
        ${NANOGUI_INCLUDE_DIR}/../ext/nanovg/src
        ${NANOGUI_INCLUDE_DIR}/../ext/glfw/include
        )

ENDIF (NANOGUI_INCLUDE_DIR AND NANOGUI_LIBRARY)

if(NANOGUI_FOUND)
  message(STATUS "Found NANOGUI: ${NANOGUI_INCLUDE_DIR}")
else(NANOGUI_FOUND)
  if (NOT NANOGUI_FIND_QUIETLY)
    message(FATAL_ERROR "could NOT find NANOGUI")
  endif (NOT NANOGUI_FIND_QUIETLY)
endif(NANOGUI_FOUND)

endif(NOT NANOGUI_FOUND)
