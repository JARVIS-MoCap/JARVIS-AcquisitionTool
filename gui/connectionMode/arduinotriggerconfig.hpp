/*******************************************************************************
 * File:			  arduinotriggerconfig.hpp
 * Created: 	  03. October 2021
 * Author:		  Timo Hueser
 * Contact: 	  timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#ifndef ARDUINOTRIGGERCONFIG_H
#define ARDUINOTRIGGERCONFIG_H

#include "globals.hpp"
#include "triggerconfiginterface.hpp"
#include "triggerinterface.hpp"
#include "arduinoconfigbackend.hpp"

#include <QLineEdit>
#include <QComboBox>


class ArduinoTriggerConfig : public TriggerConfigInterface {
	Q_OBJECT
	
	public:
		explicit ArduinoTriggerConfig(QWidget *parent = 0);
		ArduinoConfigBackend *configBackend;

		QComboBox *deviceNameCombo;
		QPushButton *updateDeviceNamesButton;
		QLineEdit *deviceNameInfo;

		bool confirmConfigClicked();
		void loadPreset(QSettings *settings);
		void savePreset(QSettings *settings);
		TriggerInterface* getTrigger();

	private:
		QList<QString> availableDevices;

	private slots:
		void updateDeviceNamesSlot();
};

#endif
