/*****************************************************************
 * File:			  triggerconnectionpanel.cpp
 * Created: 	  03. October 2021
 * Author:		  Timo Hueser
 * Contact: 	  timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     GPL v3.0
 *****************************************************************/

#include "globals.hpp"
#include "triggerconnectionpanel.hpp"
#include "triggerinterface.hpp"
#include "triggertestconfig.hpp"
#include "arduinotriggerconfig.hpp"
#include <QErrorMessage>

TriggerConnectionPanel::TriggerConnectionPanel(QWidget *parent) :
			QFrame(parent, Qt::Window) {
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	statusLogWindow = new StatusLogWindow(this);
	connect(statusLogWindow, &StatusLogWindow::logsCleared,
					this, &TriggerConnectionPanel::logsClearedSlot);
	QGridLayout *panellayout = new QGridLayout(this);
	stackWidget = new QStackedWidget(this);
	panellayout->addWidget(stackWidget,0,0);
	setLayout(panellayout);

	addButton = new QPushButton(stackWidget);
	connect(addButton, &QPushButton::clicked,
					this, &TriggerConnectionPanel::addClickedSlot);
	addButton->setIcon(QIcon::fromTheme("add_green"));
	addButton->setIconSize(QSize(100,100));
	addButton->setStyleSheet("QPushButton{border-radius: 10px;"
													 "border: 4px solid rgb(100,164,32);}"
													 "QPushButton:hover{background-color:rgb(68,74,89);}");

	triggerConfigureContainer = new QWidget(stackWidget);
	QGridLayout *triggerconfigurecontainerlayout =
				new QGridLayout(triggerConfigureContainer);
	configToolBar = new QToolBar(this);
	configToolBar->setFixedHeight(40);
	configToolBar->setIconSize(QSize(25,25));
	QLabel *configToolBarLabel = new QLabel("Configure...");
	configToolBarLabel->setFont(QFont("Sans Serif", 12, QFont::Bold));
	QWidget *configSpacer = new QWidget();
	configSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	confirmButton = new QToolButton(this);
	confirmAction = new QAction(this);
	createToolBarButton(confirmButton, confirmAction, QIcon::fromTheme("check"),
				true, false, QSize(35,35));
	connect(confirmAction, &QAction::triggered,
					this, &TriggerConnectionPanel::confirmConfigClickedSlot);
	exitButton = new QToolButton(this);
	exitAction = new QAction(this);
	createToolBarButton(exitButton, exitAction, QIcon::fromTheme("discard"),
				true, false, QSize(35,35));
	connect(exitAction, &QAction::triggered,
					this, &TriggerConnectionPanel::exitConfigClickedSlot);
	configToolBar->addWidget(configToolBarLabel);
	configToolBar->addWidget(configSpacer);
	configToolBar->addWidget(confirmButton);
	configToolBar->addWidget(exitButton);
	triggerConfigureWidget = new QWidget(triggerConfigureContainer);
	QPalette pal = palette();
	pal.setColor(QPalette::Background, QColor(22, 24, 26));
	triggerConfigureWidget->setAutoFillBackground(true);
	triggerConfigureWidget->setPalette(pal);
	triggerconfigurelayout = new QGridLayout(triggerConfigureWidget);
	configureBottomSpacer = new QWidget(triggerConfigureWidget);
	configureBottomSpacer->setSizePolicy(QSizePolicy::Expanding,
																			 QSizePolicy::Expanding);
	QLabel *triggerTypeLabel = new QLabel("Trigger Type", triggerConfigureWidget);
	triggerTypeCombo = new QComboBox(triggerConfigureWidget);
	triggerTypeCombo->addItem("Arduino Trigger");
	triggerTypeCombo->addItem("Test Trigger");
	triggerConfigInterface = new ArduinoTriggerConfig(this);


	connect(triggerTypeCombo, &QComboBox::currentTextChanged,
					this, &TriggerConnectionPanel::typeComboChangedSlot);
	triggerconfigurecontainerlayout->addWidget(configToolBar,0,0);
	triggerconfigurecontainerlayout->addWidget(triggerConfigureWidget,1,0);
	triggerconfigurecontainerlayout->setSpacing(0);
	triggerconfigurecontainerlayout->setMargin(0);

	triggerInfoContainer = new QWidget(stackWidget);
	QGridLayout *triggerinfocontainerlayout =
				new QGridLayout(triggerInfoContainer);
	infoToolBar = new QToolBar(this);
	infoToolBar->setFixedHeight(40);
	infoToolBar->setIconSize(QSize(25,25));
	QLabel *infoToolBarLabel = new QLabel("Trigger");
	infoToolBarLabel->setFont(QFont("Sans Serif", 12, QFont::Bold));
	QWidget	*infoSpacer = new QWidget();
	infoSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	deleteButton = new QToolButton(this);
	deleteAction = new QAction(this);
	createToolBarButton(deleteButton, deleteAction, QIcon::fromTheme("discard"),
				true, false, QSize(35,35));
	connect(deleteAction, &QAction::triggered,
					this, &TriggerConnectionPanel::deleteTriggerClickedSlot);
	infoToolBar->addWidget(infoToolBarLabel);
	infoToolBar->addWidget(infoSpacer);
	infoToolBar->addWidget(deleteButton);
	triggerInfoWidget = new QWidget(triggerInfoContainer);
	triggerInfoWidget->setAutoFillBackground(true);
	triggerInfoWidget->setPalette(pal);
	triggerinfolayout = new QGridLayout(triggerInfoWidget);
	infoBottomSpacer = new QWidget(triggerConfigureWidget);
	infoBottomSpacer->setSizePolicy(QSizePolicy::Expanding,
																	QSizePolicy::Expanding);
	QLabel *triggerStatusInfoLabel = new QLabel("Status:", triggerInfoWidget);
	triggerStatusInfoIcon = new QLabel(triggerInfoWidget);
	triggerStatusInfo = new QLabel(triggerInfoWidget);
	triggerStatusButton = new QPushButton("Show Log...", triggerInfoWidget);
	connect(triggerStatusButton, &QPushButton::clicked,
					this, &TriggerConnectionPanel::showLogClickedSlot);
	QWidget *triggerStatusSpacer = new QWidget(triggerInfoWidget);
	triggerStatusSpacer->setSizePolicy(QSizePolicy::Expanding,
																		 QSizePolicy::Preferred);
	triggerStatusInfoIcon->setPixmap(statusIcons[Connecting].pixmap(QSize(20,20)));
	triggerStatusInfo->setText(statusTexts[Connecting]);

	//createTestBoxes();

	int i = 0;
	triggerconfigurelayout->addWidget(triggerTypeLabel,i,0);
	triggerconfigurelayout->addWidget(triggerTypeCombo,i++,1);
	triggerconfigurelayout->addWidget(triggerConfigInterface->configEditBox, i++, 0,1,2);
	triggerconfigurelayout->addWidget(configureBottomSpacer,i,0,1,2);
	triggerconfigurecontainerlayout->addWidget(configToolBar,0,0);
	triggerconfigurecontainerlayout->addWidget(triggerConfigureWidget,1,0);
	triggerconfigurecontainerlayout->setSpacing(0);
	i = 0;
	triggerinfolayout->addWidget(triggerConfigInterface->configInfoBox, i++,0,1,5);
	triggerinfolayout->addWidget(triggerStatusInfoLabel,i,0);
	triggerinfolayout->addWidget(triggerStatusInfoIcon,i,1);
	triggerinfolayout->addWidget(triggerStatusInfo,i,2);
	triggerinfolayout->addWidget(triggerStatusSpacer,i,3);
	triggerinfolayout->addWidget(triggerStatusButton,i++,4);
	triggerinfolayout->addWidget(infoBottomSpacer,i++,0,1,5);
	triggerinfocontainerlayout->addWidget(infoToolBar,0,0);
	triggerinfocontainerlayout->addWidget(triggerInfoWidget,1,0);
	triggerinfocontainerlayout->setSpacing(0);
	triggerinfocontainerlayout->setMargin(0);

	stackWidget->addWidget(addButton);
	stackWidget->addWidget(triggerConfigureContainer);
	stackWidget->addWidget(triggerInfoContainer);
	stackWidget->setCurrentIndex(0);
	typeComboChangedSlot(triggerTypeCombo->currentText());
}

TriggerConnectionPanel::~TriggerConnectionPanel() {
	delete TriggerInterface::triggerInstance;
	TriggerInterface::triggerInstance = nullptr;
	delete statusLogWindow;
}


void TriggerConnectionPanel::addClickedSlot() {
	stackWidget->setCurrentIndex(1);
}

void TriggerConnectionPanel::exitConfigClickedSlot() {
	stackWidget->setCurrentIndex(0);
}

void TriggerConnectionPanel::confirmConfigClickedSlot() {
	if (triggerConfigInterface->confirmConfigClicked()) {
		TriggerInterface::triggerInstance = triggerConfigInterface->getTrigger();
		connect(TriggerInterface::triggerInstance, SIGNAL(statusUpdated(statusType, QString)), this, SLOT(statusUpdatedSlot(statusType, QString)));
	}
	else {
		QErrorMessage errorMessage;
    errorMessage.showMessage(
	  "No trigger device selected! Make sure your device is plugged in and configured correctly!");
    errorMessage.exec();
		return;
	}

	statusLog statusLog;
	statusLog.type = Connecting;
	statusLog.time = new QTime(0,0);
	statusLog.time->restart();
	statusLog.message = "";
	statusLogWindow->statusLogList.push_back(statusLog);
	stackWidget->setCurrentIndex(2);
	emit triggerInstanceChanged();
}

void TriggerConnectionPanel::deleteTriggerClickedSlot() {
	delete TriggerInterface::triggerInstance;
	TriggerInterface::triggerInstance = nullptr;
	stackWidget->setCurrentIndex(0);
	triggerStatusInfoIcon->setPixmap(statusIcons[Connecting].pixmap(QSize(20, 20)));
	triggerStatusInfo->setText(statusTexts[Connecting]);
	emit triggerInstanceChanged();
}

void TriggerConnectionPanel::typeComboChangedSlot(QString type) {
	QLayoutItem *item = triggerconfigurelayout->takeAt(triggerconfigurelayout->
				indexOf(triggerConfigInterface->configEditBox));
	QLayoutItem *spacerItem = triggerconfigurelayout->takeAt(triggerconfigurelayout->
				indexOf(configureBottomSpacer));
  delete item->widget();
  delete item;
  QLayoutItem *infoItem = triggerinfolayout->takeAt(triggerinfolayout->
				indexOf(triggerConfigInterface->configInfoBox));
  delete infoItem->widget();
  delete infoItem;
	delete triggerConfigInterface;
  if (type == "Arduino Trigger") {
     triggerConfigInterface = new ArduinoTriggerConfig(this);
  }
	else if (type == "Test Trigger") {
		 triggerConfigInterface = new TriggerTestConfig(this);
	}
  triggerconfigurelayout->addWidget(triggerConfigInterface->configEditBox, 2, 0,1,2);
	triggerconfigurelayout->addItem(spacerItem, 3, 0,1,2);
  triggerinfolayout->addWidget(triggerConfigInterface->configInfoBox,0,0,1,5);
}

void TriggerConnectionPanel::statusUpdatedSlot(statusType status,
			QString statusMessage) {
	TriggerInterface::triggerInstance->setTriggerStatus(status);
	triggerStatusInfoIcon->setPixmap(statusIcons[status].pixmap(QSize(20, 20)));
	triggerStatusInfo->setText(statusTexts[status]);
	statusLog statusLog;
	statusLog.type = status;
	statusLog.time = new QTime(0,0);
	statusLog.time->restart();
	statusLog.message = statusMessage;
	statusLogWindow->statusLogList.push_back(statusLog);
	statusLogWindow->updateListSlot();
	emit triggerStatusUpdated(status, statusMessage);
}

void TriggerConnectionPanel::showLogClickedSlot() {
	statusLogWindow->updateListSlot();
	statusLogWindow->show();
}

void TriggerConnectionPanel::logsClearedSlot() {
	triggerStatusInfoIcon->setPixmap(statusIcons[Ready].pixmap(QSize(20, 20)));
	triggerStatusInfo->setText(statusTexts[Ready]);
	emit triggerStatusUpdated(Ready, statusTexts[Ready]);
}
