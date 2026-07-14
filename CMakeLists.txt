cmake_minimum_required(VERSION 3.10.0)
cmake_policy(SET CMP0048 NEW)
PROJECT(Orangutan
  DESCRIPTION
  "Orangutan"
  LANGUAGES
  C CXX
  VERSION
  "1.0.0"
  )

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -g3")

# Generate compilation database for YouCompleteMe
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

# Make include root directory
include_directories(${PROJECT_SOURCE_DIR}/include)

# glfw
find_package(glfw3 3.4 REQUIRED)

# glm
set(glm_DIR ${PROJECT_SOURCE_DIR}/ext/glm)
find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIR})

find_package(assimp 4.1 REQUIRED)
include_directories( ${assimp_INCLUDE_DIR} )

find_package(STB REQUIRED)
include_directories( ${STB_INCLUDE_DIR} )

find_package(GLI REQUIRED)
include_directories( ${GLI_INCLUDE_DIR} )

# basis_universalis
file(GLOB_RECURSE BASISU_ENCODER_SOURCES
    ext/basis_universal/encoder/*.cpp
)
set(BASISU_TRANSCODER_SOURCES
    ext/basis_universal/transcoder/basisu_transcoder.cpp
)
add_library(basisu STATIC
    ${BASISU_ENCODER_SOURCES}
    ${BASISU_TRANSCODER_SOURCES}
)
target_include_directories(basisu PUBLIC
    ext/basis_universal
    ext/basis_universal/encoder
    ext/basis_universal/encoder/3rdparty
    ext/basis_universal/transcoder
)

# imgui
file(GLOB IMGUI_SOURCES
  ext/imgui/*.cpp
)
set(IMGUI_BACKEND_SOURCES
  ext/imgui/backends/imgui_impl_glfw.cpp
  ext/imgui/backends/imgui_impl_opengl3.cpp
)
include_directories(ext/imgui ext/imgui/backends)

find_package(nfd REQUIRED)
include_directories( ${nfd_INCLUDE_DIR} )

# glad
set(GLAD_SOURCES ext/glad/src/glad.c)
include_directories(ext/glad/include)

set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -lGL -luuid -lktx")

link_directories(
  /usr/local/lib
  /opt/local/lib
  )

set(LIBS
  ${LIBS}
  glfw
  assimp
  nfd
  basisu
  )

file (GLOB_RECURSE SRC_FILES src/*.cc)

# imgui recommand adding its file directly to the project
add_executable(Orangutan ${GLAD_SOURCES} ${SRC_FILES} ${IMGUI_SOURCES} ${IMGUI_BACKEND_SOURCES})

target_link_libraries(Orangutan ${LIBS})
