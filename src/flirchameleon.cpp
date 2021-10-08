/*------------------------------------------------------------
 *  flirchameleon.cpp
 *  Created: 05. June 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#include "flirchameleon.hpp"

#include <chrono>
#include <fstream>
#include "triggerinterface.hpp"

#include <QApplication>
#include <QTreeWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QPushButton>
#include <QTimer>

using namespace Spinnaker;
using namespace Spinnaker::GenApi;
using namespace Spinnaker::GenICam;

FlirWorker::FlirWorker(Spinnaker::CameraPtr pCam, const QString& cameraName,  const AcquisitionSpecs& acquisitionSpecs)
			: AcquisitionWorker{cameraName, acquisitionSpecs}, m_pCam{pCam}
{ }


FlirWorker::~FlirWorker() {
	delete m_recordingInterface;
}


void FlirWorker::acquireImages() {
	int time_buffer = 0;
	forever {
		try {
			if (TriggerInterface::triggerInstance == nullptr && QThread::currentThread()->isInterruptionRequested()) break;
			ImagePtr pResultImage = m_pCam->GetNextImage(50);
			if (pResultImage->IsIncomplete()) {
				std::cout << "INCOMPLETE" << std::endl;
			}
			else {
				auto t1 = std::chrono::high_resolution_clock::now();
				QImage img = m_recordingInterface->recordFrame(static_cast<uchar*>(pResultImage->GetData()));
				pResultImage->Release();
				emit streamImage(img);
				auto t2 = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
				time_buffer += duration - 10000;
				if (time_buffer < 0) time_buffer = 0;
				if (time_buffer > 20000) std::cout << time_buffer << std::endl;
			}
		}
		catch (Spinnaker::Exception& e)
		{
				if (e == SPINNAKER_ERR_TIMEOUT) {
					if (QThread::currentThread()->isInterruptionRequested()) {
						return;
					}
				}
				else {
					std::cout << "ErrorWorker: " << e.what() << std::endl;
				}
		}

	}
}


FLIRChameleon::FLIRChameleon(const QString& cameraName, const QString& serialNumber)
			: CameraInterface(flirChameleon, cameraName),
			  m_serialNumber{serialNumber},
			  m_camSystem{System::GetInstance()} {
	const LibraryVersion spinnakerLibraryVersion = m_camSystem->GetLibraryVersion();
	std::cout << "Spinnaker library version: "
			<< spinnakerLibraryVersion.major << "."
			<< spinnakerLibraryVersion.minor << "."
			<< spinnakerLibraryVersion.type << "."
			<< spinnakerLibraryVersion.build << std::endl << std::endl;
	CameraList cameraList = m_camSystem->GetCameras();
	m_pCam = cameraList.GetBySerial(m_serialNumber.toStdString());

	createSettings();
	QTimer *timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &FLIRChameleon::statusInitReady);
	timer->setSingleShot(true);
	timer->start(500);
}


FLIRChameleon::~FLIRChameleon() {
	if (m_pCam->IsInitialized()) m_pCam->DeInit();
	m_pCam = nullptr;
	if (cameraList.size() == 0) m_camSystem->ReleaseInstance();
	delete (m_cameraSettings);
}


bool FLIRChameleon::savePreset(const QString& preset) {
	m_pCam->Init();
	INodeMap& nodeMap = m_pCam->GetNodeMap();
	CEnumerationPtr ptrUserSetSelector = nodeMap.GetNode("UserSetSelector");
	if (!IsAvailable(ptrUserSetSelector) || !IsWritable(ptrUserSetSelector)) {
			std::cout << "Unable to access User Set Selector (enum retrieval). Aborting..." << std::endl;
			return false;
	}

	CEnumEntryPtr ptrUserSet = ptrUserSetSelector->GetEntryByName(preset.toStdString().c_str());
	if (!IsAvailable(ptrUserSet) || !IsReadable(ptrUserSet)) {
			std::cout << "Unable to access User Set (entry retrieval). Aborting..." << std::endl;
			return false;
	}
	ptrUserSetSelector->SetIntValue(ptrUserSet->GetValue());

	CCommandPtr ptrUserSetSave = m_pCam->GetNodeMap().GetNode("UserSetSave");
	if (!IsAvailable(ptrUserSetSave) || !IsWritable(ptrUserSetSave)){
			std::cout << "Unable to save to User Set. Aborting..." << std::endl;
	}
	ptrUserSetSave->Execute();
	m_pCam->DeInit();
	return true;
}

bool FLIRChameleon::loadPreset(const QString& preset) {
	m_pCam->Init();
	INodeMap& nodeMap = m_pCam->GetNodeMap();
	CEnumerationPtr ptrUserSetSelector = nodeMap.GetNode("UserSetSelector");
	if (!IsAvailable(ptrUserSetSelector) || !IsWritable(ptrUserSetSelector)) {
			std::cout << "Unable to access User Set Selector (enum retrieval). Aborting..." << std::endl;
			return false;
	}

	CEnumEntryPtr ptrUserSet = ptrUserSetSelector->GetEntryByName(preset.toStdString().c_str());
	if (!IsAvailable(ptrUserSet) || !IsReadable(ptrUserSet)) {
			std::cout << "Unable to access User Set (entry retrieval). Aborting..." << std::endl;
			return false;
	}
	ptrUserSetSelector->SetIntValue(ptrUserSet->GetValue());

	CCommandPtr ptrUserSetLoad = m_pCam->GetNodeMap().GetNode("UserSetLoad");
	if (!IsAvailable(ptrUserSetLoad) || !IsWritable(ptrUserSetLoad)){
			std::cout << "Unable to load to User Set. Aborting..." << std::endl;
	}
	ptrUserSetLoad->Execute();
	updateSettings(nodeMap, m_cameraSettings->getRootNode()->children()[0]);
	m_pCam->DeInit();
	INodeMap& genTLNodeMap = m_pCam->GetTLDeviceNodeMap();
	INodeMap& nodeMapTLStream = m_pCam->GetTLStreamNodeMap();
	updateSettings(genTLNodeMap, m_cameraSettings->getRootNode()->children()[1]);
	updateSettings(nodeMapTLStream, m_cameraSettings->getRootNode()->children()[2]);
	return true;
}

//TODO: make settingsChangedSlot more universion, can't have all those parameters (submenus specifically)
void FLIRChameleon::settingChangedSlot(const QString& name, QList<QString> subMenus,
			SettingsNode::nodeType type, const QString& val, bool update) {
	try {
		if (subMenus.last() == "FLIR Chameleon" && update) m_pCam->Init();
		INodeMap& genTLNodeMap = m_pCam->GetTLDeviceNodeMap();
		INodeMap& nodeMapTLStream = m_pCam->GetTLStreamNodeMap();
		INodeMap& appLayerNodeMap = m_pCam->GetNodeMap();

		CNodePtr ptrNode = nullptr;
		gcstring cName = name.toStdString().c_str();
		if (subMenus.last() == "FLIR Chameleon") ptrNode = appLayerNodeMap.GetNode(cName);
		else if (subMenus.last() == "Stream Parameters") ptrNode = nodeMapTLStream.GetNode(cName);
		else if (subMenus.last() == "Transport Layer") ptrNode = genTLNodeMap.GetNode(cName);
		std::cout << name.toStdString() << std::endl;
		if (type == SettingsNode::String) {
			CStringPtr ptrString = static_cast<CStringPtr>(ptrNode);
			if (IsAvailable(ptrString) && IsWritable(ptrString)) {
				ptrString->SetValue(val.toStdString().c_str());
			}
		}

		else if (type == SettingsNode::Integer) {
			CIntegerPtr ptrInt = static_cast<CIntegerPtr>(ptrNode);
			if (IsAvailable(ptrInt) && IsWritable(ptrNode)) {
				ptrInt->SetValue(val.toInt());
			}
		}

		else if (type == SettingsNode::Float) {
			CFloatPtr ptrFloat = static_cast<CFloatPtr>(ptrNode);
			if (IsAvailable(ptrFloat) && IsWritable(ptrFloat)) {
				ptrFloat->SetValue(val.toFloat());
			}
		}

		else if(type == SettingsNode::Enumeration) {
			CEnumerationPtr ptrEnum = static_cast<CEnumerationPtr>(ptrNode);
			if (IsAvailable(ptrEnum) && IsWritable(ptrEnum)) {
				CEnumEntryPtr ptrEnumItem = ptrEnum->GetEntryByName(val.toStdString().c_str());
				if (IsAvailable(ptrEnumItem) && IsReadable(ptrEnumItem)) {
					ptrEnum->SetIntValue(ptrEnumItem->GetValue());
				}
			}
		}

		else if (type == SettingsNode::Boolean) {
			CBooleanPtr ptrBool = static_cast<CBooleanPtr>(ptrNode);
			if (IsAvailable(ptrBool) && IsWritable(ptrBool)) {
				if (val == "0") {
					ptrBool->SetValue(false);
				}
				else  {
					ptrBool->SetValue(true);
				}
			}
		}

		else if (type == SettingsNode::Action) {
			CCommandPtr ptrCommand = static_cast<CCommandPtr>(ptrNode);
			if (IsAvailable(ptrCommand) && IsWritable(ptrCommand)) {
				std::cout << "Not Implemented yet" << std::endl;
			}

		}
		if (update) {
			if (subMenus.last() == "FLIR Chameleon") updateSettings(appLayerNodeMap,
						m_cameraSettings->getRootNode()->children()[0]);
			else if (subMenus.last() == "Transport Layer") updateSettings(genTLNodeMap,
						m_cameraSettings->getRootNode()->children()[1]);
			else if (subMenus.last() == "Stream Parameters") updateSettings(nodeMapTLStream,
						m_cameraSettings->getRootNode()->children()[2]);
		}
		if (subMenus.last() == "FLIR Chameleon" && update && !m_isStreaming) m_pCam->DeInit();
	}
	catch (Spinnaker::Exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
}


void FLIRChameleon::startAcquisitionSlot(AcquisitionSpecs acquisitionSpecs) {
	if (!m_isStreaming) {
		m_pCam->Init();
		INodeMap& appLayerNodeMap = m_pCam->GetNodeMap();
		acquisitionSpecs.frameRate = m_frameRate;
		acquisitionSpecs.frameSize = m_frameSize;
		acquisitionSpecs.pixelFormat = m_pixelFormat;
		try {
			m_acquisitionWorker = new FlirWorker(m_pCam, m_cameraName,acquisitionSpecs);
			m_acquisitionWorker->moveToThread(&workerThread);
			connect(this, &FLIRChameleon::startAcquisition, m_acquisitionWorker, &AcquisitionWorker::acquireImages);
			connect(m_acquisitionWorker, &AcquisitionWorker::streamImage, this, &FLIRChameleon::streamImageSlot);
			connect(&workerThread, &QThread::finished, m_acquisitionWorker, &AcquisitionWorker::deleteLater);
			m_pCam->BeginAcquisition();
			updateSettings(appLayerNodeMap, m_cameraSettings->getRootNode()->children()[0]);
			workerThread.start();
			emit startAcquisition();
			emit statusUpdated(Streaming, "");
			m_isStreaming = true;
		}
		catch (Spinnaker::Exception& e) {
			std::cout << "Error: " << e.what() << std::endl;
		}
	}
}


void FLIRChameleon::stopAcquisitionSlot() {
	std::cout << "Trying to stop Acquisition" << std::endl;
	workerThread.requestInterruption();
	workerThread.quit();
	workerThread.wait();
	std::cout << "stopped Worker" << std::endl;
	try {
		m_pCam->EndAcquisition();
		INodeMap& appLayerNodeMap = m_pCam->GetNodeMap();
		updateSettings(appLayerNodeMap, m_cameraSettings->getRootNode()->children()[0]);
		m_pCam->DeInit();
	}
	catch (Spinnaker::Exception& e) {
		std::cout << "ErrorEnd: " << e.what() << std::endl;
	}
	m_isStreaming = false;
	emit statusUpdated(Ready, "Stopped Streaming");
}


void FLIRChameleon::createSettings() {
	m_cameraSettingsRootNode = new rootNode("FLIR Chameleon");

	INodeMap& genTLNodeMap = m_pCam->GetTLDeviceNodeMap();
	categoryNode *transportLayerNode = new categoryNode(m_cameraSettingsRootNode, "Transport Layer");
	createSettingsTreeFromCam(genTLNodeMap.GetNode("Root"), transportLayerNode);

	INodeMap& nodeMapTLStream = m_pCam->GetTLStreamNodeMap();
	CIntegerPtr ptrNode  = nodeMapTLStream.GetNode("StreamBufferCountManual");
	try {
		if (IsAvailable(ptrNode) && IsWritable(ptrNode))
			ptrNode->SetValue(55);
	}
	catch (Spinnaker::Exception& e) {
		//if this error occurs try sudo sh -c 'echo 1 >/proc/sys/vm/drop_caches' and rerun
		std::cout << "Error: " << e.what() << std::endl;
	}
	categoryNode *streamLayerNode = new categoryNode(m_cameraSettingsRootNode, "Stream Parameters");
	createSettingsTreeFromCam(nodeMapTLStream.GetNode("Root"), streamLayerNode);

	m_pCam->Init();
	INodeMap& appLayerNodeMap = m_pCam->GetNodeMap();
	categoryNode *geniCamNode = new categoryNode(m_cameraSettingsRootNode, "FLIR Chameleon");
	createSettingsTreeFromCam(appLayerNodeMap.GetNode("Root"), geniCamNode);
	m_pCam->DeInit();

	m_cameraSettingsRootNode->addChild(geniCamNode);
	m_cameraSettingsRootNode->addChild(transportLayerNode);
	m_cameraSettingsRootNode->addChild(streamLayerNode);

	m_cameraSettings = new settingsObject(this, "Camera Settings", m_cameraSettingsRootNode);
	connect(m_cameraSettings, SIGNAL(settingChanged(QString, QList<QString>, SettingsNode::nodeType,
				QString, bool)), this, SLOT(settingChangedSlot(QString, QList<QString>,
				SettingsNode::nodeType, QString,bool)));
}


int FLIRChameleon::createSettingsTreeFromCam(CNodePtr node, SettingsNode *settingsNode) {
  int result = 0;
  try {
    CCategoryPtr ptrCategoryNode = static_cast<CCategoryPtr>(node);
    FeatureList_t features;
    ptrCategoryNode->GetFeatures(features);
    FeatureList_t::const_iterator it;
    for (it = features.begin(); it != features.end(); ++it) {
        CNodePtr ptrFeatureNode = *it;
        if (!IsAvailable(ptrFeatureNode) || !IsReadable(ptrFeatureNode)) {
            continue;
        }
				QString name = QString::fromStdString(ptrFeatureNode->GetName().c_str());
				QString displayName = QString::fromStdString(ptrFeatureNode->GetDisplayName().c_str());
				QString description = QString::fromStdString(ptrFeatureNode->GetDescription().c_str());
				bool writeable = IsWritable(ptrFeatureNode);
        if (ptrFeatureNode->GetPrincipalInterfaceType() == intfICategory) {
					categoryNode *catNode = new categoryNode(settingsNode, name);
					catNode->setDescription(description);
					catNode->setDisplayName(displayName);
					settingsNode->addChild(catNode);
          result = result | createSettingsTreeFromCam(ptrFeatureNode, catNode);
        }
				else if (ptrFeatureNode->GetPrincipalInterfaceType() == intfIString) {
					CStringPtr ptrStringNode = static_cast<CStringPtr>(ptrFeatureNode);
					QString value = QString::fromStdString(ptrStringNode->GetValue().c_str());
					stringNode *strNode = new stringNode(settingsNode, name);
					strNode->setDescription(description);
					strNode->setDisplayName(displayName);
					strNode->setValue(value);
					strNode->setLocked(!writeable);
					settingsNode->addChild(strNode);
        }
				else if (ptrFeatureNode->GetPrincipalInterfaceType() == intfIInteger) {
					CIntegerPtr ptrIntegerNode = static_cast<CIntegerPtr>(ptrFeatureNode);
					int value = ptrIntegerNode->GetValue();
					int max = ptrIntegerNode->GetMax();
					int min = ptrIntegerNode->GetMin();
					intNode *iNode = new intNode(settingsNode, name);
					if (name == "Width") {
						m_frameSize.width = value;
					}
					else if (name == "Height") {
						m_frameSize.height = value;
					}
					iNode->setDescription(description);
					iNode->setDisplayName(displayName);
					iNode->setRange(min,max);
					iNode->setValue(value);
					iNode->setLocked(!writeable);
					settingsNode->addChild(iNode);
				}
				else if (ptrFeatureNode->GetPrincipalInterfaceType() == intfIFloat) {
					CFloatPtr ptrFloatNode = static_cast<CFloatPtr>(ptrFeatureNode);
					float value = ptrFloatNode->GetValue();
					float max = ptrFloatNode->GetMax();
					float min = ptrFloatNode->GetMin();
					floatNode *fNode = new floatNode(settingsNode, name);
					if (name == "AcquisitionFrameRate") {
						m_frameRate = value;
					}
					fNode->setDescription(description);
					fNode->setDisplayName(displayName);
					fNode->setRange(min,max);
					fNode->setValue(value);
					fNode->setLocked(!writeable);
					settingsNode->addChild(fNode);
				}
				else if (ptrFeatureNode->GetPrincipalInterfaceType() == intfIEnumeration) {
					CEnumerationPtr ptrEnumerationNode = static_cast<CEnumerationPtr>(ptrFeatureNode);
					enumNode *eNode = new enumNode(settingsNode, name);
					eNode->setDescription(description);
					eNode->setDisplayName(displayName);
					CEnumEntryPtr ptrCurrentEnumEntryNode = ptrEnumerationNode->GetCurrentEntry();
					NodeList_t entries;
					ptrEnumerationNode->GetEntries(entries);
					NodeList_t::const_iterator it;
					for (it = entries.begin(); it != entries.end(); ++it) {
						CEnumEntryPtr ptrEnumEntryNode = *it;
						if (IsAvailable(ptrEnumEntryNode) && IsReadable(ptrEnumEntryNode)) {
							QString symbolic = QString::fromStdString(ptrEnumEntryNode->GetSymbolic().c_str());
							enumItemNode *itemNode = new enumItemNode(eNode, symbolic);
							eNode->addItem(itemNode);
							if (ptrCurrentEnumEntryNode == ptrEnumEntryNode) eNode->setCurrentItem(itemNode);
						}
					}
					eNode->setLocked(!writeable);
					settingsNode->addChild(eNode);
				}
				else if (ptrFeatureNode->GetPrincipalInterfaceType() == intfIBoolean) {
					CBooleanPtr ptrBooleanNode = static_cast<CBooleanPtr>(ptrFeatureNode);
					bool value = ptrBooleanNode->GetValue();
					boolNode *bNode = new boolNode(settingsNode, name);
					bNode->setDescription(description);
					bNode->setDisplayName(displayName);
					bNode->setValue(value);
					bNode->setLocked(!writeable);
					settingsNode->addChild(bNode);
				}
				else if (ptrFeatureNode->GetPrincipalInterfaceType() == intfICommand) {
					CCommandPtr ptrCommandNode = static_cast<CCommandPtr>(node);
					actionNode *actNode = new actionNode(settingsNode, name);
					actNode->setDescription(description);
					actNode->setDisplayName(displayName);
					actNode->setLocked(!writeable);
					settingsNode->addChild(actNode);
				}
      }
  	}
  catch (Spinnaker::Exception& e) {
    std::cout << "Error: " << e.what() << std::endl;
    result = -1;
  }
  return result;
}


void FLIRChameleon::updateSettings(INodeMap& nodeMap, SettingsNode* parent) {
	QList<QString> simpleSettings = {"ExposureAuto", "ExposureTime" ,
																	 "GainAuto", "Gain",
																	 "Width", "Height", "OffsetX", "OffsetY",
																 	 "ReverseX", "ReverseY"};
	for (const auto & child : parent->children()) {
		if (child->type() == SettingsNode::Category) {
			updateSettings(nodeMap, child);
		}
		else {
			try {
				CNodePtr ptrNode = nodeMap.GetNode(child->name().toStdString().c_str());
				if (!IsAvailable(ptrNode) || !IsReadable(ptrNode)) {
						continue;
				}
				bool writeable = IsWritable(ptrNode);

				if (ptrNode->GetPrincipalInterfaceType() == intfIString) {
					CStringPtr ptrStringNode = static_cast<CStringPtr>(ptrNode);
					QString value = QString::fromStdString(ptrStringNode->GetValue().c_str());
					child->dataField()->blockSignals(true);
					static_cast<QLineEdit*>(child->dataField())->setText(value);
					child->dataField()->blockSignals(false);
					child->setLocked(!writeable);
				}
				else if (ptrNode->GetPrincipalInterfaceType() == intfIInteger) {
					CIntegerPtr ptrIntegerNode = static_cast<CIntegerPtr>(ptrNode);
					int value = ptrIntegerNode->GetValue();
					int max = ptrIntegerNode->GetMax();
					int min = ptrIntegerNode->GetMin();
					child->dataField()->blockSignals(true);
					if (child->name() == "Width") {
						m_frameSize.width = value;
					}
					else if (child->name() == "Height") {
						m_frameSize.height = value;
					}
					static_cast<intNode*>(child)->setValue(value);
					static_cast<intNode*>(child)->setMinValue(min);
					static_cast<intNode*>(child)->setMaxValue(max);
					child->dataField()->blockSignals(false);
					child->setLocked(!writeable);
					if (simpleSettings.contains(child->name())) {
						emit simpleSettingChanged(child->name(), QString::number(ptrIntegerNode->GetValue()), writeable, min, max);
					}
				}
				else if (ptrNode->GetPrincipalInterfaceType() == intfIFloat) {
					CFloatPtr ptrFloatNode = static_cast<CFloatPtr>(ptrNode);
					float value = ptrFloatNode->GetValue();
					float max = ptrFloatNode->GetMax();
					float min = ptrFloatNode->GetMin();
					child->dataField()->blockSignals(true);
					static_cast<floatNode*>(child)->setValue(value);
					static_cast<floatNode*>(child)->setMinValue(min);
					static_cast<floatNode*>(child)->setMaxValue(max);
					child->dataField()->blockSignals(false);
					child->setLocked(!writeable);
					if (simpleSettings.contains(child->name())) {
						emit simpleSettingChanged(child->name(), QString::number(ptrFloatNode->GetValue()), writeable, min, max);
					}
				}
				else if (ptrNode->GetPrincipalInterfaceType() == intfIBoolean) {
					CBooleanPtr ptrBooleanNode = static_cast<CBooleanPtr>(ptrNode);
					bool value = ptrBooleanNode->GetValue();
					child->dataField()->blockSignals(true);
					static_cast<boolNode*>(child)->setValue(value);
					child->dataField()->blockSignals(false);
					child->setLocked(!writeable);
					if (simpleSettings.contains(child->name())) {
						emit simpleSettingChanged(child->name(), QString::number(ptrBooleanNode->GetValue()), writeable, 0,0);

					}
				}
				else if (ptrNode->GetPrincipalInterfaceType() == intfIEnumeration) {
					CEnumerationPtr ptrEnumerationNode = static_cast<CEnumerationPtr>(ptrNode);
					CEnumEntryPtr ptrCurrentEnumEntryNode = ptrEnumerationNode->GetCurrentEntry();
					child->dataField()->blockSignals(true);
					static_cast<QComboBox*>(child->dataField())->setCurrentText(ptrCurrentEnumEntryNode->GetSymbolic().c_str());
					child->dataField()->blockSignals(false);
					child->setLocked(!writeable);
					if (simpleSettings.contains(child->name()))  {
						emit simpleSettingChanged(child->name(), QString::fromStdString(ptrCurrentEnumEntryNode->GetSymbolic().c_str()), writeable,0,0);
					}
				}
			}
			catch (Spinnaker::Exception& e) {
				std::cout << "Error: " << e.what() << std::endl;
			}
		}
	}
}

void FLIRChameleon::getSimpleSettingsValues() {
	m_pCam->Init();
	INodeMap& appLayerNodeMap = m_pCam->GetNodeMap();
	updateSettings(appLayerNodeMap, m_cameraSettings->getRootNode()->children()[0]);
	m_pCam->DeInit();
}


void FLIRChameleon::changeSimpleSetting(const QString& setting, const QString& val) {
	if (setting  == "ExposureAuto" || setting == "GainAuto") {
		QString valSend;
		if (val == "0") valSend = "Off";
		else valSend = "Continuous";
		settingChangedSlot(setting, {"FLIR Chameleon"}, SettingsNode::Enumeration, valSend, true);
	}
	else if (setting == "ExposureTime" || setting == "Gain") {
		settingChangedSlot(setting, {"FLIR Chameleon"}, SettingsNode::Float, val, true);
	}
	else if (setting == "Width" || setting == "Height" || setting == "OffsetX" || setting == "OffsetY") {
		settingChangedSlot(setting, {"FLIR Chameleon"}, SettingsNode::Integer, val, true);
	}
	else if (setting == "ReverseX" || setting == "ReverseY") {
		settingChangedSlot(setting, {"FLIR Chameleon"}, SettingsNode::Boolean, val, true);
	}
}


void FLIRChameleon::streamImageSlot(QImage img) {
	emit streamImage(img);
}


QString FLIRChameleon::getDefaultUserSet() {
	m_pCam->Init();
	INodeMap& nodeMap = m_pCam->GetNodeMap();
	CEnumerationPtr ptrUserSetDefault = nodeMap.GetNode("UserSetDefault");
	if (!IsAvailable(ptrUserSetDefault) || !IsReadable(ptrUserSetDefault)) {
			std::cout << "Unable to access User Set Default(enum retrieval). Aborting..." << std::endl;
	}
	QString userSet = QString::fromStdString(ptrUserSetDefault->GetCurrentEntry()->GetSymbolic().c_str());
	m_pCam->DeInit();
	return userSet;
}


bool FLIRChameleon::setDefaultUserSet(const QString& userSet) {
	m_pCam->Init();
	INodeMap& nodeMap = m_pCam->GetNodeMap();
	CEnumerationPtr ptrUserSetSelector = nodeMap.GetNode("UserSetSelector");
	if (!IsAvailable(ptrUserSetSelector) || !IsWritable(ptrUserSetSelector)) {
			std::cout << "Unable to access User Set Selector (enum retrieval). Aborting..." << std::endl;
	}
	CEnumEntryPtr ptrUserSet = ptrUserSetSelector->GetEntryByName(userSet.toStdString().c_str());
	if (!IsAvailable(ptrUserSet) || !IsReadable(ptrUserSet)) {
			std::cout << "Unable to access User Set (entry retrieval). Aborting..." << std::endl;
			return false;
	}
	CEnumerationPtr ptrUserSetDefault = nodeMap.GetNode("UserSetDefault");
	if (!IsAvailable(ptrUserSetDefault) || !IsWritable(ptrUserSetDefault)) {
			std::cout << "Unable to access User Set Default(enum retrieval). Aborting..." << std::endl;
			return false;
	}
	ptrUserSetDefault->SetIntValue(ptrUserSet->GetValue());
	m_pCam->DeInit();
	return true;
}

bool FLIRChameleon::saveUserSetToFile(const QString& userSet, const QString& path) {
	INodeMap& nodeMapTLDevice = m_pCam->GetTLDeviceNodeMap();
	m_pCam->Init();
	if (m_pCam->FileSelector == NULL) {
			std::cout << "File selector not supported on device!";
			return false;
	}

	NodeList_t selectorList;
	m_pCam->FileSelector.GetEntries(selectorList);

	for (unsigned int i = 0; i < selectorList.size(); i++) {
		CEnumEntryPtr node = selectorList.at(i);
		if (!node || !IsReadable(node)) {
				std::cout << node->GetSymbolic() << " not supported!" << std::endl;
				continue;
		}

		if (node->GetSymbolic().compare(userSet.toStdString().c_str()) == 0) {
				m_pCam->FileSelector.SetIntValue((int64_t)node->GetNumericValue());
				int64_t bytesToRead = m_pCam->FileSize.GetValue();
				if (bytesToRead == 0) {
						std::cout << "No data available to read!" << std::endl;
						continue;
				}

				if (openFileToRead() != true) {
						std::cout << "Failed to open file!" << std::endl;
						continue;
				}

				if (m_pCam->FileAccessLength.GetValue() < m_pCam->FileAccessBuffer.GetLength()) {
						try {
								m_pCam->FileAccessLength.SetValue(m_pCam->FileAccessBuffer.GetLength());
						}
						catch (Spinnaker::Exception& e) {
								std::cout << "Unable to set FileAccessLength to FileAccessBuffer length : " << e.what() << std::endl;
						}
				}
				m_pCam->FileAccessOffset.SetValue(0);

				int64_t intermediateBufferSize = m_pCam->FileAccessLength.GetValue();
				int64_t iterations = (bytesToRead / intermediateBufferSize) + (bytesToRead % intermediateBufferSize == 0 ? 0 : 1);

				int64_t index = 0;
				int64_t totalSizeRead = 0;
				std::unique_ptr<unsigned char> dataBuffer(new unsigned char[static_cast<unsigned int>(bytesToRead)]);
				unsigned char* pData = dataBuffer.get();

				for (unsigned int i = 0; i < iterations; i++) {
						if (!executeReadCommand()) {
								std::cout << "Reading stream failed!" << std::endl;
								break;
						}
						int64_t sizeRead = m_pCam->FileOperationResult.GetValue();
						m_pCam->FileAccessBuffer.Get(&pData[index], sizeRead);
						index = index + sizeRead;

						totalSizeRead += sizeRead;
				}

				if (!closeFile()) {
						std::cout << "Failed to close file!" << std::endl;
				}

				std::ofstream myfile;
				myfile.open(path.toStdString());
				myfile.write(reinterpret_cast<char*>(pData), totalSizeRead);
				myfile.close();
				m_pCam->DeInit();
				return true;
		}
	}
	return false;
}


bool FLIRChameleon::loadUserSetFromFile(const QString& userSet, const QString& path) {
	INodeMap& nodeMapTLDevice = m_pCam->GetTLDeviceNodeMap();
	m_pCam->Init();
	INodeMap& nodeMap = m_pCam->GetNodeMap();

	if (m_pCam->FileSelector == NULL) {
			std::cout << "File selector not supported on device!" << std::endl;
			return false;
	}

	NodeList_t selectorList;
	m_pCam->FileSelector.GetEntries(selectorList);

	for (unsigned int i = 0; i < selectorList.size(); i++)
	{
			CEnumEntryPtr node = selectorList.at(i);

			if (!node || !IsReadable(node)) {
					std::cout << node->GetSymbolic() << " not supported!" << std::endl;
					continue;
			}

			if (node->GetSymbolic().compare(userSet.toStdString().c_str()) == 0)
			{
					m_pCam->FileSelector.SetIntValue((int64_t)node->GetNumericValue());
					if (m_pCam->FileSize.GetValue() > 0) {
							if (executeDeleteCommand() != true) {
									std::cout << "Failed to delete file!" << std::endl;
									continue;
							}
					}

					if (openFileToWrite() != true) {
							std::cout << "Failed to open file!" << std::endl;
							if (!closeFile()) {
								std::cout << "Problem opening file node." << std::endl;
									return false;
							}
							if (!openFileToWrite())
							{
									std::cout << "Problem opening file node." << std::endl;
									return false;
							}
					}

					if (m_pCam->FileAccessLength.GetValue() < m_pCam->FileAccessBuffer.GetLength()) {
							try {
									m_pCam->FileAccessLength.SetValue(m_pCam->FileAccessBuffer.GetLength());
							}
							catch (Spinnaker::Exception& e) {
									std::cout << "Unable to set FileAccessLength to FileAccessBuffer length : " << e.what() << std::endl;
							}
					}
					m_pCam->FileAccessOffset.SetValue(0);
					unsigned char pData[5000];

					std::ifstream infile(path.toStdString());
					infile.seekg(0, std::ios::end);
					size_t length = infile.tellg();
					infile.seekg(0, std::ios::beg);
					if (length > sizeof (pData))
					{
							length = sizeof (pData);
					}
					infile.read(reinterpret_cast<char*>(pData), length);

					int64_t totalBytesToWrite = length;
					int64_t intermediateBufferSize = m_pCam->FileAccessLength.GetValue();
					int64_t writeIterations = (totalBytesToWrite / intermediateBufferSize) +
																		(totalBytesToWrite % intermediateBufferSize == 0 ? 0 : 1);

					if (totalBytesToWrite == 0) {
							std::cout << "Empty Image. No data will be written to camera." << std::endl;
							return false;
					}

					int64_t index = 0;
					int64_t bytesLeftToWrite = totalBytesToWrite;
					int64_t totalBytesWritten = 0;
					bool paddingRequired = false;
					int numPaddings = 0;

					for (unsigned int i = 0; i < writeIterations; i++)
					{
							if (intermediateBufferSize > bytesLeftToWrite) {
									unsigned int remainder = bytesLeftToWrite % 4;
									if (remainder != 0)	{
											paddingRequired = true;
											numPaddings = 4 - remainder;
									}
							}

							int64_t tmpBufferSize = intermediateBufferSize <= bytesLeftToWrite
																					? intermediateBufferSize
																					: (bytesLeftToWrite + numPaddings);
							std::unique_ptr<unsigned char> tmpBuffer(
									new unsigned char[static_cast<unsigned int>(tmpBufferSize)]);
							memcpy(
									tmpBuffer.get(),
									&pData[index],
									static_cast<unsigned int>(
											(intermediateBufferSize <= bytesLeftToWrite) ? intermediateBufferSize : bytesLeftToWrite));

							if (paddingRequired) {
									for (int j = 0; j < numPaddings; j++) {
											unsigned char* pTmpBuffer = tmpBuffer.get();
											pTmpBuffer[bytesLeftToWrite + j] = 255;
									}
							}

							// Update index for next write iteration
							index = index +
											(intermediateBufferSize <= bytesLeftToWrite ? intermediateBufferSize : bytesLeftToWrite);

							m_pCam->FileAccessBuffer.Set(tmpBuffer.get(), tmpBufferSize);

							if (intermediateBufferSize > bytesLeftToWrite) {
									// Update FileAccessLength node appropriately to prevent garbage data outside the range of
									// the uploaded file to be written to the camera
									m_pCam->FileAccessLength.SetValue(bytesLeftToWrite);
							}

							// Perform Write command
							if (!executeWriteCommand())
							{
									std::cout << "Writing to stream failed!" << std::endl;
									break;
							}

							int64_t sizeWritten = m_pCam->FileOperationResult.GetValue();

							totalBytesWritten += sizeWritten;
							bytesLeftToWrite = totalBytesToWrite - totalBytesWritten;
					}
					if (!closeFile())
					{
							std::cout << "Failed to close file!" << std::endl;
					}
			}
	}
	m_pCam->DeInit();
}


bool FLIRChameleon::openFileToRead() {
  bool result = true;
  std::cout << "Opening file for reading..." << std::endl;
  try {
      m_pCam->FileOperationSelector.SetValue(FileOperationSelector_Open);
      m_pCam->FileOpenMode.SetValue(FileOpenMode_Read);
      m_pCam->FileOperationExecute.Execute();
      if (m_pCam->FileOperationStatus.GetValue() != FileOperationStatus_Success) {
          std::cout << "Failed to open file for reading!" << std::endl;
          return false;
      }
  }
  catch (Spinnaker::Exception& e) {
      std::cout << "Unexpected exception : " << e.what() << std::endl;
      result = false;
  }
  return result;
}


bool FLIRChameleon::openFileToWrite() {
    bool result = true;
    try {
        m_pCam->FileOperationSelector.SetValue(FileOperationSelector_Open);
        m_pCam->FileOpenMode.SetValue(FileOpenMode_Write);
        m_pCam->FileOperationExecute.Execute();

        if (m_pCam->FileOperationStatus.GetValue() != FileOperationStatus_Success) {
            std::cout << "Failed to open file for writing!" << std::endl;
            return false;
        }
    }
    catch (Spinnaker::Exception& e)
    {
        std::cout << "Unexpected exception : " << e.what() << std::endl;
        result = false;
    }
    return result;
}


bool FLIRChameleon::closeFile() {
  bool result = true;
  try {
      m_pCam->FileOperationSelector.SetValue(FileOperationSelector_Close);
      m_pCam->FileOperationExecute.Execute();

      if (m_pCam->FileOperationStatus.GetValue() != FileOperationStatus_Success) {
          std::cout << "Failed to close file!" << std::endl;
          return false;
      }
  }
  catch (Spinnaker::Exception& e) {
      std::cout << "Unexpected exception : " << e.what() << std::endl;
      result = false;
  }
}

bool FLIRChameleon::executeReadCommand() {
  bool result = true;
  try {
      m_pCam->FileOperationSelector.SetValue(FileOperationSelector_Read);
      m_pCam->FileOperationExecute.Execute();
      if (m_pCam->FileOperationStatus.GetValue() != FileOperationStatus_Success) {
          std::cout << "Failed to read file!" << std::endl;
          return false;
      }
  }
  catch (Spinnaker::Exception& e) {
      std::cout << "Unexpected exception : " << e.what() << std::endl;
      result = false;
  }
  return result;
}


bool FLIRChameleon::executeWriteCommand() {
    bool result = true;
    try {
        m_pCam->FileOperationSelector.SetValue(FileOperationSelector_Write);
        m_pCam->FileOperationExecute.Execute();
        if (m_pCam->FileOperationStatus.GetValue() != FileOperationStatus_Success) {
            std::cout << "Failed to write to file!" << std::endl;
            return false;
        }
    }
    catch (Spinnaker::Exception& e)
    {
        std::cout << "Unexpected exception : " << e.what() << std::endl;
        result = false;
    }
    return result;
}


bool FLIRChameleon::executeDeleteCommand() {
    bool result = true;
    try {
        m_pCam->FileOperationSelector.SetValue(FileOperationSelector_Delete);
        m_pCam->FileOperationExecute.Execute();

        if (m_pCam->FileOperationStatus.GetValue() != FileOperationStatus_Success) {
            std::cout << "Failed to delete file!" << std::endl;
            return false;
        }
    }
    catch (Spinnaker::Exception& e) {
        std::cout << "Unexpected exception : " << e.what() << std::endl;
        result = false;
    }
    return result;
}
