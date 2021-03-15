cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

set(CXX_LINK_FLAGS1    "-lSDL2")
set(CXX_LINK_FLAGS1    "-lSDL2_image")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${CXX_LINK_FLAGS1} ${CXX_LINK_FLAGS2}")


project(SDL2Test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} src)

add_executable(SolarSystem src/main.cpp src/Physics.cpp src/Core.cpp src/Textures.cpp src/SolarSystem.cpp src/Vector2Elm.cpp)
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(SolarSystem ${SDL2_LIBRARIES})
target_link_libraries(SolarSystem -lSDL2_image)
