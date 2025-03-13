cmake_minimum_required(VERSION 3.16)
project(testApp VERSION 1.0 LANGUAGES CXX)

#set(CMAKE_AUTOMOC ON)
#set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set(QT_QML_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if (WIN32)
    # required to build on windows, but doesn't work on linux
    set(CMAKE_BUILD_TYPE Release)
endif()


find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

set(TARGET_NAME "ExampleProject")
qt_add_executable(${TARGET_NAME} example.cpp)

target_link_libraries(${TARGET_NAME} PRIVATE Qt6::Quick)


#if(IOS)
#    set(EXPORT_PATH "plugin-export_ios")
#elseif(ANDROID)
#    set(EXPORT_PATH "plugin-export_android")
#elseif(WIN32)
#    set(EXPORT_PATH "plugin-export_windows")
#else()
#    set(EXPORT_PATH "plugin-export_linux")
#endif()

#set(PLUGIN_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../${EXPORT_PATH}")
#target_compile_definitions(${TARGET_NAME} PRIVATE
#    PLUGIN_IMPORT_PATH="${PLUGIN_PATH}"
#)
#SET(QML_IMPORT_PATH "${PLUGIN_PATH}" CACHE STRING "qml modules path")


set(MY_QML_DIR ${CMAKE_SOURCE_DIR}/../qml)

qt_add_qml_module(${TARGET_NAME}
    URI ${TARGET_NAME}
    VERSION 1.0
    IMPORT_PATH ${MY_QML_DIR}
    QML_FILES Example.qml
    #NO_RESOURCE_TARGET_PATH
)


# Avoid collision between executable name and QML module directory (QTBUG-98568).
if(NOT WIN32 AND NOT APPLE)
    set_property(TARGET ${TARGET_NAME} PROPERTY OUTPUT_NAME ${TARGET_NAME}_app)
endif()


if (ANDROID)
    # CURRENT WORKAROUND TO LOAD THE LIBRARY FOR ANDROID
    add_library(TolLib SHARED IMPORTED)
    set_property(TARGET TolLib PROPERTY IMPORTED_LOCATION "${PLUGIN_PATH}/TOL/libqml_TOL_Tol_${ANDROID_ABI}.so")
    target_link_libraries(${TARGET_NAME} PRIVATE TolLib)
elseif(IOS)
    #qt_add_ios_ffmpeg_libraries(${TARGET_NAME})

    set_target_properties(${TARGET_NAME} PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER info.tol.smartIO
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
        QT_QMLCACHEGEN_ARGUMENTS "--verbose"
    )

    #target_link_libraries(${TARGET_NAME} PRIVATE "-framework UIKit")

    # link plugin library
    #target_link_directories(${TARGET_NAME} PUBLIC
    #    ${PLUGIN_PATH}/TOL
    #)
    #set(libName "Tol")
    #if(CMAKE_BUILD_TYPE STREQUAL Debug)
    #    set(libName "${libName}_debug")
    #endif()
    #set(libName "lib${libName}.a")
    #target_link_libraries(${TARGET_NAME} PRIVATE ${libName})
    target_link_libraries(${TARGET_NAME} PRIVATE ${MY_QML_DIR}/TOL/Debug/libTol.a)
endif()
