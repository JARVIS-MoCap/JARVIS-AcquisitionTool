/*******************************************************************************
 * File:			  triggersettingswinow.hpp
 * Created: 	  23. October 2020
 * Author:		  Timo Hueser
 * Contact: 	  timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#ifndef TRIGGERSETTINGSWINDOW_H
#define TRIGGERSETTINGSWINDOW_H

#include "globals.hpp"
#include "presetswindow.hpp"
#include "settingsnode.hpp"
#include "settingsobject.hpp"
#include "savecamerapresetsinterface.hpp"
#include "loadcamerapresetsinterface.hpp"
#include "toggleswitch.hpp"

#include <QDockWidget>
#include <QSplitter>
#include <QTextEdit>
#include <QStackedWidget>
#include <QSpinBox>


class TriggerSettingsWindow : public QDockWidget {
	Q_OBJECT
	public:
		explicit TriggerSettingsWindow(QWidget *parent = nullptr,
					SettingsObject *activeSettings = nullptr);

	public slots:
		void setSettingsObjectSlot(SettingsObject*);

	signals:
		void loadPreset(SettingsObject*);

	private:
		QSettings *settings;
		QString settingsName;
		QGridLayout *layout;
		QList<QString> presets;
		PresetsWindow *loadPresetsWindow;
		PresetsWindow *savePresetsWindow;
		SaveCameraPresetsInterface *saveCameraPresetsWindow;
		LoadCameraPresetsInterface *loadCameraPresetsWindow;


		QSplitter *mainSplitter;
		QWidget *mainWidget;
		QToolBar *toolBar;
		QToolButton *advancedSimpleButton;
		QAction *advancedSimpleAction;
		QToolButton *expandButton;
		QAction *expandAction;
		QToolButton *savePresetButton;
		QAction *savePresetAction;
		QToolButton *loadPresetButton;
		QAction *loadPresetAction;

		QTextEdit *toolTipBox;

		QToolBar *searchBar;
		QLineEdit *searchEdit;

		QStackedWidget *advancedSimpleStackWidget;
		QSpinBox *frameRateEdit;

		SettingsObject *m_activeSettings = nullptr;

		void saveSettingsLayer(SettingsNode* node);
		void loadSettingsLayer(SettingsNode* node);

		int searchRecursive(QTreeWidgetItem * parent,
					QList<QTreeWidgetItem *> results);


	private slots:
		void searchEditedSlot(const QString& text);
		void advancedSimpleToggledSlot(bool toggle);
		void expandClickedSlot();
		void treeItemActivatedSlot(QTreeWidgetItem* item, int column);
		void savePresetsClickedSlot();
		void loadPresetsClickedSlot();
		void savePresetSlot(const QString& preset);
		void loadPresetSlot(const QString& preset);
		void frameRateEditChangedSlot(int val);
};

#endif
