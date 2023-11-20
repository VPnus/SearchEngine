cmake_minimum_required(VERSION 3.5)

project(Search_engine VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Test REQUIRED)

set(PROJECT_SOURCES
        src/main.cpp
        mainwindow.cpp
        src/converter.cpp
        src/inverted_index.cpp
        src/server.cpp
        include/server.h
        include/inverted_index.h
        include/converter.h
        mainwindow.h
        mainwindow.ui
        tests/index_tests.cpp
        tests/server_tests.cpp
        resources/file001.txt
        resources/file002.txt
        resources/file003.txt
        resources/file004.txt
        config/answers.json
        config/requests.json
        config/config.json

)



include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/release-1.11.0.tar.gz
)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
FetchContent_MakeAvailable(googletest)



if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Search_engine
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Search_engine APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Search_engine SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Search_engine
            ${PROJECT_SOURCES}
        )
    endif()
endif()



TARGET_LINK_LIBRARIES(Search_engine PRIVATE gtest_main)

target_link_libraries(Search_engine PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(Search_engine PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Search_engine)
endif()
