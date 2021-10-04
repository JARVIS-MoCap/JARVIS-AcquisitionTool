/*****************************************************************
 * File:			  flirchameleonconfig.hpp
 * Created: 	  03. October 2021
 * Author:		  Timo Hueser
 * Contact: 	  timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     GPL v3.0
 *****************************************************************/

#ifndef FLIRCHAMELEONCONFIG_H
#define FLIRCHAMELEONCONFIG_H

#include "globals.hpp"
#include "camconfiginterface.hpp"
#include "flirconfigbackend.hpp"

#include <QComboBox>
#include <QLineEdit>


class FlirChameleonConfig : public CamConfigInterface {
	Q_OBJECT
	public:
		explicit FlirChameleonConfig(QWidget *parent = 0);

		QComboBox *camIDCombo;
		QPushButton *updateCamIDsButton;
		QLineEdit *camIDInfo;

		bool confirmConfigClicked();
		void loadPreset(QSettings *settings);
		void savePreset(QSettings *settings);
		CameraInterface* getCamera(const QString &cameraName);

	private:
		FlirConfigBackend *configBackend;
		void updateDeviceIDs();

	private slots:
		void updateCamIDs();
};

#endif
