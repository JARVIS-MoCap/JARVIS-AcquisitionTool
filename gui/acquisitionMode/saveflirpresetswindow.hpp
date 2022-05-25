/*****************************************************************
 * File:        saveflirpresetswindow.hpp
 * Created:     23. October 2020
 * Author:      Timo Hueser
 * Contact:     timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 *****************************************************************/

#ifndef SAVEFLIRPRESETSWINDOW_H
#define SAVEFLIRPRESETSWINDOW_H

#include "camerainterface.hpp"
#include "flirchameleon.hpp"
#include "globals.hpp"
#include "savecamerapresetsinterface.hpp"

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QListWidget>
#include <QMenu>
#include <QPushButton>
#include <QSettings>
#include <QToolBar>
#include <QToolButton>

class UserSetListWidget;

class SaveFlirPresetsWindow : public SaveCameraPresetsInterface {
    Q_OBJECT

  public:
    explicit SaveFlirPresetsWindow(FLIRChameleon *cam,
                                   QWidget *parent = nullptr);
    QString getActivePreset();

  signals:

  private:
    FLIRChameleon *m_cam;

    QPushButton *saveButton;
    QPushButton *closeButton;

    UserSetListWidget *userSetList;

  private slots:
    void currentItemChangedSlot(QListWidgetItem *current,
                                QListWidgetItem *previous);
    void saveSetClickedSlot();
    void saveUserSetToFileSlot(const QString &userSet);
    void loadUserSetFromFileSlot(const QString &userSet);
};

class UserSetListWidget : public QListWidget {
    Q_OBJECT
  public:
    explicit UserSetListWidget(QWidget *parent = nullptr)
        : QListWidget(parent) {
        setContextMenuPolicy(Qt::CustomContextMenu);
        connect(this, &UserSetListWidget::customContextMenuRequested, this,
                &UserSetListWidget::showContextMenu);
    }

  signals:
    void saveUserSetToFile(const QString &userSet);
    void loadUserSetFromFile(const QString &userSet);

  private:
  private slots:
    void showContextMenu(const QPoint &pos) {
        QMenu contextMenu("File Menu", this);
        QAction *saveAction = new QAction("Save UserSet to File", this);
        saveAction->setIcon(QIcon::fromTheme("upload"));
        QAction *loadAction = new QAction("Load UserSet from File", this);
        loadAction->setIcon(QIcon::fromTheme("download"));
        contextMenu.addAction(saveAction);
        contextMenu.addAction(loadAction);
        QAction *clickedAction = contextMenu.exec(mapToGlobal(pos));
        if (clickedAction == saveAction) {
            emit saveUserSetToFile(this->currentItem()->text());
        } else if (clickedAction == loadAction) {
            emit loadUserSetFromFile(this->currentItem()->text());
        }
    }
};

#endif
