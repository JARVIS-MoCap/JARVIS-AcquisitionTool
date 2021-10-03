project (src)

find_package(OpenCV REQUIRED)
add_library(${PROJECT_NAME}
  camerainterface.hpp
	recordinginterface.hpp
  baserecorder.cpp
  cudarecorder.cpp
  triggerinterface.hpp
  settingsobject.hpp
  settingsobject.cpp
  settingsnode.hpp
  settingsnode.cpp
  testcamera.hpp
  testcamera.cpp
  testtrigger.cpp
  serialinterface.hpp
  serialinterface.cpp
  flirchameleon.hpp
  flirchameleon.cpp
  flirconfigbackend.hpp
  flirconfigbackend.cpp
)

target_include_directories( ${PROJECT_NAME}
    PUBLIC
    ${PROJECT_SOURCE_DIR}
    ${OpenCV_INCLUDE_DIRS}
    ../
)

add_library(Flir_Spinnaker SHARED IMPORTED)
set_target_properties(Flir_Spinnaker PROPERTIES
  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/FlirSpinnaker/lib/libSpinnaker.so"
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/FlirSpinnaker/include"
)

target_link_libraries(${PROJECT_NAME}
  Qt5::Widgets
  Qt5::Core
  Qt5::SerialPort
  Flir_Spinnaker
  ${OpenCV_LIBS}
  cudajpegencoder
)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Wunused)
