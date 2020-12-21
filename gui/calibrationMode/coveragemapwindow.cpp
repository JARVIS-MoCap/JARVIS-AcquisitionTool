/*------------------------------------------------------------
 *  coveragemapwindow.cpp
 *  Created: 11. November 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#include "coveragemapwindow.hpp"

#include <QLabel>

CoverageMapWindow::CoverageMapWindow(QWidget *parent) : QDockWidget(parent, Qt::Window) {
	this->setMinimumSize(400,300);
	this->setWindowTitle("Coverage Map");
	mainWidget = new QWidget();
	this->setWidget(mainWidget);
	QGridLayout *layout = new QGridLayout(mainWidget);

	toolBar = new QToolBar(this);
	toolBar->setFixedHeight(40);
	toolBar->setIconSize(QSize(25,25));
	toolBar->setStyleSheet("QToolBar {background-color: palette(base);}");
	QLabel *toolBarLabel = new QLabel("Coverage Map");
	toolBarLabel->setFont(fonts["bold"]);
	QWidget *spacer = new QWidget();
	spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	toolBar->addWidget(toolBarLabel);
	toolBar->addWidget(spacer);
	this->setTitleBarWidget(toolBar);

	heatMapWidget = new QWidget(this);
	heatMapWidget->setMinimumSize(500,100);
	QGridLayout *heatmaplayout = new QGridLayout(heatMapWidget);
	QLabel *primaryHeatLabel = new QLabel("Primary");
	primaryHeatLabel->setFont(fonts["big"]);
	primaryHeatMap = new QLabel();
	QPixmap heatMap = QPixmap("heatmap.jpeg");
	primaryHeatMap->setPixmap(heatMap.scaled(QSize(220,220)));
	primaryHeatMap->setMinimumSize(220,220);
	QLabel *secondaryHeatLabel = new QLabel("Secondary");
	secondaryHeatLabel->setFont(fonts["big"]);
	secondaryHeatMap = new QLabel();
	secondaryHeatMap->setPixmap(heatMap.scaled(QSize(220,220)));
	secondaryHeatMap->setMinimumSize(220,220);

	heatmaplayout->addWidget(primaryHeatLabel,0,0, Qt::AlignCenter);
	heatmaplayout->addWidget(primaryHeatMap,1,0,Qt::AlignCenter);
	heatmaplayout->addWidget(secondaryHeatLabel,0,1,Qt::AlignCenter);
	heatmaplayout->addWidget(secondaryHeatMap,1,1,Qt::AlignCenter);

	layout->addWidget(heatMapWidget,0,0);


}
