/*------------------------------------------------------------
 *  settingsobject.hpp
 *  Created: 23 June 2020
 *  Author:  Timo Hüser
 *------------------------------------------------------------*/

#ifndef SETTINGSOBJECT_H
#define SETTINGSOBJECT_H

#include "globals.hpp"
#include "settingsnode.hpp"

#include <QTreeWidget>
#include <QSettings>

class settingsObject : public QObject {
	Q_OBJECT
	public:
		explicit settingsObject(QObject *parent = nullptr, const QString& name = "", rootNode *rootNode = nullptr);
		QObject *parent() const {return m_parent;}
		void constructTree();
		void setSettingsName(const QString& val) {m_settingsName = val;}
		QString settingsName() const {return m_settingsName;}
		void setRootNode(rootNode* val) {m_rootNode = val;}
		rootNode *getRootNode() const {return m_rootNode;}
		void setSettingsTree(QTreeWidget *val) {m_settingsTree = val;}
		QTreeWidget *settingsTree() const {return m_settingsTree;}
		SettingsNode *findNode(const QString& name, SettingsNode* node = nullptr);
		QList<SettingsNode*> childNodes;

	signals:
		//void settingChanged(SettingsNode*, const QString& val);
		void settingChanged(const QString&, QList<QString>, SettingsNode::nodeType, QString, bool);

	private:
		QSettings *settings = new QSettings();
		QObject *m_parent;
		QString m_settingsName;
		rootNode *m_rootNode;
		QTreeWidget *m_settingsTree;
		void addAllChildren(SettingsNode *parent, QTreeWidgetItem *parentItem);

	private slots:
		void treeChangedSlot(const QString& val);
};

#endif
