/*------------------------------------------------------------
 *  tiggerconnectionpanel.cpp
 *  Created:  23. October 2020
 *  Author:   Timo Hüser

 *------------------------------------------------------------*/

#include "globals.hpp"
#include "triggerconnectionpanel.hpp"
#include "triggerinterface.hpp"
#include "testtrigger.hpp"


TriggerConnectionPanel::TriggerConnectionPanel(QWidget *parent) : QFrame(parent, Qt::Window) {
	this->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);
	statusLogWindow = new StatusLogWindow(this);
	connect(statusLogWindow, SIGNAL(logsCleared()), this, SLOT(logsClearedSlot()));
	QGridLayout *panellayout = new QGridLayout(this);
	stackWidget = new QStackedWidget(this);
	panellayout->addWidget(stackWidget,0,0);
	setLayout(panellayout);

	addButton = new QPushButton(stackWidget);
	connect(addButton, SIGNAL(clicked()), this, SLOT(addClickedSlot()));
	addButton->setIcon(QIcon("icons/add_green.png"));
	addButton->setIconSize(QSize(100,100));
	addButton->setStyleSheet(" QPushButton { border-radius: 10px; border: 4px solid rgb(100,164,32); }"
													 "QPushButton:hover { background-color: rgb(68,74,89); }");

	triggerConfigureContainer = new QWidget(stackWidget);
	QGridLayout *triggerconfigurecontainerlayout = new QGridLayout(triggerConfigureContainer);
	configToolBar = new QToolBar(this);
	configToolBar->setFixedHeight(40);
	configToolBar->setIconSize(QSize(25,25));
	QLabel *configToolBarLabel = new QLabel("Configure...");
	configToolBarLabel->setFont(fonts["big"]);
	QWidget *configSpacer = new QWidget();
	configSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	confirmButton = new QToolButton(this);
	confirmAction = new QAction(this);
	createToolBarButton(confirmButton, confirmAction, QIcon("icons/check.png"), true, false, QSize(35,35));
	connect(confirmAction, &QAction::triggered, this, &TriggerConnectionPanel::confirmConfigClickedSlot);
	exitButton = new QToolButton(this);
	exitAction = new QAction(this);
	createToolBarButton(exitButton, exitAction, QIcon("icons/discard.png"), true, false, QSize(35,35));
	connect(exitAction, &QAction::triggered, this, &TriggerConnectionPanel::exitConfigClickedSlot);
	configToolBar->addWidget(configToolBarLabel);
	configToolBar->addWidget(configSpacer);
	configToolBar->addWidget(confirmButton);
	configToolBar->addWidget(exitButton);
	triggerConfigureWidget = new QWidget(triggerConfigureContainer);
	QPalette pal = palette();
	pal.setColor(QPalette::Background, QColor(22, 24, 26));
	triggerConfigureWidget->setAutoFillBackground(true);
	triggerConfigureWidget->setPalette(pal);
	QGridLayout *triggerconfigurelayout = new QGridLayout(triggerConfigureWidget);
	QWidget *configureBottomSpacer = new QWidget(triggerConfigureWidget);
	configureBottomSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QLabel *triggerTypeLabel = new QLabel("Trigger Type", triggerConfigureWidget);
	triggerTypeCombo = new QComboBox(triggerConfigureWidget);
	triggerTypeCombo->addItem("Test Trigger");
	connect(triggerTypeCombo, SIGNAL(currentTextChanged(QString)), SLOT(typeComboChangedSlot(QString)));
	triggerconfigurecontainerlayout->addWidget(configToolBar,0,0);
	triggerconfigurecontainerlayout->addWidget(triggerConfigureWidget,1,0);
	triggerconfigurecontainerlayout->setSpacing(0);
	triggerconfigurecontainerlayout->setMargin(0);

	triggerInfoContainer = new QWidget(stackWidget);
	QGridLayout *triggerInfoContainerlayout = new QGridLayout(triggerInfoContainer);
	infoToolBar = new QToolBar(this);
	infoToolBar->setFixedHeight(40);
	infoToolBar->setIconSize(QSize(25,25));
	QLabel *infoToolBarLabel = new QLabel("Trigger");
	infoToolBarLabel->setFont(fonts["big"]);
	QWidget	*infoSpacer = new QWidget();
	infoSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	deleteButton = new QToolButton(this);
	deleteAction = new QAction(this);
	createToolBarButton(deleteButton, deleteAction, QIcon("icons/discard.png"), true, false, QSize(35,35));
	connect(deleteAction, &QAction::triggered, this, &TriggerConnectionPanel::deleteTriggerClickedSlot);
	infoToolBar->addWidget(infoToolBarLabel);
	infoToolBar->addWidget(infoSpacer);
	infoToolBar->addWidget(deleteButton);
	triggerInfoWidget = new QWidget(triggerInfoContainer);
	triggerInfoWidget->setAutoFillBackground(true);
	triggerInfoWidget->setPalette(pal);
	QGridLayout *triggerinfolayout = new QGridLayout(triggerInfoWidget);
	QWidget *infoBottomSpacer = new QWidget(triggerConfigureWidget);
	infoBottomSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QLabel *triggerStatusInfoLabel = new QLabel("Status:", triggerInfoWidget);
	triggerStatusInfoIcon = new QLabel(triggerInfoWidget);
	triggerStatusInfo = new QLabel(triggerInfoWidget);
	triggerStatusButton = new QPushButton("Show Log...", triggerInfoWidget);
	connect(triggerStatusButton, SIGNAL(clicked()), this, SLOT(showLogClickedSlot()));
	QWidget *triggerStatusSpacer = new QWidget(triggerInfoWidget);
	triggerStatusSpacer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	triggerStatusInfoIcon->setPixmap(statusIcons[Connecting].pixmap(QSize(20, 20)));
	triggerStatusInfo->setText(statusTexts[Connecting]);

	createTestBoxes();

	int i = 0;
	triggerconfigurelayout->addWidget(triggerTypeLabel,i,0);
	triggerconfigurelayout->addWidget(triggerTypeCombo,i++,1);
	triggerconfigurelayout->addWidget(testBox, i++, 0,1,2);
	triggerconfigurelayout->addWidget(configureBottomSpacer,i,0,1,2);
	triggerconfigurecontainerlayout->addWidget(infoToolBar,0,0);
	triggerconfigurecontainerlayout->addWidget(triggerInfoWidget,1,0);
	triggerconfigurecontainerlayout->setSpacing(0);
	i = 0;
	triggerinfolayout->addWidget(testInfoBox,i++,0,1,5);
	triggerinfolayout->addWidget(triggerStatusInfoLabel,i,0);
	triggerinfolayout->addWidget(triggerStatusInfoIcon,i,1);
	triggerinfolayout->addWidget(triggerStatusInfo,i,2);
	triggerinfolayout->addWidget(triggerStatusSpacer,i,3);
	triggerinfolayout->addWidget(triggerStatusButton,i++,4);
	triggerinfolayout->addWidget(infoBottomSpacer,i++,0,1,2);
	triggerInfoContainerlayout->addWidget(infoToolBar,0,0);
	triggerInfoContainerlayout->addWidget(triggerInfoWidget,1,0);
	triggerInfoContainerlayout->setSpacing(0);

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

void TriggerConnectionPanel::createTestBoxes() {
	testBox = new QGroupBox(triggerConfigureWidget);
	QGridLayout *testboxlayout = new QGridLayout(testBox);
	QLabel *example1Label = new QLabel("Exmple 1", testBox);
	example1Edit = new QLineEdit(testBox);
	QLabel*example2Label = new QLabel("Example 2", testBox);
	example2Combo = new QComboBox(testBox);
	example2Combo->addItem("Val 1");
	example2Combo->addItem("Val 2");
	testboxlayout->addWidget(example1Label, 0,0);
	testboxlayout->addWidget(example1Edit, 0,1);
	testboxlayout->addWidget(example2Label, 1,0);
	testboxlayout->addWidget(example2Combo, 1,1);

	testInfoBox = new QGroupBox("Test Trigger", triggerInfoWidget);
	QGridLayout *testinfoboxlayout = new QGridLayout(testInfoBox);
	QLabel *example1InfoLabel = new QLabel("Example 1", testInfoBox);
	example1Info = new QLineEdit(testInfoBox);
	example1Info->setReadOnly(true);
	QLabel *example2InfoLabel = new QLabel("Example 2", testInfoBox);
	example2Info = new QLineEdit(testInfoBox);
	example2Info->setReadOnly(true);
	testinfoboxlayout->addWidget(example1InfoLabel, 0,0);
	testinfoboxlayout->addWidget(example1Info, 0,1);
	testinfoboxlayout->addWidget(example2InfoLabel, 1,0);
	testinfoboxlayout->addWidget(example2Info, 1,1);
}

void TriggerConnectionPanel::addClickedSlot() {
	stackWidget->setCurrentIndex(1);
}

void TriggerConnectionPanel::exitConfigClickedSlot() {
	stackWidget->setCurrentIndex(0);
}

void TriggerConnectionPanel::confirmConfigClickedSlot() {
	example1Info->setText(example1Edit->text());
	example2Info->setText(example2Combo->currentText());
	if (triggerTypeCombo->currentText() == "Test Trigger") {
		TriggerInterface::triggerInstance = new TestTrigger(example1Edit->text().toInt(), example2Combo->currentText());
		connect(TriggerInterface::triggerInstance, SIGNAL(statusUpdated(statusType, QString)), this, SLOT(statusUpdatedSlot(statusType, QString)));
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

void TriggerConnectionPanel::toggleItemsDisplayed(QList<QWidget*> items, bool toggle) {
	if (toggle) {
		for (const auto& item : items) item->show();
	}
	else {
		for (const auto& item : items) item->hide();
	}
}

void TriggerConnectionPanel::typeComboChangedSlot(QString type) {
	QList<QWidget*> testTriggerItems = {testBox, testInfoBox};
	toggleItemsDisplayed(testTriggerItems, type == "Test Trigger");
}

void TriggerConnectionPanel::statusUpdatedSlot(statusType status, QString statusMessage) {
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
