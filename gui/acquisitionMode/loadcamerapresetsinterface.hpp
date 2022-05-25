/*******************************************************************************
 * File:        loadcamerapresetsinterface.hpp
 * Created:     23. October 2020
 * Author:      Timo Hueser
 * Contact:     timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#ifndef LOADCAMERAPRESETSINTERFACE_H
#define LOADCAMERAPRESETSINTERFACE_H

#include "globals.hpp"

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QSettings>
#include <QToolBar>
#include <QToolButton>

class LoadCameraPresetsInterface : public QDialog {
    Q_OBJECT

  public:
    explicit LoadCameraPresetsInterface(QWidget *parent = nullptr){};

  signals:

  private:
  private slots:
};

#endif
