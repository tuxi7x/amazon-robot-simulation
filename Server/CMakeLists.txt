cmake_minimum_required(VERSION 3.13)

project(Server LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Network Core REQUIRED)
enable_testing()
add_subdirectory(tests/)

include_directories(${Qt6Core_INCLUDE_DIRS})



set(PROJECT_SOURCES
    server.cpp
    server.h
    main.cpp
    EventManager.cpp
    EventManager.h
    Controller.cpp
    Controller.h
    models/Robot.cpp
    models/Robot.h
    models/Shelf.cpp
    models/Shelf.h
    models/DropOffPoint.cpp
    models/DropOffPoint.h
    models/Docker.cpp
    models/Docker.h
    models/Product.cpp
    models/Product.h
    models/PathNode.cpp
    models/PathNode.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Server
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(Server SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Server
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Server PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network)

