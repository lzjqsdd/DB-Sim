cmake_minimum_required (VERSION 2.6)
project (FETE)

set(SRC_LIST src/main.cpp)

#生成可执行文件
add_executable(fete ${SRC_LIST})
