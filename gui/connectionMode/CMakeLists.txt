#add_compile_options("-O3")

add_library(connectionMode
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


target_include_directories(connectionMode
    PUBLIC
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/src
    ../
)

target_link_libraries(connectionMode
  Qt5::Widgets
  src
)
