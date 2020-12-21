/*------------------------------------------------------------
 *  settingsobject.cpp
 *  Created: 23. October 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#include "settingsobject.hpp"

#include <QApplication>
#include <QTreeWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>

settingsObject::settingsObject(QObject *parent, const QString& name, rootNode *rootNode)
			: m_parent{parent}, m_settingsName{name}, m_rootNode{rootNode} {
	this->constructTree();
}


void settingsObject::constructTree() {
	m_settingsTree = new QTreeWidget();
	m_settingsTree->setAlternatingRowColors(true);
	m_settingsTree->setColumnCount(2);
	QStringList ColumnNames;
	ColumnNames << "" << "";
	m_settingsTree->setHeaderLabels(ColumnNames);
	if (m_rootNode != nullptr) {
		for (const auto& child : m_rootNode->children()) {
				childNodes.append(child);
				QTreeWidgetItem *topitem = new QTreeWidgetItem(m_settingsTree, QStringList(child->displayName()));
				m_settingsTree->insertTopLevelItem(0,topitem);
				addAllChildren(child, topitem);
		}
	}
}


void settingsObject::addAllChildren(SettingsNode *parent, QTreeWidgetItem *parentItem) {
	for (const auto & child : parent->children()) {
		childNodes.append(child);
		QTreeWidgetItem *child_item = new QTreeWidgetItem();
		child_item->setFlags(child_item->flags() | Qt::ItemIsSelectable);
		child_item->setText(0,child->displayName());
		parentItem->addChild(child_item);
		if (child->type() == SettingsNode::Category) {
			addAllChildren(child, child_item);
		}
		else {
			m_settingsTree->setItemWidget(child_item, 1, child->dataField());
			connect(child, SIGNAL(dataChanged(QString)), this, SLOT(treeChangedSlot(QString)));
		}
	}
}


SettingsNode* settingsObject::findNode(const QString& name, SettingsNode* node) {
	if (node == nullptr) node = m_rootNode;
	for (const auto& child : node->children()) {
		if (child->displayName() == name) {
			return child;
		}
		SettingsNode *found = findNode(name, child);
		if (found != nullptr) return found;
	}
	return nullptr;
}

void settingsObject::treeChangedSlot(const QString& val) {
	QList<QString> subMenus;
	SettingsNode* parentNode = static_cast<SettingsNode*>(sender())->parent();
	while (parentNode->type() != SettingsNode::Root) {
		subMenus.append(parentNode->name());
		parentNode = parentNode->parent();
	}
	//emit SettingChanged(static_cast<SettingsNode*>(sender())->parent(), val);
	emit settingChanged(static_cast<SettingsNode*>(sender())->name(), subMenus, static_cast<SettingsNode*>(sender())->type(),val, true);
}
