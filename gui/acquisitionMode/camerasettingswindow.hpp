/*------------------------------------------------------------
 *  camerasettingswindow.hpp
 *  Created: 23. October 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#ifndef CAMERASETTINGSWINDOW_H
#define CAMERASETTINGSWINDOW_H

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
#include <QDoubleSpinBox>

class CameraSettingsWindow : public QDockWidget {
	Q_OBJECT
	public:
		explicit CameraSettingsWindow(QWidget *parent = nullptr, const QString& name = "", settingsObject *activeSettings = nullptr);

	public slots:
		void setSettingsObjectSlot(settingsObject*);

	signals:
		void loadPreset(settingsObject*);

	private:
		QSettings *settings;
		QString settingsName;
		QGridLayout *layout;
		QList<QString> presets;
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
		ToggleSwitch *exposureToggle;
		QSpinBox *exposureEdit;
		ToggleSwitch *gainToggle;
		QDoubleSpinBox *gainEdit;
		QSpinBox *widthEdit;
		QSpinBox *heightEdit;
		QSpinBox *horizontalOffsetEdit;
		QSpinBox *verticalOffsetEdit;
		ToggleSwitch *flipHorizontalToggle;
		ToggleSwitch *flipVerticalToggle;


		settingsObject *m_activeSettings = nullptr;

		void saveSettingsLayer(SettingsNode* node);
		void loadSettingsLayer(SettingsNode* node);

		int searchRecursive(QTreeWidgetItem * parent, QList<QTreeWidgetItem *> results);

	private slots:
		void searchEditedSlot(const QString& text);
		void advancedSimpleToggledSlot(bool toggle);
		void expandClickedSlot();
		void treeItemActivatedSlot(QTreeWidgetItem* item, int column);
		void savePresetsClickedSlot();
		void loadPresetsClickedSlot();
};

#endif
