cmake_minimum_required(VERSION 3.10)
project(dining-philosophers)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# ncurses
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# threads
find_package(Threads REQUIRED)

set(SRC dining/main.cpp dining/Philosopher.cpp dining/Random.cpp dining/Table.cpp dining/Chopstick.cpp dining/Talk.cpp dining/TableSetup.cpp)

add_executable(dining-philosophers ${SRC})
target_compile_options(dining-philosophers PRIVATE -Wall -Wextra -Wpedantic -O3)
target_link_libraries(dining-philosophers ${CURSES_LIBRARIES}
                      ${CMAKE_THREAD_LIBS_INIT})
