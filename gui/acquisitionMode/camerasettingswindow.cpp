/*------------------------------------------------------------
 *  camerasettingswindow.cpp
 *  Created: 23. October 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#include "camerasettingswindow.hpp"
#include "saveflirpresetswindow.hpp"
#include "loadflirpresetswindow.hpp"
#include "camerainterface.hpp"
#include "labelwithtooltip.hpp"

#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QMessageBox>
#include <QGroupBox>
#include <QScrollArea>

CameraSettingsWindow::CameraSettingsWindow(QWidget *parent, const QString& name, settingsObject *activeSettings) :
      QDockWidget(parent, Qt::Window), m_activeSettings{activeSettings} {
	settings = new QSettings();
	setMinimumSize(335,100);
	setWindowTitle(name);
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
  advancedSimpleButton = new QToolButton(this);
  advancedSimpleAction = new QAction(this);
  createToolBarButton(advancedSimpleButton, advancedSimpleAction, QIcon::fromTheme("show"), true,
        true, QSize(35,35));
  connect(advancedSimpleAction, &QAction::toggled, this, &CameraSettingsWindow::advancedSimpleToggledSlot);
	expandButton = new QToolButton(this);
	expandAction = new QAction(this);
	createToolBarButton(expandButton, expandAction, QIcon::fromTheme("plusminus"), true,
				false, QSize(35,35));
	connect(expandAction, &QAction::triggered, this, &CameraSettingsWindow::expandClickedSlot);
	savePresetButton = new QToolButton(this);
	savePresetAction = new QAction(this);
	createToolBarButton(savePresetButton, savePresetAction, QIcon::fromTheme("upload"), true,
				false, QSize(35,35));
	connect(savePresetAction, &QAction::triggered, this, &CameraSettingsWindow::savePresetsClickedSlot);
	loadPresetButton = new QToolButton(this);
	loadPresetAction = new QAction(this);
	createToolBarButton(loadPresetButton, loadPresetAction, QIcon::fromTheme("download"), true,
				false, QSize(35,35));
	connect(loadPresetAction, &QAction::triggered, this, &CameraSettingsWindow::loadPresetsClickedSlot);
	toolBar->addWidget(settingsLabel);
	toolBar->addWidget(spacer);
  toolBar->addWidget(advancedSimpleButton);
	toolBar->addWidget(expandButton);
	toolBar->addWidget(savePresetButton);
	toolBar->addWidget(loadPresetButton);
	setTitleBarWidget(toolBar);

	searchBar = new QToolBar(mainWidget);
	searchBar->setStyleSheet("QToolBar {  background-color:palette(window); }");
	searchBar->setFixedHeight(45);
	searchBar->setMovable(false);
	QLabel *searchLabel = new QLabel(searchBar);
	QIcon icon = QIcon::fromTheme("search");
	QPixmap pixmap = icon.pixmap(QSize(25, 25));
	searchLabel->setPixmap(pixmap);
	searchEdit = new QLineEdit(this);
	searchEdit->setPlaceholderText("Search...");
	connect(searchEdit ,SIGNAL(textEdited(QString)), this, SLOT(searchEditedSlot(QString)));
	searchBar->addWidget(searchLabel);
	searchBar->addWidget(searchEdit);

  QGroupBox *simpleBox = new QGroupBox();
  simpleBox->setStyleSheet("QGroupBox{margin-top:0px; background-color:rgb(34, 36, 40)}");
  QScrollArea *simpleScrollArea = new QScrollArea(simpleBox);
  simpleScrollArea->setObjectName("simpleScrollArea");
  simpleScrollArea->setFrameShape(QFrame::NoFrame);
  simpleScrollArea->setWidgetResizable(true);
  QWidget *simpleInnerWidget = new QWidget(simpleScrollArea);
  simpleInnerWidget->setObjectName("simpleInnerWidget");
  simpleInnerWidget->setStyleSheet("QWidget#simpleInnerWidget{background-color: rgba(0,0,0,0)}");
  simpleScrollArea->setStyleSheet("QScrollArea#simpleScrollArea{background-color: rgba(0,0,0,0)}");

  QGridLayout *simplelayout = new QGridLayout(simpleInnerWidget);
  QGridLayout *simpleouterlayout = new QGridLayout(simpleBox);
  simpleouterlayout->setMargin(0);
  simpleouterlayout->addWidget(simpleScrollArea,0,0);
  simpleScrollArea->setWidget(simpleInnerWidget);
  QLabel *exposureLabel = new QLabel("Exposure Control");
  exposureLabel->setFont(QFont("Sans Serif", 12, QFont::Bold));
  LabelWithToolTip *exposureAutoLabel = new LabelWithToolTip("  Exposure Auto");
  exposureToggle = new ToggleSwitch(simpleScrollArea);
  exposureToggle->setMaximumSize(70,25);
  LabelWithToolTip *exposureTimeLabel = new LabelWithToolTip("  Exposure Time [ms]");
  exposureEdit = new QSpinBox(this);
  exposureEdit->setRange(0,100);
  QWidget *exposureSpacer = new QWidget(simpleScrollArea);
  exposureSpacer->setMinimumSize(0,10);
  exposureSpacer->setMaximumSize(9999,10);

  QLabel *gainLabel = new QLabel("Gain Control");
  gainLabel->setFont(QFont("Sans Serif", 12, QFont::Bold));
  LabelWithToolTip *gainAutoLabel = new LabelWithToolTip("  Gain Auto");
  gainToggle = new ToggleSwitch(simpleScrollArea);
  gainToggle->setMaximumSize(70,25);
  LabelWithToolTip *gainValueLabel = new LabelWithToolTip("  Gain [dB]");
  gainEdit = new QDoubleSpinBox(simpleScrollArea);
  gainEdit->setRange(0.0,10.0);
  QWidget *gainSpacer = new QWidget(simpleScrollArea);
  gainSpacer->setMinimumSize(0,10);
  gainSpacer->setMaximumSize(9999,10);

  QLabel *imageFormatControlLabel = new QLabel("Frame Format Control");
  imageFormatControlLabel->setFont(QFont("Sans Serif", 12, QFont::Bold));
  LabelWithToolTip *widthLabel = new LabelWithToolTip("  Image Width");
  widthEdit = new QSpinBox(simpleScrollArea);
  widthEdit->setRange(0,1280);
  LabelWithToolTip *heightLabel = new LabelWithToolTip("  Image Height");
  heightEdit = new QSpinBox(simpleScrollArea);
  heightEdit->setRange(0,1024);
  LabelWithToolTip *horizontalOffsetLabel = new LabelWithToolTip("  Horizontal Offset");
  horizontalOffsetEdit = new QSpinBox(simpleScrollArea);
  horizontalOffsetEdit->setRange(0,1280);
  LabelWithToolTip *verticalOffsetLabel = new LabelWithToolTip("  Vertical Offset");
  verticalOffsetEdit = new QSpinBox(simpleScrollArea);
  verticalOffsetEdit->setRange(0,1280);
  LabelWithToolTip *flipHorizontalLabel = new LabelWithToolTip("  Horizontal Flip");
  flipHorizontalToggle = new ToggleSwitch(simpleScrollArea);
  flipHorizontalToggle->setMaximumSize(70,25);
  LabelWithToolTip *flipVerticalLabel = new LabelWithToolTip("  Vertical Flip");
  flipVerticalToggle = new ToggleSwitch(simpleScrollArea);
  flipVerticalToggle->setMaximumSize(70,25);
  QWidget *bottomSpacer = new QWidget(simpleBox);
  bottomSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  int i = 0;
  simplelayout->addWidget(exposureLabel,i++,0,1,2);
  simplelayout->addWidget(exposureAutoLabel,i,0);
  simplelayout->addWidget(exposureToggle,i++,1);
  simplelayout->addWidget(exposureTimeLabel,i,0);
  simplelayout->addWidget(exposureEdit,i++,1);
  simplelayout->addWidget(exposureSpacer,i++,0,1,2);
  simplelayout->addWidget(gainLabel,i++,0,1,2);
  simplelayout->addWidget(gainAutoLabel,i,0);
  simplelayout->addWidget(gainToggle,i++,1);
  simplelayout->addWidget(gainValueLabel,i,0);
  simplelayout->addWidget(gainEdit,i++,1);
  simplelayout->addWidget(gainSpacer,i++,0,1,2);
  simplelayout->addWidget(imageFormatControlLabel,i++,0,1,2);
  simplelayout->addWidget(widthLabel, i,0);
  simplelayout->addWidget(widthEdit, i++,1);
  simplelayout->addWidget(heightLabel, i,0);
  simplelayout->addWidget(heightEdit, i++,1);
  simplelayout->addWidget(horizontalOffsetLabel, i,0);
  simplelayout->addWidget(horizontalOffsetEdit, i++,1);
  simplelayout->addWidget(verticalOffsetLabel, i,0);
  simplelayout->addWidget(verticalOffsetEdit, i++,1);
  simplelayout->addWidget(flipHorizontalLabel, i,0);
  simplelayout->addWidget(flipHorizontalToggle, i++,1);
  simplelayout->addWidget(flipVerticalLabel, i,0);
  simplelayout->addWidget(flipVerticalToggle, i++,1);
  simplelayout->addWidget(bottomSpacer,i,0,1,2);

  advancedSimpleStackWidget = new QStackedWidget(this);
  advancedSimpleStackWidget->addWidget(simpleBox);


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
  searchBar->hide();
	layout->addWidget(advancedSimpleStackWidget,0,0);
}


void CameraSettingsWindow::setSettingsObjectSlot(settingsObject *newSettings) {
  if (m_activeSettings != nullptr) {
    advancedSimpleStackWidget->removeWidget(m_activeSettings->settingsTree());
  }
	toolTipBox->setText("");
	if (newSettings == nullptr) {
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
		m_activeSettings = newSettings;
		m_activeSettings->setSettingsTree(newSettings->settingsTree());
		savePresetAction->setEnabled(true);
		loadPresetAction->setEnabled(true);
		connect(m_activeSettings->settingsTree(), SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(treeItemActivatedSlot(QTreeWidgetItem*, int)));
	}
  advancedSimpleStackWidget->addWidget(m_activeSettings->settingsTree());
}


void CameraSettingsWindow::advancedSimpleToggledSlot(bool toggle) {
  if (toggle) {
    advancedSimpleStackWidget->setCurrentIndex(1);
    searchBar->show();
  	mainSplitter->setSizes({1000,100});
  }
  else {
    advancedSimpleStackWidget->setCurrentIndex(0);
    searchBar->hide();
  	mainSplitter->setSizes({1000,0});
  }
}

void CameraSettingsWindow::saveSettingsLayer(SettingsNode* node) {
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


void CameraSettingsWindow::loadSettingsLayer(SettingsNode* node) {
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


int CameraSettingsWindow::searchRecursive(QTreeWidgetItem *parent, QList<QTreeWidgetItem *> results) {
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


void CameraSettingsWindow::searchEditedSlot(const QString& text) {
	QList<QTreeWidgetItem *>  results = m_activeSettings->settingsTree()->findItems(text, Qt::MatchContains | Qt::MatchRecursive);
	for( int i = 0; i < m_activeSettings->settingsTree()->topLevelItemCount(); i++ ) {
		QTreeWidgetItem *item = m_activeSettings->settingsTree()->topLevelItem(i);
		searchRecursive(item, results);
	}
}


void CameraSettingsWindow::expandClickedSlot() {
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


void CameraSettingsWindow::treeItemActivatedSlot(QTreeWidgetItem* item, int) {
	SettingsNode* node = m_activeSettings->findNode(item->text(0));
	if (node != nullptr) toolTipBox->setText(node->description());
}


void CameraSettingsWindow::savePresetsClickedSlot() {
  if (m_activeSettings != nullptr) {
    if (m_activeSettings->getRootNode()->name() == "FLIR Chameleon") {
      FLIRChameleon *cam = static_cast<FLIRChameleon*>(m_activeSettings->parent());
      saveCameraPresetsWindow = new SaveFlirPresetsWindow(cam);
    }
    saveCameraPresetsWindow->show();
  }
}


void CameraSettingsWindow::loadPresetsClickedSlot() {
  if (m_activeSettings != nullptr) {
    if (m_activeSettings->getRootNode()->name() == "FLIR Chameleon") {
      FLIRChameleon *cam = static_cast<FLIRChameleon*>(m_activeSettings->parent());
      loadCameraPresetsWindow = new LoadFlirPresetsWindow(cam);
    }
    loadCameraPresetsWindow->exec();
  }
}
