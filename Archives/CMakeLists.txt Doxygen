cmake_minimum_required(VERSION 2.6)
project(SequenceTest CXX C)                                                   
set(CMAKE_CXX_FLAGS "-W -Wall -pedantic -std=c++11")

find_package(Doxygen)
if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
add_custom_target(doc
${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
COMMENT "Generating API documentation with Doxygen" VERBATIM
)
endif(DOXYGEN_FOUND)

add_executable(SequenceTest src/Sequence.cpp src/Sequence.hpp test/SequenceTest.cpp)
#target_link_libraries(PopulationSimul m)

#To execute CMake: 
#- change "My_first_project" with the project's name
#- change "PopulationSimul" with the program you wan't to compile with CMake 
#- change "src/genome.cpp .... with all the files Cmake will need to compile your program
