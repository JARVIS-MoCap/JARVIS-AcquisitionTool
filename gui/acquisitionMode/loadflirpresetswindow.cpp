/*****************************************************************
 * File:			  loadflirpresetswindow.cpp
 * Created: 	  23. October 2020
 * Author:		  Timo Hueser
 * Contact: 	  timo.hueser@gmail.com
 * Copyright:  2021 Timo Hueser
 * License:    GPL v3.0
 *****************************************************************/

#include "loadflirpresetswindow.hpp"

#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QHeaderView>
#include <QToolButton>
#include <QMessageBox>
#include <QGroupBox>

LoadFlirPresetsWindow::LoadFlirPresetsWindow(FLIRChameleon *cam, QWidget *parent) :  LoadCameraPresetsInterface(parent), m_cam(cam) {
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	this->resize(600,400);
	this->setMinimumSize(600,200);
	QGridLayout *layout = new QGridLayout(this);

	QWidget *buttonWidget = new QWidget(this);
	QGridLayout *buttonlayout = new QGridLayout(buttonWidget);
	QWidget *buttonSpacer = new QWidget(this);
	buttonSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	loadButton = new QPushButton("Load");
	loadButton->setIcon(QIcon::fromTheme("download"));
	loadButton->setMinimumSize(30,30);
	connect (loadButton, &QPushButton::clicked, this, &LoadFlirPresetsWindow::loadClickedSlot);
	closeButton = new QPushButton("Close");
	closeButton->setIcon(QIcon::fromTheme("discard"));
	closeButton->setMinimumSize(30,30);
	connect(closeButton, &QPushButton::clicked, this, &LoadFlirPresetsWindow::accept);
	buttonlayout->addWidget(buttonSpacer,0,0);
	buttonlayout->addWidget(loadButton,0,1);
	buttonlayout->addWidget(closeButton,0,2);


	QGroupBox *userSetGroup = new QGroupBox("User Sets");
	QGridLayout *usersetgrouplayout = new QGridLayout(userSetGroup);
	usersetgrouplayout->setMargin(2);

	userSetList = new QListWidget(this);
	QListWidgetItem * defaultItem = new QListWidgetItem();
	defaultItem->setSizeHint(QSize (100, 27));
	defaultItem->setText("Default");
	defaultItem->setFlags(defaultItem->flags() ^ Qt::ItemIsSelectable);
	userSetList->addItem(defaultItem);
	QListWidgetItem * defaultSeperatorItem = new QListWidgetItem();
	defaultSeperatorItem->setSizeHint(QSize (100, 3));
	defaultSeperatorItem->setFlags(Qt::NoItemFlags);
	defaultSeperatorItem->setBackground(QColor(46, 50, 60));
	userSetList->addItem(defaultSeperatorItem);
	QListWidgetItem * userSet0Item = new QListWidgetItem();
	userSet0Item->setSizeHint(QSize (100, 27));
	userSet0Item->setText("UserSet0");
	userSet0Item->setFlags(userSet0Item->flags() ^ Qt::ItemIsSelectable);
	userSetList->addItem(userSet0Item);
	QListWidgetItem * seperatorItem0 = new QListWidgetItem();
	seperatorItem0->setSizeHint(QSize (100, 3));
	seperatorItem0->setFlags(Qt::NoItemFlags);
	seperatorItem0->setBackground(QColor(46, 50, 60));
	userSetList->addItem(seperatorItem0);
	QListWidgetItem * userSet1Item = new QListWidgetItem();
	userSet1Item->setSizeHint(QSize (100, 27));
	userSet1Item->setText("UserSet1");
	userSet1Item->setFlags(userSet1Item->flags() ^ Qt::ItemIsSelectable);
	userSetList->addItem(userSet1Item);
	QListWidgetItem * seperatorItem1 = new QListWidgetItem();
	seperatorItem1->setSizeHint(QSize (100, 3));
	seperatorItem1->setFlags(Qt::NoItemFlags);
	seperatorItem1->setBackground(QColor(46, 50, 60));
	userSetList->addItem(seperatorItem1);
	connect(userSetList, &QListWidget::currentItemChanged, this, &LoadFlirPresetsWindow::currentItemChangedSlot);
	usersetgrouplayout->addWidget(userSetList,0,0);

	QLabel *defaultUserSetLabel = new QLabel("Default User Set (loaded on powerup):  ");
	defaultUserSetCombo = new QComboBox(this);
	defaultUserSetCombo->addItem("Default");
	defaultUserSetCombo->addItem("UserSet0");
	defaultUserSetCombo->addItem("UserSet1");
	connect(defaultUserSetCombo, &QComboBox::currentTextChanged, this, &LoadFlirPresetsWindow::defaultUserSetChangedSlot);

	layout->addWidget(userSetGroup,0,0,1,2);
	layout->addWidget(defaultUserSetLabel,1,0);
	layout->addWidget(defaultUserSetCombo,1,1);
	layout->addWidget(buttonWidget,2,0,1,2);
	getDefaultUserSet();
}


void LoadFlirPresetsWindow::loadClickedSlot() {
	if (userSetList->currentItem() != nullptr) {
		m_cam->loadPreset(userSetList->currentItem()->text());
	}
}


void LoadFlirPresetsWindow::currentItemChangedSlot(QListWidgetItem *current,
			QListWidgetItem *previous) {
	if (current != nullptr) {
		current->setBackground(QColor(100,164,32));
	}
	if (previous != nullptr) {
		previous->setBackground(QColor(34, 36, 40));
	}
}

void LoadFlirPresetsWindow::getDefaultUserSet() {
	defaultUserSetCombo->setCurrentText(m_cam->getDefaultUserSet());
}

void LoadFlirPresetsWindow::defaultUserSetChangedSlot(const QString & userSet) {
	m_cam->setDefaultUserSet(userSet);
}
