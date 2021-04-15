cmake_minimum_required(VERSION 3.5)

project(ServerTest LANGUAGES CXX)

#[[Include the parent directory]]
include_directories(../)

find_package(QT NAMES Qt5 Qt6 COMPONENTS Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Test REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


enable_testing()

#[[ Add all relevant .cpp files here ]]
add_executable(ServerTest tst_servertest.cpp
    ../Controller.cpp
    ../models/Docker.cpp
    ../models/DropOffPoint.cpp
    ../models/PathNode.cpp
    ../models/Product.cpp
    ../models/Robot.cpp
    ../models/Shelf.cpp
    )



add_test(NAME ServerTest COMMAND ServerTest)

target_link_libraries(ServerTest PRIVATE Qt${QT_VERSION_MAJOR}::Test)

