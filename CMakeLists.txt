cmake_minimum_required(VERSION 3.17)
project(PacManFP)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

# Find all executables
file(GLOB project_SRCS src/*.cpp)

add_executable(PacManFP ${project_SRCS} src/Machine.cpp src/Machine.h src/Game.cpp src/Game.h)
target_link_libraries(PacManFP ${SDL2_LIBRARIES} )