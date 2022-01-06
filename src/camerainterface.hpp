/*------------------------------------------------------------
 *  camerainterface.hpp
 *  Created: 05. June 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#ifndef CAMERAINTERFACE_H
#define CAMERAINTERFACE_H

#include "globals.hpp"
#include "settingsnode.hpp"
#include "settingsobject.hpp"
#include "recordinginterface.hpp"
#include "baserecorder.hpp"
#ifdef USE_CUDA
	#include "cudarecorder.hpp"
#endif
#include <QTreeWidget>
#include <QThread>


class AcquisitionWorker : public QObject {
	Q_OBJECT
	public:
		explicit AcquisitionWorker(const QString& cameraName, const AcquisitionSpecs& acquisitionSpecs)
					: m_cameraName{cameraName}, m_acquisitionSpecs{acquisitionSpecs} {
			if (m_acquisitionSpecs.recorderType == BaseRecorderType) {
				m_recordingInterface = new BaseRecoder(cameraName, acquisitionSpecs);
			}
#ifdef USE_CUDA
			else if (m_acquisitionSpecs.recorderType == CudaRecorderType) {
				m_recordingInterface = new CudaRecorder(cameraName, acquisitionSpecs);
				std::cout << "Cuda support" << std::endl;
			}
#endif
	}

	public slots:
		virtual void acquireImages() = 0;

	protected:
		const QString m_cameraName;
		const AcquisitionSpecs m_acquisitionSpecs;
		RecordingInterface * m_recordingInterface;

	signals:
		//void streamImage(QPixmap);
		void streamImage(const  QImage & img);
		void latencyAndFrameNumberUpdate(int latency, unsigned long frameNumber);
		void statusUpdated(statusType status, const QString& statusMessage);

};


class CameraInterface : public QObject {
	Q_OBJECT
	public:
	 	static QList<CameraInterface*> cameraList;
		enum CameraType {testCamera, flirChameleon};
		explicit CameraInterface(CameraType cameraType, const QString& cameraName = "")
					: m_cameraType{cameraType}, m_cameraName{cameraName} { }

		CameraType cameraType() const {return m_cameraType;}
		void setCameraName(const QString& name) {m_cameraName = name;}
		QString cameraName() const {return m_cameraName;}
		SettingsObject* cameraSettings() const {return m_cameraSettings;}
		bool isStreaming() const {return m_isStreaming;}
		void setCameraStatus(const statusType& status) {m_cameraStatus = status;}
		statusType cameraStatus() const {return m_cameraStatus;}
		virtual bool savePreset(const QString& preset) = 0;
		virtual bool loadPreset(const QString& preset) = 0;
		virtual void getSimpleSettingsValues() = 0;
		virtual void changeSimpleSetting(const QString& setting, const QString& val) = 0;
		virtual int getBufferUsage() = 0;
		virtual int getBufferSize() = 0;
		virtual bool setupCamera(const CameraSettings &cameraSettings) = 0;

	public slots:
		virtual void settingChangedSlot(const QString& name, QList<QString> subMenus,
					SettingsNode::nodeType type, const QString& val, bool update) = 0;
		virtual void startAcquisitionSlot(AcquisitionSpecs acquisitionSpecs) = 0;
		virtual void stopAcquisitionSlot() = 0;
		virtual void pauseSlot() = 0;
		virtual void continueSlot() = 0;

	signals:
		void streamImage(const QImage & img);
		void latencyAndFrameNumberUpdate(int latency, unsigned long frameNumber);
		void statusUpdated(statusType status, const QString& statusMessage);
		void simpleSettingChanged(const QString& settingName, const QString& value, bool enabled, double min, double max);

	protected:
		QSettings *settings = new QSettings();
		const CameraType m_cameraType;
		QString m_cameraName;
		RootNode *m_cameraSettingsRootNode; //not sure if needed, might be enough to have settingsObject
		SettingsObject *m_cameraSettings;
		bool m_isStreaming = false;
		statusType m_cameraStatus = Connecting;
		AcquisitionWorker *m_acquisitionWorker;

		frameRate_t m_frameRate = 100;
		frameSize_t m_frameSize {1280,1024};
		PixelFormat m_pixelFormat = PixelFormat::BayerRG8;

	protected slots:
		void statusInitReady() {emit statusUpdated(Ready, "Camera initialized");};
		void statusInitFailed() {emit statusUpdated(Error, "Camera Initialisation Failed!");};

};


#endif
