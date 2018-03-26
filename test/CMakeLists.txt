cmake_minimum_required(VERSION 3.0)
project(simpleLogger)


SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
option(USE_SHARED FALSE)
add_definitions(-std=c++11)


find_package(Boost REQUIRED COMPONENTS log log_setup system thread REQUIRED)
find_package(OpenMP)
if(OpenMP_CXX_FOUND OR OPENMP_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()


set(INCLUDE_DIR "../include")
set(LIB_DIR "../lib")

set(XGBOOST_MODULE_INCLUDE "${INCLUDE_DIR}/xgboost")
set(XGBOOST_MODULE_LIB "${LIB_DIR}/xgboost")
file(GLOB_RECURSE XGBOOST_MODULE_STATIC_LIB "${LIB_DIR}/xgboost/libxgboost.a")
file(GLOB_RECURSE DMLC_MODULE_STATIC_LIB "${LIB_DIR}/xgboost/libdmlc.a")
file(GLOB_RECURSE RABIT_MODULE_STATIC_LIB "${LIB_DIR}/xgboost/librabit.a")

set(LIBSVM_MODULE_LIB "${LIB_DIR}/libsvm")

include_directories(
    ${Boost_INCLUDE_DIR}
    ${PYTHON_MODULE_INCLUDE}
    ${XGBOOST_MODULE_INCLUDE}
    )

link_directories(
    ${Boost_LIBRARY_DIRS}
    ${XGBOOST_MODULE_LIB}
    ${LIBSVM_MODULE_LIB}
)

#build boost sample
add_executable(sample sample.cpp)
target_link_libraries(sample
	boost_system
	boost_filesystem)


#build xgboost test
add_executable(test_xgboost xgboost_test.cpp)

if(USE_SHARED)
    message(STATUS "use shared lib for xgboost")
    target_link_libraries(test_xgboost
        xgboost
        pthread
    )
else()
    message(STATUS "use static lib for xgboost")
    target_link_libraries(test_xgboost
        ${XGBOOST_MODULE_STATIC_LIB}
        ${DMLC_MODULE_STATIC_LIB}
        ${RABIT_MODULE_STATIC_LIB}
        pthread
    )
endif()


#build libsvm test
add_executable(svm_train svm_train.cpp)
target_link_libraries(svm_train
    svm
)


#build log test
add_executable(log log.cpp)
target_link_libraries(log
    boost_system
    boost_log
    boost_log_setup
    boost_thread
)

#build log test2
add_executable(log2 log2.cpp)
target_link_libraries(log2
    boost_system
    boost_log
    boost_log_setup
    boost_thread
)

