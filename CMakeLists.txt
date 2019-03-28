cmake_minimum_required( VERSION 2.8 )
project( YoloTest )

# Build type
IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Release)
ENDIF()
MESSAGE("Build type: " ${CMAKE_BUILD_TYPE})

# 设置 opencv 的路径
set(OpenCV_DIR /home/wu/soft/opencv-3.2.0/build/installed/share/OpenCV) 

# 编译选项为 -Wall O3 的优化
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -Wall  -O3 -march=native ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall   -O3 -march=native")

# 添加c++ 11标准支持
set( CMAKE_CXX_FLAGS "-std=c++11" )
# Check C++11 or C++0x support
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    add_definitions(-DCOMPILEDWITHC11)
    message(STATUS "Using flag -std=c++11.")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
    add_definitions(-DCOMPILEDWITHC0X)
    message(STATUS "Using flag -std=c++0x.")
else()
    message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

# 查找 CUDA
include(FindCUDA)
LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)
LIST(APPEND CUDA_NVCC_FLAGS --compiler-options -fno-strict-aliasing -lineinfo -use_fast_math -Xptxas -dlcm=cg)
LIST(APPEND CUDA_NVCC_FLAGS -gencode arch=compute_50,code=sm_50)

# 寻找 CUDA
find_package(CUDA 8.0 REQUIRED)
# 寻找OpenCV库
find_package(OpenCV 3.2.0 EXACT REQUIRED)
message(STATUS "    version: ${OpenCV_VERSION}")

# darknet 路径.
set(DARKNET_PATH ${PROJECT_SOURCE_DIR}/darknet)
add_definitions(-DDARKNET_FILE_PATH="${DARKNET_PATH}")

# 添加头文件
include_directories( ${OpenCV_INCLUDE_DIRS}
                     ${PROJECT_SOURCE_DIR}
                     ${PROJECT_SOURCE_DIR}/include
                     ${DARKNET_PATH}/src
                     /usr/local/cuda/include)

# CUDA
set(CUDA_INCLUDE_DIR /usr/local/cuda/include)
set(CUDNN_LIBRARY_DIR /usr/local/cuda-8.0/targets/x86_64-linux/lib)

# 生成共享库.
# add_library(${PROJECT_NAME} SHARED
#             include/YOLOv3SE.h)

add_library(cuda INTERFACE)
set_target_properties(cuda PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ${CUDA_INCLUDE_DIRS}
        INTERFACE_LINK_LIBRARIES "${CUDA_LIBRARIES};${CUDA_curand_LIBRARY};${CUDA_CUFFT_LIBRARIES};${CUDA_CUBLAS_LIBRARIES}"
        )

add_executable( YoloTest main.cpp )
# 链接OpenCV库
target_link_libraries( YoloTest ${OpenCV_LIBS} )
target_link_libraries(  ${PROJECT_NAME}
                        ${PROJECT_SOURCE_DIR}/darknet/build/libYOLOv3SE.so
                        /usr/local/cuda-8.0/lib64/libcudnn.so
                        cuda
                        )