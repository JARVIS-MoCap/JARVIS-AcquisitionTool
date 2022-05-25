/*******************************************************************************
 * File:        loadflirpresetswindow.hpp
 * Created:     23. October 2020
 * Author:      Timo Hueser
 * Contact:     timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#ifndef LOADFLIRPRESETSWINDOW_H
#define LOADFLIRPRESETSWINDOW_H

#include "camerainterface.hpp"
#include "flirchameleon.hpp"
#include "globals.hpp"
#include "loadcamerapresetsinterface.hpp"

#include <QComboBox>
#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QSettings>
#include <QToolBar>
#include <QToolButton>

class LoadFlirPresetsWindow : public LoadCameraPresetsInterface {
    Q_OBJECT

  public:
    explicit LoadFlirPresetsWindow(FLIRChameleon *cam,
                                   QWidget *parent = nullptr);

  private:
    FLIRChameleon *m_cam;

    QPushButton *loadButton;
    QPushButton *closeButton;

    QListWidget *userSetList;

    QComboBox *defaultUserSetCombo;

    void getDefaultUserSet();

  private slots:
    void loadClickedSlot();
    void currentItemChangedSlot(QListWidgetItem *current,
                                QListWidgetItem *previous);
    void defaultUserSetChangedSlot(const QString &userSet);
};

#endif
