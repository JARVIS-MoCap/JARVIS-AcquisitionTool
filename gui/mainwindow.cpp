/*------------------------------------------------------------
 *  mainwindow.cpp
 *  Created: 23. October 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#include "mainwindow.hpp"
#include "camerainterface.hpp"

#include <QGridLayout>
#include <QCloseEvent>
#include <QSplitter>
#include <QStackedWidget>
#include <QStatusBar>
#include <QMenuBar>
#include <QMessageBox>
#include <QTextStream>

//----- global parameters shared by multiple widgets -----//
QList<CameraInterface*> CameraInterface::cameraList;
TriggerInterface *TriggerInterface::triggerInstance;

QMap<statusType, QIcon> statusIcons;
QMap<statusType, QString>statusTexts;

void createToolBarButton(QToolButton *button, QAction*action, QIcon icon, bool enabled,
			bool checkable, QSize minSize) {
	button->setMinimumSize(minSize);
	button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	action->setCheckable(checkable);
	action->setEnabled(enabled);
	action->setIcon(icon);
	button->setDefaultAction(action);
}


MainWindow::MainWindow(QMainWindow *parent) : QMainWindow(parent) {
	statusIcons = {
		{Connecting, QIcon::fromTheme("connect")},
		{Ready, QIcon::fromTheme("status_good")},
		{Streaming, QIcon::fromTheme("start")},
		{Warning, QIcon::fromTheme("warning")},
		{Error, QIcon::fromTheme("error")}
	};
	statusTexts = {
		{Connecting, "Connecting..."},
		{Ready, "Ready..."},
		{Streaming, "Streaming..."},
		{Warning, "Warning..."},
		{Error, "Error..."}
	};

	this->setMinimumSize(800,800);
	this->showMaximized();
	this->setWindowTitle("Camera Controller");
	this->setWindowIcon(QIcon::fromTheme("hand"));
	statusBar()->showMessage(tr("Ready"), 2000);
	mainBar = new MainBar(this);
	this->addToolBar(mainBar);

	modesWidget = new QTabWidget(this);
	modesWidget->setIconSize(QSize(80,80));
	modesWidget->setTabPosition(QTabWidget::West);
	setCentralWidget(modesWidget);

	acquisitionMode = new AcquisitionMode();
	connectionMode = new ConnectionMode();

	viewerMode = new QMainWindow(modesWidget);

	modesWidget->addTab(connectionMode, QIcon::fromTheme("network"),"");
	modesWidget->setTabToolTip(1, "Connection Mode");
	modesWidget->insertTab(0,acquisitionMode,QIcon::fromTheme("camera"), ""); //added last because resize update issues
	modesWidget->setTabToolTip(0, "Acquisition Mode");
	modesWidget->setCurrentIndex(0);

	//--- SIGNAL-SLOT Connections ---//
	//-> Incoming Signals

	//<- Outgoing Signals

	//<-> Relayed Signals
	connect(connectionMode, &ConnectionMode::triggerInstanceChanged, acquisitionMode, &AcquisitionMode::triggerInstanceChangedSlot);
	connect(connectionMode, &ConnectionMode::camAdded, acquisitionMode, &AcquisitionMode::camAdded);
	connect(connectionMode, &ConnectionMode::camListChanged, acquisitionMode, &AcquisitionMode::camListChanged);
	connect(connectionMode, &ConnectionMode::statusUpdated, acquisitionMode, &AcquisitionMode::statusUpdated);
}


void MainWindow::closeEvent (QCloseEvent *event) {
	QList<QString> activeCamsList;
	for (const auto& cam  : CameraInterface::cameraList) {
		if (cam->isStreaming()) {
			activeCamsList.append(cam->cameraName());
		}
	}
	if (activeCamsList.size() != 0) {
		QMessageBox msgBox;
		QString msg;
		QTextStream msgStream(&msg);
		msgStream << activeCamsList.size();
		if (activeCamsList.size() == 1) msgStream << " Camera is still streaming!";
		else msgStream <<  " Cameras are still streaming!";
		msgBox.setText(msg);
		msgBox.setInformativeText("If you exit now the Recording might not get saved correctly.\nClose anyways?");
		msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Close);
		msgBox.setDefaultButton(QMessageBox::Cancel);
		int ret = msgBox.exec();
		if (ret == QMessageBox::Cancel) {
			event->ignore();
		}
		else {
			for (const auto& cam  : CameraInterface::cameraList){
				cam->stopAcquisitionSlot();
			}
		}
	}
}
