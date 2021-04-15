cmake_minimum_required(VERSION 3.13)

project(Client LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Network Core REQUIRED)
enable_testing()
add_subdirectory(tests/)

include_directories(${Qt6Core_INCLUDE_DIRS})

set(PROJECT_SOURCES
    ${CMAKE_PROJECT_DIR}/main.cpp
    ${CMAKE_PROJECT_DIR}/views/ApplicationMenu.cpp
    ${CMAKE_PROJECT_DIR}/views/ApplicationMenu.h
    ${CMAKE_PROJECT_DIR}/library/buttons/MainMenuButton.cpp
    ${CMAKE_PROJECT_DIR}/library/buttons/MainMenuButton.h
    ${CMAKE_PROJECT_DIR}/library/dialogs/DialogBase.cpp
    ${CMAKE_PROJECT_DIR}/library/dialogs/DialogBase.h
    ${CMAKE_PROJECT_DIR}/library/dialogs/HelpDialog.cpp
    ${CMAKE_PROJECT_DIR}/library/dialogs/HelpDialog.h
    ${CMAKE_PROJECT_DIR}/library/dialogs/ConnectDialog.cpp
    ${CMAKE_PROJECT_DIR}/library/dialogs/ConnectDialog.h
    ${CMAKE_PROJECT_DIR}/library/dialogs/ErrorDialog.cpp
    ${CMAKE_PROJECT_DIR}/library/dialogs/ErrorDialog.h
    ${CMAKE_PROJECT_DIR}/library/dialogs/StartSimFromFileDialog.cpp
    ${CMAKE_PROJECT_DIR}/library/dialogs/StartSimFromFileDialog.h
    ${CMAKE_PROJECT_DIR}/views/MapEditor.cpp
    ${CMAKE_PROJECT_DIR}/views/MapEditor.h
    ${CMAKE_PROJECT_DIR}/controllers/MapEditorController.cpp
    ${CMAKE_PROJECT_DIR}/controllers/MapEditorController.h
    ${CMAKE_PROJECT_DIR}/library/buttons/editor/EditorGridButton.cpp
    ${CMAKE_PROJECT_DIR}/library/buttons/editor/EditorGridButton.h
    ${CMAKE_PROJECT_DIR}/library/buttons/editor/SideBarButton.cpp
    ${CMAKE_PROJECT_DIR}/library/buttons/editor/SideBarButton.h
    ${CMAKE_PROJECT_DIR}/models/RobotFieldModel.h
    ${CMAKE_PROJECT_DIR}/models/RobotFieldModel.cpp
    ${CMAKE_PROJECT_DIR}/models/DockerFieldModel.cpp
    ${CMAKE_PROJECT_DIR}/models/DockerFieldModel.h
    ${CMAKE_PROJECT_DIR}/models/ShelfFieldModel.cpp
    ${CMAKE_PROJECT_DIR}/models/ShelfFieldModel.h
    ${CMAKE_PROJECT_DIR}/models/DropOffPointFieldModel.cpp
    ${CMAKE_PROJECT_DIR}/models/DropOffPointFieldModel.h
    ${CMAKE_PROJECT_DIR}/models/ProductModel.cpp
    ${CMAKE_PROJECT_DIR}/models/ProductModel.h
    ${CMAKE_PROJECT_DIR}/library/dialogs/ProductsOnShelfDialog.cpp
    ${CMAKE_PROJECT_DIR}/library/dialogs/ProductsOnShelfDialog.h
    ${CMAKE_PROJECT_DIR}/ViewWrapper.cpp
    ${CMAKE_PROJECT_DIR}/ViewWrapper.h
    ${CMAKE_PROJECT_DIR}/library/dialogs/OrderDialog.h
    ${CMAKE_PROJECT_DIR}/library/dialogs/OrderDialog.cpp
    ${CMAKE_PROJECT_DIR}/views/SimulationWindow.cpp
    ${CMAKE_PROJECT_DIR}/views/SimulationWindow.h
    ${CMAKE_PROJECT_DIR}/controllers/Connection.cpp
    ${CMAKE_PROJECT_DIR}/controllers/Connection.h
    ${CMAKE_PROJECT_DIR}/library/buttons/SimulationButton.cpp
    ${CMAKE_PROJECT_DIR}/library/buttons/SimulationButton.h
    ${CMAKE_PROJECT_DIR}/library/dialogs/RobotInfoDialog.cpp
    ${CMAKE_PROJECT_DIR}/library/dialogs/RobotInfoDialog.h
)



if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Client
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(Client SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Client
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Client PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)
