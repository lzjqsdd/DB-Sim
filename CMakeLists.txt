cmake_minimum_required (VERSION 2.6)
project (FETE)

set(SRC_ROOT src)
set(SRC_LIST 
    ${SRC_ROOT}/utils/tinyxml2.cpp
    ${SRC_ROOT}/main.cpp
    )

#设置编译选项
set(CMAKE_C_FLAGS_DEBUG "-g -Wall")

#生成可执行文件
add_executable(fete ${SRC_LIST})
