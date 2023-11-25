cmake_minimum_required(VERSION 3.16)
project(SCHOTTEN_TOTTEN)

set(CMAKE_CXX_STANDARD 14)

add_executable(SCHOTTEN_TOTTEN main.cpp Carte.cpp Carte.h Chateau.cpp Chateau.h Player.cpp Player.h Judge.cpp Judge.h)