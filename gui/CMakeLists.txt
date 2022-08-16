add_subdirectory(Qt-DarkStyle)
add_subdirectory(acquisitionMode)
add_subdirectory(connectionMode)

add_library(gui
    mainwindow.hpp
    mainwindow.cpp
    mainbar.cpp
    mainbar.hpp
    presetswindow.hpp
    presetswindow.cpp
    imageviewer.hpp
    imageviewer.cpp
    streamingpanel.hpp
    streamingpanel.cpp
    labelwithtooltip.hpp
    labelwithtooltip.cpp
    toggleswitch.cpp
    toggleswitch.hpp
    hardwarecheck.hpp
    hardwarecheck.cpp
    settingswindow.hpp
    settingswindow.cpp

)

target_include_directories(gui
    PUBLIC
    ${PROJECT_SOURCE_DIR}
    acquisitionMode
    connectionMode
    ${LIBUSB_1_INCLUDE_DIRS}

)

message("AAAA"${LIBUSB_1_LIBRARIES} )

target_link_libraries(gui
  Qt::Widgets
  acquisitionMode
  connectionMode
  ${LIBUSB_1_LIBRARIES}
)
