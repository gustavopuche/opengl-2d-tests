cmake_minimum_required(VERSION 3.15)
#SET (CMAKE_CXX_COMPILER "/usr/bin/clang++" CACHE STRING "C++ compiler" FORCE)
project( game )
# Enable C++17
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
file(GLOB SRC
     "*.h"
     "*.cpp"
)

# find_package(Threads REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
add_executable( game ${SRC} )
set (CMAKE_CXX_FLAGS "-g")
# target_link_libraries(game Threads::Threads)
# include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
target_include_directories (game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES})
target_link_libraries(game ${OPENGL_LIBRARIES} ${GLUT_glut_LIBRARY} )
add_custom_target(run)
add_custom_command( TARGET run
	POST_BUILD COMMAND ./game)
