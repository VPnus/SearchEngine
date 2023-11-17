cmake_minimum_required(VERSION 3.5)

project(Search_engine VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(gtest_disable_pthreads on)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Test REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        converter.cpp
        inverted_index.cpp
        server.cpp
        server.h
        inverted_index.h
        converter.h
        mainwindow.h
        mainwindow.ui

)

include(FetchContent)
    FetchContent_Declare(
    googletest
    URL
    https://github.com/google/googletest/archive/609281088cfefc76f9d0ce8
    2e1ff6c30cc3591e5.zip
)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
FetchContent_MakeAvailable(googletest)
enable_testing()

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



target_link_libraries(Search_engine PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Test)

set_target_properties(Search_engine PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Search_engine)
endif()
