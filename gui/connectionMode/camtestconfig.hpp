/*------------------------------------------------------------
 *  camtestconfig.hpp
 *  Created: 23. October 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#ifndef CAMTESTCONFIG_H
#define CAMTESTCONFIG_H

#include "globals.hpp"
#include "camconfiginterface.hpp"

#include <QStackedWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>


class CamTestConfig : public CamConfigInterface {
	Q_OBJECT
public:
	explicit CamTestConfig(QWidget *parent = 0);

	QLineEdit *example1Edit;
	QLineEdit *example2Edit;
	QLineEdit *example1Info;
	QLineEdit *example2Info;

	void confirmConfigClicked();
	void loadPreset(QSettings *settings);
	void savePreset(QSettings *settings);
	CameraInterface* getCamera(const QString &cameraName);

private:

signals:

private slots:
};

#endif
