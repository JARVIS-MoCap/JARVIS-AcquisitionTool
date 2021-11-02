/*******************************************************************************
 * File:			  monitoringwindow.hpp
 * Created: 	  17. October 2021
 * Author:		  Timo Hueser
 * Contact: 	  timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#ifndef MONITORINGWINDOW_H
#define MONITORINGWINDOW_H

#include "globals.hpp"
#include "camerainterface.hpp"
#include "latencychartview.hpp"

#include <QDockWidget>
#include <QSplitter>
#include <QTextEdit>
#include <QStackedWidget>
#include <QSpinBox>
#include <QToolBar>
#include <QLabel>
#include <QScrollArea>
#include <QGroupBox>
#include <QGridLayout>
#include <QProgressBar>


class CameraMonitor;


class MonitoringWindow : public QDockWidget {
	Q_OBJECT

	public:
		explicit MonitoringWindow(QWidget *parent = nullptr);

	public slots:
		void updateListSlot();

	signals:

	private:
		QToolBar *toolBar;
		QGridLayout *mainlayout;
		QToolButton *showGraphsButton;
		QAction *showGraphsAction;
		QMap<CameraInterface*,CameraMonitor*> cameraMonitorMap;
		void updateBufferStates();

	private slots:
		void showGraphsSlot(bool toggle);
};


class CameraMonitor : public QGroupBox {
	Q_OBJECT

	public:
		explicit CameraMonitor(CameraInterface *cam, QWidget *parent = nullptr);
		void updateBufferState();
		unsigned long getFrameNumber() {return m_frameNumber;}
		void toggleGraph(bool toggle);

	public slots:
		void latencyAndFrameNumberUpdateSlot(int latency,
					unsigned long frameNumber);

	private:
		CameraInterface * m_cam;
		unsigned long m_frameNumber = 0;
		QProgressBar *bufferStatusBar;
		QSpinBox *latencyEdit;
		int m_bufferUpdateCounter = 0;
		LatencyChartView *latencyChartView;

};


#endif
