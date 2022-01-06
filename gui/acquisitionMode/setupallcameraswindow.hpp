/*******************************************************************************
 * File:			  setupallcameraswindow.hpp
 * Created: 	  06. January 2022
 * Author:		  Timo Hueser
 * Contact: 	  timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#ifndef SETUPALLCAMERASWINDOW_H
#define SETUPALLCAMERASWINDOW_H

#include "globals.hpp"
#include "toggleswitch.hpp"

#include <QDockWidget>
#include <QSplitter>
#include <QTextEdit>
#include <QStackedWidget>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QDialog>
#include <QSettings>
#include <QPushButton>



class SetupAllCamerasWindow : public QDialog {
	Q_OBJECT

	public:
		explicit SetupAllCamerasWindow(QWidget *parent = nullptr);

		CameraSettings& getSettings()  {return m_cameraSettings;}

	public slots:

	signals:

	private:
		QSettings *settings;
		CameraSettings m_cameraSettings;
		void loadSettings();
		void saveSettings();

		ToggleSwitch *loadDefaultUserSetToggle;
		ToggleSwitch *externalTriggerToggle;
		ToggleSwitch *exposureAutoToggle;
		QDoubleSpinBox *exposureEdit;
		ToggleSwitch *gainAutoToggle;
		QDoubleSpinBox *gainEdit;
		//QComboBox *pixelFormatBox;
		QPushButton *setupButton;

	private slots:
		void exposureAutoToggledSlot(bool toggle);
		void gainAutoToggledSlot(bool toggle);
		void setupButtonClickedSlot();
};


#endif
