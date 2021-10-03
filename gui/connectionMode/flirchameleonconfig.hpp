/*------------------------------------------------------------
 *  flirchameleonconfig.hpp
 *  Created: 23. October 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#ifndef FLIRCHAMELEONCONFIG_H
#define FLIRCHAMELEONCONFIG_H

#include "globals.hpp"
#include "camconfiginterface.hpp"
#include "flirconfigbackend.hpp"

#include <QStackedWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>


class FlirChameleonConfig : public CamConfigInterface {
	Q_OBJECT
public:
	explicit FlirChameleonConfig(QWidget *parent = 0);


	QComboBox *camIDCombo;
	QLineEdit *camIDInfo;

	void confirmConfigClicked();
	void loadPreset(QSettings *settings);
	void savePreset(QSettings *settings);
	CameraInterface* getCamera(const QString &cameraName);

private:
	FlirConfigBackend *configBackend;
	void updateDeviceIDs();

signals:

private slots:
};

#endif
