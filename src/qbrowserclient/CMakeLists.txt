cmake_minimum_required(VERSION 3.19)
project(qbrowserclient)

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

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
	set(
		LINK_LIBRARY
		X11
		libEGL.so
		libGLESv2.so
		libvk_swiftshader.so
		libvulkan.so.1
		libcef.so
		${CMAKE_SOURCE_DIR}/libs/cef/libcef_dll_wrapper.a
		)
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
	set(
		LINK_LIBRARY
		comctl32.lib
		gdi32.lib
		rpcrt4.lib
		shlwapi.lib
		ws2_32.lib
		${CMAKE_SOURCE_DIR}/libs/cef/libcef_dll_wrapper.lib
		)
endif ()

include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR})

link_directories($<$<CONFIG:DEBUG>:${CMAKE_SOURCE_DIR}/libs/cef/Debug>)
link_directories($<$<CONFIG:RELEASE>:${CMAKE_SOURCE_DIR}/libs/cef/Release>)

add_executable(
	qbrowserclient
	main.cpp
	clienthandler.cc clienthandler.h
	qbrowserwindow.cc qbrowserwindow.h
	browserclient.cc browserclient.h
	qdownloadwidget.cpp qdownloadwidget.h qdownloadwidget.ui
)


target_link_libraries(
	qbrowserclient PUBLIC
	Qt::Core
	Qt::Gui
	Qt::Widgets
	Qt::Quick
	${LINK_LIBRARY}
)

if (CMAKE_SYSTEM_NAME MATCHES "Windows")
	# Add custom manifest files to an executable target.
	macro(ADD_WINDOWS_MANIFEST manifest_path target extension)
		add_custom_command(
			TARGET ${target}
			POST_BUILD
			COMMAND "mt.exe" -nologo
			-manifest \"${manifest_path}/${target}.${extension}.manifest\" \"${manifest_path}/compatibility.manifest\"
			-outputresource:"${CMAKE_BINARY_DIR}/${target}.${extension}"\;\#1
			COMMENT "Adding manifest..."
		)
	endmacro()
	ADD_WINDOWS_MANIFEST("${CMAKE_CURRENT_SOURCE_DIR}" "qbrowserclient" "exe")
endif ()