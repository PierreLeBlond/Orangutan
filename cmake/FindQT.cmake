#
# Try to find QT library and include path.
# Once done this will define
#
# QT_FOUND
# QT_INCLUDE_DIR
# QT_CORE_INCLUDE_DIR
# QT_GUI_INCLUDE_DIR
# QT_OPENGL_INCLUDE_DIR

if(NOT QT_FOUND)

# QT INCLUDE DIR
FIND_PATH(QT_INCLUDE_DIR QtCore/qstring.h
    PATHS
    ${PROJECT_SOURCE_DIR}/ext/qt5/include/
    /usr/local/include/qt5/
    /usr/x11/include/qt5/
    /usr/include/qt5/
    /usr/include/x86_64-linux-gnu/qt5/
    NO_DEFAULT_PATH
    )


# Core
FIND_PATH(QT_CORE_INCLUDE_DIR qstring.h
    PATHS
    ${PROJECT_SOURCE_DIR}/ext/qt5/include/QtCore/
    /usr/local/include/qt5/QtCore/
    /usr/x11/include/qt5/QtCore/
    /usr/include/qt5/QtCore/
    /usr/include/x86_64-linux-gnu/qt5/QtCore/
    NO_DEFAULT_PATH
    )

# Gui
FIND_PATH(QT_GUI_INCLUDE_DIR qopengl.h
    PATHS
    ${PROJECT_SOURCE_DIR}/ext/qt5/include/QtGui/
    /usr/local/include/qt5/QtGui/
    /usr/x11/include/qt5/QtGui/
    /usr/include/qt5/QtGui/
    /usr/include/x86_64-linux-gnu/qt5/QtGui/
    NO_DEFAULT_PATH
    )

# Opengl
FIND_PATH(QT_OPENGL_INCLUDE_DIR qgl.h
    PATHS
    ${PROJECT_SOURCE_DIR}/ext/qt5/include/QtOpenGL/
    /usr/local/include/qt5/QtOpenGL/
    /usr/x11/include/qt5/QtOpenGL/
    /usr/include/qt5/QtOpenGL/
    /usr/include/x86_64-linux-gnu/qt5/QtOpenGL/
    NO_DEFAULT_PATH
    )

#FIND_PATH( NANOGUI_LIB_DIRS nanogui.lib
#  PATHS
#    ${PROJECT_SOURCE_DIR}/ext/nanogui/build
#    /usr/local
#    /usr/X11
#    /usr
#    NO_DEFAULT_PATH
#    )

# FIND_LIBRARY( NANOGUI_LIBRARY NAMES nanogui
#   PATHS
#     ${PROJECT_SOURCE_DIR}/ext/nanogui/build
#     /usr/local
#     /usr/X11
#     /usr
#     NO_DEFAULT_PATH
#     )

SET(QT_FOUND "NO")

IF (QT_CORE_INCLUDE_DIR AND QT_GUI_INCLUDE_DIR AND QT_OPENGL_INCLUDE_DIR)
    SET(QT_FOUND "YES")
ENDIF (QT_CORE_INCLUDE_DIR AND QT_GUI_INCLUDE_DIR AND QT_OPENGL_INCLUDE_DIR)

if(QT_FOUND)
    message(STATUS "Found QT: ${QT_INCLUDE_DIR}, ${QT_CORE_INCLUDE_DIR}, ${QT_GUI_INCLUDE_DIR}, ${QT_OPENGL_INCLUDE_DIR}")
else(QT_FOUND)
    if (NOT QT_FIND_QUIETLY)
        message(FATAL_ERROR "could NOT find QT")
    endif (NOT QT_FIND_QUIETLY)
endif(QT_FOUND)

endif(NOT QT_FOUND)
