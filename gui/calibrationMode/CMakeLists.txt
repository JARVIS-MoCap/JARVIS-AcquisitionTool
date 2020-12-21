project (calibrationMode)


add_library(${PROJECT_NAME}
    calibrationmode.hpp
		calibrationwidget.hpp
		calibrationtool.hpp
		calibrationcontrolbar.hpp
		calibrationsettingswindow.hpp
		calibrationstatisticswindow.hpp
		coveragemapwindow.hpp
		calibrationcommons.hpp
		calibrationmode.cpp
		calibrationwidget.cpp
		calibrationtool.cpp
		calibrationcontrolbar.cpp
		calibrationsettingswindow.cpp
		calibrationstatisticswindow.cpp
		coveragemapwindow.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${PROJECT_SOURCE_DIR}
    ../
    ../../
)

target_link_libraries(${PROJECT_NAME}
  Qt5::Widgets
	Qt5::Charts
  src
)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Wunused)
