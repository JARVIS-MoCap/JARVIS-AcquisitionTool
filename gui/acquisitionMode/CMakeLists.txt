project (acquisitionMode)


add_library(${PROJECT_NAME}
    acquistionmode.hpp   #correct name of file!!
    camselectorwindow.hpp
    controlbar.hpp
    streamingwidget.hpp
		timestampwindow.hpp
    acquisitionmode.cpp
    camselectorwindow.cpp
    controlbar.cpp
    streamingwidget.cpp
		timestampwindow.cpp
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
)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Wunused)
