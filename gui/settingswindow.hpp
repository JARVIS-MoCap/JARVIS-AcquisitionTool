/*------------------------------------------------------------
 *  settingswinow.hpp
 *  Created: 23. October 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include "globals.hpp"
#include "presetswindow.hpp"
#include "settingsnode.hpp"
#include "settingsobject.hpp"

#include <QDockWidget>
#include <QSplitter>
#include <QTextEdit>

class SettingsWindow : public QDockWidget {
	Q_OBJECT
	public:
		explicit SettingsWindow(QWidget *parent = nullptr, const QString& name = "", settingsObject *activeSettings = nullptr);

	public slots:
		void setSettingsObjectSlot(settingsObject*);

	signals:
		void loadPreset(settingsObject*);

	private:
		QSettings *settings;
		QString settingsName;
		QGridLayout *layout;
		QList<QString> presets;
		PresetsWindow *loadPresetsWindow;
		PresetsWindow *savePresetsWindow;

		QSplitter *mainSplitter;
		QWidget *mainWidget;
		QToolBar *toolBar;
		QToolButton *expandButton;
		QAction *expandAction;
		QToolButton *savePresetButton;
		QAction *savePresetAction;
		QToolButton *loadPresetButton;
		QAction *loadPresetAction;

		QTextEdit *toolTipBox;

		QToolBar *searchBar;
		QLineEdit *searchEdit;

		settingsObject *m_activeSettings = nullptr;
		void saveSettingsLayer(SettingsNode* node);
		void loadSettingsLayer(SettingsNode* node);

		int searchRecursive(QTreeWidgetItem * parent, QList<QTreeWidgetItem *> results);


	private slots:
		void searchEditedSlot(const QString& text);
		void expandClickedSlot();
		void treeItemActivatedSlot(QTreeWidgetItem* item, int column);
		void savePresetsClickedSlot();
		void loadPresetsClickedSlot();
		void loadPresetSlot(const QString& preset);
		void savePresetSlot(const QString& preset);
};

#endif
