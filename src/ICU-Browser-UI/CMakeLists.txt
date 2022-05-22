cmake_minimum_required(VERSION 3.19)

project(ICU-Browser-UI VERSION 0.1 LANGUAGES CXX)

add_compile_definitions(NOMINMAX)

include(../cmake/cef.cmake)
include(../cmake/shared.cmake)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 20)

find_package(bsoncxx CONFIG REQUIRED)
find_package(mongocxx CONFIG REQUIRED)
find_package(
	Qt6 6.2 COMPONENTS
	Quick Widgets QuickWidgets
	REQUIRED
)

include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR} ${SHARED_INCLUDE_PATH})

link_directories(${CMAKE_CURRENT_BINARY_DIR})

qt_add_executable(
	ICU-Browser-UI
	main.cpp
	cefwindow.h cefwindow.cpp
	resource.qrc
	${SHARED_BROWSER_SRCS}
	${SHARED_WINDOW_SRCS}
	${SHARED_DOWNLOAD_SRCS}
	${SHARED_FAVORITES_SRCS}
	${SHARED_HISTORY_SRCS}
	${SHARED_USER_SRCS}
	${SHARED_AB_BLOCK_SRCS}
	${SHARED_PROFILE_SRCS}
)

#qt_add_qml_module(apptest3
#    URI test3
#    VERSION 1.0
#    QML_FILES main.qml
#)

set_target_properties(
	ICU-Browser-UI PROPERTIES
	MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
	MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
	MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
	MACOSX_BUNDLE TRUE
	WIN32_EXECUTABLE TRUE
)

target_compile_definitions(
	ICU-Browser-UI
	PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)

COPY_FILES("${PROJECT_NAME}" "${CEF_BINARY_FILES}" "${CEF_BINARY_DIR}" "${CMAKE_CURRENT_BINARY_DIR}")
COPY_FILES("${PROJECT_NAME}" "${CEF_RESOURCE_FILES}" "${CEF_RESOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}")

target_link_libraries(
	ICU-Browser-UI
	PRIVATE
	Qt6::Quick
	Qt6::Widgets
	Qt6::QuickWidgets
	${CEF_STANDARD_LIBS}
	${CEF_LIBS}
	mongo::bsoncxx_shared
	mongo::mongocxx_shared
)


if (CMAKE_SYSTEM_NAME MATCHES "Windows")
	ADD_WINDOWS_MANIFEST("${WINDOWS_MANIFEST_DIR}" "ICU-Browser-UI" "exe")
endif ()
