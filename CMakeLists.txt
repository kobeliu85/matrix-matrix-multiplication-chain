cmake_minimum_required(VERSION 3.24)
project(test_mmmc)

set(CMAKE_CXX_STANDARD 17)

set(MKL_INCLUDE_DIRS "/media/HDD/oneapi/mkl/latest/include/")
set(MKL_LIBRARIES "/media/HDD/oneapi/mkl/latest/lib/intel64/")
include_directories(${MKL_INCLUDE_DIRS})
link_directories(${MKL_LIBRARIES})

add_executable(test_mmmc test_mmc1.cpp)
target_link_libraries(test_mmmc
        mkl_intel_lp64
        mkl_gnu_thread
        mkl_core
        gomp
        pthread
        m
        dl)

add_executable(test_mmmc2 test_mmc2.cpp)
target_link_libraries(test_mmmc2
        mkl_intel_lp64
        mkl_gnu_thread
        mkl_core
        gomp
        pthread
        m
        dl)