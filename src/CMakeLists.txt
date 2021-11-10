if(USE_CUDA)
  add_library(src
    camerainterface.hpp
  	recordinginterface.hpp
    baserecorder.cpp
    cudarecorder.hpp
    cudarecorder.cpp
    triggerinterface.hpp
    settingsobject.hpp
    settingsobject.cpp
    settingsnode.hpp
    settingsnode.cpp
    testcamera.hpp
    testcamera.cpp
    testtrigger.cpp
    arduinotrigger.hpp
    arduinotrigger.cpp
    serialinterface.hpp
    serialinterface.cpp
    flirchameleon.hpp
    flirchameleon.cpp
    flirconfigbackend.hpp
    flirconfigbackend.cpp
    arduinoconfigbackend.hpp
    arduinoconfigbackend.cpp
  )
else()
  add_library(src
    camerainterface.hpp
    recordinginterface.hpp
    baserecorder.cpp
    triggerinterface.hpp
    settingsobject.hpp
    settingsobject.cpp
    settingsnode.hpp
    settingsnode.cpp
    testcamera.hpp
    testcamera.cpp
    testtrigger.cpp
    arduinotrigger.hpp
    arduinotrigger.cpp
    serialinterface.hpp
    serialinterface.cpp
    flirchameleon.hpp
    flirchameleon.cpp
    flirconfigbackend.hpp
    flirconfigbackend.cpp
    arduinoconfigbackend.hpp
    arduinoconfigbackend.cpp
  )
endif()

target_include_directories(src
    PUBLIC
    ${PROJECT_SOURCE_DIR}
    ${OpenCV_INCLUDE_DIRS}
)

add_library(Flir_Spinnaker SHARED IMPORTED)
set_target_properties(Flir_Spinnaker PROPERTIES
  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/libs/FlirSpinnaker/${OS_LIB_DIR}/lib/libSpinnaker.so"
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/libs/FlirSpinnaker/${OS_LIB_DIR}/include"
)

if(USE_CUDA)
  target_compile_definitions(src PUBLIC USE_CUDA=1)
  message(STATUS "USING CUDA")
target_link_libraries(src
  Qt5::Widgets
  Qt5::Core
  Qt5::SerialPort
  Flir_Spinnaker
  ${OpenCV_LIBS}
  cudajpegencoder
)
else()
  target_link_libraries(src
    Qt5::Widgets
    Qt5::Core
    Qt5::SerialPort
    Flir_Spinnaker
    ${OpenCV_LIBS}
  )
endif()
