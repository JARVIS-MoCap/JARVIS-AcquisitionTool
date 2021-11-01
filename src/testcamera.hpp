/*******************************************************************************
 * File:			  testcamera.hpp
 * Created: 	  05. June 2020
 * Author:		  Timo Hueser
 * Contact: 	  timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#ifndef TESTCAMERA_H
#define TESTCAMERA_H

#include "globals.hpp"
#include "camerainterface.hpp"

#include <QTreeWidget>
#include <QThread>


class TestAcquisitionWorker : public AcquisitionWorker {
		Q_OBJECT

	public:
		explicit TestAcquisitionWorker(const QString& cameraName,
					const AcquisitionSpecs& acquisitionSpecs, QImage **testimgs);

	public slots:
	  void acquireImages();

	private:
		int m_frameCount = 0;
		QImage **m_testimgs;
};


class TestCamera : public CameraInterface {
		Q_OBJECT
	public:
		explicit TestCamera(QString cameraName, const QString& example1 = "",
					const QString& example2 = "");
		~TestCamera();
		QThread workerThread;
		bool savePreset(const QString&) {}
		bool loadPreset(const QString&) {};
		void getSimpleSettingsValues() {}
		void changeSimpleSetting(const QString& setting, const QString& val) {}
		int getBufferUsage() {return 10;}
		int getBufferSize() {return 100;}

	public slots:
		void settingChangedSlot(const QString& name, QList<QString> subMenus,
					SettingsNode::nodeType type, const QString& val, bool update);
		void startAcquisitionSlot(AcquisitionSpecs acquisitionSpecs);
		void stopAcquisitionSlot();
		void pauseSlot() {}
		void continueSlot() {}

	signals:
		void startAcquisition();

	private:
		QImage *testimgs[200];

		void createSettings();

	private slots:
		void testStatusReadySlot();
		void testStatusWarningSlot();
		void testStatusErrorSlot();
		void streamImageSlot(QImage);
};


#endif
