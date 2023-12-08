cmake_minimum_required(VERSION 3.15)
project(snakesnladders C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall")
set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/sources)

add_executable(snakesnladders
        src/headers/common.h
        src/sources/utils.c src/headers/utils.h
        src/sources/tile.c src/headers/tile.h
        src/sources/board.c src/headers/board.h
        src/sources/sequence.c src/headers/sequence.h
        src/sources/state.c src/headers/state.h
        src/sources/board_utils.c src/headers/board_utils.h
        src/sources/game.c src/headers/game.h
        src/sources/menu.c src/headers/menu.h
        src/sources/main.c)

add_custom_command(TARGET snakesnladders POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${PROJECT_SOURCE_DIR}/resources/
                $<TARGET_FILE_DIR:snakesnladders>/resources/)

