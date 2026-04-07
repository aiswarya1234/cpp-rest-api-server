cmake_minimum_required(VERSION 3.10)
project(cpp_rest_api)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads REQUIRED)

include_directories(src)

add_executable(app
    src/main.cpp
    src/user_service.cpp
    src/user_controller.cpp
)

target_link_libraries(app Threads::Threads)
