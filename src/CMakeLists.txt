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
    metadatawriter.cpp
    metadatawriter.hpp
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
    metadatawriter.cpp
    metadatawriter.hpp
  )
endif()

if (UNIX)
find_path(Spinnaker_INCLUDE_DIRS NAMES
  Spinnaker.h
  PATHS
  /opt/spinnaker/include
  "${CMAKE_SOURCE_DIR}/libs/FlirSpinnaker/${OS_LIB_DIR}/include"
  )
find_library(Spinnaker_LIBRARIES NAMES Spinnaker
  PATHS
  /opt/spinnaker/lib
  "${CMAKE_SOURCE_DIR}/libs/FlirSpinnaker/${OS_LIB_DIR}/lib/"
)
else()
  set(SPINNAKER_DIR "C:/Program Files/FLIR Systems/Spinnaker/")
  find_path(Spinnaker_INCLUDE_DIRS
            NAMES Spinnaker.h
            PATHS
            ${SPINNAKER_DIR}/include)
  find_library(Spinnaker_LIBRARIES
               NAMES Spinnaker_v140
               PATHS
             ${SPINNAKER_DIR}/lib64/vs2015)
endif()

message(STATUS "Spinnaker_INCLUDE_DIRS: ${Spinnaker_INCLUDE_DIRS}")
message(STATUS "Spinnaker_LIBRARIES:    ${Spinnaker_LIBRARIES}")

add_library(Flir_Spinnaker STATIC IMPORTED)
set_target_properties(Flir_Spinnaker PROPERTIES
  IMPORTED_LOCATION "${Spinnaker_LIBRARIES}"
  INTERFACE_INCLUDE_DIRECTORIES "${Spinnaker_INCLUDE_DIRS}"
)

target_include_directories(src
    PUBLIC
    ${PROJECT_SOURCE_DIR}
    ${OpenCV_INCLUDE_DIRS}
    ${SPINNAKER_INCLUDE_DIR}
)

if(USE_CUDA)
  target_compile_definitions(src PUBLIC USE_CUDA=1)
target_link_libraries(src
  Qt::Widgets
  Qt::Core
  Qt::SerialPort
  Flir_Spinnaker
  ${OpenCV_LIBS}
  cudajpegencoder
)
else()
  target_link_libraries(src
    Qt::Widgets
    Qt::Core
    Qt::SerialPort
    Flir_Spinnaker
    ${OpenCV_LIBS}
  )
endif()
