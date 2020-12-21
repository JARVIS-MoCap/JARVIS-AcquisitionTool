/*------------------------------------------------------------
 *  calibrationsettingswindow.hpp
 *  Created: 11. November 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#ifndef CALIBRATIONSETTINGSWINDOW_H
#define CALIBRATIONSETTINGSWINDOW_H

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

class CalibrationSettingsWindow : public QDockWidget {
	Q_OBJECT
	public:
		explicit CalibrationSettingsWindow(QWidget *parent = nullptr);

	public slots:

	signals:


	private:
		QWidget *mainWidget;
		QToolBar *toolBar;

		QComboBox *boardTypeCombo;
		QLineEdit *boardHeightEdit;
		QLineEdit *boardWidthEdit;
		QLineEdit *sideLengthEdit;
		QCheckBox *enebaleMinimumSizeToggle;
		QLineEdit *minimumSizeEdit;

		QWidget *heatMapWidget;
		QLabel *primaryHeatMap;
		QLabel *secondaryHeatMap;
	private slots:
};

#endif
