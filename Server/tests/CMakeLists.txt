cmake_minimum_required(VERSION 3.5)

project(ServerTest LANGUAGES CXX)

find_package(QT NAMES Qt5 Qt6 COMPONENTS Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Test REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

add_executable(ServerTest tst_servertest.cpp)


set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )

set(PROJECT_SOURCES
    ../Controller.h
    ../Controller.cpp
)

add_test(NAME ServerTest COMMAND ServerTest)
add_custom_command(TARGET ServerTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:ServerTest> ${PROJECT_BINARY_DIR}/ServerTest.exe
    COMMENT "Created ${PROJECT_BINARY_DIR}/ServerTest.exe"
)

target_link_libraries(ServerTest PRIVATE Qt${QT_VERSION_MAJOR}::Test)

