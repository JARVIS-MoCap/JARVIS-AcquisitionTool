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
    settingswindow.hpp
    settingswindow.cpp
)

target_include_directories(gui
    PUBLIC
    ${PROJECT_SOURCE_DIR}
    acquisitionMode
    connectionMode
)

target_link_libraries(gui
  Qt5::Widgets
  acquisitionMode
  connectionMode
)
