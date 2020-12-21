/*------------------------------------------------------------
 *  calibrationcontrolbar.hpp
 *  Created: 23. October 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#ifndef CALIBRATIONCONTROLBAR_H
#define CALIBRATIONCONTROLBAR_H

#include "globals.hpp"
#include "camerainterface.hpp"

#include <QLabel>
#include <QLineEdit>
#include <QToolBar>


class CalibrationControlBar : public QToolBar {
	Q_OBJECT
	public:
		explicit CalibrationControlBar(QWidget *parent = nullptr);

	public slots:
		void activateCalibrateButton();
		void counterChangedSlot(int count);
		void calibrationFinishedSlot();

	signals:
		void startAcquisition(AcquisitionSpecs);
		void stopAcquisition();
		void calibrateClicked();
		void recalibrateClicked();
		void resetClicked();

	private:
		QSettings *settings;
		QToolButton *startButton;
		QAction *startAction;
		QToolButton *stopButton;
		QAction *stopAction;
		QToolButton *pauseButton;
		QAction *pauseAction;
		QLabel *recordingTimeLabel;
		QTimer *recordingTimer;
		QTime *recordingTime;
		QLabel *counterLabel;
		QLineEdit *counterEdit;
		QPushButton *calibrateButton;
		QAction *calibrateAction;
		QPushButton *recalibrateButton;
		QAction *recalibrateAction;
		QPushButton *resetButton;
		QAction *resetAction;
		QPushButton *saveButton;
		QAction *saveAction;

	private slots:
		void startClickedSlot(bool toggled);
		void pauseClickedSlot(bool toggled);
		void stopClickedSlot();
		void recordingTimerSlot();
		void resetClickedSlot();
};

#endif
