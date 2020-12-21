/*------------------------------------------------------------
 *  mainbar.cpp
 *  Created:  27. October 2020
 *  Author:   Timo Hüser
 * *------------------------------------------------------------*/

#include "mainbar.hpp"

MainBar::MainBar(QWidget *parent) : QToolBar(parent) {
	this->setFixedHeight(60);
	this->setMovable(false);

	QLabel *iconLabel = new QLabel(this);
	iconLabel->setPixmap(QIcon("icons/hand.png").pixmap(50,50));
	QWidget *nameSpacer = new QWidget(this);
	nameSpacer->setMinimumSize(5,5);
	QLabel *nameLabel = new QLabel(this);
	nameLabel->setFont(fonts["headline"]);
	nameLabel->setText("<font color=#2664a3>Camera</font><font color=#64a420>Controller</font>");
	QWidget *spacer = new QWidget();
	spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	settingsButton = new QToolButton(this);
	settingsAction = new QAction(this);
	createToolBarButton(settingsButton, settingsAction, QIcon("icons/settings.png"),
				true, false, QSize(50,50));
	this->addWidget(iconLabel);
	this->addWidget(nameSpacer);
	this->addWidget(nameLabel);
	this->addWidget(spacer);
	this->addWidget(settingsButton);
}
