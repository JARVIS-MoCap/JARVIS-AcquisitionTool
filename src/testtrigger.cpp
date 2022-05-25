/*******************************************************************************
 * File:        testtrigger.cpp
 * Created:     05. June 2020
 * Author:      Timo Hueser
 * Contact:     timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#include "testtrigger.hpp"

#include <QApplication>
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTimer>
#include <QTreeWidget>

TestTrigger::TestTrigger(const QString &, const QString &)
    : TriggerInterface{testTrigger} {
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
    m_triggerSettingsRootNode = new RootNode("Test Trigger");

    CategoryNode *analogControlNode =
        new CategoryNode(m_triggerSettingsRootNode, "AnalogControl");
    analogControlNode->setDescription(
        "Analog Control, does something probably");
    StringNode *gainSelectorNode =
        new StringNode(analogControlNode, "GainSelector");
    gainSelectorNode->setDescription("Select the Gain, as a String of course");
    IntNode *gainNode = new IntNode(analogControlNode, "Gain");
    gainNode->setDescription("Gain, this acutally has the right type");
    FloatNode *whiteBalanceNode =
        new FloatNode(analogControlNode, "WhiteBalance");
    whiteBalanceNode->setDescription("Test Text");
    whiteBalanceNode->setDefaultValue(9.8);
    whiteBalanceNode->setRange(0, 20);
    EnumNode *enumTestNode = new EnumNode(analogControlNode, "enumTest");
    EnumItemNode *testItem1Node = new EnumItemNode(enumTestNode, "Test 1");
    EnumItemNode *testItem2Node = new EnumItemNode(enumTestNode, "Test 2");
    BoolNode *boolTestNode = new BoolNode(analogControlNode, "boolTest");
    ActionNode *actionTestNode =
        new ActionNode(analogControlNode, "actionTest");
    enumTestNode->addItem(testItem1Node);
    enumTestNode->addItem(testItem2Node);

    analogControlNode->addChild(gainSelectorNode);
    analogControlNode->addChild(gainNode);
    analogControlNode->addChild(whiteBalanceNode);
    analogControlNode->addChild(enumTestNode);
    analogControlNode->addChild(boolTestNode);
    analogControlNode->addChild(actionTestNode);

    CategoryNode *deviceControlNode =
        new CategoryNode(m_triggerSettingsRootNode, "DeviceControl");
    m_triggerSettingsRootNode->addChild(analogControlNode);
    m_triggerSettingsRootNode->addChild(deviceControlNode);

    m_triggerSettings =
        new SettingsObject(this, "Trigger Settings", m_triggerSettingsRootNode);
}

void TestTrigger::testStatusReadySlot() { emit statusUpdated(Ready, ""); }

void TestTrigger::testStatusWarningSlot() {
    emit statusUpdated(Warning, "This is a test Warning");
}

void TestTrigger::testStatusErrorSlot() {
    emit statusUpdated(Error, "This is a test Error");
}
