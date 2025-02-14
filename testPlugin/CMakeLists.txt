cmake_minimum_required(VERSION 3.16)
project(testPlugin VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(QT_QML_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(QT_QML_GENERATE_QMLLS_INI ON)

if (WIN32)
    # required to build on windows, but doesn't work on linux
    set(CMAKE_BUILD_TYPE Release)
endif()


find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Quick)


qt_standard_project_setup(REQUIRES 6.8)


set(LIBRARY_NAME "test-plugin")
set(TARGET_NAME "Tol")
set(PLUGIN_URI "TOL")

qt_add_library(${TARGET_NAME} SHARED)

qt_add_qml_module(${TARGET_NAME}
    URI ${PLUGIN_URI}
    PLUGIN_TARGET ${LIBRARY_NAME}
    CLASS_NAME MyItem
    SOURCES myitem.cpp myitem.h testimageprovider.h testimageprovider.cpp
    RESOURCE_PREFIX /
    NO_PLUGIN_OPTIONAL
    NO_GENERATE_PLUGIN_SOURCE
    SOURCES testelement.h testelement.cpp
)

target_link_libraries(${TARGET_NAME} PRIVATE Qt6::Quick)


if (IOS)
    set(EXPORT_PATH "plugin-export_ios")
elseif(ANDROID)
    set(EXPORT_PATH "plugin-export_android")
elseif(WIN32)
    set(EXPORT_PATH "plugin-export_windows")
else()
    set(EXPORT_PATH "plugin-export_linux")
endif()


# COPY THE BUILD OUTPUT TO A SHARED FOLDER SO IT CAN BE LOADED BY THE APP

set(OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../${EXPORT_PATH}/${PLUGIN_URI}")
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_DIR})

if (ANDROID)
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
      COMMAND "${CMAKE_COMMAND}" -E copy
         "$<TARGET_FILE:${TARGET_NAME}>"
         "${OUTPUT_DIR}"
      COMMENT "Copying library to output directory")
else()
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
      COMMAND "${CMAKE_COMMAND}" -E copy
         "$<TARGET_FILE:${TARGET_NAME}>"
         "${OUTPUT_DIR}/$<TARGET_FILE_PREFIX:${TARGET_NAME}>${LIBRARY_NAME}$<TARGET_FILE_SUFFIX:${TARGET_NAME}>"
      COMMENT "Copying library to output directory")
endif()

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
  COMMAND "${CMAKE_COMMAND}" -E copy
     "${CMAKE_CURRENT_BINARY_DIR}/${PLUGIN_URI}/qmldir"
     "${CMAKE_CURRENT_BINARY_DIR}/${PLUGIN_URI}/${TARGET_NAME}.qmltypes"
     "${OUTPUT_DIR}"
  COMMENT "Copying qml helper files to output directory")
