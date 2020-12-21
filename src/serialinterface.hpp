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
		SerialInterface();
		int write(int val);
		int send_instruction(int mode, int readwrite, int val1, int val2);
		int get_answer(int answer[]);
		int get_answer();

	bool serial_conn;
	private:
		QString serialPortName;
		QSerialPort *serialPort;
};


#endif
