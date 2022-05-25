/*******************************************************************************
 * File:        settingsobject.hpp
 * Created:     23 June 2020
 * Author:      Timo Hueser
 * Contact:     timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#ifndef SETTINGSOBJECT_H
#define SETTINGSOBJECT_H

#include "globals.hpp"
#include "settingsnode.hpp"

#include <QSettings>
#include <QTreeWidget>

class SettingsObject : public QObject {
    Q_OBJECT

  public:
    explicit SettingsObject(QObject *parent = nullptr, const QString &name = "",
                            RootNode *rootNode = nullptr);
    QObject *parent() const { return m_parent; }
    void constructTree();
    void setSettingsName(const QString &val) { m_settingsName = val; }
    QString settingsName() const { return m_settingsName; }
    void setRootNode(RootNode *val) { m_rootNode = val; }
    RootNode *getRootNode() const { return m_rootNode; }
    void setSettingsTree(QTreeWidget *val) { m_settingsTree = val; }
    QTreeWidget *settingsTree() const { return m_settingsTree; }
    SettingsNode *findNode(const QString &name, SettingsNode *node = nullptr);
    QList<SettingsNode *> childNodes;

  signals:
    void settingChanged(const QString &, QList<QString>, SettingsNode::nodeType,
                        QString, bool);

  private:
    QSettings *settings = new QSettings();
    QObject *m_parent;
    QString m_settingsName;
    RootNode *m_rootNode;
    QTreeWidget *m_settingsTree;
    void addAllChildren(SettingsNode *parent, QTreeWidgetItem *parentItem);

  private slots:
    void treeChangedSlot(const QString &val);
};

#endif
