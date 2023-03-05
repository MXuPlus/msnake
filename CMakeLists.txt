cmake_minimum_required(VERSION 3.24)
project(msnake C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)

add_executable(msnake main.c msnake.c msnake.h snake_main.c snake_main.h snake_data.c snake_data.h)

target_link_libraries(msnake ncurses)

# This option is designed for debug
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")