/*------------------------------------------------------------
 *  flirconfigbackend.cpp
 *  Created: 05. June 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#include "flirconfigbackend.hpp"


#include <QApplication>

using namespace Spinnaker;
using namespace Spinnaker::GenApi;
using namespace Spinnaker::GenICam;

FlirConfigBackend::FlirConfigBackend(QObject *parent) : QObject(parent), m_camSystem{System::GetInstance()} {
	CameraList cameraList = m_camSystem->GetCameras();
	unsigned int numCameras = cameraList.GetSize();
	for (unsigned int i = 0; i < numCameras; ++i) {
   CameraPtr pCamera = cameraList.GetByIndex(i);
	 pCamera->Init();
	 cameraIDList.append(QString::fromStdString(pCamera->DeviceSerialNumber.GetValue().c_str()));
	 pCamera->DeInit();
	}
}


FlirConfigBackend::~FlirConfigBackend() {
	//m_camSystem->ReleaseInstance(); Not sure if need/allowed here
}

QList<QString> FlirConfigBackend::getCameraIDs() {
	return cameraIDList;
}
