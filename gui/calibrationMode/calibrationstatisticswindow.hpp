/*------------------------------------------------------------
 *  calibrationstatisticswindow.hpp
 *  Created: 11. November 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#ifndef CALIBRATIONSTATISTICSWINDOW_H
#define CALIBRATIONSTATISTICSWINDOW_H

#include "globals.hpp"

#include <QDockWidget>
#include <QGridLayout>
#include <QToolBar>
#include <QtCharts>


class CalibrationStatisticsWindow : public QDockWidget {
	Q_OBJECT
	public:
		explicit CalibrationStatisticsWindow(QWidget *parent = nullptr);
		void plotData();
		void setData(std::vector<double> *reproErrors, std::vector<std::vector<cv::Point3f>> *objectPointsIntrinsics,
					std::vector<std::vector<cv::Point2f>> *imagePointsIntrinsics);

	public slots:
		void clearDataSlot();

	signals:
		void counterChanged(int count);


	private:
		QWidget *mainWidget;
		QToolBar *toolBar;
		QChartView *chartView;
		QSlider * thresholdSlider;
		QLineEdit *thresholdEdit;
		QPushButton *removeButton;

		std::vector <double> *m_reproErrors;
		std::vector<std::vector<cv::Point3f>> *m_objectPointsIntrinsics;
		std::vector<std::vector<cv::Point2f>> *m_imagePointsIntrinsics;
		double m_reproErrorThreshold = 5;
		double m_minValue = 0;
		double m_maxValue = 10;

	private slots:
		void thresholdChangedSlot();
		void removeClickedSlot();
};

#endif
