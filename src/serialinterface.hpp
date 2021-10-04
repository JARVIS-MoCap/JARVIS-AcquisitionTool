/*------------------------------------------------------------
 *  serialinterface.hpp
 *  Created: 23 June 2020
 *  Author:  Timo Hüser
 *------------------------------------------------------------*/

#ifndef SERIALINTERFACE_H
#define SERIALINTERFACE_H

#include "globals.hpp"
#include <QtSerialPort/QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>

class SerialInterface {
	public:
		static QList<QString> getAvailableDevices();
		SerialInterface(const QString& deviceName);
		~SerialInterface();
		int write(int val);
		int send_instruction(int mode, int readwrite, int val1, int val2);
		int get_answer(int answer[]);
		int get_answer();
		bool isConnected() {return serial_conn;}
	private:
		bool serial_conn = false;
		QString serialPortName;
		QSerialPort *serialPort;
};


#endif
