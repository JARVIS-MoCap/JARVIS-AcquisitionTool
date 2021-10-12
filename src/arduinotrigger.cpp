/*------------------------------------------------------------
 *  arduinotrigger.cpp
 *  Created: 03. October 2021
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#include "arduinotrigger.hpp"

#include <QApplication>
#include <QTimer>

ArduinoTrigger::ArduinoTrigger(const QString& deviceName)
			: TriggerInterface {arduinoTrigger} {
	createSettings();
	serialInterface = new SerialInterface(deviceName);
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(intitialStatusSlot()));
	timer->setSingleShot(true);
	timer->start(100);
}

ArduinoTrigger::~ArduinoTrigger() {
	delete serialInterface;
	delete m_triggerSettings;
}

void ArduinoTrigger::intitialStatusSlot() {
	if (serialInterface->isConnected()) {
		emit statusUpdated(Ready, "");
	}
	else {
		emit statusUpdated(Error, "Connection Failed!");
	}
}

void ArduinoTrigger::createSettings() {
	m_triggerSettingsRootNode = new rootNode("");

	categoryNode *arduinoTriggerNode = new categoryNode(m_triggerSettingsRootNode, "ArduinoTrigger");
	arduinoTriggerNode->setDescription("Arduino Trigger Settings");

	intNode *frameRateNode = new intNode(arduinoTriggerNode, "FrameRate");
	frameRateNode->setDescription("Recording Frame Rate.");
	frameRateNode->setValue(100);

	m_triggerSettingsRootNode->addChild(arduinoTriggerNode);
	arduinoTriggerNode->addChild(frameRateNode);

	m_triggerSettings = new settingsObject(this, "Trigger Settings", m_triggerSettingsRootNode);

	connect(m_triggerSettings, SIGNAL(settingChanged(QString, QList<QString>, SettingsNode::nodeType,
				QString, bool)), this, SLOT(settingChangedSlot(QString, QList<QString>,
				SettingsNode::nodeType, QString,bool)));
}

void ArduinoTrigger::enable() {
	serialInterface->write(1000/m_frameRate);
}

void ArduinoTrigger::disable() {
	serialInterface->write(0);
}

void ArduinoTrigger::settingChangedSlot(const QString& name, QList<QString> subMenus,
			SettingsNode::nodeType type, const QString& val, bool update) {
		if (name == "FrameRate") {
			m_frameRate = val.toInt();
		}
}

void ArduinoTrigger::changeSimpleSetting(const QString& setting, const QString& value) {
	std::cout << setting.toStdString() << ", " << value.toStdString() << std::endl;
	if (setting == "FrameRate") {
		m_frameRate = value.toInt();
		static_cast<intNode*>(m_triggerSettings->findNode("FrameRate"))->setValue(m_frameRate);
	}

}
