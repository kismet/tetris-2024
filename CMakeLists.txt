cmake_minimum_required(VERSION 3.26)
project(tetris-2024)
#set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
#set(CMAKE_EXE_LINKER_FLAGS "-static")

include_directories(
        libs/include/SDL2
)

link_directories(
        libs/lib
)

#add_executable(test_easysdl_init
#        easy_sdl_init.cpp
#)

add_executable(test_easysdl_init
        test/easy_sdl_init.cpp
        src/easy_sdl.cpp
)

target_link_libraries(test_easysdl_init SDL2 SDL2_image SDL2_ttf)
