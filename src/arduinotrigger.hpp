/*------------------------------------------------------------
 *  arduinotrigger.hpp
 *  Created: 03. October 2021
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#ifndef ARDUINOTRIGGER_H
#define ARDUINOTRIGGER_H

#include "globals.hpp"
#include "triggerinterface.hpp"
#include "serialinterface.hpp"


#include <QTreeWidget>

class ArduinoTrigger : public TriggerInterface {
	Q_OBJECT
	public:
		explicit ArduinoTrigger(const QString& deviceName);
		~ArduinoTrigger();

		void enable();
		void disable();

	private:
		SerialInterface *serialInterface;
		void createSettings();

	private slots:
		void intitialStatusSlot();
		void settingChangedSlot(const QString& name, QList<QString> subMenus,
					SettingsNode::nodeType type, const QString& val, bool update);
};


#endif
