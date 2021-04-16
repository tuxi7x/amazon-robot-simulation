cmake_minimum_required(VERSION 3.5)

project(TestClient LANGUAGES CXX)

#[[Include the parent directory]]
include_directories(../)

find_package(QT NAMES Qt5 Qt6 COMPONENTS Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Test REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Network Core REQUIRED)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

add_executable(TestClient tst_testclient.cpp
    ../controllers/MapEditorController.cpp
    ../models/DockerFieldModel.cpp
    ../models/DropOffPointFieldModel.cpp
    ../models/ProductModel.cpp
    ../models/RobotFieldModel.cpp
    ../models/ShelfFieldModel.cpp
    )
add_test(NAME TestClient COMMAND TestClient)

target_link_libraries(TestClient PRIVATE Qt${QT_VERSION_MAJOR}::Test Qt${QT_VERSION_MAJOR}::Network)

