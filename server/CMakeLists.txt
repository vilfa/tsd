# CMakeList.txt : CMake project for server, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (server "server.cc" "server.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET server PROPERTY CXX_STANDARD 23)
endif()

set(ROOT_DIR "${PROJECT_SOURCE_DIR}")

# Add includes.

set(INCLUDE_DIR "${ROOT_DIR}/include")
target_include_directories(server PUBLIC "${INCLUDE_DIR}" "${INCLUDE_DIR}/os")

# Add externals.

set(EXT_DIR "${ROOT_DIR}/ext")
target_include_directories(server PRIVATE "${EXT_DIR}/spdlog/include")

# Add tests.
