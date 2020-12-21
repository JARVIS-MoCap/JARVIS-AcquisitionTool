/*------------------------------------------------------------
 *  calibrationstatisticswindow.cpp
 *  Created: 11. November 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#include "calibrationstatisticswindow.hpp"

#include <random>

#include <QLabel>

CalibrationStatisticsWindow::CalibrationStatisticsWindow(QWidget *parent) : QDockWidget(parent, Qt::Window) {
	std::default_random_engine generator;
	std::normal_distribution<double> distribution(5.0,2.0);
	this->setMinimumSize(300,300);
	this->setWindowTitle("Reprojection Errors");
	mainWidget = new QWidget();
	this->setWidget(mainWidget);
	QGridLayout *layout = new QGridLayout(mainWidget);
	//layout->setMargin(0);

	toolBar = new QToolBar(this);
	toolBar->setFixedHeight(40);
	toolBar->setIconSize(QSize(25,25));
	toolBar->setStyleSheet("QToolBar {background-color: palette(base);}");
	QLabel *toolBarLabel = new QLabel("Reprojection Errors");
	toolBarLabel->setFont(fonts["bold"]);
	QWidget *spacer = new QWidget();
	spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	toolBar->addWidget(toolBarLabel);
	toolBar->addWidget(spacer);
	this->setTitleBarWidget(toolBar);

	chartView = new QChartView();
	chartView->setStyleSheet("plotOptions: {series: {groupPadding: 0,pointPadding: 0}}");
 	chartView->setRenderHint(QPainter::Antialiasing);

	thresholdSlider = new QSlider(Qt::Vertical);
	thresholdSlider->setValue(50);
	thresholdSlider->setEnabled(false);
	connect(thresholdSlider, &QSlider::valueChanged, this, &CalibrationStatisticsWindow::thresholdChangedSlot);

	QLabel *thresholdLabel = new QLabel("Threshold:");
	thresholdEdit = new QLineEdit();
	thresholdEdit->setReadOnly(true);
	removeButton = new QPushButton("Remove");
	connect(removeButton, &QPushButton::clicked, this, &CalibrationStatisticsWindow::removeClickedSlot);

	layout->addWidget(thresholdSlider, 0,0);
	layout->addWidget(chartView,0,1,1,3);
	layout->addWidget(thresholdLabel,1,1);
	layout->addWidget(thresholdEdit, 1,2);
	layout->addWidget(removeButton,1,3);

	QChart *chart = new QChart();
	chart->setTheme(QChart::ChartThemeDark);
	chart->setBackgroundBrush(QBrush(QColor(34, 36, 40)));
	chart->legend()->setVisible(false);
	chartView->setChart(chart);

}

void CalibrationStatisticsWindow::plotData() {
	QChart *chart = new QChart();
	//chart->setAnimationOptions(QChart::SeriesAnimations);
	chart->setTheme(QChart::ChartThemeDark);
	chart->setBackgroundBrush(QBrush(QColor(34, 36, 40)));
	chart->legend()->setVisible(false);
	m_minValue = *std::min_element(m_reproErrors->begin(), m_reproErrors->end());
	m_minValue = m_minValue-(m_minValue*0.1);
	m_maxValue = *std::max_element(m_reproErrors->begin(), m_reproErrors->end());
	m_maxValue = m_maxValue+(m_maxValue*0.1);
	thresholdEdit->setText(QString::number(m_maxValue));
	QValueAxis *axisY = new QValueAxis();
	axisY->setRange(m_minValue,m_maxValue);
	chart->addAxis(axisY, Qt::AlignLeft);
	chartView->setChart(chart);
	for (const auto& error : *m_reproErrors) {
		QBarSeries *series = new QBarSeries();
		QBarSet * set = new QBarSet("Test");
		if (error > m_reproErrorThreshold) {
			set->setColor(QColor(100,32,164));
			set->setBorderColor(QColor(100,32,164));
			*set << error;
		}
		else {
			set->setColor(QColor(100,164,32));
			set->setBorderColor(QColor(100,164,32));
			*set << error;
		}
		series->append(set);
		chart->addSeries(series);
		series->attachAxis(axisY);
	}
}

void CalibrationStatisticsWindow::clearDataSlot() {
	m_reproErrors = nullptr;
	m_objectPointsIntrinsics = nullptr;
	m_imagePointsIntrinsics = nullptr;
	thresholdSlider->setEnabled(false);
	QChart *chart = new QChart();
	chart->setTheme(QChart::ChartThemeDark);
	chart->setBackgroundBrush(QBrush(QColor(34, 36, 40)));
	chart->legend()->setVisible(false);
	chartView->setChart(chart);

}

void CalibrationStatisticsWindow::setData(std::vector<double> *reproErrors, std::vector<std::vector<cv::Point3f>> *objectPointsIntrinsics,
				std::vector<std::vector<cv::Point2f>> *imagePointsIntrinsics) {
	m_reproErrors = reproErrors;
	m_objectPointsIntrinsics = objectPointsIntrinsics;
	m_imagePointsIntrinsics = imagePointsIntrinsics;
	thresholdSlider->setValue(100);
	thresholdSlider->setEnabled(true);
	plotData();
}

void CalibrationStatisticsWindow::thresholdChangedSlot() {
	m_reproErrorThreshold = (thresholdSlider->value()/100.0*(m_maxValue-m_minValue)+m_minValue)+0.01*(m_maxValue-m_minValue);
	thresholdEdit->setText(QString::number(m_reproErrorThreshold));
	plotData();
}

void CalibrationStatisticsWindow::removeClickedSlot() {
	for (int i = 0; i < m_reproErrors->size(); i++) {
		if ((*m_reproErrors)[i] > m_reproErrorThreshold) {
			m_reproErrors->erase(m_reproErrors->begin()+i);
			m_objectPointsIntrinsics->erase(m_objectPointsIntrinsics->begin()+i);
			m_imagePointsIntrinsics->erase(m_imagePointsIntrinsics->begin()+i);
		}
	}
	plotData();
	emit counterChanged(m_reproErrors->size());
}
