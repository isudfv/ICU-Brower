cmake_minimum_required(VERSION 3.19)
project(qbrowserclient)

include(../cmake/cef.cmake)
include(../cmake/shared.cmake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(
        Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Quick
        REQUIRED
)

include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR} ${SHARED_INCLUDE_PATH})

link_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(
        qbrowserclient
        main.cpp
        ${SHARED_BROWSER_SRCS}
        ${SHARED_WINDOW_SRCS}
        ${SHARED_DOWNLOAD_SRCS}
)

COPY_FILES("${PROJECT_NAME}" "${CEF_BINARY_FILES}" "${CEF_BINARY_DIR}" "${CMAKE_CURRENT_BINARY_DIR}")
COPY_FILES("${PROJECT_NAME}" "${CEF_RESOURCE_FILES}" "${CEF_RESOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}")

target_link_libraries(
        qbrowserclient PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Quick
        ${CEF_STANDARD_LIBS}
        ${CEF_LIBS}
)

if (CMAKE_SYSTEM_NAME MATCHES "Windows")
    ADD_WINDOWS_MANIFEST("${WINDOWS_MANIFEST_DIR}" "qbrowserclient" "exe")
endif ()