project (connectionMode)


add_library(${PROJECT_NAME}
    connectionmode.hpp
    connectionwidget.hpp
    camconnectionpanel.hpp
    statuslogwindow.hpp
    triggerconnectionpanel.hpp
    connectionmode.cpp
    connectionwidget.cpp
    camconnectionpanel.cpp
    statuslogwindow.cpp
    triggerconnectionpanel.cpp
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
