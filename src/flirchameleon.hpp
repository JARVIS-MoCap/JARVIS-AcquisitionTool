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

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>


class FlirWorker : public AcquisitionWorker {
	Q_OBJECT
	public:
		FlirWorker(Spinnaker::CameraPtr pCam, const QString& cameraName, const AcquisitionSpecs& acquisitionSpecs);
		~FlirWorker();

	public slots:
		void acquireImages();

	private:
		const Spinnaker::CameraPtr m_pCam;
};


class FLIRChameleon : public CameraInterface {
	Q_OBJECT
	public:
		explicit FLIRChameleon(const QString& cameraName, const QString& serialNumber);
		~FLIRChameleon();
		QThread workerThread;
		void loadPreset();

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
		void loadPresetRecursive(SettingsNode *settingsNode);

	private slots:
		void streamImageSlot(QPixmap pix);
};

#endif
