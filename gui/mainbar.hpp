/*******************************************************************************
 * File:        mainbar.hpp
 * Created:     23. October 2020
 * Author:      Timo Hueser
 * Contact:     timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#ifndef MAINBAR_H
#define MAINBAR_H

#include "globals.hpp"
#include "settingswindow.hpp"

#include <QLabel>
#include <QLineEdit>
#include <QToolBar>

class MainBar : public QToolBar {
    Q_OBJECT

  public:
    explicit MainBar(QWidget *parent = nullptr);

  private:
    SettingsWindow *settingsWindow;
    QToolButton *settingsButton;
    QAction *settingsAction;

  private slots:
    void settingsClickedSlot();
};

#endif
