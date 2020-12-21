/*------------------------------------------------------------
 *  calibrationmode.cpp
 *  Created: 11. November 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#include "calibrationmode.hpp"

CalibrationMode::CalibrationMode(QMainWindow *parent) : QMainWindow(parent) {
	calibrationWidget = new CalibrationWidget(this);
	this->setCentralWidget(calibrationWidget);

	//--- SIGNAL-SLOT Connections ---//
	//-> Incoming Signals

	//<- Outgoing Signals

	//<-> Relayed Signals
	connect(this, &CalibrationMode::camListChanged, calibrationWidget, &CalibrationWidget::camListChangedSlot);
}
