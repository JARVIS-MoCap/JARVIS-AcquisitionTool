/*******************************************************************************
 * File:        latencychartview.cpp
 * Created:     03. December 2021
 * Author:      Timo Hueser
 * Contact:     timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#include "latencychartview.hpp"

LatencyChartView::LatencyChartView() : QChartView() {
    setMinimumSize(20, 200);
    setMaximumSize(99999, 200);
    chart = new QChart();
    chart->layout()->setContentsMargins(0, 0, 0, 0);
    chart->setBackgroundRoundness(0);
    chart->setTheme(QChart::ChartThemeDark);
    chart->setBackgroundBrush(QBrush(QColor(34, 36, 40)));
    chart->legend()->setVisible(false);
    lineSeries = new QSplineSeries();
    QPen pen = lineSeries->pen();
    pen.setWidth(2);
    pen.setColor(QColor(100, 164, 32));
    lineSeries->setPen(pen);
    chart->addSeries(lineSeries);
    axisX = new QValueAxis;
    axisX->setTickCount(2);
    axisX->setLabelFormat("@");
    chart->addAxis(axisX, Qt::AlignBottom);
    lineSeries->attachAxis(axisX);
    axisY = new QValueAxis;
    axisY->setLabelFormat("%.1f");
    axisY->setTitleText("Latency [ms]");
    chart->addAxis(axisY, Qt::AlignLeft);
    lineSeries->attachAxis(axisY);
    this->setChart(chart);
    axisX->setRange(0, 40);
    axisY->setRange(0, 0.9);
    axisX->setGridLineVisible(false);
    axisY->setGridLineVisible(false);
    axisY->setTickCount(3);
    this->setRenderHint(QPainter::Antialiasing);
}

void LatencyChartView::update(int value) {
    if (m_values.size() > 39) {
        m_values.erase(m_values.begin());
    }
    m_values.push_back(static_cast<double>(value) / 1000.0);
    double maxValue = *std::max_element(m_values.begin(), m_values.end());
    axisY->setRange(0.0, 1.3 * maxValue);
    lineSeries->clear();
    lineSeries->blockSignals(true);
    for (int i = 0; i < m_values.size(); i++) {
        if (i == m_values.size() - 2) {
            lineSeries->blockSignals(false);
        }
        lineSeries->append(i, m_values.at(i));
    }
}
