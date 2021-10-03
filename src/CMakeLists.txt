project (src)

if (USE_FLIR)
  find_package(OpenCV REQUIRED)
  add_library(${PROJECT_NAME}
    settingsobject.hpp
    settingsnode.hpp
    camerainterface.hpp
    testcamera.hpp
		recordinginterface.hpp
    baserecorder.cpp
    cudarecorder.cpp
    triggerinterface.hpp
    settingsobject.cpp
    settingsnode.cpp
    testcamera.cpp
    testtrigger.cpp
    serialinterface.hpp
    serialinterface.cpp
    flirchameleon.hpp
    flirchameleon.cpp
    flirconfigbackend.hpp
    flirconfigbackend.cpp
  )
else ()
  add_library(${PROJECT_NAME}
    settingsobject.hpp
    settingsnode.hpp
    camerainterface.hpp
		recordinginterface.hpp
    testcamera.hpp
		baserecorder.cpp
    cudarecorder.cpp
    triggerinterface.hpp
    settingsobject.cpp
    settingsnode.cpp
    testcamera.cpp
    testtrigger.cpp
    serialinterface.hpp
    serialinterface.cpp
  )
endif()


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

if(CUDA_FOUND)
	target_link_libraries(${PROJECT_NAME}
	  Qt5::Widgets
	  Qt5::Core
    Qt5::SerialPort
	  Flir_Spinnaker
	  ${OpenCV_LIBS}
	  cudajpegencoder
)
else()
	target_link_libraries(${PROJECT_NAME}
	  Qt5::Widgets
	  Qt5::Core
    Qt5::SerialPort
	  Flir_Spinnaker
	  ${OpenCV_LIBS}
	)
endif()

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Wunused)
