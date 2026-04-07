cmake_minimum_required(VERSION 3.10)
project(cpp_rest_api)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads REQUIRED)

add_executable(app src/main.cpp)

target_link_libraries(app Threads::Threads)
