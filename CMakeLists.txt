cmake_minimum_required (VERSION 3.0)
project (FETE)

add_definitions(-std=c++11)
#设置工程类型
set(CMAKE_BUILD_TYPE Debug)
#SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
#set(CMAKE_BUILD_TYPE Release)

#添加自定义宏
if(CMAKE_BUILD_TYPE STREQUAL Debug)
    add_definitions(-DDEBUG)
endif()
add_definitions(-DBOOST_ALL_DYN_LINK)


#设置第三方库根目录
set(INCLUDE_DIR "./include")
set(LIB_DIR "./lib")

#设置第三方库
#libconfig
set(LIBCONFIG_MODULE_INCLUDE "${INCLUDE_DIR}/libconfig")
file(GLOB_RECURSE LIBCONFIG_MODULE_LIB "${LIB_DIR}/libconfig/*.so")

#boost
set(BOOST_MODULE_INCLUDE "/usr/include")

#python
set(PYTHON_MODULE_INCLUDE "/usr/include/python2.7")
#set(LIBPYTHON_MODULE_LIB "~/APP/anaconda3/lib")

set(XGBOOST_MODULE_INCLUDE "${INCLUDE_DIR}/xgboost")
file(GLOB_RECURSE XGBOOST_MODULE_LIB "{LIB_DIR}/xgboost/*.so")
file(GLOB_RECURSE RABIT_MODULE_LIB "{LIB_DIR}/xgboost/librabit.a")
file(GLOB_RECURSE DMLC_MODULE_LIB "{LIB_DIR}/xgboost/libdmlc.a")


#查找库
find_package(Boost REQUIRED COMPONENTS
        system
		filesystem
        log
        log_setup
        thread)

if(Boost_FOUND)
    set(BOOST_MODULE_INCLUDE ${Boost_MODULE_DIR})
endif()

#设置头文件查找路径
include_directories(
    ${LIBCONFIG_MODULE_INCLUDE}
    ${BOOST_MODULE_INCLUDE}
    ${PYTHON_MODULE_INCLUDE}
    ${XGBOOST_MODULE_INCLUDE}
)

link_directories(
    #    ${LIBPYTHON_MODULE_LIB}
)

#设置编译选项
set(CMAKE_C_FLAGS_DEBUG "-g -Wall -o0")
set(CMAKe_C_FLAGS_RELEASE "-g -Wall -02")

#添加编译子目录
aux_source_directory(./src/core SRC_CORE)
aux_source_directory(./src/utils SRC_UTILS)
aux_source_directory(./src/model SRC_MODEL)

#设置编译文件
set(SRC_LIST
    ${SRC_CORE}
    ${SRC_MODEL}
    src/main.cpp
    )

#添加编译子项目
add_subdirectory(./src/utils)
add_subdirectorY(./test)

#生成可执行文件
add_executable(fete ${SRC_LIST})

#链接第三方库
target_link_libraries(fete
    ${LIBCONFIG_MODULE_LIB}
    ${XGBOOST_MODULE_LIB}
    ${RABIT_MODULE_LIB}
    ${DMLC_MODULE_LIB}
    stdc++
    boost_system
    boost_log
    boost_log_setup
    boost_thread
	boost_filesystem
    pthread
    tinyxml2
    python2.7
)
