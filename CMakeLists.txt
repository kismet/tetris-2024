cmake_minimum_required(VERSION 3.10)
project(tetris)
set(BUILD_SHARED_LIBS OFF)
set(SDL2_DIR libs/lib/cmake/SDL2)
set(SDL2_image_DIR libs/lib/cmake/SDL2_image)
set(SDL2_ttf_DIR libs/lib/cmake/SDL2_ttf)
set(CMAKE_CXX_STANDARD 17)

# Link statico per runtime GCC
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++ -static")

# Trova le librerie SDL2
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_executable(tetris
        main.cpp
        src/game_engine.cpp
        src/easy_sdl.cpp
)

target_link_libraries(tetris
        SDL2::SDL2-static
        SDL2_image::SDL2_image-static
        SDL2_ttf::SDL2_ttf-static
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
