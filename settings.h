#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

class Settings
  : public QSettings
{

  public:
    static Settings *instance();

  private:
    Settings();

};

#endif

