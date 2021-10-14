cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)


project(CameraController VERSION 1.0.0  LANGUAGES CXX CUDA)

#find_package(Qt5 COMPONENTS Widgets Core Gui Charts SerialPort REQUIRED)

set(Qt5_DIR "libs/Qt_5.15.2/Ubuntu_2004/lib/cmake/Qt5")
set(Qt5Core_DIR "libs/Qt_5.15.2/Ubuntu_2004/lib/cmake/Qt5Core")
set(Qt5Widgets_DIR "libs/Qt_5.15.2/Ubuntu_2004/lib/cmake/Qt5Widgets")
set(Qt5Charts_DIR "libs/Qt_5.15.2/Ubuntu_2004/lib/cmake/Qt5Charts")
set(Qt5SerialPort_DIR "libs/Qt_5.15.2/Ubuntu_2004/lib/cmake/Qt5SerialPort")

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Charts REQUIRED)
find_package(Qt5SerialPort REQUIRED)

message (STATUS "QT DIRECTORY ${Qt5Core_DIR}")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

# detect operating system and host processor
message(STATUS "We are on a ${CMAKE_SYSTEM_NAME} system")
message(STATUS "The host processor is ${CMAKE_HOST_SYSTEM_PROCESSOR}")


add_subdirectory(gui)
add_subdirectory(src)

find_package(CUDA)
if(CUDA_FOUND)
	add_definitions(-DUSE_CUDA)
	add_subdirectory(cudajpegencoder)
endif()


add_executable(${PROJECT_NAME}
    main.cpp
    globals.hpp
    gui/Qt-DarkStyle/darkstyle.qrc
)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Wunused)

target_include_directories( ${PROJECT_NAME}
    PUBLIC
    ${PROJECT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
  Qt5::Widgets
	Qt5::Charts
  gui
  src
  darkstyle
)
