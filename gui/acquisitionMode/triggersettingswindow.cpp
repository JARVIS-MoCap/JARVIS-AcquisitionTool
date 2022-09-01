/*******************************************************************************
 * File:        triggersettingswinow.hpp
 * Created:     23. October 2020
 * Author:      Timo Hueser
 * Contact:     timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#include "triggersettingswindow.hpp"
#include "camerainterface.hpp"
#include "labelwithtooltip.hpp"
#include "loadflirpresetswindow.hpp"
#include "saveflirpresetswindow.hpp"
#include "triggerinterface.hpp"

#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>
#include <QLineEdit>
#include <QMessageBox>

TriggerSettingsWindow::TriggerSettingsWindow(QWidget *parent,
                                             SettingsObject *activeSettings)
    : QDockWidget(parent, Qt::Window), m_activeSettings(activeSettings) {
    settings = new QSettings();
    setMinimumSize(325, 300);
    setWindowTitle("Trigger Settings");
    loadPresetsWindow =
        new PresetsWindow(&presets, "load", "Trigger Settings/");
    savePresetsWindow =
        new PresetsWindow(&presets, "save", "Trigger Settings/");
    connect(loadPresetsWindow, &PresetsWindow::loadPreset, this,
            &TriggerSettingsWindow::loadPresetSlot);
    connect(savePresetsWindow, &PresetsWindow::savePreset, this,
            &TriggerSettingsWindow::savePresetSlot);
    settingsName = "Trigger Settings";
    mainSplitter = new QSplitter(Qt::Vertical, this);
    mainWidget = new QWidget(mainSplitter);
    setWidget(mainSplitter);
    layout = new QGridLayout(mainWidget);

    toolBar = new QToolBar(this);
    toolBar->setFixedHeight(40);
    toolBar->setIconSize(QSize(25, 25));
    toolBar->setStyleSheet("QToolBar {background-color: palette(base);}");
    QLabel *settingsLabel = new QLabel("Trigger Settings");
    settingsLabel->setFont(QFont("Sans Serif", 11, QFont::Bold));
    QWidget *spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    advancedSimpleButton = new QToolButton(this);
    advancedSimpleAction = new QAction(this);
    createToolBarButton(advancedSimpleButton, advancedSimpleAction,
                        QIcon::fromTheme("show"), true, true, QSize(35, 35));
    connect(advancedSimpleAction, &QAction::toggled, this,
            &TriggerSettingsWindow::advancedSimpleToggledSlot);
    expandButton = new QToolButton(this);
    expandAction = new QAction(this);
    createToolBarButton(expandButton, expandAction,
                        QIcon::fromTheme("plusminus"), true, false,
                        QSize(35, 35));
    connect(expandAction, &QAction::triggered, this,
            &TriggerSettingsWindow::expandClickedSlot);
    savePresetButton = new QToolButton(this);
    savePresetAction = new QAction(this);
    createToolBarButton(savePresetButton, savePresetAction,
                        QIcon::fromTheme("upload"), true, false, QSize(35, 35));
    connect(savePresetAction, &QAction::triggered, this,
            &TriggerSettingsWindow::savePresetsClickedSlot);
    loadPresetButton = new QToolButton(this);
    loadPresetAction = new QAction(this);
    createToolBarButton(loadPresetButton, loadPresetAction,
                        QIcon::fromTheme("download"), true, false,
                        QSize(35, 35));
    connect(loadPresetAction, &QAction::triggered, this,
            &TriggerSettingsWindow::loadPresetsClickedSlot);
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
    QIcon *icon = new QIcon("icons/search.png");
    QPixmap pixmap = icon->pixmap(QSize(25, 25));
    searchLabel->setPixmap(pixmap);
    searchEdit = new QLineEdit(this);
    searchEdit->setPlaceholderText("Search...");
    connect(searchEdit, &QLineEdit::textEdited, this,
            &TriggerSettingsWindow::searchEditedSlot);
    searchBar->addWidget(searchLabel);
    searchBar->addWidget(searchEdit);

    QGroupBox *simpleBox = new QGroupBox();
    simpleBox->setStyleSheet(
        "QGroupBox{margin-top:0px; background-color:rgb(34, 36, 40)}");
    QGridLayout *simplelayout = new QGridLayout(simpleBox);
    LabelWithToolTip *frameRateLabel = new LabelWithToolTip("FrameRate (FPS)");
    frameRateEdit = new QSpinBox(this);
    frameRateEdit->setRange(std::numeric_limits<uint8_t>::min(),
                            std::numeric_limits<uint8_t>::max());

    LabelWithToolTip *frameLimitLabel =
        new LabelWithToolTip("FrameLimit (Frames)");
    frameLimitEdit = new QDoubleSpinBox(this);
    frameLimitEdit->setRange(std::numeric_limits<uint32_t>::min(),
                             std::numeric_limits<uint32_t>::max());
    frameLimitEdit->setDecimals(0);

    LabelWithToolTip *cmdDelayLabel =
        new LabelWithToolTip("CmdDelay (\u00B5s)");
    cmdDelayEdit = new QDoubleSpinBox(this);
    cmdDelayEdit->setRange(std::numeric_limits<uint32_t>::min(),
                           std::numeric_limits<uint32_t>::max());
    cmdDelayEdit->setDecimals(0);

    LabelWithToolTip *syncRisingEdgeLabel =
        new LabelWithToolTip("Sync rising edge");
    syncRisingEdgeToggle = new ToggleSwitch(this);
    syncRisingEdgeToggle->setToggled(false);

    frameRateEdit->setEnabled(false);
    frameLimitEdit->setEnabled(false);
    cmdDelayEdit->setEnabled(false);
    connect(frameRateEdit, QOverload<int>::of(&QSpinBox::valueChanged), this,
            &TriggerSettingsWindow::frameRateEditChangedSlot);
    connect(frameLimitEdit,
            QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
            &TriggerSettingsWindow::frameLimitEditChangedSlot);
    connect(cmdDelayEdit, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &TriggerSettingsWindow::cmdDelayEditChangedSlot);
    connect(syncRisingEdgeToggle, QOverload<bool>::of(&ToggleSwitch::toggled),
            this, &TriggerSettingsWindow::syncRisingEdgeToggleChangedSlot);

    QWidget *bottomSpacer = new QWidget(simpleBox);
    bottomSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    simplelayout->addWidget(frameRateLabel, 0, 0);
    simplelayout->addWidget(frameRateEdit, 0, 1);
    simplelayout->addWidget(frameLimitLabel, 1, 0);
    simplelayout->addWidget(frameLimitEdit, 1, 1);
    simplelayout->addWidget(cmdDelayLabel, 2, 0);
    simplelayout->addWidget(cmdDelayEdit, 2, 1);
    simplelayout->addWidget(syncRisingEdgeLabel, 3, 0);
    simplelayout->addWidget(syncRisingEdgeToggle, 3, 1);
    simplelayout->addWidget(bottomSpacer, 4, 0, 1, 2);

    advancedSimpleStackWidget = new QStackedWidget(this);
    advancedSimpleStackWidget->addWidget(simpleBox);

    QWidget *toolTipWidget = new QWidget(mainSplitter);
    QGridLayout *tooltiplayout = new QGridLayout(toolTipWidget);
    toolTipBox = new QTextEdit(mainSplitter);
    toolTipBox->setText("");

    tooltiplayout->addWidget(toolTipBox, 0, 0);

    mainSplitter->addWidget(mainWidget);
    mainSplitter->addWidget(toolTipWidget);
    mainSplitter->setSizes({1000, 0});
    setSettingsObjectSlot(m_activeSettings);
    layout->setMenuBar(searchBar);
    searchBar->hide();
    layout->addWidget(advancedSimpleStackWidget, 0, 0);
}

void TriggerSettingsWindow::setSettingsObjectSlot(SettingsObject *newSettings) {
    if (m_activeSettings != nullptr) {
        advancedSimpleStackWidget->removeWidget(
            m_activeSettings->settingsTree());
    }
    toolTipBox->setText("");
    if (newSettings == nullptr) {
        savePresetAction->setEnabled(false);
        loadPresetAction->setEnabled(false);
        m_activeSettings = new SettingsObject();
        m_activeSettings->settingsTree()->setAlternatingRowColors(true);
        m_activeSettings->settingsTree()->setColumnCount(2);
        QStringList ColumnNames;
        ColumnNames << ""
                    << "";
        m_activeSettings->settingsTree()->setHeaderLabels(ColumnNames);
        frameRateEdit->setEnabled(false);
        frameLimitEdit->setEnabled(false);
        cmdDelayEdit->setEnabled(false);
    } else {
        m_activeSettings = newSettings;
        m_activeSettings->setSettingsTree(newSettings->settingsTree());
        savePresetAction->setEnabled(true);
        loadPresetAction->setEnabled(true);
        connect(m_activeSettings->settingsTree(), &QTreeWidget::itemClicked,
                this, &TriggerSettingsWindow::treeItemActivatedSlot);
        frameRateEdit->setEnabled(true);
        frameRateEdit->setValue(
            TriggerInterface::triggerInstance->getFrameRate());
        frameLimitEdit->setEnabled(true);
        frameLimitEdit->setValue(
            TriggerInterface::triggerInstance->getFrameLimit());
        cmdDelayEdit->setEnabled(true);
        cmdDelayEdit->setValue(
            TriggerInterface::triggerInstance->getCmdDelay());
    }
    advancedSimpleStackWidget->addWidget(m_activeSettings->settingsTree());
}

void TriggerSettingsWindow::advancedSimpleToggledSlot(bool toggle) {
    if (toggle) {
        advancedSimpleStackWidget->setCurrentIndex(1);
        searchBar->show();
        mainSplitter->setSizes({1000, 100});
    } else {
        advancedSimpleStackWidget->setCurrentIndex(0);
        searchBar->hide();
        mainSplitter->setSizes({1000, 0});
    }
}

void TriggerSettingsWindow::saveSettingsLayer(SettingsNode *node) {
    for (const auto &child : node->children()) {
        SettingsNode::nodeType type = child->type();
        if (type == SettingsNode::String || type == SettingsNode::Integer ||
            type == SettingsNode::Float) {
            settings->setValue(
                child->name(),
                static_cast<QLineEdit *>(child->dataField())->text());
        } else if (type == SettingsNode::Enumeration) {
            settings->setValue(
                child->name(),
                static_cast<QComboBox *>(child->dataField())->currentText());
        } else if (type == SettingsNode::Boolean) {
            settings->setValue(
                child->name(),
                static_cast<QCheckBox *>(child->dataField())->checkState());
        }
        saveSettingsLayer(child);
    }
}

void TriggerSettingsWindow::loadSettingsLayer(SettingsNode *node) {
    for (const auto &child : node->children()) {
        SettingsNode::nodeType type = child->type();
        if (type == SettingsNode::String || type == SettingsNode::Integer ||
            type == SettingsNode::Float) {
            QString newText = settings->value(child->name()).toString();
            static_cast<QLineEdit *>(child->dataField())->setText(newText);
        } else if (type == SettingsNode::Enumeration) {
            static_cast<QComboBox *>(child->dataField())->blockSignals(true);
            QString newText = settings->value(child->name()).toString();
            static_cast<QComboBox *>(child->dataField())
                ->setCurrentText(newText);
            static_cast<QComboBox *>(child->dataField())->blockSignals(false);
        } else if (type == SettingsNode::Boolean) {
            int newState = settings->value(child->name()).toInt();
            static_cast<QCheckBox *>(child->dataField())
                ->setCheckState(static_cast<Qt::CheckState>(newState));
        }
        loadSettingsLayer(child);
    }
}

int TriggerSettingsWindow::searchRecursive(QTreeWidgetItem *parent,
                                           QList<QTreeWidgetItem *> results) {
    int count = 0;
    for (int j = 0; j < parent->childCount(); j++) {
        QTreeWidgetItem *child = parent->child(j);
        count += searchRecursive(child, results);
        if (child->childCount() == 0)
            child->setHidden(!results.contains(child));
        if (results.contains(child))
            count++;
    }
    parent->setHidden(count == 0);
    parent->setExpanded(count != 0);
    return count;
}

void TriggerSettingsWindow::searchEditedSlot(const QString &text) {
    QList<QTreeWidgetItem *> results =
        m_activeSettings->settingsTree()->findItems(
            text, Qt::MatchContains | Qt::MatchRecursive);
    for (int i = 0; i < m_activeSettings->settingsTree()->topLevelItemCount();
         i++) {
        QTreeWidgetItem *item =
            m_activeSettings->settingsTree()->topLevelItem(i);
        searchRecursive(item, results);
    }
}

void TriggerSettingsWindow::expandClickedSlot() {
    int expandedCount = 0;
    for (int i = 0; i < m_activeSettings->settingsTree()->topLevelItemCount();
         i++) {
        QTreeWidgetItem *item =
            m_activeSettings->settingsTree()->topLevelItem(i);
        if (item->isExpanded())
            expandedCount++;
    }
    for (int i = 0; i < m_activeSettings->settingsTree()->topLevelItemCount();
         i++) {
        QTreeWidgetItem *item =
            m_activeSettings->settingsTree()->topLevelItem(i);
        item->setExpanded(expandedCount == 0);
    }
}

void TriggerSettingsWindow::treeItemActivatedSlot(QTreeWidgetItem *item, int) {
    SettingsNode *node = m_activeSettings->findNode(item->text(0));
    if (node != nullptr)
        toolTipBox->setText(node->description());
}

void TriggerSettingsWindow::savePresetsClickedSlot() {
    savePresetsWindow->updateListSlot();
    savePresetsWindow->show();
}

void TriggerSettingsWindow::loadPresetsClickedSlot() {
    loadPresetsWindow->updateListSlot();
    loadPresetsWindow->show();
}

void TriggerSettingsWindow::savePresetSlot(const QString &preset) {
    settings->beginGroup(preset);
    settings->setValue("triggerType", m_activeSettings->getRootNode()->name());
    saveSettingsLayer(m_activeSettings->getRootNode());
    settings->endGroup();
}

void TriggerSettingsWindow::loadPresetSlot(const QString &preset) {
    settings->beginGroup(preset);
    if (settings->value("triggerType") !=
        m_activeSettings->getRootNode()->name()) {
        QMessageBox *wrongCamMsg = new QMessageBox();
        wrongCamMsg->setText("Preset for wrong trigger type!");
        wrongCamMsg->show();
        settings->endGroup();
        return;
    }
    loadSettingsLayer(m_activeSettings->getRootNode());
    emit loadPreset(m_activeSettings);
    settings->endGroup();
}

void TriggerSettingsWindow::frameRateEditChangedSlot(int val) {
    TriggerInterface::triggerInstance->changeSimpleSetting(
        "FrameRate", QString::number(val));
}
void TriggerSettingsWindow::frameLimitEditChangedSlot(double val) {
    TriggerInterface::triggerInstance->changeSimpleSetting(
        "FrameLimit", QString::number(val, 'd'));
}
void TriggerSettingsWindow::cmdDelayEditChangedSlot(double val) {
    TriggerInterface::triggerInstance->changeSimpleSetting(
        "CmdDelay", QString::number(val, 'd'));
}

void TriggerSettingsWindow::syncRisingEdgeToggleChangedSlot(bool val) {
    TriggerInterface::triggerInstance->changeSimpleSetting(
        "SyncRisingEdge", QString::number(val));
}
