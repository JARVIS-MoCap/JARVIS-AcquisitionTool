/*------------------------------------------------------------
 *  SerialInterface.cpp
 *  Created:  10. July 2018
 *  Author:   Timo Hüser
 *
 *  Implementation of the Serial interface to communicate with the Arduino using the QSerialPort library
 *------------------------------------------------------------*/

#include "serialinterface.hpp"

QList<QString> SerialInterface::getAvailableDevices() {
	QList<QSerialPortInfo> serialPortInfos = QSerialPortInfo::availablePorts();
	QList<QString> deviceNames;
	for (const auto& port : serialPortInfos) {
		deviceNames.append(port.description());
	}
	return deviceNames;
}


SerialInterface::SerialInterface(const QString& deviceName) {
	QList<QSerialPortInfo> serialPortInfos = QSerialPortInfo::availablePorts();
	for (int i= 0; i <  serialPortInfos.count(); i++) {
		if (serialPortInfos[i].description() == deviceName) {	//"0043" is the identifier used by the Arduino, probably different for other Arduinos
			serialPortName = serialPortInfos[i].portName();
			std::cout << serialPortName.toStdString() << std::endl;
			serialPort = new QSerialPort();
			serialPort->setPortName(serialPortName);
			if(serialPort->open(QIODevice::ReadWrite)) {	//standard Serial port settings, if coms buggy changing baud rate here and on the arduino might help
				serial_conn = true;
				serialPort->setBaudRate(QSerialPort::Baud115200);
				serialPort->setParity(QSerialPort::NoParity);
				serialPort->setStopBits(QSerialPort::OneStop);
				serialPort->setFlowControl(QSerialPort::NoFlowControl);
				serialPort->setDataBits(QSerialPort::Data8);
				delayl(1000);	//Important!! Arduino goes into serial programming mode if this delay is removed
				return;
			}
		}
	}
}

SerialInterface::~SerialInterface()  {
	serialPort->close();
}

int SerialInterface::write(int val) {
	QByteArray cmd;
	cmd[0] = val >> 8;
	cmd[1] = val;
	if (serial_conn) {
		serialPort->write(cmd);
		serialPort->waitForBytesWritten(1);
		return 1;
	}
	return 0;
}

int SerialInterface::send_instruction(int mode, int readwrite, int val1, int val2) {
	QByteArray cmd;
	cmd[0] = mode;
	cmd[1] = readwrite;
	cmd[2] = val1 >> 8;
	cmd[3] = val1;
	cmd[4] = val2 >> 8;
	cmd[5] = val2;
	if (serial_conn) {
		serialPort->write(cmd);
		serialPort->waitForBytesWritten(1);
	}
	else return 0;
	return 1;
}

int SerialInterface::get_answer(int answer[]) {
	uint8_t temp[5];
	temp[0] = 0;
	for (int i = 0; i < 5; i++) {
		serialPort->waitForReadyRead(10);
	}
	int nread = serialPort->read((char*)temp, 5);
	if (nread != 5) {
		std::cout  << "Error Reading Answer" << std::endl;
		return 0;
	}
	answer[0] = ((int8_t)temp[1]<<8) + temp[2];
	answer[1] = ((int8_t)temp[3]<<8) + temp[4];
	return (int) (temp[0]);

}

int SerialInterface::get_answer() {
	uint8_t temp[5];
	temp[0] = 0;
		for (int i = 0; i < 5; i++) {
			serialPort->waitForReadyRead(10);
		}
	int nread = serialPort->read((char*)temp, 5);
	if (nread != 5) {
		std::cout << "Error Reading Answer" << std::endl;
		return 0;
	}
	return (int)(temp[0]);
}
