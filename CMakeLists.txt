project(QTcpPlanetWars)

find_package(Qt COMPONENTS QtCore QtGui REQUIRED)
include(${QT_USE_FILE})

set(planetwars_SRCS
  main.cpp
  mainwindow.cpp)

add_executable(qtcpplanetwars ${planetwars_SRCS})

target_link_libraries(qtcpplanetwars ${QT_LIBRARIES})

