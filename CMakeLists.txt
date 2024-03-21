cmake_minimum_required(VERSION 3.25)
project(Wet_2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Wet_2
        olympics24a2.cpp DynamicHashTable.cpp main24a2.cpp AVLRankTreeTeamPower.cpp AVLRankTreePower.h)
