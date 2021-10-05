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

LoadFlirPresetsWindow::LoadFlirPresetsWindow(QWidget *parent) :  LoadCameraPresetsInterface(parent) {
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	this->resize(600,400);
	this->setMinimumSize(600,200);
	QGridLayout *layout = new QGridLayout(this);
	QLabel *testLabel = new QLabel("HELOOOO from loading");
	layout->addWidget(testLabel,0,0);
}
