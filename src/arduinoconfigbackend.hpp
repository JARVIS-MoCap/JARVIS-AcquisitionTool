/*------------------------------------------------------------
 *  arduinoconfigbackend.hpp
 *  Created: 05. June 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#ifndef ARDUINOCONFIGBACKEND_H
#define ARDUINOCONFIGBACKEND_H

#include "globals.hpp"
#include "serialinterface.hpp"


class ArduinoConfigBackend : public QObject {
	Q_OBJECT
	public:
		static ArduinoConfigBackend* getInstance()
        {
            static ArduinoConfigBackend    instance; // Guaranteed to be destroyed.
                                  // Instantiated on first use.
            return &instance;
        }
		explicit ArduinoConfigBackend(QObject *parent = nullptr);

		QList<QString> getAvailableDevices();

	private:
		QList<QString> availableDevices;
};


#endif
