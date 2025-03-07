cmake_minimum_required(VERSION 3.16)
project(testApp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(QT_QML_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

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

qt_add_qml_module(${TARGET_NAME}
    URI ${TARGET_NAME}
    VERSION 1.0
    QML_FILES example.qml
    NO_RESOURCE_TARGET_PATH
)

if (IOS)
    set(EXPORT_PATH "plugin-export_ios")
elseif(ANDROID)
    set(EXPORT_PATH "plugin-export_android")
elseif(WIN32)
    set(EXPORT_PATH "plugin-export_windows")
else()
    set(EXPORT_PATH "plugin-export_linux")
endif()

set(PLUGIN_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../${EXPORT_PATH}")
target_compile_definitions(${TARGET_NAME} PRIVATE
    PLUGIN_IMPORT_PATH="${PLUGIN_PATH}"
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
endif()
