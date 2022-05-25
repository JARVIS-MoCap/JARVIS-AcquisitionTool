/*******************************************************************************
 * File:        savecamerapresetsinterface.cpp
 * Created:     23. October 2020
 * Author:      Timo Hueser
 * Contact:     timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#include "saveflirpresetswindow.hpp"

#include <QFileDialog>
#include <QGridLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QToolButton>

SaveFlirPresetsWindow::SaveFlirPresetsWindow(FLIRChameleon *cam,
                                             QWidget *parent)
    : SaveCameraPresetsInterface(parent), m_cam(cam) {
    setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    setWindowTitle("Save Camera Settings as UserSets");
    this->resize(600, 400);
    this->setMinimumSize(600, 200);
    QGridLayout *layout = new QGridLayout(this);

    QWidget *buttonSpacer = new QWidget(this);
    buttonSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    saveButton = new QPushButton("Save");
    saveButton->setIcon(QIcon::fromTheme("save"));
    saveButton->setMinimumSize(30, 30);
    connect(saveButton, &QPushButton::clicked, this,
            &SaveFlirPresetsWindow::saveSetClickedSlot);
    closeButton = new QPushButton("Close");
    closeButton->setIcon(QIcon::fromTheme("discard"));
    closeButton->setMinimumSize(30, 30);
    connect(closeButton, &QPushButton::clicked, this,
            &SaveFlirPresetsWindow::accept);

    QGroupBox *userSetGroup = new QGroupBox("User Sets");
    QGridLayout *usersetgrouplayout = new QGridLayout(userSetGroup);
    usersetgrouplayout->setMargin(2);

    userSetList = new UserSetListWidget(this);
    QListWidgetItem *userSet0Item = new QListWidgetItem();
    userSet0Item->setSizeHint(QSize(100, 27));
    userSet0Item->setText("UserSet0");
    userSet0Item->setFlags(userSet0Item->flags() ^ Qt::ItemIsSelectable);
    userSetList->addItem(userSet0Item);
    QListWidgetItem *seperatorItem0 = new QListWidgetItem();
    seperatorItem0->setSizeHint(QSize(100, 3));
    seperatorItem0->setFlags(Qt::NoItemFlags);
    seperatorItem0->setBackground(QColor(46, 50, 60));
    userSetList->addItem(seperatorItem0);
    QListWidgetItem *userSet1Item = new QListWidgetItem();
    userSet1Item->setSizeHint(QSize(100, 27));
    userSet1Item->setText("UserSet1");
    userSet1Item->setFlags(userSet1Item->flags() ^ Qt::ItemIsSelectable);
    userSetList->addItem(userSet1Item);
    QListWidgetItem *seperatorItem1 = new QListWidgetItem();
    seperatorItem1->setSizeHint(QSize(100, 3));
    seperatorItem1->setFlags(Qt::NoItemFlags);
    seperatorItem1->setBackground(QColor(46, 50, 60));
    userSetList->addItem(seperatorItem1);
    connect(userSetList, &UserSetListWidget::currentItemChanged, this,
            &SaveFlirPresetsWindow::currentItemChangedSlot);
    connect(userSetList, &UserSetListWidget::saveUserSetToFile, this,
            &SaveFlirPresetsWindow::saveUserSetToFileSlot);
    connect(userSetList, &UserSetListWidget::loadUserSetFromFile, this,
            &SaveFlirPresetsWindow::loadUserSetFromFileSlot);

    usersetgrouplayout->addWidget(userSetList, 0, 0);

    layout->addWidget(userSetGroup, 0, 0, 1, 3);
    layout->addWidget(buttonSpacer, 1, 0);
    layout->addWidget(saveButton, 1, 1);
    layout->addWidget(closeButton, 1, 2);
}

QString SaveFlirPresetsWindow::getActivePreset() {
    return userSetList->currentItem()->text();
}

void SaveFlirPresetsWindow::saveSetClickedSlot() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "", "Overwrite this UserSet?\n",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        m_cam->savePreset(userSetList->currentItem()->text());
    }
}

void SaveFlirPresetsWindow::saveUserSetToFileSlot(const QString &userSet) {
    QFileDialog fd(this);
    QString cameraName = m_cam->cameraName();
    QString fileName = fd.getSaveFileName(this, "Save" + userSet,
                                          cameraName + "_" + userSet + ".bin",
                                          tr("BIN Files (*.bin)"));
    fd.setAcceptMode(QFileDialog::AcceptSave);
    std::cout << fileName.toStdString() << std::endl;
    if (fileName != "") {
        m_cam->saveUserSetToFile(userSet, fileName);
    }
}

void SaveFlirPresetsWindow::loadUserSetFromFileSlot(const QString &userSet) {
    QFileDialog fd(this);
    QString cameraName = m_cam->cameraName();
    QString fileName = fd.getOpenFileName(this, "Load " + userSet, "",
                                          tr("BIN Files (*.bin)"));
    if (fileName != "") {
        m_cam->loadUserSetFromFile(userSet, fileName);
    }
}

void SaveFlirPresetsWindow::currentItemChangedSlot(QListWidgetItem *current,
                                                   QListWidgetItem *previous) {
    if (current != nullptr) {
        current->setBackground(QColor(100, 164, 32));
    }
    if (previous != nullptr) {
        previous->setBackground(QColor(34, 36, 40));
    }
}
