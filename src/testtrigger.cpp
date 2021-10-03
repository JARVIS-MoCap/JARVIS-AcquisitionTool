/*------------------------------------------------------------
 *  testtrigger.cpp
 *  Created: 23. October 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#include "testtrigger.hpp"

#include <QApplication>
#include <QTreeWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>
#include <QTimer>

TestTrigger::TestTrigger(const QString&, const QString&)
			: TriggerInterface {testTrigger}{
	std::cout << "Creating Trigger" << std::endl;
	createSettings();
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(testStatusReadySlot()));
	timer->setSingleShot(true);
	timer->start(2000);
	QTimer *timer2 = new QTimer(this);
	connect(timer2, SIGNAL(timeout()), this, SLOT(testStatusWarningSlot()));
	timer2->setSingleShot(false);
	timer2->start(5000);
}

TestTrigger::~TestTrigger() {
	delete (m_triggerSettings);
	std::cout << "Deleting Trigger" << std::endl;
}

void TestTrigger::createSettings() {
	m_triggerSettingsRootNode = new rootNode("Test Trigger");

	categoryNode *analogControlNode = new categoryNode(m_triggerSettingsRootNode, "AnalogControl");
	analogControlNode->setDescription("Analog Control, does something probably");
	stringNode *gainSelectorNode = new stringNode(analogControlNode, "GainSelector");
	gainSelectorNode->setDescription("Select the Gain, as a String of course");
	intNode *gainNode = new intNode(analogControlNode, "Gain");
	gainNode->setDescription("Gain, this acutally has the right type");
	floatNode *whiteBalanceNode = new floatNode(analogControlNode, "WhiteBalance");
	whiteBalanceNode->setDescription("Test Text");
	whiteBalanceNode->setDefaultValue(9.8);
	whiteBalanceNode->setRange(0,20);
	enumNode *enumTestNode = new enumNode(analogControlNode, "enumTest");
	enumItemNode *testItem1Node = new enumItemNode(enumTestNode, "Test 1");
	enumItemNode *testItem2Node = new enumItemNode(enumTestNode, "Test 2");
	boolNode *boolTestNode = new boolNode(analogControlNode, "boolTest");
	actionNode *actionTestNode = new actionNode(analogControlNode, "actionTest");
	enumTestNode->addItem(testItem1Node);
	enumTestNode->addItem(testItem2Node);

	analogControlNode->addChild(gainSelectorNode);
	analogControlNode->addChild(gainNode);
	analogControlNode->addChild(whiteBalanceNode);
	analogControlNode->addChild(enumTestNode);
	analogControlNode->addChild(boolTestNode);
	analogControlNode->addChild(actionTestNode);

	categoryNode *deviceControlNode = new categoryNode(m_triggerSettingsRootNode, "DeviceControl");
	m_triggerSettingsRootNode->addChild(analogControlNode);
	m_triggerSettingsRootNode->addChild(deviceControlNode);

	m_triggerSettings = new settingsObject(this, "Trigger Settings", m_triggerSettingsRootNode);
}

void TestTrigger::testStatusReadySlot() {
	emit statusUpdated(Ready,"");
}

void TestTrigger::testStatusWarningSlot() {
	emit statusUpdated(Warning,"This is a test Warning");
}

void TestTrigger::testStatusErrorSlot() {
	emit statusUpdated(Error,"This is a test Error");
}
