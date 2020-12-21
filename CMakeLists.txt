cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)


project(CameraContoller VERSION 1.0.0  LANGUAGES CXX CUDA) #removed CUDA here!!

find_package(Qt5 COMPONENTS Widgets Core Gui Charts SerialPort REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

option(USE_FLIR "Include Flir Spinnaker Library" ON)
if (USE_FLIR)
add_definitions(-DFLIR_CHAMELEON)
endif(USE_FLIR)

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
