cmake_minimum_required(VERSION 3.19)
project(ad-blocker)

include(../cmake/shared.cmake)

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR} ${SHARED_INCLUDE_PATH})

link_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(
        ad-blocker
        main.cpp
        ${SHARED_AB_BLOCK_SRCS}
)