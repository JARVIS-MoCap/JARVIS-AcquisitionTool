/*******************************************************************************
 * File:        acquisitionmode.hpp
 * Created:     23. October 2020
 * Author:      Timo Hueser
 * Contact:     timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#ifndef ACQUISITIONMODE_H
#define ACQUISITIONMODE_H

#include "camerainterface.hpp"
#include "camerasettingswindow.hpp"
#include "camselectorwindow.hpp"
#include "controlbar.hpp"
#include "globals.hpp"
#include "monitoringwindow.hpp"
#include "streamingwidget.hpp"
#include "triggerinterface.hpp"
#include "triggersettingswindow.hpp"

#include <QMainWindow>

class AcquisitionMode : public QMainWindow {
    Q_OBJECT

  public:
    explicit AcquisitionMode(QMainWindow *parent = nullptr);

  public slots:
    void camSelectedSlot(CameraInterface *cam);
    void triggerInstanceChangedSlot();

  signals:
    void camListChanged();
    void camAdded(CameraInterface *cam);
    void statusUpdated(CameraInterface *cam, statusType status,
                       const QString &message);

  private:
    CamSelectorWindow *camSelector;
    StreamingWidget *streamingWidget;
    ControlBar *controlBar;
    CameraSettingsWindow *camSettingsWindow;
    TriggerSettingsWindow *triggerSettingsWindow;
    MonitoringWindow *monitoringWindow;

  private slots:
    void loadCameraPresetSlot(SettingsObject *activeSettings);
    void setupAllCamerasClickedSlot(const CameraSettings &cameraSettings);
};

#endif
