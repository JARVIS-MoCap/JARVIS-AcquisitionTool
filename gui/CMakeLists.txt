project (gui)

add_subdirectory(Qt-DarkStyle)
add_subdirectory(acquisitionMode)
add_subdirectory(connectionMode)

add_library(${PROJECT_NAME}
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
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${PROJECT_SOURCE_DIR}
    ../
)

target_link_libraries(${PROJECT_NAME}
  Qt5::Widgets
  acquisitionMode
  connectionMode
)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Wunused)
