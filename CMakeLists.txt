project(QTcpPlanetWars)

find_package(Qt4 COMPONENTS QtCore QtGui QtNetwork REQUIRED)
include(${QT_USE_FILE})

set(planetwars_SRCS
  main.cpp
  mainwindow.cpp
  game.cpp
  player.cpp
  settings.cpp
  gamescene.cpp
  planet.cpp
  gamewidget.cpp)

set(planetwars_HDRS
  mainwindow.h
  game.h
  player.h
  settings.h
  gamescene.h
  planet.h
  gamewidget.h)

set(planetwars_UI
  ui/mainwindow.ui)

QT4_WRAP_UI(planetwarsui ${planetwars_UI})
QT4_AUTOMOC(${planetwars_SRCS})

add_executable(qtcpplanetwars ${planetwars_SRCS} ${planetwarsmoc} ${planetwarsui})

target_link_libraries(qtcpplanetwars ${QT_LIBRARIES})

