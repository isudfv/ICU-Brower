cmake_minimum_required(VERSION 3.16)

project(movie VERSION 1.0.0 LANGUAGES CXX)

#set(CMAKE_PREFIX_PATH "C:/Qt/6.2.4/mingw_64/lib/cmake")
#set(CMAKE_PREFIX_PATH "C:/Qt/6.2.4/msvc2019_64/lib/cmake")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBAV REQUIRED IMPORTED_TARGET
        libavdevice
        libavfilter
        libavformat
        libavcodec
        libswresample
        libswscale
        libavutil)

include_directories(include)

add_executable(test
        src/test.cpp
        src/displaywidget.cpp
        src/displaywidget.ui)

target_link_libraries(test PRIVATE Qt6::Widgets PkgConfig::LIBAV)
