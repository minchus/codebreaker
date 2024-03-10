cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    codebreaker
    VERSION 0.1.0
    DESCRIPTION "Crack mono-alphabetic substitution ciphers"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    codebreaker_lib OBJECT
        source/cracker.cpp
)

target_include_directories(
    codebreaker_lib ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_compile_features(codebreaker_lib PUBLIC cxx_std_20)

find_package(fmt REQUIRED)
target_link_libraries(codebreaker_lib PRIVATE fmt::fmt)

# ---- Declare executable ----

add_executable(codebreaker_exe source/main.cpp)
add_executable(codebreaker::exe ALIAS codebreaker_exe)

set_property(TARGET codebreaker_exe PROPERTY OUTPUT_NAME codebreaker)

target_compile_features(codebreaker_exe PRIVATE cxx_std_20)

target_link_libraries(codebreaker_exe PRIVATE codebreaker_lib)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT codebreaker_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of codebreaker"
  )
endif()

include(cmake/dev-mode.cmake)
