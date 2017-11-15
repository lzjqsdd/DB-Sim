cmake_minimum_required(VERSION 3.0) 
project(simpleLogger)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)

find_package(Boost 1.58 COMPONENTS log log_setup system thread REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

message(status "** Boost Include: ${Boost_INCLUDE_DIR}")
message(status "** Boost Libraries: ${Boost_LIBRARY_DIRS}")
message(status "** Boost Libraries: ${Boost_LIBRARIES}")

#add_library(simpleLogger simpleLogger.cpp)
#target_link_libraries(simpleLogger ${Boost_LIBRARIES} pthread)

add_library(tinyxml2 SHARED tinyxml2.cpp)
target_link_libraries(tinyxml2 stdc++)
