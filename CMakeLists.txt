cmake_minimum_required (VERSION 2.6)
project (FETE)

#设置工程类型
set(CMAKE_BUILD_TYPE Debug)

#添加自定义宏
if(CMAKE_BUILD_TYPE STREQUAL Debug)
    add_definitions(-D_DEBUG)
endif()

#设置第三方库
#set(LIB_CONFIG_MODULE "/usr/local/libconfig/lib/libconfig++.so")
set(CONFIG_MODULE_INCLUDE "/usr/local/libconfig/include")
file(GLOB_RECURSE LIBCONFIG_MODULE_LIB "/usr/local/libconfig/lib/*.so")

set(BOOST_MODULE_INCLUDE "/usr/include/boost")

#设置头文件查找路径
include_directories(
#    "/usr/local/libconfig/include"
    ${CONFIG_MODULE_INCLUDE}
    "/usr/inclde/boost"
)


#设置编译选项
set(CMAKE_C_FLAGS_DEBUG "-std=c++11 -g -Wall -o0")
set(CMAKe_C_FLAGS_RELEASE "-std=c++11 -g -Wall -02")

#添加编译子目录
aux_source_directory(./src/core SRC_CORE)
aux_source_directory(./src/utils SRC_UTILS)

#设置编译文件
set(SRC_LIST 
    ${SRC_CORE}
    ${SRC_UTILS}
    src/main.cpp
    )

#生成可执行文件
add_executable(fete ${SRC_LIST})

#链接第三方库
target_link_libraries(fete
    ${LIBCONFIG_MODULE_LIB}
    boost_system
    stdc++
)
