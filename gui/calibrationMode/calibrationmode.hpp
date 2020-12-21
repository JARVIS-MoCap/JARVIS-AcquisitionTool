/*------------------------------------------------------------
 *  calibrationmode.hpp
 *  Created: 11. November 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#ifndef CALIBRATIONMODE_H
#define CALIBRATIONMODE_H

#include "globals.hpp"
#include "calibrationwidget.hpp"

#include <QMainWindow>

class CalibrationMode : public QMainWindow {
	Q_OBJECT
	public:
		explicit CalibrationMode(QMainWindow *parent = nullptr);

	public slots:

	signals:
		void camListChanged();

	private:
		CalibrationWidget *calibrationWidget;

	private slots:
};


#endif
