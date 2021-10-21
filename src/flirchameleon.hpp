/*------------------------------------------------------------
 *  flirchameleon.hpp
 *  Created: 05. June 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#ifndef FLIRCHAMELEON_H
#define FLIRCHAMELEON_H

#include "globals.hpp"
#include "camerainterface.hpp"

#include <QTreeWidget>
#include <QThread>

#include "Spinnaker.h"
#include "SpinGenApi/SpinnakerGenApi.h"


class FlirWorker : public AcquisitionWorker {
	Q_OBJECT
	public:
		FlirWorker(Spinnaker::CameraPtr pCam, const QString& cameraName, const AcquisitionSpecs& acquisitionSpecs);
		~FlirWorker();

	public slots:
		void acquireImages();

	private:
		const Spinnaker::CameraPtr m_pCam;
		QImage m_img;
};


class FLIRChameleon : public CameraInterface {
	Q_OBJECT
	public:
		explicit FLIRChameleon(const QString& cameraName, const QString& serialNumber);
		~FLIRChameleon();
		QThread workerThread;
		bool savePreset(const QString& preset);
		bool loadPreset(const QString& preset);
		bool saveUserSetToFile(const QString& userSet, const QString& path);
		bool loadUserSetFromFile(const QString& userSet, const QString& path);
		QString getDefaultUserSet();
		bool setDefaultUserSet(const QString &userSet);
		void getSimpleSettingsValues();
		void changeSimpleSetting(const QString& setting, const QString& val);
		const QString& getDeviceID() {return m_serialNumber;}
		int getBufferUsage();
		int getBufferSize();

	public slots:
		void settingChangedSlot(const QString& name, QList<QString> subMenus, SettingsNode::nodeType type,
					const QString& val, bool update);
		void startAcquisitionSlot(AcquisitionSpecs acquisitionSpecs);
		void stopAcquisitionSlot();
		void pauseSlot() {}
		void continueSlot() {}


	signals:
		void startAcquisition();

	private:
		void createSettings();
		const QString m_serialNumber;
		const Spinnaker::SystemPtr m_camSystem;
		Spinnaker::CameraPtr m_pCam;

		int createSettingsTreeFromCam(Spinnaker::GenApi::CNodePtr node, SettingsNode *settingsNode);
		void updateSettings(Spinnaker::GenApi::INodeMap& nodeMap, SettingsNode *settingsNode);

		bool openFileToRead();
		bool openFileToWrite();
		bool closeFile();
		bool executeReadCommand();
		bool executeWriteCommand();
		bool executeDeleteCommand();

	private slots:
		void streamImageSlot(QImage img);
};

#endif
