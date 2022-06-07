cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)




if(USE_CUDA)
  if (WIN32)
    set (CMAKE_CUDA_COMPILER "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v10.2/bin/nvcc.exe")
  endif()
  project(AcquisitionTool VERSION 0.3.0  LANGUAGES CXX CUDA)
  message(STATUS "Using CUDA")
  else()
	project(AcquisitionTool VERSION 0.3.0  LANGUAGES CXX)
  message(STATUS "Skipping CUDA")
endif()

# Version String
# Get the current working branch
execute_process(
    COMMAND git rev-parse --abbrev-ref HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_BRANCH
    OUTPUT_STRIP_TRAILING_WHITESPACE)

# Get the latest commit hash
execute_process(
    COMMAND git rev-parse --short HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE)

# Get working tree status (dirty)
execute_process(
  COMMAND git diff --quiet
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  RESULT_VARIABLE GIT_DIRTY_RET
  OUTPUT_STRIP_TRAILING_WHITESPACE)

if(GIT_DIRTY_RET)
  set(VERSION_STRING "(git)${GIT_BRANCH}:${GIT_COMMIT_HASH}-dirty")
else()
  set(VERSION_STRING "git ${GIT_BRANCH}:${GIT_COMMIT_HASH}")
endif()
add_definitions("-DVERSION_STRING=\"${VERSION_STRING}\"")
message(STATUS "VERSION_STRING " ${VERSION_STRING})

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
  find_package(Eigen3 REQUIRED)
else()
	set(OpenCV_DIR "libs/OpenCV_4.5.1/${OS_LIB_DIR}")
endif()

find_package(OpenCV REQUIRED)

message(STATUS "OPENCV_DIR ${OpenCV_DIR}")

# detect operating system and host processor
message(STATUS "CMAKE_SYSTEM_INFO_FILE: ${CMAKE_SYSTEM_INFO_FILE}")
message(STATUS "CMAKE_SYSTEM_NAME:      ${CMAKE_SYSTEM_NAME}")
message(STATUS "CMAKE_SYSTEM_PROCESSOR: ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "CMAKE_SYSTEM:           ${CMAKE_SYSTEM}")


add_subdirectory(gui)
add_subdirectory(src)


set(CMAKE_INSTALL_RPATH /usr/local/lib/JARVIS-AcquisitionTool;/usr/local/lib/JARVIS-AcquisitionTool/nvjpeg)
add_executable(${PROJECT_NAME}
    main.cpp
    globals.hpp
    gui/Qt-DarkStyle/darkstyle.qrc
)

if(${UBUNTU_VERSION} AND ${UBUNTU_VERSION} STREQUAL "2004")
  install(TARGETS ${PROJECT_NAME} DESTINATION ${PROJECT_SOURCE_DIR}/deployment/deb_packages/JARVIS-AcquisitionTool_1.0-1_amd64_2004/usr/local/bin)
elseif(${UBUNTU_VERSION})
  install(TARGETS ${PROJECT_NAME} DESTINATION ${PROJECT_SOURCE_DIR}/deployment/deb_packages/JARVIS-AcquisitionTool_1.0-1_amd64_1804/usr/local/bin)
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



