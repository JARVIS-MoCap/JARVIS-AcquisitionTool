/*------------------------------------------------------------
 *  settingswinow.cpp
 *  Created: 23. October 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#include "settingswindow.hpp"

#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QMessageBox>


SettingsWindow::SettingsWindow(QWidget *parent, const QString& name, settingsObject *activeSettings) :
      QDockWidget(parent, Qt::Window), m_activeSettings{activeSettings} {
	settings = new QSettings();
	setMinimumSize(325,300);
	setWindowTitle(name);
	loadPresetsWindow = new PresetsWindow(&presets, "load", name + "/");
	savePresetsWindow = new PresetsWindow(&presets, "save", name + "/");
	connect(loadPresetsWindow, SIGNAL(loadPreset(QString)), this, SLOT(loadPresetSlot(QString)));
	connect(savePresetsWindow, SIGNAL(savePreset(QString)), this, SLOT(savePresetSlot(QString)));
	settingsName = name;
	mainSplitter = new QSplitter(Qt::Vertical, this);
	mainWidget = new QWidget (mainSplitter);
	setWidget(mainSplitter);
	layout = new QGridLayout(mainWidget);

	toolBar = new QToolBar(this);
	toolBar->setFixedHeight(40);
	toolBar->setIconSize(QSize(25,25));
	toolBar->setStyleSheet("QToolBar {background-color: palette(base);}");
	QLabel *settingsLabel = new QLabel(name);
	settingsLabel->setFont(fonts["bold"]);
	QWidget *spacer = new QWidget();
	spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	expandButton = new QToolButton(this);
	expandAction = new QAction(this);
	createToolBarButton(expandButton, expandAction, QIcon::fromTheme("plusminus"), true,
				false, QSize(35,35));
	connect(expandAction, &QAction::triggered, this, &SettingsWindow::expandClickedSlot);
	savePresetButton = new QToolButton(this);
	savePresetAction = new QAction(this);
	createToolBarButton(savePresetButton, savePresetAction, QIcon::fromTheme("upload"), true,
				false, QSize(35,35));
	connect(savePresetAction, &QAction::triggered, this, &SettingsWindow::savePresetsClickedSlot);
	loadPresetButton = new QToolButton(this);
	loadPresetAction = new QAction(this);
	createToolBarButton(loadPresetButton, loadPresetAction, QIcon::fromTheme("download"), true,
				false, QSize(35,35));
	connect(loadPresetAction, &QAction::triggered, this, &SettingsWindow::loadPresetsClickedSlot);
	toolBar->addWidget(settingsLabel);
	toolBar->addWidget(spacer);
	toolBar->addWidget(expandButton);
	toolBar->addWidget(savePresetButton);
	toolBar->addWidget(loadPresetButton);
	setTitleBarWidget(toolBar);

	searchBar = new QToolBar(mainWidget);
	searchBar->setStyleSheet("QToolBar {  background-color:palette(window); }");
	searchBar->setFixedHeight(45);
	searchBar->setMovable(false);
	QLabel *searchLabel = new QLabel(searchBar);
	QIcon *icon = new QIcon("icons/search.png");
	QPixmap pixmap = icon->pixmap(QSize(25, 25));
	searchLabel->setPixmap(pixmap);
	searchEdit = new QLineEdit(this);
	searchEdit->setPlaceholderText("Search...");
	connect(searchEdit ,SIGNAL(textEdited(QString)), this, SLOT(searchEditedSlot(QString)));
	searchBar->addWidget(searchLabel);
	searchBar->addWidget(searchEdit);

	QWidget *toolTipWidget = new QWidget(mainSplitter);
	QGridLayout *tooltiplayout = new QGridLayout(toolTipWidget);
	toolTipBox = new QTextEdit(mainSplitter);
	toolTipBox->setText("");

	tooltiplayout->addWidget(toolTipBox,0,0);

	mainSplitter->addWidget(mainWidget);
	mainSplitter->addWidget(toolTipWidget);
	mainSplitter->setSizes({1000,0});
	setSettingsObjectSlot(m_activeSettings);
	layout->setMenuBar(searchBar);
	layout->addWidget(m_activeSettings->settingsTree(),0,0);
}


void SettingsWindow::setSettingsObjectSlot(settingsObject *newSettings) {
	toolTipBox->setText("");
	if (newSettings == nullptr) {
		mainSplitter->setSizes({1000,0});
		savePresetAction->setEnabled(false);
		loadPresetAction->setEnabled(false);
		m_activeSettings = new settingsObject();
		m_activeSettings->settingsTree()->setAlternatingRowColors(true);
		m_activeSettings->settingsTree()->setColumnCount(2);
		QStringList ColumnNames;
		ColumnNames << "" << "";
		m_activeSettings->settingsTree()->setHeaderLabels(ColumnNames);
	}
	else {
		mainSplitter->setSizes({1000,100});
		m_activeSettings->settingsTree()->hide();
		m_activeSettings = newSettings;
		m_activeSettings->setSettingsTree(newSettings->settingsTree());
		savePresetAction->setEnabled(true);
		loadPresetAction->setEnabled(true);
		connect(m_activeSettings->settingsTree(), SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(treeItemActivatedSlot(QTreeWidgetItem*, int)));
	}
	layout->addWidget(m_activeSettings->settingsTree(),0,0);
	m_activeSettings->settingsTree()->show();
	m_activeSettings->settingsTree()->raise();
}


void SettingsWindow::saveSettingsLayer(SettingsNode* node) {
	for (const auto& child : node->children()) {
			SettingsNode::nodeType type = child->type();
			if (type == SettingsNode::String || type == SettingsNode::Integer || type == SettingsNode::Float) {
				settings->setValue(child->name(), static_cast<QLineEdit*>(child->dataField())->text());
			}
			else if (type == SettingsNode::Enumeration) {
				settings->setValue(child->name(), static_cast<QComboBox*>(child->dataField())->currentText());
			}
			else if (type == SettingsNode::Boolean) {
				settings->setValue(child->name(), static_cast<QCheckBox*>(child->dataField())->checkState());
			}
			saveSettingsLayer(child);
	}
}


void SettingsWindow::loadSettingsLayer(SettingsNode* node) {
	for (const auto& child : node->children()) {
		SettingsNode::nodeType type = child->type();
		if (type == SettingsNode::String || type == SettingsNode::Integer || type == SettingsNode::Float) {
			QString newText = settings->value(child->name()).toString();
			static_cast<QLineEdit*>(child->dataField())->setText(newText);
		}
		else if (type == SettingsNode::Enumeration) {
			static_cast<QComboBox*>(child->dataField())->blockSignals(true);
			QString newText = settings->value(child->name()).toString();
			static_cast<QComboBox*>(child->dataField())->setCurrentText(newText);
			static_cast<QComboBox*>(child->dataField())->blockSignals(false);
		}
		else if (type == SettingsNode::Boolean) {
			int newState = settings->value(child->name()).toInt();
			static_cast<QCheckBox*>(child->dataField())->setCheckState(static_cast<Qt::CheckState>(newState));
		}
		loadSettingsLayer(child);
	}
}


int SettingsWindow::searchRecursive(QTreeWidgetItem *parent, QList<QTreeWidgetItem *> results) {
	int count = 0;
	for  (int j = 0; j < parent->childCount(); j++) {
		QTreeWidgetItem *child = parent->child(j);
		count += searchRecursive(child, results);
    if (child->childCount() == 0) child->setHidden(!results.contains(child));
		if (results.contains(child)) count++;
	}
	parent->setHidden(count == 0);
	parent->setExpanded(count != 0);
  return count;
}


void SettingsWindow::searchEditedSlot(const QString& text) {
	QList<QTreeWidgetItem *>  results = m_activeSettings->settingsTree()->findItems(text, Qt::MatchContains | Qt::MatchRecursive);
	for( int i = 0; i < m_activeSettings->settingsTree()->topLevelItemCount(); i++ ) {
		QTreeWidgetItem *item = m_activeSettings->settingsTree()->topLevelItem(i);
		searchRecursive(item, results);
	}
}


void SettingsWindow::expandClickedSlot() {
	int expandedCount = 0;
	for( int i = 0; i < m_activeSettings->settingsTree()->topLevelItemCount(); i++ ) {
		QTreeWidgetItem *item = m_activeSettings->settingsTree()->topLevelItem(i);
		if (item->isExpanded()) expandedCount++;
	}
	for( int i = 0; i < m_activeSettings->settingsTree()->topLevelItemCount(); i++ ) {
		QTreeWidgetItem *item = m_activeSettings->settingsTree()->topLevelItem(i);
		item->setExpanded(expandedCount == 0);
	}
}


void SettingsWindow::treeItemActivatedSlot(QTreeWidgetItem* item, int) {
	SettingsNode* node = m_activeSettings->findNode(item->text(0));
	if (node != nullptr) toolTipBox->setText(node->description());
}


void SettingsWindow::savePresetsClickedSlot() {
	savePresetsWindow->updateListSlot();
	savePresetsWindow->show();
}


void SettingsWindow::loadPresetsClickedSlot() {
	loadPresetsWindow->updateListSlot();
	loadPresetsWindow->show();
}


void SettingsWindow::savePresetSlot(const QString& preset) {
	settings->beginGroup(preset);
	settings->setValue("cameraType", m_activeSettings->getRootNode()->name());
	saveSettingsLayer(m_activeSettings->getRootNode());
	settings->endGroup();

}


void SettingsWindow::loadPresetSlot(const QString& preset) {
	settings->beginGroup(preset);
	if (settings->value("cameraType") != m_activeSettings->getRootNode()->name()) {
		QMessageBox *wrongCamMsg = new QMessageBox();
		wrongCamMsg->setText("Preset for wrong camera type!");
		wrongCamMsg->show();
		settings->endGroup();
		return;
	}
	loadSettingsLayer(m_activeSettings->getRootNode());
	emit loadPreset(m_activeSettings);
	settings->endGroup();
}
