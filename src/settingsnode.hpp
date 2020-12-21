/*------------------------------------------------------------
 *  settingsnode.hpp
 *  Created: 23 June 2020
 *  Author:  Timo Hüser
 *------------------------------------------------------------*/

#ifndef SETTINGSNODE_H
#define SETTINGSNODE_H

#include "globals.hpp"

#include <limits.h>
#include <float.h>

#include <QTreeWidget>
#include <QSettings>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>


class SettingsNode: public QObject {
	Q_OBJECT
	public:
		enum nodeType {
			Root,
			Category,
			String,
			Integer,
			Float,
			Enumeration,
			EnumerationItem,
			Boolean,
			Action
		};
		explicit SettingsNode(nodeType type, SettingsNode* parent, const QString& name);

		nodeType type() const {return m_type;}
		QString name() const {return m_name;}
		void setDisplayName(const QString& val) {m_displayName = val;}
		QString displayName() const {return m_displayName;}
		void setDescription(const QString& val) {m_description = val;}
		QString description() const {return m_description;}
		QWidget * dataField() const {return m_dataField;}
		void setLocked (bool lock) {
			m_locked = lock;
			m_dataField->setEnabled(!m_locked);
		}
		bool isLocked() const {return m_locked;}
		SettingsNode *parent() const {return m_parent;}
		void addChild(SettingsNode *child) {m_children.append(child);}
		QList<SettingsNode*> children() const {return m_children;}

	signals:
		void dataChanged(QString);

	protected:
		const nodeType m_type;
		SettingsNode * const m_parent;
		const QString m_name;
		QString m_displayName;
		QString m_description = "";
		QWidget * m_dataField = nullptr;
		bool m_locked = false;
		QList<SettingsNode*> m_children = {};

	private slots:
		void dataChangedSlot(const QString& data) {emit dataChanged(data);};
		void dataChangedSlot(int data) {emit dataChanged(QString::number(data));};
		void dataChangedSlot() {emit dataChanged("");};
};


class rootNode : public SettingsNode {
	Q_OBJECT
	public:
		explicit rootNode(const QString& name = "");
};


class categoryNode : public SettingsNode {
	Q_OBJECT
	public:
		explicit categoryNode(SettingsNode *parent, const QString& name);
};


class stringNode : public SettingsNode {
	Q_OBJECT
	public:
		explicit stringNode(SettingsNode *parent, const QString& name);

		void setDefaultValue(const QString& val) {m_defaultValue = val;}
		QString defaultValue() const {return m_defaultValue;}
		void setValue(const QString& val) {static_cast<QLineEdit*>(m_dataField)->setText(val);}
		QString value() const {return static_cast<QLineEdit*>(m_dataField)->text();}

	private:
		QString m_defaultValue = "";
	};


	class intNode : public SettingsNode {
		Q_OBJECT
	public:
		explicit intNode(SettingsNode *parent, const QString& name);

		void setDefaultValue(int val) {m_defaultValue = val;}
		int defaultValue() const {return m_defaultValue;}
		void setMinValue(int val) {m_minValue = val;}
		int minValue() const {return m_minValue;}
		void setMaxValue(int val) {m_maxValue = val;}
		int maxValue() const {return m_maxValue;}
		void setRange(int min, int max) {m_minValue = min; m_maxValue = max;}
		void setValue(int val) 	{static_cast<QLineEdit*>(m_dataField)->setText(QString::number(val));}
		int value() {return static_cast<QLineEdit*>(m_dataField)->text().toInt();}

	private:
		int m_defaultValue = 0;
		int m_minValue = INT_MIN;
		int m_maxValue = INT_MAX;
};


class floatNode : public SettingsNode {
	Q_OBJECT
	public:
		explicit floatNode(SettingsNode *parent, const QString& name);

		void setDefaultValue(float val) {m_defaultValue = val;};
		float defaultValue() const {return m_defaultValue;};
		void setMinValue(float val) {m_minValue = val;};
		float minValue() const {return m_minValue;};
		void setMaxValue(float val) {m_maxValue = val;};
		float maxValue() const {return m_maxValue;};
		void setRange(float min, float max) {m_minValue = min; m_maxValue = max;}
		void setValue(float val) {static_cast<QLineEdit*>(m_dataField)->setText(QString::number(val));}
		float value() const {return static_cast<QLineEdit*>(m_dataField)->text().toFloat();}

	signals:
		void returnPressed(QString);

	private:
		float m_defaultValue = 0.0;
		float m_minValue = FLT_MIN;
		float m_maxValue = FLT_MAX;

	private slots:
		void returnPressedSlot();
};


class enumItemNode : public SettingsNode {
	Q_OBJECT
	public:
		explicit enumItemNode(SettingsNode *parent, const QString& name);
};


class enumNode : public SettingsNode {
	Q_OBJECT
	public:
		explicit enumNode(SettingsNode *parent, const QString& name);

		void addItem(enumItemNode* item);
		enumItemNode *item(int i) const {return m_enumItems[i];}
		QList<enumItemNode*> items() const {return m_enumItems;}
		void setCurrentItem(enumItemNode* item) {static_cast<QComboBox*>(m_dataField)->setCurrentText(item->displayName());}
		enumItemNode* currentItem() const {return m_enumItems[static_cast<QComboBox*>(m_dataField)->currentIndex()];}
		void setCurrentIndex(int i) {static_cast<QComboBox*>(m_dataField)->setCurrentIndex(i);}
		int currentIndex() const {return static_cast<QComboBox*>(m_dataField)->currentIndex();}

	private:
		QList<enumItemNode*> m_enumItems = {};
};


class boolNode : public SettingsNode {
	Q_OBJECT
	public:
		explicit boolNode(SettingsNode *parent, const QString& name);

		void setDefaultValue(bool val) {m_defaultValue = val;};
		bool defaultValue() const {return m_defaultValue;};
		void setValue(bool val);
		bool value() const {return static_cast<QCheckBox*>(m_dataField)->checkState();}

	private:
		bool m_defaultValue = false;
};

class actionNode : public SettingsNode {
	Q_OBJECT
	public:
		explicit actionNode(SettingsNode *parent, const QString& name, const QString& buttonLabel = "Execute");
};


#endif
