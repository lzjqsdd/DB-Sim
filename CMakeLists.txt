cmake_minimum_required (VERSION 2.6)
project (FETE)

set(ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../)

#set(CMAKE_CXX_FLAGS "-g -std=c++1 -W -Wall -fPIC")

#aux_source_directory(${ROOT}/src DIR_SRCS)
aux_source_directory(. DIR_SRCS)

#add_executable(FETE ${DIR_SRCS})
add_executable(FETE ${ROOT}/src/main.cpp)
