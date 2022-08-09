/*******************************************************************************
 * File:        mainbar.cpp
 * Created:     23. October 2020
 * Author:      Timo Hueser
 * Contact:     timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#ifndef VERSION_STRING
#define VERSION_STRING "unknown version"
#endif

#include "mainbar.hpp"

MainBar::MainBar(QWidget *parent) : QToolBar(parent) {
    this->setFixedHeight(60);
    this->setMovable(false);

    settingsWindow = new SettingsWindow();
    settingsWindow->hide();

    QLabel *iconLabel = new QLabel(this);
    iconLabel->setPixmap(QIcon::fromTheme("hand").pixmap(50, 50));

    QWidget *nameSpacer = new QWidget(this);
    nameSpacer->setMinimumSize(5, 5);

    QLabel *nameLabel = new QLabel(this);
    nameLabel->setFont(QFont("Sans Serif", 20, QFont::Bold));
    nameLabel->setText("<font color=#2664a3>Camera</font>"
                       "<font color=#64a420>Controller</font>");

    QWidget *spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    settingsButton = new QToolButton(this);
    settingsAction = new QAction(this);
    createToolBarButton(settingsButton, settingsAction,
                        QIcon::fromTheme("settings"), true, false,
                        QSize(50, 50));
    connect(settingsAction, &QAction::triggered, this,
            &MainBar::settingsClickedSlot);
    this->addWidget(iconLabel);
    this->addWidget(nameSpacer);
    this->addWidget(nameLabel);
    this->addWidget(spacer);
    this->addWidget(settingsButton);
    this->addSeparator();
}

void MainBar::settingsClickedSlot() {
    settingsWindow->show();
    settingsWindow->raise();
}
