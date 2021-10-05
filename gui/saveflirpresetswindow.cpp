/*****************************************************************
 * File:			  saveflirpresetswindow.cpp
 * Created: 	  23. October 2020
 * Author:		  Timo Hueser
 * Contact: 	  timo.hueser@gmail.com
 * Copyright:  2021 Timo Hueser
 * License:    GPL v3.0
 *****************************************************************/

#include "saveflirpresetswindow.hpp"

#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QHeaderView>
#include <QToolButton>
#include <QMessageBox>
#include <QGroupBox>

SaveFlirPresetsWindow::SaveFlirPresetsWindow(QWidget *parent) :  SaveCameraPresetsInterface(parent) {
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	this->resize(600,400);
	this->setMinimumSize(600,200);
	QGridLayout *layout = new QGridLayout(this);

	QWidget *buttonSpacer = new QWidget(this);
	buttonSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	saveButton = new QPushButton("Save");
	saveButton->setMinimumSize(30,30);
	closeButton = new QPushButton("Close");
	closeButton->setMinimumSize(30,30);

	QGroupBox *userSetGroup = new QGroupBox("User Sets");
	QGridLayout *usersetgrouplayout = new QGridLayout(userSetGroup);
	usersetgrouplayout->setMargin(2);

	userSetList = new QListWidget(this);
	usersetgrouplayout->addWidget(userSetList,0,0);

	layout->addWidget(userSetGroup,0,0,1,3);
	layout->addWidget(buttonSpacer,1,0);
	layout->addWidget(saveButton,1,1);
	layout->addWidget(closeButton,1,2);
}
