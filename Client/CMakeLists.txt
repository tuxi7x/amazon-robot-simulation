cmake_minimum_required(VERSION 3.5)

project(Client LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Network Core REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        views/ApplicationMenu.cpp
        views/ApplicationMenu.h
	library/buttons/MainMenuButton.cpp
        library/buttons/MainMenuButton.h
        library/dialogs/DialogBase.cpp
        library/dialogs/DialogBase.h
        library/dialogs/HelpDialog.cpp
        library/dialogs/HelpDialog.h
        library/dialogs/ConnectDialog.cpp
        library/dialogs/ConnectDialog.h
        library/dialogs/ErrorDialog.cpp
        library/dialogs/ErrorDialog.h
        library/dialogs/StartSimFromFileDialog.cpp
        library/dialogs/StartSimFromFileDialog.h
        views/MapEditor.cpp
        views/MapEditor.h
        controllers/MapEditorController.cpp
        controllers/MapEditorController.h
        library/buttons/editor/EditorGridButton.cpp
        library/buttons/editor/EditorGridButton.h
        library/buttons/editor/SideBarButton.cpp
        library/buttons/editor/SideBarButton.h
        models/RobotFieldModel.h
        models/RobotFieldModel.cpp
        models/DockerFieldModel.cpp
        models/DockerFieldModel.h
        models/ShelfFieldModel.cpp
        models/ShelfFieldModel.h
        models/DropOffPointFieldModel.cpp
        models/DropOffPointFieldModel.h
        models/ProductModel.cpp
        models/ProductModel.h
        library/dialogs/ProductsOnShelfDialog.cpp
        library/dialogs/ProductsOnShelfDialog.h
        ViewWrapper.cpp
        ViewWrapper.h
        library/dialogs/OrderDialog.h
        library/dialogs/OrderDialog.cpp
        views/SimulationWindow.cpp
        views/SimulationWindow.h
        controllers/Connection.cpp
        controllers/Connection.h
        library/buttons/SimulationButton.cpp
        library/buttons/SimulationButton.h
        library/dialogs/RobotInfoDialog.cpp
        library/dialogs/RobotInfoDialog.h

        resources.qrc
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
