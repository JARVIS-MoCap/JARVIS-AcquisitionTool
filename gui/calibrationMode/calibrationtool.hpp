/*------------------------------------------------------------
 *  calibrationtool.hpp
 *  Created: 11. November 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#ifndef CALIBRATIONTOOL_H
#define CALIBRATIONTOOL_H

#include "globals.hpp"
#include "calibrationcontrolbar.hpp"
#include "streamingpanel.hpp"
#include "calibrationsettingswindow.hpp"
#include "calibrationstatisticswindow.hpp"
#include "coveragemapwindow.hpp"
#include "calibrationbackend.hpp"


#include <QMainWindow>
#include <QSettings>
#include <QListWidget>
#include <QGridLayout>


class CalibrationStreamingWidget : public QWidget {
	Q_OBJECT
	public:
		explicit CalibrationStreamingWidget(QWidget *parent = nullptr);
		StreamingPanel *streamingPanel;

	private:
		QGridLayout *layout;


	private slots:
		void resizeStreamingPanel();
		void resizeEvent(QResizeEvent *) override {resizeStreamingPanel();}
};
		void setMode(const QString& mode);


class CalibrationTool : public QMainWindow {
	Q_OBJECT
	public:
		explicit CalibrationTool(QWidget *parent = nullptr);


	public slots:
		void cameraSelectedSlot(CameraInterface *camera);
		void calibrateClickedSlot();
		void stopAcquisitionSlot();

	signals:
		void activateCalibrateButton();

	private:
		QSettings *settings;
		CalibrationBackend *calibrationBackend;

		CalibrationControlBar *calibrationControlBar;
		CalibrationStreamingWidget *calibrationStreamingWidget;
		CalibrationSettingsWindow *calibrationSettingsWindow;
		CoverageMapWindow *coverageMapWindow;
		CalibrationStatisticsWindow *calibrationStatisticsWindow;
		CameraInterface *m_camera = nullptr;

	private slots:
		void calibrationFinishedSlot();

};

#endif
