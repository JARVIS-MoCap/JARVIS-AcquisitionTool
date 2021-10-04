/*------------------------------------------------------------
 *  testtrigger.hpp
 *  Created: 05. June 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#ifndef TESTTRIGGER_H
#define TESTTRIGGER_H

#include "globals.hpp"
#include "triggerinterface.hpp"

#include <QTreeWidget>

class TestTrigger : public TriggerInterface {
	Q_OBJECT
	public:
		explicit TestTrigger(const QString& example1 = "", const QString& example2 = "");
		~TestTrigger();
		void enable() {}
		void disable() {}

	private:
		void createSettings();

	private slots:
		void testStatusReadySlot();
		void testStatusWarningSlot();
		void testStatusErrorSlot();
};


#endif
