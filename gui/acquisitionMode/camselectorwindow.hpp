/*******************************************************************************
 * File:        camselectorwindow.hpp
 * Created:     23. October 2020
 * Author:      Timo Hueser
 * Contact:     timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#ifndef CAMSELECTORWINDOW_H
#define CAMSELECTORWINDOW_H

#include "camerainterface.hpp"
#include "globals.hpp"

#include <QDockWidget>
#include <QGridLayout>
#include <QTableWidget>
#include <QToolBar>

class CamSelectorWindow : public QDockWidget {
    Q_OBJECT
  public:
    explicit CamSelectorWindow(QWidget *parent = nullptr);
    static QMap<CameraInterface *, bool> camVisibilityMap;

  public slots:
    void updateListSlot();
    void statusUpdatedSlot(CameraInterface *cam, statusType status,
                           const QString &);
    void camVisibilityToggledSlot(CameraInterface *cam, bool toggle);

  signals:
    void cameraSelected(CameraInterface *cam);
    void camVisibilityToggled(CameraInterface *cam, bool toggle);

  private:
    QWidget *mainWidget;
    QToolBar *toolBar;
    QTableWidget *camsTable;
    QMap<QTableWidgetItem *, CameraInterface *> m_camMap;
    QMap<QTableWidgetItem *, int> m_checkStateMap;

  private slots:
    void selectionChangedSlot(int row, int);
    void tableItemPressed(QTableWidgetItem *item);
    void tableItemClicked(QTableWidgetItem *item);
};

#endif
