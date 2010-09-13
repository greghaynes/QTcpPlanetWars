#include "settings.h"

Settings *Settings::instance()
{
  static Settings *i;
  if(!i)
    i = new Settings();
  return i;
}

Settings::Settings()
  : QSettings("aicontest", "qtcpplanetwars")
{
}

