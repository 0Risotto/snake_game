cmake_minimum_required(VERSION 3.10)
project(snake_game)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find ncurses
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# Source files
set(SOURCES
    main.cpp
    snake.cpp
    food.cpp
    map.cpp
    score.cpp
    bot.cpp
    ai.cpp
)

# Executable
add_executable(snake ${SOURCES})

# Link ncurses
target_link_libraries(snake ${CURSES_LIBRARIES})

