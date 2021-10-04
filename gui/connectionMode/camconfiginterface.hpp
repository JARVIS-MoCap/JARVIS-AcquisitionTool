/*****************************************************************
 * File:			  camconfiginterface.cpp
 * Created: 	  03. October 2021
 * Author:		  Timo Hueser
 * Contact: 	  timo.hueser@gmail.com
 * Copyright:  2021 Timo Hueser
 * License:    GPL v3.0
 *****************************************************************/


#ifndef CAMCONFIGINTERFACE_H
#define CAMCONFIGINTERFACE_H

#include "globals.hpp"
#include "camerainterface.hpp"

#include <QGroupBox>
#include <QSettings>


class CamConfigInterface : public QWidget {
	Q_OBJECT
	public:
		explicit CamConfigInterface(QWidget *parent = 0) {}

		QGroupBox *configEditBox;
		QGroupBox *configInfoBox;

		virtual bool confirmConfigClicked() = 0;
		virtual void loadPreset(QSettings *settings) = 0;
		virtual void savePreset(QSettings *settings) = 0;
		virtual CameraInterface* getCamera(const QString &cameraName) = 0;

	private:

	signals:

	private slots:
};

#endif
