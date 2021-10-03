/*------------------------------------------------------------
 *  timestampwindow.cpp
 *  Created: 23. October 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#include "timestampwindow.hpp"

#include <QLineEdit>
#include <QTextStream>
#include <QHeaderView>
#include <QInputDialog>

TimeStampWindow::TimeStampWindow(QWidget *parent) : QDockWidget(parent, Qt::Window) {
	settings = new QSettings();
	this->setMinimumSize(325,300);
	this->setWindowTitle("Timestamp Editor");
	this->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	loadPresetsWindow = new PresetsWindow(&presets, "load", "Timestamp Editor/");
	savePresetsWindow = new PresetsWindow(&presets, "save", "Timestamp Editor/");
	connect(loadPresetsWindow, SIGNAL(loadPreset(QString)), this, SLOT(loadPresetSlot(QString)));
	connect(savePresetsWindow, SIGNAL(savePreset(QString)), this, SLOT(savePresetSlot(QString)));
	mainSplitter = new QSplitter(this);
	mainSplitter->setOrientation(Qt::Horizontal);
	this->setWidget(mainSplitter);

	toolBar = new QToolBar(this);
	toolBar->setFixedHeight(40);
	toolBar->setIconSize(QSize(25,25));
	toolBar->setStyleSheet("QToolBar {background-color: palette(base);}");
	QLabel *settingsLabel = new QLabel("Timestamp Editor");
	settingsLabel->setFont(fonts["bold"]);
	QWidget *spacer = new QWidget();
	spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	savePresetButton = new QToolButton(this);
	savePresetAction = new QAction(this);
	createToolBarButton(savePresetButton, savePresetAction, QIcon::fromTheme("upload"), true,
				false, QSize(35,35));
	connect(savePresetAction, &QAction::triggered, this, &TimeStampWindow::savePresetsClickedSlot);
	loadPresetButton = new QToolButton(this);
	loadPresetAction = new QAction(this);
	createToolBarButton(loadPresetButton, loadPresetAction, QIcon::fromTheme("download"), true,
				false, QSize(35,35));
	connect(loadPresetAction, &QAction::triggered, this, &TimeStampWindow::loadPresetsClickedSlot);
	closeButton = new QToolButton(this);
	closeAction = new QAction(this);
	createToolBarButton(closeButton, closeAction, QIcon::fromTheme("discard"), true,
				false, QSize(35,35));
	connect(closeAction, &QAction::triggered, this, &TimeStampWindow::closeClickedSlot);
	toolBar->addWidget(settingsLabel);
	toolBar->addWidget(spacer);
	toolBar->addWidget(savePresetButton);
	toolBar->addWidget(loadPresetButton);
	toolBar->addWidget(closeButton);
	setTitleBarWidget(toolBar);

	firstWidget = new QWidget(mainSplitter);
	firstlayout = new QGridLayout(firstWidget);
	secondWidget = new QWidget(mainSplitter);
	secondlayout = new QGridLayout(secondWidget);
	mainSplitter->addWidget(firstWidget);
	mainSplitter->addWidget(secondWidget);


	currentStampEdit = new QLineEdit(this);
	currentStampEdit->setReadOnly(true);
	addButton = new QPushButton("Add");
	connect(addButton, &QPushButton::clicked, this, &TimeStampWindow::addTimeStampSlot);

	timeStampTable = new QTableWidget(0, 2);
	timeStampTable->setAlternatingRowColors(true);
	QStringList labels;
	labels << "Time" << "Label";
	timeStampTable->setHorizontalHeaderLabels(labels);
	timeStampTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
	timeStampTable->verticalHeader()->hide();
	timeStampTable->setShowGrid(false);
	timeStampTable->setSelectionBehavior(QAbstractItemView::SelectRows);

	labelSelectorWidget = new QWidget();
	labelselectorlayout = new QGridLayout(labelSelectorWidget);
	labelSelectorList = new QListWidget(labelSelectorWidget);
	labelSelectorList->setAlternatingRowColors(true);
	connect(labelSelectorList, &QListWidget::itemDoubleClicked, this, &TimeStampWindow::labelSelectedSlot);
	moveLabelUpButton = new QPushButton();
	moveLabelUpButton->setIcon(QIcon::fromTheme("up"));
	moveLabelUpButton->setMinimumSize(35,35);
	connect(moveLabelUpButton, &QPushButton::clicked, this, &TimeStampWindow::moveLabelUpSlot);
	moveLabelDownButton = new QPushButton();
	moveLabelDownButton->setIcon(QIcon::fromTheme("down"));
	moveLabelDownButton->setMinimumSize(35,35);
	connect(moveLabelDownButton, &QPushButton::clicked, this, &TimeStampWindow::moveLabelDownSlot);
	addLabelButton = new QPushButton();
	addLabelButton->setIcon(QIcon::fromTheme("plus"));
	addLabelButton->setMinimumSize(35,35);
	connect(addLabelButton, &QPushButton::clicked, this, &TimeStampWindow::addLabelSlot);
	deleteLabelButton = new QPushButton();
	deleteLabelButton->setIcon(QIcon::fromTheme("discard"));
	deleteLabelButton->setMinimumSize(35,35);
	connect(deleteLabelButton, &QPushButton::clicked, this, &TimeStampWindow::removeLabelSlot);
	labelselectorlayout->addWidget(labelSelectorList,0,0,1,4);
	labelselectorlayout->addWidget(moveLabelUpButton,1,0);
	labelselectorlayout->addWidget(moveLabelDownButton,1,1);
	labelselectorlayout->addWidget(addLabelButton,1,2);
	labelselectorlayout->addWidget(deleteLabelButton,1,3);

	firstlayout->addWidget(currentStampEdit,0,0);
	firstlayout->addWidget(addButton,0,1);
	firstlayout->addWidget(labelSelectorWidget,1,0,1,2);

	secondlayout->addWidget(timeStampTable,0,0);

	mainSplitter->setSizes({300,500});
}

void TimeStampWindow::recordingInfoFileCreatedSlot(QFile *file, QTime * recordingTime) {
	m_recordingInfoFile = file;
	m_recordingTime = recordingTime;
	if (m_recordingInfoFile->open(QIODevice::Append | QIODevice::Text)) {
		QTextStream out(m_recordingInfoFile);
		out << "Timestamps:\n" << "Time\t\tLabel\n";
		m_recordingInfoFile->close();
	}
}

void TimeStampWindow::acquisitionStoppedSlot()  {
	m_recordingInfoFile = nullptr;
}

void TimeStampWindow::addTimeStampSlot() {
	if (m_recordingInfoFile != nullptr && currentStampEdit->text() != "") {
		if (m_recordingInfoFile->open(QIODevice::Append | QIODevice::Text)) {
			QTextStream out(m_recordingInfoFile);
			out << m_recordingTime->toString("mm:ss:zzz") << "\t" << currentStampEdit->text() << "\n";
			m_recordingInfoFile->close();
		}
		timeStampTable->setRowCount(timeStampTable->rowCount()+1);
		QTableWidgetItem* timeItem = new QTableWidgetItem();
    timeItem->setText(m_recordingTime->toString("mm:ss:zzz"));
		timeItem->setFlags(timeItem->flags() ^ Qt::ItemIsEditable);
		timeStampTable->setItem(timeStampTable->rowCount()-1,0,timeItem);
		QTableWidgetItem* labelItem = new QTableWidgetItem();
    labelItem->setText(currentStampEdit->text());
		labelItem->setFlags(labelItem->flags() ^ Qt::ItemIsEditable);
		timeStampTable->setItem(timeStampTable->rowCount()-1,1,labelItem);
	}
}

void TimeStampWindow::labelSelectedSlot(QListWidgetItem *item) {
	currentStampEdit->setText(item->text());
}

void TimeStampWindow::moveLabelUpSlot() {
	int row = labelSelectorList->currentRow();
	QListWidgetItem *item = labelSelectorList->takeItem(row);
	int newRow = std::max(row-1,0);
	labelSelectorList->insertItem(newRow,item);
	labelSelectorList->setCurrentRow(newRow);
}

void TimeStampWindow::moveLabelDownSlot() {
	int row = labelSelectorList->currentRow();
	QListWidgetItem *item = labelSelectorList->takeItem(row);
	int newRow = std::min(row+1,labelSelectorList->count());
	labelSelectorList->insertItem(newRow,item);
	labelSelectorList->setCurrentRow(newRow);
}

void TimeStampWindow::addLabelSlot() {
	QString label = QInputDialog::getText(this,"Timestamp Editor","Enter Label:", QLineEdit::Normal);
	if (label != "") labelSelectorList->addItem(label);
}

void TimeStampWindow::removeLabelSlot() {
	delete labelSelectorList->takeItem(labelSelectorList->currentRow());
}


void TimeStampWindow::savePresetsClickedSlot() {
	savePresetsWindow->updateListSlot();
	savePresetsWindow->show();
}


void TimeStampWindow::loadPresetsClickedSlot() {
	loadPresetsWindow->updateListSlot();
	loadPresetsWindow->show();
}


void TimeStampWindow::savePresetSlot(const QString& preset) {
	settings->beginGroup(preset);
	QList<QString> labelsList;
	for (const auto& item : labelSelectorList->findItems("",Qt::MatchContains)) {
		labelsList.append(item->text());
		std::cout << item->text().toStdString() << std::endl;
	}
	settings->setValue("ĺabelsList", QVariant::fromValue(labelsList));
	settings->endGroup();

}


void TimeStampWindow::loadPresetSlot(const QString& preset) {
	labelSelectorList->clear();
	settings->beginGroup(preset);
	QList<QString> labelsList = settings->value("ĺabelsList").value<QList<QString>>();
	for (const auto& label : labelsList) {
		labelSelectorList->addItem(label);
	}
	settings->endGroup();
}

void TimeStampWindow::closeClickedSlot() {
	this->hide();
}

void TimeStampWindow::resizeEvent(QResizeEvent *) {
	if (this->size().width() > 550) {
		mainSplitter->setOrientation(Qt::Horizontal);
	}
	else {
		mainSplitter->setOrientation(Qt::Vertical);
	}
}
