cmake_minimum_required(VERSION 2.6)
project(genom-2 CXX C)                                                   
set(CMAKE_CXX_FLAGS "-W -Wall -pedantic -std=c++11")
add_executable(PopulationSimul src/genome.cpp src/population.cpp src/individual.cpp)
target_link_libraries(PopulationSimul m)

#To execute CMake: 
#- change "My_first_project" with the project's name
#- change "PopulationSimul" with the program you wan't to compile with CMake 
#- change "src/genome.cpp .... with all the files Cmake will need to compile your program
