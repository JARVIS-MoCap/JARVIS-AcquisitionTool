/*------------------------------------------------------------
 *  calibrationwidget.hpp
 *  Created: 11. November 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#ifndef CALIBRATIONWIDGET_H
#define CALIBRATIONWIDGET_H

#include "globals.hpp"
#include "calibrationtool.hpp"

#include <QSettings>
#include <QListWidget>
#include <QGridLayout>


class CalibrationWidget : public QWidget {
	Q_OBJECT
	public:
		explicit CalibrationWidget(QWidget *parent = nullptr);

	public slots:
		void camListChangedSlot();

	signals:
		void cameraSelected(CameraInterface * camera);

	private:
		QSettings *settings;
		QListWidget *cameraList;
		QStackedWidget * stackWidget;
		QWidget *selectionInfoWidget;
		QWidget *loadNewWidget;
		QPushButton *loadCalibrationButton;
		QPushButton *newCalibrationButton;
		CalibrationTool *calibrationTool;
		CameraInterface *m_camera = nullptr;


	private slots:
		void listSelectedSlot(QListWidgetItem * selectedItem);
		void newCalibrationClickedSlot();
};

#endif
