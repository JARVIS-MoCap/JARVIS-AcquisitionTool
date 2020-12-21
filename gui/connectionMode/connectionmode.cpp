/*------------------------------------------------------------
 *  acquisitionmode.cpp
 *  Created: 23. October 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#include "connectionmode.hpp"

ConnectionMode::ConnectionMode(QMainWindow *parent) : QMainWindow(parent) {
	connectionWidget = new ConnectionWidget();
	this->setCentralWidget(connectionWidget);

	//--- SIGNAL-SLOT Connections ---//
	//-> Incoming Signals
	connect(connectionWidget, &ConnectionWidget::camListChanged, this, &ConnectionMode::camListChanged);
	connect(connectionWidget, &ConnectionWidget::camAdded, this, &ConnectionMode::camAdded);
	connect(connectionWidget, &ConnectionWidget::triggerInstanceChanged, this, &ConnectionMode::triggerInstanceChanged);
	connect(connectionWidget, &ConnectionWidget::statusUpdated, this, &ConnectionMode::statusUpdated);

	//<- Outgoing Signals

	//<-> Relayed Signals


}
