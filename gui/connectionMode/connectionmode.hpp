/*******************************************************************************
 * File:        connectionmode.hpp
 * Created:     23. October 2020
 * Author:      Timo Hueser
 * Contact:     timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#ifndef CONNECTIONMODE_H
#define CONNECTIONMODE_H

#include "connectionwidget.hpp"
#include "globals.hpp"
#include <QMainWindow>

class ConnectionMode : public QMainWindow {
    Q_OBJECT

  public:
    explicit ConnectionMode(QMainWindow *parent = 0);

  signals:
    void camListChanged();
    void camAdded(CameraInterface *);
    void triggerInstanceChanged();
    void statusUpdated(CameraInterface *cam, statusType status,
                       QString message);

  private:
    ConnectionWidget *connectionWidget;
};

#endif
