cmake_minimum_required(VERSION 3.30)
project(searching_algorithms)

set(CMAKE_CXX_STANDARD 20)

Include(FetchContent)
FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.12.0
)
FetchContent_MakeAvailable(spdlog)

add_executable(search_algorithms
        main.cpp
        src/brute_force.cpp
        src/boyer_moore.cpp
)

target_include_directories(search_algorithms PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(search_algorithms PRIVATE spdlog::spdlog)
