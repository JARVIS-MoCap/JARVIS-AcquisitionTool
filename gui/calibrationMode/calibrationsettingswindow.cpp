/*------------------------------------------------------------
 *  calibrationsettingswindow.cpp
 *  Created: 11. November 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#include "calibrationsettingswindow.hpp"

#include <QLabel>

CalibrationSettingsWindow::CalibrationSettingsWindow(QWidget *parent) : QDockWidget(parent, Qt::Window) {
	this->setMinimumSize(300,300);
	this->setWindowTitle("Calibration Settings");
	mainWidget = new QWidget();
	this->setWidget(mainWidget);
	QGridLayout *layout = new QGridLayout(mainWidget);

	toolBar = new QToolBar(this);
	toolBar->setFixedHeight(40);
	toolBar->setIconSize(QSize(25,25));
	toolBar->setStyleSheet("QToolBar {background-color: palette(base);}");
	QLabel *toolBarLabel = new QLabel("Calibration Settings");
	toolBarLabel->setFont(fonts["bold"]);
	QWidget *spacer = new QWidget();
	spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	toolBar->addWidget(toolBarLabel);
	toolBar->addWidget(spacer);
	this->setTitleBarWidget(toolBar);

	QLabel *boardTypeLabel = new QLabel("Board Type", this);
	boardTypeCombo = new QComboBox(this);
	boardTypeCombo->addItem("Checkerboard");
	boardTypeCombo->addItem("Aruco Bord");
	QLabel *boardWidthLabel = new QLabel("Board Width");
	boardWidthEdit = new QLineEdit(this);
	boardWidthEdit->setText("9");
	QLabel *boardHeightLabel = new QLabel("Board Height");
	boardHeightEdit = new QLineEdit(this);
	boardHeightEdit->setText("6");
	QLabel *sideLengthLabel = new QLabel("Pattern Side Length");
	sideLengthEdit = new QLineEdit(this);
	sideLengthEdit->setText("25.4");

	QWidget *settingsSpacer = new QWidget(this);
	settingsSpacer->setMinimumSize(10,10);
	settingsSpacer->setMaximumSize(10,10);

	QLabel *enableMinimumSizeLabel = new QLabel("Enable min. Detection Size");
	enebaleMinimumSizeToggle = new QCheckBox(this);
	enebaleMinimumSizeToggle->setEnabled(true);
	QLabel *minimumSizeLabel = new QLabel("Minimum Detection Size [px]");
	minimumSizeEdit = new QLineEdit(this);
	minimumSizeEdit->setText("500");

	QWidget *bottomSpacer = new QWidget(this);
	bottomSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	int i = 0;
	layout->addWidget(boardTypeLabel, i,0);
	layout->addWidget(boardTypeCombo, i++,1);
	layout->addWidget(boardWidthLabel,i,0);
	layout->addWidget(boardWidthEdit,i++,1);
	layout->addWidget(boardHeightLabel,i,0);
	layout->addWidget(boardHeightEdit,i++,1);
	layout->addWidget(sideLengthLabel,i,0);
	layout->addWidget(sideLengthEdit,i++,1);
	layout->addWidget(settingsSpacer,i++,0,1,2);
	layout->addWidget(enableMinimumSizeLabel,i,0);
	layout->addWidget(enebaleMinimumSizeToggle,i++,1);
	layout->addWidget(minimumSizeLabel, i,0);
	layout->addWidget(minimumSizeEdit,i++,1);
	layout->addWidget(bottomSpacer,i,0,1,2);



}
