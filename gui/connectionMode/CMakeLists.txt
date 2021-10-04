project (connectionMode)

add_library(${PROJECT_NAME}
    connectionmode.hpp
    connectionmode.cpp
    connectionwidget.hpp
    connectionwidget.cpp
    camconnectionpanel.hpp
    camconnectionpanel.cpp
    statuslogwindow.hpp
    statuslogwindow.cpp
    triggerconnectionpanel.hpp
    triggerconnectionpanel.cpp
    camconfiginterface.hpp
    flirchameleonconfig.hpp
    flirchameleonconfig.cpp
    camtestconfig.hpp
    camtestconfig.cpp
    triggerconfiginterface.hpp
    triggertestconfig.hpp
    triggertestconfig.cpp
    arduinotriggerconfig.hpp
    arduinotriggerconfig.cpp
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
