cmake_minimum_required(VERSION 3.19)

project(ICU-Browser-UI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QT_PATH /home/liang/Qt/6.2.4/gcc_64)

set(CMAKE_PREFIX_PATH ${QT_PATH})

find_package(Qt6 6.2 COMPONENTS
    Quick Widgets QuickWidgets
    REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/../qbrowserclient ${PROJECT_SOURCE_DIR}/../qbrowserclient/include)

link_directories(${PROJECT_BINARY_DIR})

qt_add_executable(ICU-Browser-UI
    main.cpp
    cefwindow.h cefwindow.cpp
    resource.qrc
    ${PROJECT_SOURCE_DIR}/../qbrowserclient/qbrowserwindow.h
    ${PROJECT_SOURCE_DIR}/../qbrowserclient/qbrowserwindow.cc
        ${PROJECT_SOURCE_DIR}/../qbrowserclient/qdownloadwidget.h
        ${PROJECT_SOURCE_DIR}/../qbrowserclient/qdownloadwidget.ui
        ${PROJECT_SOURCE_DIR}/../qbrowserclient/qdownloadwidget.cpp

        ${PROJECT_SOURCE_DIR}/../qbrowserclient/clienthandler.cc
        ${PROJECT_SOURCE_DIR}/../qbrowserclient/clienthandler.h


        ${PROJECT_SOURCE_DIR}/../qbrowserclient/browserclient.cc
        ${PROJECT_SOURCE_DIR}/../qbrowserclient/browserclient.h
        )

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(LINK_LIBRARY
            X11
            libcef_dll_wrapper.a
            libcef.so
            libEGL.so
            libGLESv2.so
            libvk_swiftshader.so
            libvulkan.so.1)
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(LINK_LIBRARY
            comctl32.lib
            gdi32.lib
            rpcrt4.lib
            shlwapi.lib
            ws2_32.lib
            libcef_dll_wrapper.lib
            libcef.lib)
endif()

#qt_add_qml_module(apptest3
#    URI test3
#    VERSION 1.0
#    QML_FILES main.qml
#)

set_target_properties(ICU-Browser-UI PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(ICU-Browser-UI
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(ICU-Browser-UI
    PRIVATE Qt6::Quick
    Qt6::Widgets
    Qt6::QuickWidgets
    ${LINK_LIBRARY}
)
