project(QTcpPlanetWars)

find_package(Qt COMPONENTS QtCore QtGui REQUIRED)
include(${QT_USE_FILE})

set(planetwars_SRCS
  main.cpp
  mainwindow.cpp)

set(planetwars_HDRS
  mainwindow.h)

set(planetwars_UI
  ui/mainwindow.ui)

QT4_WRAP_UI(planetwarsui ${planetwars_UI})
QT4_WRAP_CPP(planetwarsmoc ${planetwars_SRCS})
QT4_AUTOMOC(${planetwars_SRCS})

add_executable(qtcpplanetwars ${planetwars_SRCS} ${planetwarsmoc} ${planetwarsui})

target_link_libraries(qtcpplanetwars ${QT_LIBRARIES})

