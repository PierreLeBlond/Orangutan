cmake_minimum_required(VERSION 2.8.8)
PROJECT(Orangutan)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g -Wall -fPIC")

# Make include root directory
include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(OpenGL REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIR} )
message(STATUS "Found OpenGL: ${OPENGL_INCLUDE_DIR}")

find_package(GLM REQUIRED)
include_directories( ${GLM_INCLUDE_DIR} )

find_package(EIGEN REQUIRED)
include_directories( "${EIGEN_INCLUDE_DIR}" )
find_package(GLFW REQUIRED)
include_directories( ${GLFW_INCLUDE_DIR} )
find_package(NANOGUI REQUIRED)
include_directories( ${NANOGUI_INCLUDE_DIRS} )
find_package(SOIL REQUIRED)
include_directories( ${SOIL_INCLUDE_DIR} )

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
file (GLOB CORESHADERSRCFILES src/core/shader/*.cpp)
file (GLOB CORETEXTURESRCFILES src/core/texture/*.cpp)
file (GLOB COREBUFFERSRCFILES src/core/buffer/*.cpp)
file (GLOB COREVERTEXSRCFILES src/core/vertex/*.cpp)
file (GLOB OBJECTSRCFILES src/object/*.cpp)
file (GLOB CAMERASRCFILES src/camera/*.cpp)
file (GLOB PHYSICSSRCFILES src/physics/*.cpp)
file (GLOB SCENESRCFILES src/scene/*.cpp)
file (GLOB SHADERSRCFILES src/shader/*.cpp)
file (GLOB UTILSRCFILES src/util/*.cpp)
file (GLOB MODELSRCFILES src/model/*.cpp)
file (GLOB PRESENTERSRCFILES src/presenter/*.cpp)
file (GLOB VIEWSRCFILES src/view/*.cpp)

set(SRCFILES
    ${VIEWSRCFILES}
    ${CORESHADERSRCFILES}
    ${CORETEXTURESRCFILES}
    ${COREBUFFERSRCFILES}
    ${COREVERTEXSRCFILES}
    ${APPSRCFILES}
    ${CORESRCFILES}
    ${OBJECTSRCFILES}
    ${CAMERASRCFILES}
    ${PHYSICSSRCFILES}
    ${SCENESRCFILES}
    ${SHADERSRCFILES}
    ${UTILSRCFILES}
    ${MODELSRCFILES}
    ${PRESENTERSRCFILES}
    )

add_executable(Orangutan ${SRCFILES})

target_link_libraries(Orangutan ${LIBS})
