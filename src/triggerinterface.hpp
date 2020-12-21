/*------------------------------------------------------------
 *  triggerinterface.hpp
 *  Created: 23. October 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#ifndef TRIGGERINTERFACE_H
#define TRIGGERINTERFACE_H

#include "globals.hpp"
#include "settingsnode.hpp"
#include "settingsobject.hpp"

#include <QTreeWidget>

class TriggerInterface : public QObject {
	Q_OBJECT
	public:
		static TriggerInterface *triggerInstance;
		enum TriggerType {testTrigger, arduinoTrigger};
		explicit TriggerInterface(TriggerType triggerType)
					: m_triggerType{triggerType} { }

		TriggerType triggerType() const {return m_triggerType;}
		settingsObject *triggerSettings() const {return m_triggerSettings;}
		void setTriggerStatus(const statusType& status) {m_triggerStatus = status;}  //maybe clearTriggerStatus() isntead??
		statusType triggerStatus() const {return m_triggerStatus;}

	signals:
		void statusUpdated(statusType status, const QString& statusMessage);

	protected:
		QSettings *settings = new QSettings();
		const TriggerType m_triggerType;
		rootNode *m_triggerSettingsRootNode;
		settingsObject *m_triggerSettings;
		statusType m_triggerStatus = Connecting;

	private slots:
		void statusInitReady() {emit statusUpdated(Ready, "");};
};


#endif
