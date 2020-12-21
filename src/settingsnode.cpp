/*------------------------------------------------------------
 *  settingsnode.cpp
 *  Created: 23. October 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#include "settingsnode.hpp"

#include <QApplication>
#include <QTreeWidget>


SettingsNode::SettingsNode(nodeType type, SettingsNode* parent, const QString& name)
			: m_type{type},
			  m_parent{parent},
			  m_name{name},
				m_displayName{name}
{ }

rootNode::rootNode(const QString& name)
			: SettingsNode{Root, nullptr, name}
{ }


categoryNode::categoryNode(SettingsNode *parent, const QString& name)
			: SettingsNode{Category, parent, name}
{ }


stringNode::stringNode(SettingsNode *parent, const QString& name)
			: SettingsNode{String, parent, name}  {
	m_dataField = new QLineEdit();
	static_cast<QLineEdit*>(m_dataField)->setFrame(false);
	this->setDefaultValue(m_defaultValue);
	connect(this->m_dataField, SIGNAL(textEdited(QString)), this, SLOT(dataChangedSlot(QString)));
}


intNode::intNode(SettingsNode *parent, const QString& name)
			: SettingsNode{Integer, parent, name} {
	m_dataField = new QLineEdit();
	static_cast<QLineEdit*>(m_dataField)->setFrame(false);
	static_cast<QLineEdit*>(m_dataField)->setValidator(new QIntValidator(m_minValue, m_maxValue, this));
	this->setValue(m_defaultValue);
	connect(this->m_dataField, SIGNAL(textEdited(QString)), this, SLOT(dataChangedSlot(QString)));
}


floatNode::floatNode(SettingsNode *parent, const QString& name)
			: SettingsNode{Float, parent, name} {
	m_dataField = new QLineEdit();
	static_cast<QLineEdit*>(m_dataField)->setFrame(false);
	this->setDefaultValue(m_defaultValue);
	connect(this->m_dataField, SIGNAL(returnPressed()), this, SLOT(returnPressedSlot()));
	connect(this, SIGNAL(returnPressed(QString)), this, SLOT(dataChangedSlot(QString)));
}

void floatNode::returnPressedSlot() {
	emit returnPressed(static_cast<QLineEdit*>(m_dataField)->text());
}


enumItemNode::enumItemNode(SettingsNode *parent, const QString& name)
			: SettingsNode{EnumerationItem, parent, name}
{ }


enumNode::enumNode(SettingsNode *parent, const QString& name)
			: SettingsNode{Enumeration, parent, name} {
	m_dataField = new QComboBox();
	connect(this->m_dataField, SIGNAL(currentTextChanged(QString)), this, SLOT(dataChangedSlot(QString)));
}

void enumNode::addItem(enumItemNode* item) {
	static_cast<QComboBox*>(m_dataField)->addItem(item->displayName());
	m_enumItems.append(item);
}


boolNode::boolNode(SettingsNode *parent, const QString& name)
			: SettingsNode{Boolean, parent, name} {
	m_dataField = new QCheckBox();
	this->setValue(m_defaultValue);
	connect(this->m_dataField, SIGNAL(stateChanged(int)), this, SLOT(dataChangedSlot(int)));
}

void boolNode::setValue(bool val) {
	if (val) static_cast<QCheckBox*>(m_dataField)->setCheckState(Qt::Checked);
	else static_cast<QCheckBox*>(m_dataField)->setCheckState(Qt::Unchecked);
}


actionNode::actionNode(SettingsNode *parent, const QString& name, const QString& buttonLabel)
			: SettingsNode{Action, parent, name} {
	m_dataField = new QPushButton(buttonLabel);
	connect(this->m_dataField, SIGNAL(clicked()), this, SLOT(dataChangedSlot()));
}
