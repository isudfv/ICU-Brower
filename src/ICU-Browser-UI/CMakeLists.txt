cmake_minimum_required(VERSION 3.16)

project(ICU-Browser-UI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS
    Quick Widgets QuickWidgets
    REQUIRED)

qt_add_executable(ICU-Browser-UI
    main.cpp
    cefwindow.h cefwindow.cpp
    resource.qrc
)

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
)
