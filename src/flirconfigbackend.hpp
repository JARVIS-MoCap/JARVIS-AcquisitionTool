/*------------------------------------------------------------
 *  flirconfigbackend.hpp
 *  Created: 05. June 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#ifndef FLIRCONFIGBACKEND_H
#define FLIRCONFIGBACKEND_H

#include "globals.hpp"

#include "Spinnaker.h"
#include "SpinGenApi/SpinnakerGenApi.h"

class FlirConfigBackend : public QObject {
	Q_OBJECT
	public:
		static FlirConfigBackend* getInstance()
        {
            static FlirConfigBackend    instance; // Guaranteed to be destroyed.
                                  // Instantiated on first use.
            return &instance;
        }
		explicit FlirConfigBackend(QObject *parent = nullptr);
		//~FlirConfigBackend();

		QList<QString> getCameraIDs();
		void updateIDs();

	private:
		QList<QString> cameraIDList;
		const Spinnaker::SystemPtr m_camSystem;
};


#endif
