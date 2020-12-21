/*------------------------------------------------------------
 *  calibrationwidget.cpp
 *  Created:  11. November 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#include "calibrationwidget.hpp"
#include "camerainterface.hpp"

#include <QLabel>
#include <QToolBar>
#include <QSplitter>
#include <QStackedWidget>

CalibrationWidget::CalibrationWidget(QWidget *parent) : QWidget(parent) {
	QGridLayout *layout = new QGridLayout(this);
	layout->setMargin(0);
	settings = new QSettings();
	QSplitter *mainSplitter = new QSplitter(this);
	layout->addWidget(mainSplitter,0,0);
	QWidget *listWidget = new QWidget(mainSplitter);
	QGridLayout *listlayout = new QGridLayout(listWidget);
	listlayout->setMargin(0);

	QToolBar *toolBar = new QToolBar(this);
	toolBar->setFixedHeight(45);
	QLabel * cameraLabel = new QLabel("Camera");
	cameraLabel->setFont(fonts["verybig"]);
	toolBar->addWidget(cameraLabel);
	cameraList = new QListWidget();
	//primaryList->setStyleSheet("QListWidget::item {border-top: 2px solid palette(highlight);}");
	connect(cameraList, &QListWidget::itemDoubleClicked, this, &CalibrationWidget::listSelectedSlot);

	listlayout->addWidget(toolBar,0,0);
	listlayout->addWidget(cameraList,1,0);

	selectionInfoWidget = new QWidget(this);
	selectionInfoWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QSpacerItem *infoTopSpacer = new QSpacerItem(100,300,QSizePolicy::Maximum,QSizePolicy::Maximum);
	QSpacerItem *infoBottomSpacer = new QSpacerItem(100,100,QSizePolicy::Expanding,QSizePolicy::Expanding);
	QGridLayout *infolayout = new QGridLayout(selectionInfoWidget);
	QLabel *infoLabel = new QLabel("Select a camera for intrinsics calibration");
	infoLabel->setAlignment(Qt::AlignCenter);
	infoLabel->setFont(fonts["infotext"]);
	infoLabel->setStyleSheet("QLabel {color: rgb(32,100,164)}");
	infolayout->addItem(infoTopSpacer,0,0);
	infolayout->addWidget(infoLabel,1,0);
	infolayout->addItem(infoBottomSpacer,2,0);

	loadNewWidget = new QWidget(this);
	QSpacerItem *loadNewTopSpacer = new QSpacerItem(100,300,QSizePolicy::Maximum,QSizePolicy::Maximum);
	QSpacerItem *loadNewBottomSpacer = new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Expanding);
	QGridLayout *loadnewlayout = new QGridLayout(loadNewWidget);
	loadnewlayout->setSpacing(16);
	QLabel *loadNewLabel = new QLabel("Load existing calibration or create new one?");
	loadNewLabel->setFont(fonts["infotext"]);
	loadNewLabel->setStyleSheet("QLabel {color: rgb(32,100,164)}");
	loadCalibrationButton = new QPushButton("Load Calibration");
	loadCalibrationButton->setMinimumSize(450,80);
	loadCalibrationButton->setFont(fonts["headline"]);
	loadCalibrationButton->setStyleSheet(" QPushButton { border-radius: 10px; border: 4px solid rgb(100,164,32); }"
													 "QPushButton:hover { background-color: rgb(68,74,89); }"
													 "QPushButton { color: rgb(100,164,32);}");
	newCalibrationButton = new QPushButton("New Calibration");
	newCalibrationButton->setMinimumSize(450,80);
	newCalibrationButton->setFont(fonts["headline"]);
	newCalibrationButton->setStyleSheet(" QPushButton { border-radius: 10px; border: 4px solid rgb(100,164,32); }"
													 "QPushButton:hover { background-color: rgb(68,74,89); }"
													 "QPushButton { color: rgb(100,164,32);}");
	connect(newCalibrationButton, &QPushButton::clicked, this, &CalibrationWidget::newCalibrationClickedSlot);
	loadnewlayout->addItem(loadNewTopSpacer,0,0,1,2);
	loadnewlayout->addWidget(loadNewLabel,1,0,1,2,Qt::AlignCenter);
	loadnewlayout->addWidget(loadCalibrationButton,2,0,Qt::AlignRight);
	loadnewlayout->addWidget(newCalibrationButton,2,1,Qt::AlignLeft);
	loadnewlayout->addItem(loadNewBottomSpacer,3,0,1,2);

	calibrationTool = new CalibrationTool();

	stackWidget = new QStackedWidget(mainSplitter);
	stackWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	stackWidget->addWidget(selectionInfoWidget);
	stackWidget->addWidget(loadNewWidget);
	stackWidget->addWidget(calibrationTool);

	mainSplitter->addWidget(listWidget);
	mainSplitter->addWidget(stackWidget);
	mainSplitter->setSizes({250,1000});

	//--- SIGNAL-SLOT Connections ---//
	//-> Incoming Signals

	//<- Outgoing Signals
	connect(this, &CalibrationWidget::cameraSelected, calibrationTool, &CalibrationTool::cameraSelectedSlot);

	//<-> Relayed Signals
}

void CalibrationWidget::camListChangedSlot() {
	//maybe check why this gets triggered so often!!
	cameraList->clear();
	for (const auto& cam : CameraInterface::cameraList) {
		QListWidgetItem * camItem = new QListWidgetItem();
		camItem->setSizeHint(QSize (100, 50));
		camItem->setText(cam->cameraName());
		camItem->setFlags(camItem->flags() ^ Qt::ItemIsSelectable);
		cameraList->addItem(camItem);
		QListWidgetItem * seperatorItem = new QListWidgetItem();
		seperatorItem->setSizeHint(QSize (100, 2));
		seperatorItem->setFlags(Qt::NoItemFlags);
		seperatorItem->setBackground(QColor(46, 50, 60));
		cameraList->addItem(seperatorItem);
	}
}

void CalibrationWidget::listSelectedSlot(QListWidgetItem * selectedItem) {
	stackWidget->setCurrentIndex(1);
	for (int i = 0;  i < cameraList->count(); i+=2) {
		QListWidgetItem * item = cameraList->item(i);
		if (item == selectedItem) {
			item->setBackground(QColor(100, 164,32));
		}
		else {
			item->setBackground(QColor(34, 36, 40));
		}
	}
	m_camera = CameraInterface::cameraList[cameraList->row(selectedItem)/2];
	emit cameraSelected(m_camera);
}


void CalibrationWidget::newCalibrationClickedSlot() {
	stackWidget->setCurrentIndex(2);
}
