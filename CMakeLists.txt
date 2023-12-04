cmake_minimum_required(VERSION 3.16)
project(cli_minesweeper VERSION 0.0.0)

add_executable(cli_minesweeper
    "src/main.c"
    "src/board.c"
    "src/game.c"
    "src/draw.c"
)

include_directories(cli_minesweeper ./include)