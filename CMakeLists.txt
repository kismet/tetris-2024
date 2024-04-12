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

add_executable(test_font_easysdl
        test/easy_sdl_font.cpp
        src/easy_sdl.cpp
)
target_link_libraries(test_font_easysdl SDL2 SDL2_image SDL2_ttf)

add_executable(test_asset_easysdl
        test/easy_sdl_asset.cpp
        src/easy_sdl.cpp
)
target_link_libraries(test_asset_easysdl SDL2 SDL2_image SDL2_ttf)

add_executable(test_init_easysdl
        test/easy_sdl_init.cpp
        src/easy_sdl.cpp
)
target_link_libraries(test_init_easysdl SDL2 SDL2_image SDL2_ttf)


add_executable(demo_menu
        src/easy_sdl.cpp
        main.cpp
)
target_link_libraries(demo_menu SDL2 SDL2_image SDL2_ttf)

add_executable(first_demo
        test/loading_assets.cpp
        src/easy_sdl.cpp
        src/testris_asset.cpp
)
target_link_libraries(first_demo SDL2 SDL2_image SDL2_ttf)

add_executable(tetris
        main.cpp
        src/game_engine.cpp
        src/easy_sdl.cpp
)
target_link_libraries(tetris SDL2 SDL2_image SDL2_ttf)
