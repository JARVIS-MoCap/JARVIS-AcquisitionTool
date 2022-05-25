/*******************************************************************************
 * File:        flirconfigbackend.hpp
 * Created:     05. June 2020
 * Author:      Timo Hueser
 * Contact:     timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#ifndef FLIRCONFIGBACKEND_H
#define FLIRCONFIGBACKEND_H

#include "globals.hpp"

#include "SpinGenApi/SpinnakerGenApi.h"
#include "Spinnaker.h"

class FlirConfigBackend : public QObject {
    Q_OBJECT

  public:
    static FlirConfigBackend *getInstance() {
        static FlirConfigBackend instance;
        return &instance;
    }
    explicit FlirConfigBackend(QObject *parent = nullptr);
    ~FlirConfigBackend();

    QList<QString> getCameraIDs();
    void updateIDs();
    bool checkCamList();

  private:
    QList<QString> m_cameraIDList;
    const Spinnaker::SystemPtr m_camSystem;
};

#endif
