cmake_minimum_required(VERSION 2.6)

project(genom-2 CXX C)

option(test "Build tests." OFF) #declares a boolean that tells that we are doing a test version.
option(Qt "Building Graphic Interface." OFF)

set(CMAKE_BUILD_TYPE Debug) #Allows to debug
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -pedantic -std=c++11")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(src)
link_directories("/usr/local/lib") #Tells cmake where some libs could potentially be located
link_directories("/usr/lib")
add_executable(Main src/main.cpp src/Matrix.cpp src/Sequence.cpp src/utility.cpp src/user_interaction.cpp src/procedures.cpp)
#target_link_libraries(PopulationSimul m)

if (test)
	enable_testing()
	find_package(GTest REQUIRED)
	include_directories(${GTEST_INCLUDE_DIRS})
	add_executable(gtests test/gTest.cpp src/Matrix.cpp)
	target_link_libraries(gtests ${GTEST_BOTH_LIBRARIES} pthread) 
	add_test(genom-2 MainTest)
endif (test)

if (Qt)
	set(CMAKE_AUTOMOC ON)
	set(CMAKE_AUTOOUIC ON)
	execute_process(COMMAND bash ../qt.sh )
	find_package(Qt4 REQUIRED)
	include_directories(src /usr/include/qt4/Qt)
	link_directories("/usr/local/lib" "/usr/lib") #Tells cmake where some libs could potentially be located
	add_executable(MainQt src/askbaseprobability.cpp src/askdouble.cpp src/askposandlength.cpp src/mainQt.cpp src/Matrix.cpp src/resultswindow.cpp src/savematrix.cpp src/savesequence.cpp src/Sequence.cpp src/user_interactionQt.cpp src/utility.cpp src/window.cpp)
	target_link_libraries(MainQt Qt4::QtGui)
endif (Qt)

find_package(Doxygen)
if(DOXYGEN_FOUND)
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
	add_custom_target(doc ALL ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	COMMENT "Generating API documentation with Doxygen" VERBATIM
)
endif(DOXYGEN_FOUND)



#To execute CMake: 
#- change "My_first_project" with the project's name
#- change "PopulationSimul" with the program you wan't to compile with CMake 
#- change "src/genome.cpp .... with all the files Cmake will need to compile your program
