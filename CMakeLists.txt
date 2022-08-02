cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

set (UBUNTU_VERSION 2004)
set (USE_CUDA True)

if(USE_CUDA)
  if (WIN32)
    set (CMAKE_CUDA_COMPILER "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v11.7/bin/nvcc.exe")
  endif()
  project(AcquisitionTool VERSION 1.1.0  LANGUAGES CXX CUDA)
  message(STATUS "Using CUDA")
  else()
	project(AcquisitionTool VERSION 1.1.0  LANGUAGES CXX)
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


set (CMAKE_PREFIX_PATH "libs/Qt/qt_install/lib/cmake/")
find_package(Qt6  QUIET PATHS "libs/Qt/qt_install/lib/cmake/" REQUIRED COMPONENTS Core Widgets Charts SerialPort)

add_definitions("-DQT_DEBUG")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if (NOT (WIN32 OR APPLE))
  find_package(Eigen3 REQUIRED)
endif()

if(NOT WIN32)
	set(OpenCV_DIR "libs/OpenCV/opencv_install/lib/cmake/opencv4")
	set(OpenCV_STATIC ON)
else()
	set(OpenCV_DIR "libs/OpenCV/opencv_install")
endif()

find_package(OpenCV REQUIRED)
message(STATUS "OPENCV_DIR ${OpenCV_DIR}")

add_subdirectory(gui)
add_subdirectory(src)

set(CMAKE_INSTALL_RPATH /usr/local/lib/JARVIS-AcquisitionTool;/usr/local/lib/JARVIS-AcquisitionTool/nvjpeg;/usr/local/lib/JARVIS-AcquisitionTool/spinnaker)
add_executable(${PROJECT_NAME}
    main.cpp
    globals.hpp
    gui/Qt-DarkStyle/darkstyle.qrc
)

if (${UBUNTU_VERSION})
  if(${UBUNTU_VERSION} AND ${UBUNTU_VERSION} STREQUAL "2004")
    install(TARGETS ${PROJECT_NAME} DESTINATION ${PROJECT_SOURCE_DIR}/deployment/deb_packages/JARVIS-AcquisitionTool_1.0-1_amd64_2004/usr/local/bin)
  elseif(${UBUNTU_VERSION})
    install(TARGETS ${PROJECT_NAME} DESTINATION ${PROJECT_SOURCE_DIR}/deployment/deb_packages/JARVIS-AcquisitionTool_1.0-1_amd64_1804/usr/local/bin)
  endif()
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
  Qt::Widgets
  Qt::Charts
  gui
  src
  darkstyle
)
