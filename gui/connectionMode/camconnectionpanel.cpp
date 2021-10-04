/*****************************************************************
 * File:			  camconnectionpanelwidget.cpp
 * Created: 	  23. October 2020
 * Author:		  Timo Hueser
 * Contact: 	  timo.hueser@gmail.com
 * Copyright:  	2021 Timo Hueser
 * License:    	GPL v3.0
 *****************************************************************/

#include "camconnectionpanel.hpp"
#include "globals.hpp"
#include "flirchameleonconfig.hpp"
#include "camtestconfig.hpp"

#include <QErrorMessage>



CamConnectionPanel::CamConnectionPanel(QWidget *parent) : QFrame(parent, Qt::Window) {
	statusLogWindow = new StatusLogWindow(this);
	connect(statusLogWindow, SIGNAL(logsCleared()), this, SLOT(logsClearedSlot()));

	QGridLayout *panellayout = new QGridLayout(this);
	stackWidget = new QStackedWidget(this);
	panellayout->addWidget(stackWidget,0,0);
	setLayout(panellayout);

	addButton = new QPushButton(stackWidget);
	connect(addButton, SIGNAL(clicked()), this, SLOT(addClickedSlot()));
	addButton->setIcon(QIcon::fromTheme("add"));
	addButton->setIconSize(QSize(100,100));
	addButton->setStyleSheet("QPushButton {border-radius: 10px;"
																				"border: 4px solid rgb(32,100,164);}"
													 "QPushButton:hover{ background-color: rgb(68,74,89);}");

	camConfigureContainer = new QWidget(stackWidget);
	QGridLayout *camconfigurecontainerlayout = new QGridLayout(camConfigureContainer);
	configToolBar = new QToolBar(this);
	configToolBar->setFixedHeight(40);
	configToolBar->setIconSize(QSize(25,25));
	QLabel *configToolBarLabel = new QLabel("Configure...");
	configToolBarLabel->setFont(fonts["big"]);
	QWidget *configSpacer = new QWidget();
	configSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	confirmButton = new QToolButton(this);
	confirmAction = new QAction(this);
	createToolBarButton(confirmButton, confirmAction, QIcon::fromTheme("check"),
				true, false, QSize(35,35));
	connect(confirmAction, &QAction::triggered,
					this, &CamConnectionPanel::confirmConfigClickedSlot);
	exitButton = new QToolButton(this);
	exitAction = new QAction(this);
	createToolBarButton(exitButton, exitAction, QIcon::fromTheme("discard"),
				true, false, QSize(35,35));
	connect(exitAction, &QAction::triggered,
					this, &CamConnectionPanel::exitConfigClickedSlot);
	configToolBar->addWidget(configToolBarLabel);
	configToolBar->addWidget(configSpacer);
	configToolBar->addWidget(confirmButton);
	configToolBar->addWidget(exitButton);
	camConfigureWidget = new QWidget(camConfigureContainer);
	QPalette pal = palette();
	pal.setColor(QPalette::Background, QColor(22, 24, 26));
	camConfigureWidget->setAutoFillBackground(true);
	camConfigureWidget->setPalette(pal);
	camconfigurelayout = new QGridLayout(camConfigureWidget);
	QWidget *configureBottomSpacer = new QWidget(camConfigureWidget);
	configureBottomSpacer->setSizePolicy(QSizePolicy::Expanding,
																			 QSizePolicy::Expanding);
	QLabel *camNameLabel = new QLabel("Camera Name", camConfigureWidget);
	camNameEdit = new QLineEdit(camConfigureWidget);
	camNameEdit->setPlaceholderText("Enter Name...");
	QLabel *camTypeLabel = new QLabel("Camera Type", camConfigureWidget);
	camTypeCombo = new QComboBox(camConfigureWidget);
  camTypeCombo->addItem("FLIR Chameleon");
	camTypeCombo->addItem("Test Camera");
  camConfigInterface = new FlirChameleonConfig(this);
	connect(camTypeCombo, &QComboBox::currentTextChanged,
					this, &CamConnectionPanel::typeComboChangedSlot);

	camInfoContainer = new QWidget(stackWidget);
	QGridLayout *caminfocontainerlayout = new QGridLayout(camInfoContainer);
	infoToolBar = new QToolBar(this);
	infoToolBar->setFixedHeight(40);
	infoToolBar->setIconSize(QSize(25,25));
	infoToolBarLabel = new QLineEdit(infoToolBar);
	infoToolBarLabel->setFont(fonts["big"]);
	infoToolBarLabel->setFrame(false);
	infoToolBarLabel->installEventFilter(this);
	infoToolBarLabel->setReadOnly(true);
	connect(infoToolBarLabel, &QLineEdit::editingFinished,
					this, &CamConnectionPanel::nameEditedSlot);
	QWidget	*infoSpacer = new QWidget();
	infoSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	deleteButton = new QToolButton(this);
	deleteAction = new QAction(this);
	createToolBarButton(deleteButton, deleteAction, QIcon::fromTheme("discard"),
				true, false, QSize(35,35));
	connect(deleteAction, &QAction::triggered,
					this, &CamConnectionPanel::deleteCamClickedSlot);
	infoToolBar->addWidget(infoToolBarLabel);
	infoToolBar->addWidget(infoSpacer);
	infoToolBar->addWidget(deleteButton);
	camInfoWidget = new QWidget(camInfoContainer);
	camInfoWidget->setAutoFillBackground(true);
	camInfoWidget->setPalette(pal);
	caminfolayout = new QGridLayout(camInfoWidget);
	QWidget *infoBottomSpacer = new QWidget(camConfigureWidget);
	infoBottomSpacer->setSizePolicy(QSizePolicy::Expanding,
																	QSizePolicy::Expanding);
	QLabel *camStatusInfoLabel = new QLabel("Status:", camInfoWidget);
	camStatusInfoIcon = new QLabel(camInfoWidget);
	camStatusInfo = new QLabel(camInfoWidget);
	camStatusButton = new QPushButton("Show Log...", camInfoWidget);
	connect(camStatusButton, &QPushButton::clicked,
					this, &CamConnectionPanel::showLogClickedSlot);
	QWidget *camStatusSpacer = new QWidget(camInfoWidget);
	camStatusSpacer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	camStatusInfoIcon->setPixmap(statusIcons[Connecting].pixmap(QSize(20, 20)));
	camStatusInfo->setText(statusTexts[Connecting]);

	int i = 0;
	camconfigurelayout->addWidget(camNameLabel,i,0);
	camconfigurelayout->addWidget(camNameEdit,i++,1);
	camconfigurelayout->addWidget(camTypeLabel,i,0);
	camconfigurelayout->addWidget(camTypeCombo,i++,1);
	camconfigurelayout->addWidget(camConfigInterface->configEditBox, i++, 0,1,2);
	camconfigurelayout->addWidget(configureBottomSpacer,i,0,1,2);
	camconfigurecontainerlayout->addWidget(configToolBar,0,0);
	camconfigurecontainerlayout->addWidget(camConfigureWidget,1,0);
	camconfigurecontainerlayout->setSpacing(0);
	camconfigurecontainerlayout->setMargin(0);

	i = 0;
	caminfolayout->addWidget(camConfigInterface->configInfoBox,i++,0,1,5);
	caminfolayout->addWidget(camStatusInfoLabel,i,0);
	caminfolayout->addWidget(camStatusInfoIcon,i,1);
	caminfolayout->addWidget(camStatusInfo,i,2);
	caminfolayout->addWidget(camStatusSpacer,i,3);
	caminfolayout->addWidget(camStatusButton,i++,4);
	caminfolayout->addWidget(infoBottomSpacer,i++,0,1,2);
	caminfocontainerlayout->addWidget(infoToolBar,0,0);
	caminfocontainerlayout->addWidget(camInfoWidget,1,0);
	caminfocontainerlayout->setSpacing(0);
	caminfocontainerlayout->setMargin(0);

	stackWidget->addWidget(addButton);
	stackWidget->addWidget(camConfigureContainer);
	stackWidget->addWidget(camInfoContainer);
	stackWidget->setCurrentIndex(0);
	typeComboChangedSlot(camTypeCombo->currentText());
}


CamConnectionPanel::~CamConnectionPanel() {
	CameraInterface::cameraList.removeAll(camera);
	delete camera;
	camera = nullptr;
	delete statusLogWindow;
  std::cout << "destroying connection panel" << std::endl;
}

void CamConnectionPanel::addClickedSlot() {
	stackWidget->setCurrentIndex(1);
}


void CamConnectionPanel::exitConfigClickedSlot() {
	stackWidget->setCurrentIndex(0);
}


void CamConnectionPanel::confirmConfigClickedSlot() {
	QString cameraName;
	if (camNameEdit->text() == "") cameraName = "Camera_" +
				QString::number(CameraInterface::cameraList.size());
	else cameraName = camNameEdit->text();
  if (camConfigInterface->confirmConfigClicked()) {
		camera = camConfigInterface->getCamera(cameraName);
		connect(camera, &CameraInterface::statusUpdated,
						this, &CamConnectionPanel::statusUpdatedSlot);
		infoToolBarLabel->setText(cameraName);
		CameraInterface::cameraList.append(camera);

		statusLog statusLog;
		statusLog.type = Connecting;
		statusLog.time = new QTime(0,0);
		statusLog.time->restart();
		statusLog.message = "";
		statusLogWindow->statusLogList.push_back(statusLog);
		stackWidget->setCurrentIndex(2);
		emit camListChanged();
		emit camAdded(camera);
	}
	else {
		QErrorMessage errorMessage;
		errorMessage.showMessage(
		"No camera selected! Make sure there is a camera plugged in and you're usb permissions are set correctly!");
		errorMessage.exec();
		return;
	}
}


void CamConnectionPanel::deleteCamClickedSlot() {
	CameraInterface::cameraList.removeAll(camera);
	delete camera;
	camera = nullptr;
	stackWidget->setCurrentIndex(0);
	camStatusInfoIcon->setPixmap(statusIcons[Connecting].pixmap(QSize(20, 20)));
	camStatusInfo->setText(statusTexts[Connecting]);
	emit camListChanged();
}


void CamConnectionPanel::typeComboChangedSlot(QString type) {
  QLayoutItem *item = camconfigurelayout->takeAt(camconfigurelayout->
				indexOf(camConfigInterface->configEditBox));
  delete item->widget();
  delete item;
  QLayoutItem *infoItem = caminfolayout->takeAt(caminfolayout->
				indexOf(camConfigInterface->configInfoBox));
  delete infoItem->widget();
  delete infoItem;
	delete camConfigInterface;
  if (type == "Test Camera") {
    camConfigInterface = new CamTestConfig(this);
  }
  else if (type == "FLIR Chameleon") {
    camConfigInterface = new FlirChameleonConfig(this);
  }
  camconfigurelayout->addWidget(camConfigInterface->configEditBox, 2, 0,1,2);
  caminfolayout->addWidget(camConfigInterface->configInfoBox,0,0,1,5);
}


void CamConnectionPanel::nameEditedSlot() {
	camera->setCameraName(infoToolBarLabel->text());
	infoToolBarLabel->setReadOnly(true);
	emit camListChanged();
}


void CamConnectionPanel::statusUpdatedSlot(statusType status,
																					 QString statusMessage) {
	camera->setCameraStatus(status);
	camStatusInfoIcon->setPixmap(statusIcons[status].pixmap(QSize(20, 20)));
	camStatusInfo->setText(statusTexts[status]);
	statusLog statusLog;
	statusLog.type = status;
	statusLog.time = new QTime(0,0);
	statusLog.time->restart();
	statusLog.message = statusMessage;
	statusLogWindow->statusLogList.push_back(statusLog);
	statusLogWindow->updateListSlot();
	emit statusUpdated(camera, status, statusMessage);
}


void CamConnectionPanel::showLogClickedSlot() {
	statusLogWindow->updateListSlot();
	statusLogWindow->show();
}


void CamConnectionPanel::logsClearedSlot() {
	camStatusInfoIcon->setPixmap(statusIcons[Ready].pixmap(QSize(20, 20)));
	camStatusInfo->setText(statusTexts[Ready]);
	emit statusUpdated(camera, Ready, statusTexts[Ready]);
}


bool CamConnectionPanel::eventFilter(QObject* object, QEvent* event) {
    if(object == infoToolBarLabel && event->type() == QEvent::MouseButtonDblClick) {
			infoToolBarLabel->setReadOnly(false);
        return false;
    }
    return false;
}
