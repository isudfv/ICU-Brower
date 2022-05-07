set(SHARED_INCLUDE_PATH
        ${CMAKE_SOURCE_DIR}/src/shared/browser
        ${CMAKE_SOURCE_DIR}/src/shared/window
        ${CMAKE_SOURCE_DIR}/src/shared/download)

set(SHARED_BROWSER_SRCS
        ${CMAKE_SOURCE_DIR}/src/shared/browser/browserclient.cc
        ${CMAKE_SOURCE_DIR}/src/shared/browser/browserclient.h
        ${CMAKE_SOURCE_DIR}/src/shared/browser/clienthandler.cc
        ${CMAKE_SOURCE_DIR}/src/shared/browser/clienthandler.h)

set(SHARED_WINDOW_SRCS
        ${CMAKE_SOURCE_DIR}/src/shared/window/qbrowserwindow.cc
        ${CMAKE_SOURCE_DIR}/src/shared/window/qbrowserwindow.h)

set(SHARED_DOWNLOAD_SRCS
        ${CMAKE_SOURCE_DIR}/src/shared/download/qdownloadwidget.cpp
        ${CMAKE_SOURCE_DIR}/src/shared/download/qdownloadwidget.h
        ${CMAKE_SOURCE_DIR}/src/shared/download/qdownloadwidget.ui)

set(WINDOWS_MANIFEST_DIR
        ${CMAKE_SOURCE_DIR}/src/shared/manifest)