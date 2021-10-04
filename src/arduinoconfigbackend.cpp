/*------------------------------------------------------------
 *  arduinoconfigbackend.cpp
 *  Created: 05. June 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#include "arduinoconfigbackend.hpp"


#include <QApplication>


ArduinoConfigBackend::ArduinoConfigBackend(QObject *parent) : QObject(parent) {

}


QList<QString> ArduinoConfigBackend::getAvailableDevices() {
	return SerialInterface::getAvailableDevices();
}
