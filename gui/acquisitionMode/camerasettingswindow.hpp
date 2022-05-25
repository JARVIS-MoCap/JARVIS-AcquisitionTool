/*******************************************************************************
 * File:        camerasettingswindow.hpp
 * Created:     23. October 2020
 * Author:      Timo Hueser
 * Contact:     timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#ifndef CAMERASETTINGSWINDOW_H
#define CAMERASETTINGSWINDOW_H

#include "camerainterface.hpp"
#include "globals.hpp"
#include "loadcamerapresetsinterface.hpp"
#include "presetswindow.hpp"
#include "savecamerapresetsinterface.hpp"
#include "settingsnode.hpp"
#include "settingsobject.hpp"
#include "setupallcameraswindow.hpp"
#include "toggleswitch.hpp"

#include <QDockWidget>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QSplitter>
#include <QStackedWidget>
#include <QTextEdit>

class CameraSettingsWindow : public QDockWidget {
    Q_OBJECT

  public:
    explicit CameraSettingsWindow(QWidget *parent = nullptr,
                                  SettingsObject *activeSettings = nullptr);

  public slots:
    void setSettingsObjectSlot(SettingsObject *);

  signals:
    void loadPreset(SettingsObject *);
    void setupAllCamerasButtonClicked(const CameraSettings &cameraSettings);

  private:
    QSettings *settings;
    QGridLayout *layout;
    CameraInterface *m_cam;
    SaveCameraPresetsInterface *saveCameraPresetsWindow;
    LoadCameraPresetsInterface *loadCameraPresetsWindow;
    QLabel *settingsLabel;
    SetupAllCamerasWindow *setupAllCamerasWindow;

    QSplitter *mainSplitter;
    QWidget *mainWidget;
    QToolBar *toolBar;
    QToolButton *advancedSimpleButton;
    QAction *advancedSimpleAction;
    QToolButton *expandButton;
    QAction *expandAction;
    QToolButton *savePresetButton;
    QAction *savePresetAction;
    QToolButton *loadPresetButton;
    QAction *loadPresetAction;

    QTextEdit *toolTipBox;

    QToolBar *searchBar;
    QLineEdit *searchEdit;

    QStackedWidget *advancedSimpleStackWidget;
    ToggleSwitch *exposureToggle;
    QDoubleSpinBox *exposureEdit;
    ToggleSwitch *gainToggle;
    QDoubleSpinBox *gainEdit;
    QSpinBox *widthEdit;
    QSpinBox *heightEdit;
    QSpinBox *horizontalOffsetEdit;
    QSpinBox *verticalOffsetEdit;
    ToggleSwitch *flipHorizontalToggle;
    ToggleSwitch *flipVerticalToggle;

    QPushButton *setupAllCamerasButton;

    SettingsObject *m_activeSettings = nullptr;

    void saveSettingsLayer(SettingsNode *node);
    void loadSettingsLayer(SettingsNode *node);

    int searchRecursive(QTreeWidgetItem *parent,
                        QList<QTreeWidgetItem *> results);

  private slots:
    void searchEditedSlot(const QString &text);
    void searchReturnPressedSlot();
    void advancedSimpleToggledSlot(bool toggle);
    void expandClickedSlot();
    void treeItemActivatedSlot(QTreeWidgetItem *item, int column);
    void savePresetsClickedSlot();
    void loadPresetsClickedSlot();
    void simpleSettingChangedSlot(const QString &settingName,
                                  const QString &value, bool enabled,
                                  double min, double max);
    void setupAllCamerasButtonClickedSlot();

    void exposureAutoToggledSlot(bool toggle);
    void exposureEditChangedSlot(double val);
    void gainAutoToggledSlot(bool toggle);
    void gainEditChangedSlot(double val);
    void widthEditChangedSlot(int val);
    void heightEditChangedSlot(int val);
    void horizontalOffsetEditChangedSlot(int val);
    void verticalOffsetEditChangedSlot(int val);
    void flipHorizontalToggledSlot(bool toggle);
    void flipVerticalToggledSlot(bool toggle);
};

#endif
