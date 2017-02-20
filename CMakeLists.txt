cmake_minimum_required(VERSION 2.8.8)
PROJECT(Orangutan)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g -Wall -fPIC")

option(USE_QT "Enable qt context" OFF)

# Make include root directory
include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(OpenGL REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIR} )
message(STATUS "Found OpenGL: ${OPENGL_INCLUDE_DIR}")

find_package(GLM REQUIRED)
include_directories( ${GLM_INCLUDE_DIR} )

if(USE_QT)
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    set(CMAKE_AUTOMOC ON)
else()
    find_package(EIGEN REQUIRED)
    include_directories( "${EIGEN_INCLUDE_DIR}" )
    find_package(GLFW REQUIRED)
    include_directories( ${GLFW_INCLUDE_DIR} )
    find_package(NANOGUI REQUIRED)
    include_directories( ${NANOGUI_INCLUDE_DIRS} )
    find_package(SOIL REQUIRED)
    include_directories( ${SOIL_INCLUDE_DIR} )
endif()

find_package(LIBPNG REQUIRED)
include_directories( ${LIBPNG_INCLUDE_DIR} )

set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -lGL -lm -lGLU")

link_directories(
    /usr/local/lib
    /opt/local/lib
    ${NANOGUI_LIB_DIRS}
    ${SOIL_LIB_DIRS}
    ${LIBPNG_LIB_DIRS}
    )

set(LIBS
    ${LIBS}
    ${OPENGL_LIBRARIES}
    ${NANOGUI_LIBRARY}
    ${SOIL_LIBRARY}
    ${LIBPNG_LIBRARY}
    )

file (GLOB APPSRCFILES src/app/*.cpp)
file (GLOB CORESRCFILES src/core/*.cpp)
file (GLOB OBJECTSRCFILES src/object/*.cpp)
file (GLOB CAMERASRCFILES src/camera/*.cpp)
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
        ${CAMERASRCFILES}
        ${PHYSICSSRCFILES}
        ${SCENESRCFILES}
        ${SHADERSRCFILES}
        ${UTILSRCFILES}
        ${QTAPPSRCFILES}
        ${QTCORESRCFILES}
        )
else()
    file (GLOB NANOGUIAPPSRCFILES src/app/nanogui/*.cpp)
    file (GLOB NANOGUIVIEWSRCFILES src/view/nanogui/*.cpp)
    file (GLOB NANOGUICORESRCFILES src/core/nanogui/*.cpp)
    file (GLOB NANOGUICORESHADERSRCFILES src/core/nanogui/shader/*.cpp)
    file (GLOB NANOGUICORETEXTURESRCFILES src/core/nanogui/texture/*.cpp)
    file (GLOB NANOGUICOREBUFFERSRCFILES src/core/nanogui/buffer/*.cpp)
    file (GLOB NANOGUICOREVERTEXSRCFILES src/core/nanogui/vertex/*.cpp)
    set(SRCFILES
        ${APPSRCFILES}
        ${CORESRCFILES}
        ${OBJECTSRCFILES}
        ${CAMERASRCFILES}
        ${PHYSICSSRCFILES}
        ${SCENESRCFILES}
        ${SHADERSRCFILES}
        ${UTILSRCFILES}
        ${NANOGUIAPPSRCFILES}
        ${NANOGUIVIEWSRCFILES}
        ${NANOGUICORESRCFILES}
        ${NANOGUICORESHADERSRCFILES}
        ${NANOGUICORETEXTURESRCFILES}
        ${NANOGUICOREBUFFERSRCFILES}
        ${NANOGUICOREVERTEXSRCFILES}
        )
endif()

add_executable(Orangutan ${SRCFILES})

if(USE_QT)
    find_package(Qt5Widgets REQUIRED)
    find_package(Qt5OpenGL REQUIRED)
    QT5_USE_MODULES(Orangutan Core Gui Widgets OpenGL)
endif()
target_link_libraries(Orangutan ${LIBS})
