/*------------------------------------------------------------
 *  camconfiginterface.hpp
 *  Created: 23. October 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#ifndef CAMCONFIGINTERFACE_H
#define CAMCONFIGINTERFACE_H

#include "globals.hpp"
#include "camerainterface.hpp"

#include <QStackedWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QSettings>


class CamConfigInterface : public QWidget {
	Q_OBJECT
public:
	explicit CamConfigInterface(QWidget *parent = 0) {}

	QGroupBox *configEditBox;
	QGroupBox *configInfoBox;

	virtual void confirmConfigClicked() = 0;
	virtual void loadPreset(QSettings *settings) = 0;
	virtual void savePreset(QSettings *settings) = 0;
	virtual CameraInterface* getCamera(const QString &cameraName) = 0;

private:

signals:

private slots:
};

#endif
