cmake_minimum_required(VERSION 3.30)
project(boyer_mourse)

set(CMAKE_CXX_STANDARD 20)

Include(FetchContent)
FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.12.0
)
FetchContent_MakeAvailable(spdlog)

# Добавляем исполняемый файл
add_executable(search_algorithms
        main.cpp
        src/brute_force.cpp
        src/boyer_moore.cpp
        include/boyer_moore.h
)

# Добавляем директории с заголовочными файлами
target_include_directories(search_algorithms PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Линкуем с spdlog (исправлено имя цели)
target_link_libraries(search_algorithms PRIVATE spdlog::spdlog)
