/*******************************************************************************
 * File:			  arduinoconfigbackend.cpp
 * Created: 	  05. September 2021
 * Author:		  Timo Hueser
 * Contact: 	  timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#include "arduinoconfigbackend.hpp"

#include <QApplication>


ArduinoConfigBackend::ArduinoConfigBackend(QObject *parent) : QObject(parent) {

}


QList<QString> ArduinoConfigBackend::getAvailableDevices() {
	return SerialInterface::getAvailableDevices();
}
