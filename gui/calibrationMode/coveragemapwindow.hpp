/*------------------------------------------------------------
 *  coveragemapwindow.hpp
 *  Created: 11. November 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#ifndef COVERAGEMAPWINDOW_H
#define COVERAGEMAPWINDOW_H

#include "globals.hpp"

#include <QDockWidget>
#include <QGridLayout>
#include <QToolBar>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>
#include <QGroupBox>

class CoverageMapWindow : public QDockWidget {
	Q_OBJECT
	public:
		explicit CoverageMapWindow(QWidget *parent = nullptr);

	public slots:

	signals:


	private:
		QWidget *mainWidget;
		QToolBar *toolBar;

		QWidget *heatMapWidget;
		QLabel *primaryHeatMap;
		QLabel *secondaryHeatMap;
	private slots:
};

#endif
