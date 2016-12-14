cmake_minimum_required(VERSION 2.8.6)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# Make include root directory
include_directories(${CMAKE_SOURCE_DIR}/src)

find_package(OPENGL REQUIRED)
include_directories( ${OPENGL_DIR} )

find_package(GLM REQUIRED)
include_directories( ${GLM_INCLUDE_DIR} )

find_package(NANOGUI REQUIRED)
include_directories( ${NANOGUI_INCLUDE_DIR} )


link_directories(
  /usr/local/lib
  /opt/local/lib
  ${NANOGUI_LIB_DIRS}
)

set(LIBS
    ${LIBS}
    ${OPENGL_LIBRARIES}
    ${NANOGUI_LIBRARIES}
    )

set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -lGL -lm")

file (GLOB_RECURSE SRCFILES src/*.cpp)

add_executable(decimator ${SRCFILES})
target_link_libraries(decimator ${LIBS})
