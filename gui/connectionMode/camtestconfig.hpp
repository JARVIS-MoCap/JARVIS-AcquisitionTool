/*******************************************************************************
 * File:        camtestconfig.cpp
 * Created:     03. October 2021
 * Author:      Timo Hueser
 * Contact:     timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#ifndef CAMTESTCONFIG_H
#define CAMTESTCONFIG_H

#include "camconfiginterface.hpp"
#include "globals.hpp"

#include <QLineEdit>

class CamTestConfig : public CamConfigInterface {
    Q_OBJECT

  public:
    explicit CamTestConfig(QWidget *parent = 0);

    QLineEdit *example1Edit;
    QLineEdit *example2Edit;
    QLineEdit *example1Info;
    QLineEdit *example2Info;

    bool confirmConfigClicked();
    void loadPreset(QSettings *settings);
    void savePreset(QSettings *settings);
    CameraInterface *getCamera(const QString &cameraName);
};

#endif
