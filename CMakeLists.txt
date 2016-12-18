cmake_minimum_required(VERSION 2.8.8)
PROJECT(Orangutan)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall")

option(USE_QT "Enable qt context" ON)

# Make include root directory
include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(OpenGL REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIR} )
message(STATUS "Found OpenGL: ${OPENGL_INCLUDE_DIR}")

find_package(GLM REQUIRED)
include_directories( ${GLM_INCLUDE_DIR} )

if(USE_QT)
    #find_package(QT REQUIRED)
    #include_directories( ${QT_INCLUDE_DIR} )
    #include_directories( ${QT_CORE_INCLUDE_DIR} )
    #include_directories( ${QT_GUI_INCLUDE_DIR} )
    #include_directories( ${QT_OPENGL_INCLUDE_DIR} )
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_INCLUDE_CURRENT_DIR ON)

    find_package(Qt5Widgets REQUIRED)
    find_package(Qt5OpenGL REQUIRED)
    #set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -lGL -lm ${Qt5Core_EXECUTABLE_COMPILE_FLAGS}, ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}, ${Qt5Gui_EXECUTABLE_COMPILE_FLAGS}, ${Qt5OpenGL_EXECUTABLE_COMPILE_FLAGS}")
# Call moc automatically when needed
else()
    find_package(NANOGUI REQUIRED)
    include_directories( ${NANOGUI_INCLUDE_DIR} )
endif()

set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -lGL -lm -lGLU")

link_directories(
  /usr/local/lib
  /opt/local/lib
  ${NANOGUI_LIB_DIRS}
  ${QT_LIB_DIRS}
)

set(LIBS
    ${LIBS}
    ${OPENGL_LIBRARIES}
    ${NANOGUI_LIBRARIES}
    ${QT_LIBRARIES}
    )


file (GLOB APPSRCFILES src/app/*.cpp)
file (GLOB CORESRCFILES src/core/*.cpp)
file (GLOB OBJECTSRCFILES src/object/*.cpp)
file (GLOB PHYSICSSRCFILES src/physics/*.cpp)
file (GLOB SCENESRCFILES src/scene/*.cpp)
file (GLOB SHADERSRCFILES src/shader/*.cpp)
file (GLOB UTILSRCFILES src/util/*.cpp)

if(USE_QT)
    file (GLOB QTAPPSRCFILES src/app/qt/*.cpp)
    file (GLOB QTCORESRCFILES src/core/qt/*.cpp)
    set(SRCFILES
        ${APPSRCFILES}
        ${CORESRCFILES}
        ${OBJECTSRCFILES}
        ${PHYSICSSRCFILES}
        ${SCENESRCFILES}
        ${SHADERSRCFILES}
        ${UTILSRCFILES}
        ${QTAPPSRCFILES}
        ${QTCORESRCFILES}
        )
endif()

add_executable(orangutan ${SRCFILES})
QT5_USE_MODULES(orangutan Widgets OpenGL)
target_link_libraries(orangutan ${LIBS})
