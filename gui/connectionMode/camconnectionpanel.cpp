/*------------------------------------------------------------
 *  camconnectionpanelwidget.cpp
 *  Created:  23. October 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

 #include "camconnectionpanel.hpp"
#include "globals.hpp"
#include "testcamera.hpp"
#ifdef FLIR_CHAMELEON
#include "flirchameleon.hpp"
#endif

CamConnectionPanel::CamConnectionPanel(QWidget *parent) : QFrame(parent, Qt::Window) {
	statusLogWindow = new StatusLogWindow(this);
	connect(statusLogWindow, SIGNAL(logsCleared()), this, SLOT(logsClearedSlot()));

	QGridLayout *panellayout = new QGridLayout(this);
	stackWidget = new QStackedWidget(this);
	panellayout->addWidget(stackWidget,0,0);
	setLayout(panellayout);

	addButton = new QPushButton(stackWidget);
	connect(addButton, SIGNAL(clicked()), this, SLOT(addClickedSlot()));
	addButton->setIcon(QIcon("icons/add.png"));
	addButton->setIconSize(QSize(100,100));
	addButton->setStyleSheet(" QPushButton { border-radius: 10px; border: 4px solid rgb(32,100,164); }"
													 "QPushButton:hover { background-color: rgb(68,74,89); }");

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
	createToolBarButton(confirmButton, confirmAction, QIcon("icons/check.png"), true, false, QSize(35,35));
	connect(confirmAction, &QAction::triggered, this, &CamConnectionPanel::confirmConfigClickedSlot);
	exitButton = new QToolButton(this);
	exitAction = new QAction(this);
	createToolBarButton(exitButton, exitAction, QIcon("icons/discard.png"), true, false, QSize(35,35));
	connect(exitAction, &QAction::triggered, this, &CamConnectionPanel::exitConfigClickedSlot);
	configToolBar->addWidget(configToolBarLabel);
	configToolBar->addWidget(configSpacer);
	configToolBar->addWidget(confirmButton);
	configToolBar->addWidget(exitButton);
	camConfigureWidget = new QWidget(camConfigureContainer);
	QPalette pal = palette();
	pal.setColor(QPalette::Background, QColor(22, 24, 26));
	camConfigureWidget->setAutoFillBackground(true);
	camConfigureWidget->setPalette(pal);
	QGridLayout *camconfigurelayout = new QGridLayout(camConfigureWidget);
	QWidget *configureBottomSpacer = new QWidget(camConfigureWidget);
	configureBottomSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QLabel *camNameLabel = new QLabel("Camera Name", camConfigureWidget);
	camNameEdit = new QLineEdit(camConfigureWidget);
	camNameEdit->setPlaceholderText("Enter Name...");
	QLabel *camTypeLabel = new QLabel("Camera Type", camConfigureWidget);
	camTypeCombo = new QComboBox(camConfigureWidget);
	camTypeCombo->addItem("Test Camera");
	connect(camTypeCombo, SIGNAL(currentTextChanged(QString)), SLOT(typeComboChangedSlot(QString)));


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
	connect(infoToolBarLabel, SIGNAL(editingFinished()), this, SLOT(nameEditedSlot()));
	QWidget	*infoSpacer = new QWidget();
	infoSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	deleteButton = new QToolButton(this);
	deleteAction = new QAction(this);
	createToolBarButton(deleteButton, deleteAction, QIcon("icons/discard.png"), true, false, QSize(35,35));
	connect(deleteAction, &QAction::triggered, this, &CamConnectionPanel::deleteCamClickedSlot);
	infoToolBar->addWidget(infoToolBarLabel);
	infoToolBar->addWidget(infoSpacer);
	infoToolBar->addWidget(deleteButton);
	camInfoWidget = new QWidget(camInfoContainer);
	camInfoWidget->setAutoFillBackground(true);
	camInfoWidget->setPalette(pal);
	QGridLayout *caminfolayout = new QGridLayout(camInfoWidget);
	QWidget *infoBottomSpacer = new QWidget(camConfigureWidget);
	infoBottomSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QLabel *camStatusInfoLabel = new QLabel("Status:", camInfoWidget);
	camStatusInfoIcon = new QLabel(camInfoWidget);
	camStatusInfo = new QLabel(camInfoWidget);
	camStatusButton = new QPushButton("Show Log...", camInfoWidget);
	connect(camStatusButton, SIGNAL(clicked()), this, SLOT(showLogClickedSlot()));
	QWidget *camStatusSpacer = new QWidget(camInfoWidget);
	camStatusSpacer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	camStatusInfoIcon->setPixmap(statusIcons[Connecting].pixmap(QSize(20, 20)));
	camStatusInfo->setText(statusTexts[Connecting]);

	#ifdef FLIR_CHAMELEON
	camTypeCombo->addItem("FLIR Chameleon");
	createFlirBoxes();
	#endif
	createTestBoxes();

	int i = 0;
	camconfigurelayout->addWidget(camNameLabel,i,0);
	camconfigurelayout->addWidget(camNameEdit,i++,1);
	camconfigurelayout->addWidget(camTypeLabel,i,0);
	camconfigurelayout->addWidget(camTypeCombo,i++,1);
	#ifdef FLIR_CHAMELEON
	camconfigurelayout->addWidget(flirBox, i++, 0,1,2);
	#endif
	camconfigurelayout->addWidget(testBox, i++, 0,1,2);
	camconfigurelayout->addWidget(configureBottomSpacer,i,0,1,2);
	camconfigurecontainerlayout->addWidget(configToolBar,0,0);
	camconfigurecontainerlayout->addWidget(camConfigureWidget,1,0);
	camconfigurecontainerlayout->setSpacing(0);
	camconfigurecontainerlayout->setMargin(0);
	i = 0;
	#ifdef FLIR_CHAMELEON
	caminfolayout->addWidget(flirInfoBox,i++,0,1,5);
	#endif
	caminfolayout->addWidget(testInfoBox,i++,0,1,5);
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
}

void CamConnectionPanel::createFlirBoxes() {
	flirBox = new QGroupBox(camConfigureWidget);
	QGridLayout *flirboxlayout = new QGridLayout(flirBox);
	QLabel *camIDLabel = new QLabel("Device ID", camConfigureWidget);
	camIDEdit = new QLineEdit(camConfigureWidget);
	flirboxlayout->addWidget(camIDLabel,0,0);
	flirboxlayout->addWidget(camIDEdit,0,1);

	flirInfoBox = new QGroupBox("Flir Chameleon", camInfoWidget);
	QGridLayout *testinfoboxlayout = new QGridLayout(flirInfoBox);
	QLabel *camIDInfoLabel = new QLabel("Device ID", flirInfoBox);
	camIDInfo = new QLineEdit(flirInfoBox);
	camIDInfo->setReadOnly(true);
	testinfoboxlayout->addWidget(camIDInfoLabel,0,0);
	testinfoboxlayout->addWidget(camIDInfo,1,1,1,4);
}

void CamConnectionPanel::createTestBoxes() {
	testBox = new QGroupBox(camConfigureWidget);
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

	testInfoBox = new QGroupBox("Test Camera", camInfoWidget);
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

void CamConnectionPanel::addClickedSlot() {
	stackWidget->setCurrentIndex(1);
}

void CamConnectionPanel::exitConfigClickedSlot() {
	stackWidget->setCurrentIndex(0);
}

void CamConnectionPanel::confirmConfigClickedSlot() {
	QString cameraName;
	if (camNameEdit->text() == "") cameraName = "Camera_" + QString::number(CameraInterface::cameraList.size());
	else cameraName = camNameEdit->text();
	if (camTypeCombo->currentText() == "Test Camera") {
    example1Info->setText(example1Edit->text());
    example2Info->setText(example2Combo->currentText());
		camera = new TestCamera(cameraName, example1Edit->text(), example2Combo->currentText());
		connect(camera, SIGNAL(statusUpdated(statusType, QString)), this, SLOT(statusUpdatedSlot(statusType, QString)));
		infoToolBarLabel->setText(cameraName);
		CameraInterface::cameraList.append(camera);
	}
	#ifdef FLIR_CHAMELEON
	else if (camTypeCombo->currentText() == "FLIR Chameleon") {
    camIDInfo->setText(camIDEdit->text());
		camera = new FLIRChameleon(cameraName, camIDEdit->text());
		connect(camera, SIGNAL(statusUpdated(statusType, QString)), this, SLOT(statusUpdatedSlot(statusType, QString)));
		infoToolBarLabel->setText(cameraName);
		CameraInterface::cameraList.append(camera);
	}
	#endif
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

void CamConnectionPanel::deleteCamClickedSlot() {
	CameraInterface::cameraList.removeAll(camera);
	delete camera;
	camera = nullptr;
	stackWidget->setCurrentIndex(0);
	camStatusInfoIcon->setPixmap(statusIcons[Connecting].pixmap(QSize(20, 20)));
	camStatusInfo->setText(statusTexts[Connecting]);
	emit camListChanged();
}

void CamConnectionPanel::toggleItemsDisplayed(QList<QWidget*> items, bool toggle) {
	if (toggle) {
		for (const auto& item : items) item->show();
	}
	else {
		for (const auto& item : items) item->hide();
	}
}

void CamConnectionPanel::typeComboChangedSlot(QString type) {
	#ifdef FLIR_CHAMELEON
	QList<QWidget*> flirChameleonItems = {flirBox,flirInfoBox};
	toggleItemsDisplayed(flirChameleonItems, type == "FLIR Chameleon");
	#endif
	QList<QWidget*> testCameraItems = {testBox, testInfoBox};
	toggleItemsDisplayed(testCameraItems, type == "Test Camera");

}

void CamConnectionPanel::nameEditedSlot() {
	camera->setCameraName(infoToolBarLabel->text());
	infoToolBarLabel->setReadOnly(true);
	emit camListChanged();
}

void CamConnectionPanel::statusUpdatedSlot(statusType status, QString statusMessage) {
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
