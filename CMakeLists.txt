cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)



if(USE_CUDA)
<<<<<<< HEAD
	project(AcquisitionTool VERSION 0.3.0  LANGUAGES CXX CUDA)
  message(STATUS "Using CUDA")
  else()
	project(AcquisitionTool VERSION 0.3.0  LANGUAGES CXX)
  message(STATUS "Skipping CUDA")
=======
  project(AcquisitionTool VERSION 0.3.0  LANGUAGES CXX CUDA)
else()
  project(AcquisitionTool VERSION 0.3.0  LANGUAGES CXX)
>>>>>>> upstream/master
endif()

if(APPLE)
  set(OS_LIB_DIR "MacOS")
elseif(WIN32)
  set(OS_LIB_DIR "Windows")
elseif(UNIX)
  if(${UBUNTU_VERSION} STREQUAL "2004")
    set(OS_LIB_DIR "Ubuntu_2004")
  else()
    set(OS_LIB_DIR "Ubuntu_1804")
  endif()
endif()

#find_package(Qt5 COMPONENTS Widgets Core Gui Charts SerialPort REQUIRED)

set(Qt5_DIR "libs/Qt_5.15.2/${OS_LIB_DIR}/lib/cmake/Qt5")
set(Qt5Core_DIR "libs/Qt_5.15.2/${OS_LIB_DIR}/lib/cmake/Qt5Core")
set(Qt5Widgets_DIR "libs/Qt_5.15.2/${OS_LIB_DIR}/lib/cmake/Qt5Widgets")
set(Qt5Charts_DIR "libs/Qt_5.15.2/${OS_LIB_DIR}/lib/cmake/Qt5Charts")
set(Qt5SerialPort_DIR "libs/Qt_5.15.2/${OS_LIB_DIR}/lib/cmake/Qt5SerialPort")

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Charts REQUIRED)
find_package(Qt5SerialPort REQUIRED)

message (STATUS "QT DIRECTORY ${Qt5Core_DIR}")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


#set(Eigen3_DIR "libs/eigen-3.3.8/Ubuntu/cmake/")
#find_package(Eigen3 3.3 REQUIRED NO_MODULE)

#set(OpenCV_DIR "libs/OpenCV_4.5.1/${OS_LIB_DIR}/lib/cmake/opencv4")
find_package(OpenCV REQUIRED)
message(STATUS "OPENCV_DIR ${OpenCV_DIR}")

# detect operating system and host processor
message(STATUS "CMAKE_SYSTEM_INFO_FILE: ${CMAKE_SYSTEM_INFO_FILE}")
message(STATUS "CMAKE_SYSTEM_NAME:      ${CMAKE_SYSTEM_NAME}")
message(STATUS "CMAKE_SYSTEM_PROCESSOR: ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "CMAKE_SYSTEM:           ${CMAKE_SYSTEM}")


add_subdirectory(gui)
add_subdirectory(src)


set(CMAKE_INSTALL_RPATH /usr/local/lib/JARVIS-AcquisitionTool;/usr/local/lib/JARVIS-AcquisitionTool/OpenCV;/usr/local/lib/JARVIS-AcquisitionTool/Qt5/lib;/usr/local/lib/JARVIS-AcquisitionTool/FlirSpinnaker/lib;/usr/local/lib/JARVIS-AcquisitionTool/nvjpeg)
add_executable(${PROJECT_NAME}
    main.cpp
    globals.hpp
    gui/Qt-DarkStyle/darkstyle.qrc
)

if(${UBUNTU_VERSION} STREQUAL "2004")
  install(TARGETS ${PROJECT_NAME} DESTINATION ${PROJECT_SOURCE_DIR}/deployment/deb_packages/JARVIS-AcquisitionTool_0.3-1_amd64_2004/usr/local/bin)
else()
  install(TARGETS ${PROJECT_NAME} DESTINATION ${PROJECT_SOURCE_DIR}/deployment/deb_packages/JARVIS-AcquisitionTool_0.3-1_amd64_1804/usr/local/bin)
endif()



if(USE_CUDA)
  find_package(CUDA)
  add_subdirectory(cudajpegencoder)
endif()

target_compile_options(${PROJECT_NAME} PRIVATE -O3)

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
