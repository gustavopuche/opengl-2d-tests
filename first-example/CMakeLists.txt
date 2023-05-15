cmake_minimum_required(VERSION 3.15)
#SET (CMAKE_CXX_COMPILER "/usr/bin/clang++" CACHE STRING "C++ compiler" FORCE)
project( first )
# Enable C++17
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# find_package(Threads REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
add_executable( first first.cpp )
# target_link_libraries(first Threads::Threads)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(first ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
add_custom_target(run)
add_custom_command( TARGET run
	POST_BUILD COMMAND ./first)
