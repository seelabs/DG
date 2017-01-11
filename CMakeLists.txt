cmake_minimum_required(VERSION 3.1.0)

if (DEFINED ENV{NIH})
  set(NIH $ENV{NIH})
else()
  set(NIH $ENV{HOME}/projs/nih)
endif()

set(CMAKE_MODULE_PATH "${NIH}/cmake/module")
include(CMakeFuncs)

set(CMAKE_CXX_STANDARD 14)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads)

add_executable(main src/main.cpp ${NIH}/fmt/fmt/format.cc ${NIH}/fmt/fmt/ostream.cc)
target_link_libraries(main Threads::Threads)
nih(main boost fmt range spdlog)

add_executable(utest test/main.cpp ${NIH}/fmt/fmt/format.cc ${NIH}/fmt/fmt/ostream.cc)
target_link_libraries(utest Threads::Threads)
nih(utest boost catch fmt range spdlog)
