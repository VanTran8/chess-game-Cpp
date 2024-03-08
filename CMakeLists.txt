cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


project(chess_game)

include_directories(include)

add_executable(chess_game  source/board.cpp  source/main.cpp source/pieces.cpp source/position_history.cpp)
