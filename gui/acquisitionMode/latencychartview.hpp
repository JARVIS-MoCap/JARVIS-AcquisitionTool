/*******************************************************************************
 * File:			  latencychartview.hpp
 * Created: 	  03. December 2021
 * Author:		  Timo Hueser
 * Contact: 	  timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#ifndef LATENCYCHARTVIEW_H
#define LATENCYCHARTVIEW_H

#include "globals.hpp"

#include <QGridLayout>
#include <QLabel>
#include <QtCharts>


class LatencyChartView : public QChartView {
	Q_OBJECT

	public:
		explicit LatencyChartView();
		void update(int value);

	private:
		QSplineSeries *lineSeries;

		QChart *chart;
		std::vector<double> m_values;

		QValueAxis *axisX;
		QValueAxis *axisY;
};

#endif
