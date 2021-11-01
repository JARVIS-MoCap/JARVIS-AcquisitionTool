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
#include "camerainterface.hpp"


#include <QDockWidget>
#include <QSplitter>
#include <QTextEdit>
#include <QStackedWidget>
#include <QSpinBox>
#include <QDoubleSpinBox>

class CameraSettingsWindow : public QDockWidget {
	Q_OBJECT
	public:
		explicit CameraSettingsWindow(QWidget *parent = nullptr, SettingsObject *activeSettings = nullptr);

	public slots:
		void setSettingsObjectSlot(SettingsObject*);

	signals:
		void loadPreset(SettingsObject*);

	private:
		QSettings *settings;
		QGridLayout *layout;
		CameraInterface *m_cam;
		SaveCameraPresetsInterface *saveCameraPresetsWindow;
		LoadCameraPresetsInterface *loadCameraPresetsWindow;
		QLabel *settingsLabel;

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
		QDoubleSpinBox *exposureEdit;
		ToggleSwitch *gainToggle;
		QDoubleSpinBox *gainEdit;
		QSpinBox *widthEdit;
		QSpinBox *heightEdit;
		QSpinBox *horizontalOffsetEdit;
		QSpinBox *verticalOffsetEdit;
		ToggleSwitch *flipHorizontalToggle;
		ToggleSwitch *flipVerticalToggle;


		SettingsObject *m_activeSettings = nullptr;

		void saveSettingsLayer(SettingsNode* node);
		void loadSettingsLayer(SettingsNode* node);

		int searchRecursive(QTreeWidgetItem * parent, QList<QTreeWidgetItem *> results);

	private slots:
		void searchEditedSlot(const QString& text);
		void searchReturnPressedSlot();
		void advancedSimpleToggledSlot(bool toggle);
		void expandClickedSlot();
		void treeItemActivatedSlot(QTreeWidgetItem* item, int column);
		void savePresetsClickedSlot();
		void loadPresetsClickedSlot();
		void simpleSettingChangedSlot(const QString& settingName, const QString& value, bool enabled, double min, double max);

		void exposureAutoToggledSlot(bool toggle);
		void exposureEditChangedSlot(double val);
		void gainAutoToggledSlot(bool toggle);
		void gainEditChangedSlot(double val);
		void widthEditChangedSlot(int val);
		void heightEditChangedSlot(int val);
		void horizontalOffsetEditChangedSlot(int val);
		void verticalOffsetEditChangedSlot(int val);
		void flipHorizontalToggledSlot(bool toggle);
		void flipVerticalToggledSlot(bool toggle);
};

#endif
