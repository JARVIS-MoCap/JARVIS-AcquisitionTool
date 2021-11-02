/*******************************************************************************
 * File:			  triggertestconfig.hpp
 * Created: 	  03. October 2021
 * Author:		  Timo Hueser
 * Contact: 	  timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#ifndef TRIGGERTESTCONFIG_H
#define TRIGGERTESTCONFIG_H

#include "globals.hpp"
#include "triggerconfiginterface.hpp"
#include "triggerinterface.hpp"

#include <QLineEdit>


class TriggerTestConfig : public TriggerConfigInterface {
	Q_OBJECT
	public:
		explicit TriggerTestConfig(QWidget *parent = 0);

		QLineEdit *example1Edit;
		QLineEdit *example2Edit;
		QLineEdit *example1Info;
		QLineEdit *example2Info;

		bool confirmConfigClicked();
		void loadPreset(QSettings *settings);
		void savePreset(QSettings *settings);
		TriggerInterface* getTrigger();
};

#endif
