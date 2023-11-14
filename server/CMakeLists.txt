# Main target.
add_executable(server "server.cc" "${PROJECT_SOURCE_DIR}/include/server.h")

# CXX standard
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET server PROPERTY CXX_STANDARD 23)
endif()

# Add sources.

set(ROOT_DIR "${PROJECT_SOURCE_DIR}")
add_subdirectory("net")

# Add includes.

set(INCLUDE_DIR "${ROOT_DIR}/include")
target_include_directories(server PUBLIC "${INCLUDE_DIR}" "${INCLUDE_DIR}/os")

# Add libs.

if(WIN32)
  target_link_libraries(server wsock32 ws2_32)
endif()

# Add externals.

set(EXT_DIR "${ROOT_DIR}/ext")
target_include_directories(server PRIVATE "${EXT_DIR}/spdlog/include")

# Add tests.
