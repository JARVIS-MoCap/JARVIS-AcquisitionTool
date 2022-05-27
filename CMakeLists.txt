cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)

if(USE_CUDA)
  set (CMAKE_CUDA_COMPILER "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v10.2/bin/nvcc.exe")
  project(AcquisitionTool VERSION 0.3.0  LANGUAGES CXX CUDA)
else()
  project(AcquisitionTool VERSION 0.3.0  LANGUAGES CXX)
endif()

if(APPLE)
  set(OS_LIB_DIR "MacOS")
elseif(WIN32)
  set(OS_LIB_DIR "Windows")
elseif(UNIX)
  message ("System ${CMAKE_SYSTEM}")
  if(${UBUNTU_VERSION} STREQUAL "2004")
    set(OS_LIB_DIR "Ubuntu_2004")
  else()
    set(OS_LIB_DIR "Ubuntu_1804")
  endif()
endif()

if (NOT UNIX)
  set(Qt5_DIR "libs/Qt_5.15.2/${OS_LIB_DIR}/lib/cmake/Qt5")
  set(Qt5Core_DIR "libs/Qt_5.15.2/${OS_LIB_DIR}/lib/cmake/Qt5Core")
  set(Qt5Widgets_DIR "libs/Qt_5.15.2/${OS_LIB_DIR}/lib/cmake/Qt5Widgets")
  set(Qt5Charts_DIR "libs/Qt_5.15.2/${OS_LIB_DIR}/lib/cmake/Qt5Charts")
  set(Qt5SerialPort_DIR "libs/Qt_5.15.2/${OS_LIB_DIR}/lib/cmake/Qt5SerialPort")
endif()

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Charts REQUIRED)
find_package(Qt5SerialPort REQUIRED)

message (STATUS "QT DIRECTORY ${Qt5Core_DIR}")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(NOT WIN32)
	set(OpenCV_DIR "libs/OpenCV_4.5.1/${OS_LIB_DIR}/lib/cmake/opencv4")
else()
	set(OpenCV_DIR "libs/OpenCV_4.5.1/${OS_LIB_DIR}")
endif()

find_package(OpenCV REQUIRED)

message(STATUS "OPENCV_DIR ${OpenCV_DIR}")


# detect operating system and host processor
message(STATUS "We are on a ${CMAKE_SYSTEM_NAME} system")
message(STATUS "The host processor is ${CMAKE_HOST_SYSTEM_PROCESSOR}")


add_subdirectory(gui)
add_subdirectory(src)


set(CMAKE_INSTALL_RPATH /usr/local/lib/JARVIS-AcquisitionTool;/usr/local/lib/JARVIS-AcquisitionTool/OpenCV;/usr/local/lib/JARVIS-AcquisitionTool/nvjpeg)
add_executable(${PROJECT_NAME}
    main.cpp
    globals.hpp
    gui/Qt-DarkStyle/darkstyle.qrc
)

if(${UBUNTU_VERSION} AND ${UBUNTU_VERSION} STREQUAL "2004")
  install(TARGETS ${PROJECT_NAME} DESTINATION ${PROJECT_SOURCE_DIR}/deployment/deb_packages/JARVIS-AcquisitionTool_0.3-1_amd64_2004/usr/local/bin)
elseif(${UBUNTU_VERSION})
  install(TARGETS ${PROJECT_NAME} DESTINATION ${PROJECT_SOURCE_DIR}/deployment/deb_packages/JARVIS-AcquisitionTool_0.3-1_amd64_1804/usr/local/bin)
endif()



if(USE_CUDA)
  find_package(CUDA)
  add_subdirectory(cudajpegencoder)
endif()

if (UNIX)
  target_compile_options(${PROJECT_NAME} PRIVATE -O3)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -O2)
endif()

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
