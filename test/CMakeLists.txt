cmake_minimum_required(VERSION 3.0) 
project(simpleLogger)

add_definitions(-std=c++11)


find_package(Boost 1.58 COMPONENTS log log_setup system thread REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

add_executable(sample sample.cpp)
target_link_libraries(sample 
	boost_system
	boost_filesystem)
