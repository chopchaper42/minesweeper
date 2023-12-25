cmake_minimum_required(VERSION 3.26)
project(minesweeper)

set(CMAKE_CXX_STANDARD 17)

add_executable(minesweeper main.cpp
        implementations/Game.cpp
        headers/Game.h
        implementations/Cell.cpp
        headers/Cell.h
        implementations/CellFactory.cpp
        headers/CellFactory.h
        headers/GameMode.h
        implementations/ArgumentParser.cpp
        headers/ArgumentParser.h
)
