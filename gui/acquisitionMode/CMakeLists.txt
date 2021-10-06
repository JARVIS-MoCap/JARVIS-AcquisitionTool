project (acquisitionMode)


add_library(${PROJECT_NAME}
    acquisitionmode.hpp
    acquisitionmode.cpp
    camselectorwindow.hpp
    camselectorwindow.cpp
    controlbar.hpp
    controlbar.cpp
    streamingwidget.hpp
    streamingwidget.cpp
    camerasettingswindow.hpp
    camerasettingswindow.cpp
    triggersettingswindow.hpp
    triggersettingswindow.cpp
    savecamerapresetsinterface.hpp
    loadcamerapresetsinterface.hpp
    saveflirpresetswindow.hpp
    saveflirpresetswindow.cpp
    loadflirpresetswindow.hpp
    loadflirpresetswindow.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${PROJECT_SOURCE_DIR}
    ../
    ../../
)

target_link_libraries(${PROJECT_NAME}
  Qt5::Widgets
  src
  gui
)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Wunused)
