/*******************************************************************************
 * File:        arduinoconfigbackend.hpp
 * Created:     05. September 2021
 * Author:      Timo Hueser
 * Contact:     timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#ifndef ARDUINOCONFIGBACKEND_H
#define ARDUINOCONFIGBACKEND_H

#include "globals.hpp"
#include "serialinterface.hpp"

class ArduinoConfigBackend : public QObject {
    Q_OBJECT

  public:
    static ArduinoConfigBackend *getInstance() {
        static ArduinoConfigBackend instance;
        return &instance;
    }
    explicit ArduinoConfigBackend(QObject *parent = nullptr);
    QList<QString> getAvailableDevices();

  private:
    QList<QString> availableDevices;
};

#endif
