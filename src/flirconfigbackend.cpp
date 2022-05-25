/*******************************************************************************
 * File:			  flirconfigbackend.cpp
 * Created: 	  05. June 2020
 * Author:		  Timo Hueser
 * Contact: 	  timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#include "flirconfigbackend.hpp"
#include "camerainterface.hpp"
#include "flirchameleon.hpp"

#include <QApplication>

using namespace Spinnaker;
using namespace Spinnaker::GenApi;
using namespace Spinnaker::GenICam;


FlirConfigBackend::FlirConfigBackend(QObject *parent) : QObject(parent),
			m_camSystem{System::GetInstance()} {
	updateIDs();
}


FlirConfigBackend::~FlirConfigBackend() {
	m_camSystem->ReleaseInstance();
}

QList<QString> FlirConfigBackend::getCameraIDs() {
	QList<QString> availableCameraIDList = m_cameraIDList;
	for (CameraInterface* cam : CameraInterface::cameraList) {
		if (cam->cameraType() == CameraInterface::flirChameleon) {
			availableCameraIDList.removeAll(
						static_cast<FLIRChameleon*>(cam)->getDeviceID());
		}
	}
	return availableCameraIDList;
}

void FlirConfigBackend::updateIDs() {
	m_cameraIDList.clear();
	CameraList cameraList = m_camSystem->GetCameras();

	unsigned int numCameras = cameraList.GetSize();
	for (unsigned int i = 0; i < numCameras; ++i) {
	 CameraPtr pCamera = cameraList.GetByIndex(i);
	 pCamera->Init();
	 m_cameraIDList.append(QString::fromStdString(
		 		pCamera->DeviceSerialNumber.GetValue().c_str()));
	 pCamera->DeInit();
	}
}

bool FlirConfigBackend::checkCamList() {
	CameraList cameraList = m_camSystem->GetCameras();
	if (cameraList.GetSize() != m_cameraIDList.size()) {
		return false;
	}
	return true;
}
