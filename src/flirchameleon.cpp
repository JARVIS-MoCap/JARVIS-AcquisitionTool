/*******************************************************************************
 * File:			  flirchameleon.cpp
 * Created: 	  05. June 2020
 * Author:		  Timo Hueser
 * Contact: 	  timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

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
//using namespace Spinnaker::GenApi;
using namespace Spinnaker::GenICam;

FlirWorker::FlirWorker(Spinnaker::CameraPtr pCam, const QString& cameraName,
			const AcquisitionSpecs& acquisitionSpecs) :
			AcquisitionWorker{cameraName, acquisitionSpecs}, m_pCam{pCam}
{ }


FlirWorker::~FlirWorker() {
	delete m_recordingInterface;
}


void FlirWorker::acquireImages() {
	unsigned long frameIndex = 0;
	int duration_sum = 0;
	forever {
		try {
			if (TriggerInterface::triggerInstance == nullptr &&
						QThread::currentThread()->isInterruptionRequested()) break;
			ImagePtr pResultImage = m_pCam->GetNextImage(2000 /
						m_acquisitionSpecs.frameRate);

			if (pResultImage->IsIncomplete()) {
				emit statusUpdated(statusType::Error, "Incomplete Image received");
			}
			else {
				auto t1 = std::chrono::high_resolution_clock::now();
				m_img = m_recordingInterface->recordFrame(
							static_cast<uchar*>(pResultImage->GetData()));
				pResultImage->Release();
				if (!m_acquisitionSpecs.record || globalSettings.streamingEnabled) {
					emit streamImage(m_img);
				}
				auto t2 = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::microseconds>
							(t2 - t1).count();
				duration_sum += duration;
				if (frameIndex > 0 && frameIndex%(std::max(1,
							m_acquisitionSpecs.frameRate / 8)) == 0) {
					emit latencyAndFrameNumberUpdate(duration_sum /
								std::max(1, m_acquisitionSpecs.frameRate / 8), frameIndex);
					duration_sum = 0;
				}
				frameIndex++;
			}
		}
		catch (Spinnaker::Exception& e)
		{
				if (e == SPINNAKER_ERR_TIMEOUT) {
					if (QThread::currentThread()->isInterruptionRequested()) {
						return;
					}
					else if (TriggerInterface::triggerInstance == nullptr) {
						emit statusUpdated(statusType::Error, e.what());
					}
				}
				else {
					emit statusUpdated(statusType::Error, e.what());
					delayl(1000);
				}
		}

	}
}



FLIRChameleon::FLIRChameleon(const QString& cameraName,
			const QString& serialNumber) : CameraInterface(flirChameleon, cameraName),
			  m_serialNumber{serialNumber},
			  m_camSystem{System::GetInstance()} {
	const LibraryVersion spinnakerLibraryVersion =
				m_camSystem->GetLibraryVersion();
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
	//if (cameraList.size() == 0) m_camSystem->ReleaseInstance();
	delete (m_cameraSettings);
}


bool FLIRChameleon::savePreset(const QString& preset) {
	try {
		bool deinit = false;
		if (!m_pCam->IsInitialized()) {
			m_pCam->Init();
			deinit = true;
		}
		GenApi::INodeMap& nodeMap = m_pCam->GetNodeMap();
		GenApi::CEnumerationPtr ptrUserSetSelector =
					nodeMap.GetNode("UserSetSelector");
		if (!IsAvailable(ptrUserSetSelector) || !IsWritable(ptrUserSetSelector)) {
				std::cout << "Unable to access User Set Selector "
				"(enum retrieval). Aborting..." << std::endl;
				return false;
		}

		GenApi::CEnumEntryPtr ptrUserSet = ptrUserSetSelector->GetEntryByName(
					preset.toStdString().c_str());
		if (!IsAvailable(ptrUserSet) || !IsReadable(ptrUserSet)) {
				std::cout << "Unable to access User Set (entry retrieval). "
				"Aborting..." << std::endl;
				return false;
		}
		ptrUserSetSelector->SetIntValue(ptrUserSet->GetValue());

		GenApi::CCommandPtr ptrUserSetSave =
					m_pCam->GetNodeMap().GetNode("UserSetSave");
		if (!IsAvailable(ptrUserSetSave) || !IsWritable(ptrUserSetSave)){
				std::cout << "Unable to save to User Set. Aborting..." << std::endl;
		}
		ptrUserSetSave->Execute();
		if (deinit) {
			m_pCam->DeInit();
		}
	}
	catch (Spinnaker::Exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
		emit statusUpdated(statusType::Warning, e.what());
		return false;
	}
	return true;
}


bool FLIRChameleon::loadPreset(const QString& preset) {
	try {
		bool deinit = false;
		if (!m_pCam->IsInitialized()) {
			m_pCam->Init();
			deinit = true;
		}
		GenApi::INodeMap& nodeMap = m_pCam->GetNodeMap();
		GenApi::CEnumerationPtr ptrUserSetSelector =
					nodeMap.GetNode("UserSetSelector");
		if (!IsAvailable(ptrUserSetSelector) || !IsWritable(ptrUserSetSelector)) {
				std::cout << "Unable to access User Set Selector (enum retrieval). "
				"Aborting..." << std::endl;
				return false;
		}

		GenApi::CEnumEntryPtr ptrUserSet =
					ptrUserSetSelector->GetEntryByName(preset.toStdString().c_str());
		if (!IsAvailable(ptrUserSet) || !IsReadable(ptrUserSet)) {
				std::cout << "Unable to access User Set (entry retrieval). "
				"Aborting..." << std::endl;
				return false;
		}
		ptrUserSetSelector->SetIntValue(ptrUserSet->GetValue());

		GenApi::CCommandPtr ptrUserSetLoad =
					m_pCam->GetNodeMap().GetNode("UserSetLoad");
		if (!IsAvailable(ptrUserSetLoad) || !IsWritable(ptrUserSetLoad)){
				std::cout << "Unable to load to User Set. Aborting..." << std::endl;
		}
		ptrUserSetLoad->Execute();
		updateSettings(nodeMap, m_cameraSettings->getRootNode()->children()[0]);
		if (deinit) {
			m_pCam->DeInit();
		}
		GenApi::INodeMap& genTLNodeMap = m_pCam->GetTLDeviceNodeMap();
		GenApi::INodeMap& nodeMapTLStream = m_pCam->GetTLStreamNodeMap();
		updateSettings(genTLNodeMap,
					m_cameraSettings->getRootNode()->children()[1]);
		updateSettings(nodeMapTLStream,
					m_cameraSettings->getRootNode()->children()[2]);
		return true;
	}
	catch (Spinnaker::Exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
		emit statusUpdated(statusType::Warning, e.what());
		return false;
	}
}


void FLIRChameleon::settingChangedSlot(const QString& name,
	QList<QString> subMenus, SettingsNode::nodeType type,
	const QString& val, bool update) {
	try {
		if (subMenus.last() == "FLIR Chameleon" && update) m_pCam->Init();
		GenApi::INodeMap& genTLNodeMap = m_pCam->GetTLDeviceNodeMap();
		GenApi::INodeMap& nodeMapTLStream = m_pCam->GetTLStreamNodeMap();
		GenApi::INodeMap& appLayerNodeMap = m_pCam->GetNodeMap();

		GenApi::CNodePtr ptrNode = nullptr;
		gcstring cName = name.toStdString().c_str();
		if (subMenus.last() == "FLIR Chameleon") ptrNode =
					appLayerNodeMap.GetNode(cName);
		else if (subMenus.last() == "Stream Parameters") ptrNode =
					nodeMapTLStream.GetNode(cName);
		else if (subMenus.last() == "Transport Layer") ptrNode =
					genTLNodeMap.GetNode(cName);
		if (type == SettingsNode::String) {
			GenApi::CStringPtr ptrString = static_cast<GenApi::CStringPtr>(ptrNode);
			if (IsAvailable(ptrString) && IsWritable(ptrString)) {
				ptrString->SetValue(val.toStdString().c_str());
			}
		}

		else if (type == SettingsNode::Integer) {
			GenApi::CIntegerPtr ptrInt = static_cast<GenApi::CIntegerPtr>(ptrNode);
			if (IsAvailable(ptrInt) && IsWritable(ptrNode)) {
				ptrInt->SetValue(val.toInt());
			}
		}

		else if (type == SettingsNode::Float) {
			GenApi::CFloatPtr ptrFloat = static_cast<GenApi::CFloatPtr>(ptrNode);
			if (IsAvailable(ptrFloat) && IsWritable(ptrFloat)) {
				ptrFloat->SetValue(val.toFloat());
			}
		}

		else if(type == SettingsNode::Enumeration) {
			GenApi::CEnumerationPtr ptrEnum =
						static_cast<GenApi::CEnumerationPtr>(ptrNode);
			if (IsAvailable(ptrEnum) && IsWritable(ptrEnum)) {
				auto ptrEnumItem = ptrEnum->GetEntryByName(val.toStdString().c_str());
				if (IsAvailable(ptrEnumItem) && IsReadable(ptrEnumItem)) {
					ptrEnum->SetIntValue(ptrEnumItem->GetValue());
				}
			}
		}

		else if (type == SettingsNode::Boolean) {
			GenApi::CBooleanPtr ptrBool = static_cast<GenApi::CBooleanPtr>(ptrNode);
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
			GenApi::CCommandPtr ptrCommand =
						static_cast<GenApi::CCommandPtr>(ptrNode);
			if (IsAvailable(ptrCommand) && IsWritable(ptrCommand)) {
				std::cout << "Not Implemented yet" << std::endl;
			}

		}
		if (update) {
			if (subMenus.last() == "FLIR Chameleon") updateSettings(appLayerNodeMap,
						m_cameraSettings->getRootNode()->children()[0]);
			else if (subMenus.last() == "Transport Layer")
						updateSettings(genTLNodeMap,
													 m_cameraSettings->getRootNode()->children()[1]);
			else if (subMenus.last() == "Stream Parameters")
						updateSettings(nodeMapTLStream,
													 m_cameraSettings->getRootNode()->children()[2]);
		}
		if (subMenus.last() == "FLIR Chameleon" && update && !m_isStreaming)
					m_pCam->DeInit();
	}
	catch (Spinnaker::Exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
		emit statusUpdated(statusType::Warning, e.what());
	}
}


void FLIRChameleon::startAcquisitionSlot(AcquisitionSpecs acquisitionSpecs) {
	if (!m_isStreaming) {
		try {
			m_pCam->Init();
			GenApi::INodeMap& appLayerNodeMap = m_pCam->GetNodeMap();
			updateSettings(appLayerNodeMap, m_cameraSettings->findNode("Pixel Format",
						m_cameraSettings->getRootNode()->children()[0]));
			updateSettings(appLayerNodeMap, m_cameraSettings->findNode("Width",
						m_cameraSettings->getRootNode()->children()[0]));
			updateSettings(appLayerNodeMap, m_cameraSettings->findNode("Height",
						m_cameraSettings->getRootNode()->children()[0]));
			if(TriggerInterface::triggerInstance == nullptr) {
				acquisitionSpecs.frameRate = m_frameRate;
			}
			acquisitionSpecs.frameSize = m_frameSize;
			acquisitionSpecs.pixelFormat = m_pixelFormat;
			m_acquisitionWorker = new FlirWorker(m_pCam, m_cameraName,acquisitionSpecs);
			m_acquisitionWorker->moveToThread(&workerThread);
			connect(this, &FLIRChameleon::startAcquisition,
							m_acquisitionWorker, &AcquisitionWorker::acquireImages);
			connect(m_acquisitionWorker, &AcquisitionWorker::streamImage,
							this, &FLIRChameleon::streamImage);
			connect(m_acquisitionWorker, &AcquisitionWorker::latencyAndFrameNumberUpdate,
							this, &FLIRChameleon::latencyAndFrameNumberUpdate);
			connect(m_acquisitionWorker, &AcquisitionWorker::statusUpdated,
							this, &FLIRChameleon::statusUpdated);
			connect(&workerThread, &QThread::finished,
							m_acquisitionWorker, &AcquisitionWorker::deleteLater);
			m_pCam->BeginAcquisition();
			updateSettings(appLayerNodeMap, m_cameraSettings->findNode("Exposure Auto",
						m_cameraSettings->getRootNode()->children()[0]));
			updateSettings(appLayerNodeMap, m_cameraSettings->findNode("Exposure Time",
						m_cameraSettings->getRootNode()->children()[0]));
			updateSettings(appLayerNodeMap, m_cameraSettings->findNode("Gain Auto",
			 			m_cameraSettings->getRootNode()->children()[0]));
			updateSettings(appLayerNodeMap, m_cameraSettings->findNode("Gain",
						m_cameraSettings->getRootNode()->children()[0]));
			updateSettings(appLayerNodeMap, m_cameraSettings->findNode("Width",
						m_cameraSettings->getRootNode()->children()[0]));
			updateSettings(appLayerNodeMap, m_cameraSettings->findNode("Height",
						m_cameraSettings->getRootNode()->children()[0]));
			workerThread.start();
			emit startAcquisition();
			emit statusUpdated(Streaming, "Started Streaming");
			m_isStreaming = true;
		}
		catch (Spinnaker::Exception& e) {
			std::cout << "Error: " << e.what() << std::endl;
			emit statusUpdated(statusType::Error, e.what());
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
		GenApi::INodeMap& appLayerNodeMap = m_pCam->GetNodeMap();
		updateSettings(appLayerNodeMap,
					m_cameraSettings->getRootNode()->children()[0]);
		m_pCam->DeInit();
		emit statusUpdated(Ready, "Stopped Streaming");
	}
	catch (Spinnaker::Exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
		emit statusUpdated(statusType::Error, e.what());
	}
	m_isStreaming = false;
}


void FLIRChameleon::createSettings() {
	m_cameraSettingsRootNode = new RootNode("FLIR Chameleon");

	GenApi::INodeMap& genTLNodeMap = m_pCam->GetTLDeviceNodeMap();
	CategoryNode *transportLayerNode = new CategoryNode(m_cameraSettingsRootNode,
				"Transport Layer");
	createSettingsTreeFromCam(genTLNodeMap.GetNode("Root"), transportLayerNode);

	GenApi::INodeMap& nodeMapTLStream = m_pCam->GetTLStreamNodeMap();
	GenApi::CIntegerPtr ptrNode =
				nodeMapTLStream.GetNode("StreamBufferCountManual");
	try {
		if (IsAvailable(ptrNode) && IsWritable(ptrNode))
			ptrNode->SetValue(55);
	}
	catch (Spinnaker::Exception& e) {
		//if this error occurs try sudo sh -c 'echo 1 >/proc/sys/vm/drop_caches' and rerun
		std::cout << "Error: " << e.what() << std::endl;
		emit statusUpdated(statusType::Warning, e.what());
	}
	CategoryNode *streamLayerNode = new CategoryNode(m_cameraSettingsRootNode,
					"Stream Parameters");
	createSettingsTreeFromCam(nodeMapTLStream.GetNode("Root"), streamLayerNode);

	m_pCam->Init();
	GenApi::INodeMap& appLayerNodeMap = m_pCam->GetNodeMap();
	CategoryNode *geniCamNode = new CategoryNode(m_cameraSettingsRootNode,
				"FLIR Chameleon");
	createSettingsTreeFromCam(appLayerNodeMap.GetNode("Root"), geniCamNode);
	m_pCam->DeInit();

	m_cameraSettingsRootNode->addChild(geniCamNode);
	m_cameraSettingsRootNode->addChild(transportLayerNode);
	m_cameraSettingsRootNode->addChild(streamLayerNode);

	m_cameraSettings = new SettingsObject(this, "Camera Settings",
				m_cameraSettingsRootNode);
	connect(m_cameraSettings, &SettingsObject::settingChanged,
					this, &FLIRChameleon::settingChangedSlot);
}


int FLIRChameleon::createSettingsTreeFromCam(GenApi::CNodePtr node,
				SettingsNode *settingsNode) {
  int result = 0;
  try {
    GenApi::CCategoryPtr ptrCategoryNode =
					static_cast<GenApi::CCategoryPtr>(node);
    GenApi::FeatureList_t features;
    ptrCategoryNode->GetFeatures(features);
    GenApi::FeatureList_t::const_iterator it;
    for (it = features.begin(); it != features.end(); ++it) {
        GenApi::CNodePtr ptrFeatureNode = *it;
        if (!IsAvailable(ptrFeatureNode) || !IsReadable(ptrFeatureNode)) {
            continue;
        }
				QString name = QString::fromStdString(ptrFeatureNode->GetName().c_str());
				QString displayName = QString::fromStdString(
							ptrFeatureNode->GetDisplayName().c_str());
				QString description = QString::fromStdString(
							ptrFeatureNode->GetDescription().c_str());
				bool writeable = IsWritable(ptrFeatureNode);
        if (ptrFeatureNode->GetPrincipalInterfaceType() ==
						GenApi::intfICategory) {
					CategoryNode *catNode = new CategoryNode(settingsNode, name);
					catNode->setDescription(description);
					catNode->setDisplayName(displayName);
					settingsNode->addChild(catNode);
          result = result | createSettingsTreeFromCam(ptrFeatureNode, catNode);
        }
				else if (ptrFeatureNode->GetPrincipalInterfaceType() ==
								 GenApi::intfIString) {
					GenApi::CStringPtr ptrStringNode =
								static_cast<GenApi::CStringPtr>(ptrFeatureNode);
					QString value = QString::fromStdString(
								ptrStringNode->GetValue().c_str());
					StringNode *strNode = new StringNode(settingsNode, name);
					strNode->setDescription(description);
					strNode->setDisplayName(displayName);
					strNode->setValue(value);
					strNode->setLocked(!writeable);
					settingsNode->addChild(strNode);
        }
				else if (ptrFeatureNode->GetPrincipalInterfaceType() ==
							GenApi::intfIInteger) {
					GenApi::CIntegerPtr ptrIntegerNode =
								static_cast<GenApi::CIntegerPtr>(ptrFeatureNode);
					int value = ptrIntegerNode->GetValue();
					int max = ptrIntegerNode->GetMax();
					int min = ptrIntegerNode->GetMin();
					IntNode *iNode = new IntNode(settingsNode, name);
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
				else if (ptrFeatureNode->GetPrincipalInterfaceType() ==
							GenApi::intfIFloat) {
					GenApi::CFloatPtr ptrFloatNode =
								static_cast<GenApi::CFloatPtr>(ptrFeatureNode);
					float value = ptrFloatNode->GetValue();
					float max = ptrFloatNode->GetMax();
					float min = ptrFloatNode->GetMin();
					FloatNode *fNode = new FloatNode(settingsNode, name);
					if (name == "AcquisitionFrameRate") {
						m_frameRate = std::max(1,static_cast<int>(value));
					}
					fNode->setDescription(description);
					fNode->setDisplayName(displayName);
					fNode->setRange(min,max);
					fNode->setValue(value);
					fNode->setLocked(!writeable);
					settingsNode->addChild(fNode);
				}
				else if (ptrFeatureNode->GetPrincipalInterfaceType() ==
							GenApi::intfIEnumeration) {
					GenApi::CEnumerationPtr ptrEnumerationNode =
								static_cast<GenApi::CEnumerationPtr>(ptrFeatureNode);
					EnumNode *eNode = new EnumNode(settingsNode, name);
					eNode->setDescription(description);
					eNode->setDisplayName(displayName);
					auto ptrCurrentEnumEntryNode = ptrEnumerationNode->GetCurrentEntry();
					GenApi::NodeList_t entries;
					ptrEnumerationNode->GetEntries(entries);
					GenApi::NodeList_t::const_iterator it;
					for (it = entries.begin(); it != entries.end(); ++it) {
						GenApi::CEnumEntryPtr ptrEnumEntryNode = *it;
						if (IsAvailable(ptrEnumEntryNode) && IsReadable(ptrEnumEntryNode)) {
							QString symbolic = QString::fromStdString(
										ptrEnumEntryNode->GetSymbolic().c_str());
							EnumItemNode *itemNode = new EnumItemNode(eNode, symbolic);
							eNode->addItem(itemNode);
							if (ptrCurrentEnumEntryNode == ptrEnumEntryNode)
										eNode->setCurrentItem(itemNode);
						}
					}
					eNode->setLocked(!writeable);
					settingsNode->addChild(eNode);
				}
				else if (ptrFeatureNode->GetPrincipalInterfaceType() ==
							GenApi::intfIBoolean) {
					GenApi::CBooleanPtr ptrBooleanNode =
								static_cast<GenApi::CBooleanPtr>(ptrFeatureNode);
					bool value = ptrBooleanNode->GetValue();
					BoolNode *bNode = new BoolNode(settingsNode, name);
					bNode->setDescription(description);
					bNode->setDisplayName(displayName);
					bNode->setValue(value);
					bNode->setLocked(!writeable);
					settingsNode->addChild(bNode);
				}
				else if (ptrFeatureNode->GetPrincipalInterfaceType() ==
							GenApi::intfICommand) {
					GenApi::CCommandPtr ptrCommandNode =
								static_cast<GenApi::CCommandPtr>(node);
					ActionNode *actNode = new ActionNode(settingsNode, name);
					actNode->setDescription(description);
					actNode->setDisplayName(displayName);
					actNode->setLocked(!writeable);
					settingsNode->addChild(actNode);
				}
      }
  	}
  catch (Spinnaker::Exception& e) {
    std::cout << "Error: " << e.what() << std::endl;
		emit statusUpdated(statusType::Warning, e.what());
    result = -1;
  }
  return result;
}


void FLIRChameleon::updateSettings(GenApi::INodeMap& nodeMap,
			SettingsNode* parent) {
	QList<QString> simpleSettings = {"ExposureAuto", "ExposureTime" ,
																	 "GainAuto", "Gain",
																	 "Width", "Height", "OffsetX", "OffsetY",
																 	 "ReverseX", "ReverseY"};
if(parent->type() == SettingsNode::Root || parent->type() ==
			SettingsNode::Category) {
	for (const auto & child : parent->children()) {
		updateSettings(nodeMap, child);
	}
}
else {
		try {
			GenApi::CNodePtr ptrNode = nodeMap.GetNode(
						parent->name().toStdString().c_str());
			if (!IsAvailable(ptrNode) || !IsReadable(ptrNode)) {
					return;
			}
			bool writeable = IsWritable(ptrNode);

			if (ptrNode->GetPrincipalInterfaceType() == GenApi::intfIString) {
				GenApi::CStringPtr ptrStringNode =
							static_cast<GenApi::CStringPtr>(ptrNode);
				QString value = QString::fromStdString(
							ptrStringNode->GetValue().c_str());
				parent->dataField()->blockSignals(true);
				static_cast<QLineEdit*>(parent->dataField())->setText(value);
				parent->dataField()->blockSignals(false);
				parent->setLocked(!writeable);
			}
			else if (ptrNode->GetPrincipalInterfaceType() == GenApi::intfIInteger) {
				GenApi::CIntegerPtr ptrIntegerNode =
							static_cast<GenApi::CIntegerPtr>(ptrNode);
				int value = ptrIntegerNode->GetValue();
				int max = ptrIntegerNode->GetMax();
				int min = ptrIntegerNode->GetMin();
				parent->dataField()->blockSignals(true);
				if (parent->name() == "Width") {
					m_frameSize.width = value;
				}
				else if (parent->name() == "Height") {
					m_frameSize.height = value;
				}
				static_cast<IntNode*>(parent)->setValue(value);
				static_cast<IntNode*>(parent)->setMinValue(min);
				static_cast<IntNode*>(parent)->setMaxValue(max);
				parent->dataField()->blockSignals(false);
				parent->setLocked(!writeable);
				if (simpleSettings.contains(parent->name())) {
					emit simpleSettingChanged(parent->name(),
								QString::number(ptrIntegerNode->GetValue()), writeable,
								min, max);
				}
			}
			else if (ptrNode->GetPrincipalInterfaceType() == GenApi::intfIFloat) {
				GenApi::CFloatPtr ptrFloatNode =
							static_cast<GenApi::CFloatPtr>(ptrNode);
				float value = ptrFloatNode->GetValue();
				float max = ptrFloatNode->GetMax();
				float min = ptrFloatNode->GetMin();
				parent->dataField()->blockSignals(true);
				static_cast<FloatNode*>(parent)->setValue(value);
				static_cast<FloatNode*>(parent)->setMinValue(min);
				static_cast<FloatNode*>(parent)->setMaxValue(max);
				parent->dataField()->blockSignals(false);
				parent->setLocked(!writeable);
				if (simpleSettings.contains(parent->name())) {
					emit simpleSettingChanged(parent->name(),
								QString::number(ptrFloatNode->GetValue()), writeable, min, max);
				}
				if (parent->name() == "AcquisitionFrameRate") {
					m_frameRate = std::max(1,static_cast<int>(ptrFloatNode->GetValue()));
				}
			}
			else if (ptrNode->GetPrincipalInterfaceType() == GenApi::intfIBoolean) {
				GenApi::CBooleanPtr ptrBooleanNode =
							static_cast<GenApi::CBooleanPtr>(ptrNode);
				bool value = ptrBooleanNode->GetValue();
				parent->dataField()->blockSignals(true);
				static_cast<BoolNode*>(parent)->setValue(value);
				parent->dataField()->blockSignals(false);
				parent->setLocked(!writeable);
				if (simpleSettings.contains(parent->name())) {
					emit simpleSettingChanged(parent->name(),
								QString::number(ptrBooleanNode->GetValue()), writeable, 0,0);

				}
			}
			else if (ptrNode->GetPrincipalInterfaceType() ==
						GenApi::intfIEnumeration) {
				parent->dataField()->blockSignals(true);
				GenApi::CEnumerationPtr ptrEnumerationNode =
							static_cast<GenApi::CEnumerationPtr>(ptrNode);
				GenApi::CEnumEntryPtr ptrCurrentEnumEntryNode =
							ptrEnumerationNode->GetCurrentEntry();
				GenApi::NodeList_t entries;
				ptrEnumerationNode->GetEntries(entries);
				GenApi::NodeList_t::const_iterator it;
				static_cast<EnumNode*>(parent)->clearItems();
				for (it = entries.begin(); it != entries.end(); ++it) {
					GenApi::CEnumEntryPtr ptrEnumEntryNode = *it;
					if (IsAvailable(ptrEnumEntryNode) && IsReadable(ptrEnumEntryNode)) {
						QString symbolic = QString::fromStdString(
									ptrEnumEntryNode->GetSymbolic().c_str());
						EnumItemNode *itemNode = new EnumItemNode(parent, symbolic);
						static_cast<EnumNode*>(parent)->addItem(itemNode);
						if (ptrCurrentEnumEntryNode == ptrEnumEntryNode)
									static_cast<EnumNode*>(parent)->setCurrentItem(itemNode);
					}
				}
				static_cast<QComboBox*>(parent->dataField())->setCurrentText(
							ptrCurrentEnumEntryNode->GetSymbolic().c_str());
				parent->dataField()->blockSignals(false);
				parent->setLocked(!writeable);
				if (simpleSettings.contains(parent->name()))  {
					emit simpleSettingChanged(parent->name(),
								QString::fromStdString(
								ptrCurrentEnumEntryNode->GetSymbolic().c_str()), writeable,0,0);
				}
				QString camPixelFormat = QString::fromStdString(
							ptrCurrentEnumEntryNode->GetSymbolic().c_str());
				if (parent->name() == "PixelFormat") {
					if (camPixelFormat == "BayerRG8") {
						m_pixelFormat = PixelFormat::BayerRG8;
					}
					else if (camPixelFormat == "BayerGB8") {
						m_pixelFormat = PixelFormat::BayerGB8;
					}
					else if (camPixelFormat == "BayerGR8") {
						m_pixelFormat = PixelFormat::BayerGR8;
					}
					else if (camPixelFormat == "BayerBG8") {
						m_pixelFormat = PixelFormat::BayerBG8;
					}
					else if (camPixelFormat == "BGR8") {
						m_pixelFormat = PixelFormat::BGR8;
					}
					else if (camPixelFormat == "Mono8") {
						m_pixelFormat = PixelFormat::Mono8;
					}
					else if (camPixelFormat == "YCbCr422_8") {
						m_pixelFormat = PixelFormat::YCbCr422;
					}
				}
			}
		}
		catch (Spinnaker::Exception& e) {
			std::cout << "Error: " << e.what() << std::endl;
			emit statusUpdated(statusType::Warning, e.what());
		}
	}
}

void FLIRChameleon::getSimpleSettingsValues() {
	try {
		bool deinit = false;
		if(!m_pCam->IsInitialized()) {
			m_pCam->Init();
			deinit = true;
		}
		GenApi::INodeMap& appLayerNodeMap = m_pCam->GetNodeMap();
		updateSettings(appLayerNodeMap,
					m_cameraSettings->getRootNode()->children()[0]);
		if (deinit) {
			m_pCam->DeInit();
		}
	}
	catch (Spinnaker::Exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
		emit statusUpdated(statusType::Warning, e.what());
	}
}


void FLIRChameleon::changeSimpleSetting(const QString& setting,
			const QString& val) {
	if (setting  == "ExposureAuto" || setting == "GainAuto") {
		QString valSend;
		if (val == "0") valSend = "Off";
		else valSend = "Continuous";
		settingChangedSlot(setting, {"FLIR Chameleon"}, SettingsNode::Enumeration,
					valSend, true);
	}
	else if (setting == "ExposureTime" || setting == "Gain") {
		settingChangedSlot(setting, {"FLIR Chameleon"}, SettingsNode::Float, val,
					true);
	}
	else if (setting == "Width" || setting == "Height" || setting == "OffsetX" ||
				setting == "OffsetY") {
		settingChangedSlot(setting, {"FLIR Chameleon"}, SettingsNode::Integer, val,
					true);
	}
	else if (setting == "ReverseX" || setting == "ReverseY") {
		settingChangedSlot(setting, {"FLIR Chameleon"}, SettingsNode::Boolean, val,
					true);
	}
}

//TODO:: probably delete since now done by signal relay
void FLIRChameleon::streamImageSlot(QImage img) {
	emit streamImage(img);
}

int FLIRChameleon::getBufferUsage() {
	int bufferState = 0;
	GenApi::INodeMap& nodeMapTLStream = m_pCam->GetTLStreamNodeMap();
	GenApi::CIntegerPtr ptrNode =
				nodeMapTLStream.GetNode("StreamOutputBufferCount");
	try {
		if (IsAvailable(ptrNode))
			bufferState = ptrNode->GetValue();
	}
	catch (Spinnaker::Exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
		emit statusUpdated(statusType::Warning, e.what());
	}
	return bufferState;
}

int FLIRChameleon::getBufferSize() {
	int bufferSize = 0;
	GenApi::INodeMap& nodeMapTLStream = m_pCam->GetTLStreamNodeMap();
	GenApi::CIntegerPtr ptrNode =
				nodeMapTLStream.GetNode("StreamBufferCountResult");
	try {
		if (IsAvailable(ptrNode))
			bufferSize = ptrNode->GetValue();
	}
	catch (Spinnaker::Exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
		emit statusUpdated(statusType::Warning, e.what());
	}
	return bufferSize;
}

QString FLIRChameleon::getDefaultUserSet() {
	try {
		bool deinit = false;
		if (!m_pCam->IsInitialized()) {
			m_pCam->Init();
			deinit = true;
		}
		GenApi::INodeMap& nodeMap = m_pCam->GetNodeMap();
		GenApi::CEnumerationPtr ptrUserSetDefault =
					nodeMap.GetNode("UserSetDefault");
		if (!IsAvailable(ptrUserSetDefault) || !IsReadable(ptrUserSetDefault)) {
				std::cout << "Unable to access User Set Default(enum retrieval). "
				"Aborting..." << std::endl;
		}
		QString userSet = QString::fromStdString(
					ptrUserSetDefault->GetCurrentEntry()->GetSymbolic().c_str());
		if (deinit) {
			m_pCam->DeInit();
		}
		return userSet;
	}
	catch (Spinnaker::Exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
		emit statusUpdated(statusType::Warning, e.what());
		return "Default";
	}
}


bool FLIRChameleon::setDefaultUserSet(const QString& userSet) {
	try {
		bool deinit = false;
		if (!m_pCam->IsInitialized()) {
			m_pCam->Init();
			deinit = true;
		}
		GenApi::INodeMap& nodeMap = m_pCam->GetNodeMap();
		GenApi::CEnumerationPtr ptrUserSetSelector =
					nodeMap.GetNode("UserSetSelector");
		if (!IsAvailable(ptrUserSetSelector) || !IsWritable(ptrUserSetSelector)) {
				std::cout << "Unable to access User Set Selector (enum retrieval). "
				"Aborting..." << std::endl;
		}
		GenApi::CEnumEntryPtr ptrUserSet = ptrUserSetSelector->GetEntryByName(
					userSet.toStdString().c_str());
		if (!IsAvailable(ptrUserSet) || !IsReadable(ptrUserSet)) {
				std::cout << "Unable to access User Set (entry retrieval). "
				"Aborting..." << std::endl;
				return false;
		}
		GenApi::CEnumerationPtr ptrUserSetDefault =
					nodeMap.GetNode("UserSetDefault");
		if (!IsAvailable(ptrUserSetDefault) || !IsWritable(ptrUserSetDefault)) {
				std::cout << "Unable to access User Set Default(enum retrieval). "
				"Aborting..." << std::endl;
				return false;
		}
		ptrUserSetDefault->SetIntValue(ptrUserSet->GetValue());
		if (deinit) {
			m_pCam->DeInit();
		}
		return true;
	}
	catch (Spinnaker::Exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
		emit statusUpdated(statusType::Warning, e.what());
		return false;
	}
}

bool FLIRChameleon::saveUserSetToFile(const QString& userSet,
				const QString& path) {
	GenApi::INodeMap& nodeMapTLDevice = m_pCam->GetTLDeviceNodeMap();
	m_pCam->Init();
	if (m_pCam->FileSelector == NULL) {
			std::cout << "File selector not supported on device!";
			return false;
	}

	GenApi::NodeList_t selectorList;
	m_pCam->FileSelector.GetEntries(selectorList);

	for (unsigned int i = 0; i < selectorList.size(); i++) {
		GenApi::CEnumEntryPtr node = selectorList.at(i);
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

				if (m_pCam->FileAccessLength.GetValue() <
							m_pCam->FileAccessBuffer.GetLength()) {
						try {
								m_pCam->FileAccessLength.SetValue(
											m_pCam->FileAccessBuffer.GetLength());
						}
						catch (Spinnaker::Exception& e) {
								std::cout << "Unable to set FileAccessLength to "
								"FileAccessBuffer length : " << e.what() << std::endl;
						}
				}
				m_pCam->FileAccessOffset.SetValue(0);

				int64_t intermediateBufferSize = m_pCam->FileAccessLength.GetValue();
				int64_t iterations = (bytesToRead / intermediateBufferSize) +
							(bytesToRead % intermediateBufferSize == 0 ? 0 : 1);

				int64_t index = 0;
				int64_t totalSizeRead = 0;
				std::unique_ptr<unsigned char> dataBuffer(
								new unsigned char[static_cast<unsigned int>(bytesToRead)]);
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


bool FLIRChameleon::loadUserSetFromFile(const QString& userSet,
			const QString& path) {
	GenApi::INodeMap& nodeMapTLDevice = m_pCam->GetTLDeviceNodeMap();
	m_pCam->Init();
	GenApi::INodeMap& nodeMap = m_pCam->GetNodeMap();

	if (m_pCam->FileSelector == NULL) {
			std::cout << "File selector not supported on device!" << std::endl;
			return false;
	}

	GenApi::NodeList_t selectorList;
	m_pCam->FileSelector.GetEntries(selectorList);

	for (unsigned int i = 0; i < selectorList.size(); i++)
	{
			GenApi::CEnumEntryPtr node = selectorList.at(i);

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

					if (m_pCam->FileAccessLength.GetValue() <
								m_pCam->FileAccessBuffer.GetLength()) {
							try {
									m_pCam->FileAccessLength.SetValue(
												m_pCam->FileAccessBuffer.GetLength());
							}
							catch (Spinnaker::Exception& e) {
									std::cout << "Unable to set FileAccessLength to "
									"FileAccessBuffer length : " << e.what() << std::endl;
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
					int64_t writeIterations = (totalBytesToWrite /
								intermediateBufferSize) +
								(totalBytesToWrite % intermediateBufferSize == 0 ? 0 : 1);

					if (totalBytesToWrite == 0) {
							std::cout << "Empty Image. No data will be written to camera."
							<< std::endl;
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
											(intermediateBufferSize <= bytesLeftToWrite) ?
														intermediateBufferSize : bytesLeftToWrite));

							if (paddingRequired) {
									for (int j = 0; j < numPaddings; j++) {
											unsigned char* pTmpBuffer = tmpBuffer.get();
											pTmpBuffer[bytesLeftToWrite + j] = 255;
									}
							}

							// Update index for next write iteration
							index = index +
											(intermediateBufferSize <= bytesLeftToWrite ?
														intermediateBufferSize : bytesLeftToWrite);

							m_pCam->FileAccessBuffer.Set(tmpBuffer.get(), tmpBufferSize);

							if (intermediateBufferSize > bytesLeftToWrite) {
									// Update FileAccessLength node appropriately to prevent
									//garbage data outside the range of
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
      if (m_pCam->FileOperationStatus.GetValue() !=
						FileOperationStatus_Success) {
          std::cout << "Failed to open file for reading!" << std::endl;
          return false;
      }
  }
  catch (Spinnaker::Exception& e) {
      std::cout << "Unexpected exception : " << e.what() << std::endl;
			emit statusUpdated(statusType::Warning, e.what());
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

        if (m_pCam->FileOperationStatus.GetValue() !=
							FileOperationStatus_Success) {
            std::cout << "Failed to open file for writing!" << std::endl;
            return false;
        }
    }
    catch (Spinnaker::Exception& e)
    {
        std::cout << "Unexpected exception : " << e.what() << std::endl;
				emit statusUpdated(statusType::Warning, e.what());
        result = false;
    }
    return result;
}


bool FLIRChameleon::closeFile() {
  bool result = true;
  try {
      m_pCam->FileOperationSelector.SetValue(FileOperationSelector_Close);
      m_pCam->FileOperationExecute.Execute();

      if (m_pCam->FileOperationStatus.GetValue() !=
						FileOperationStatus_Success) {
          std::cout << "Failed to close file!" << std::endl;
          return false;
      }
  }
  catch (Spinnaker::Exception& e) {
      std::cout << "Unexpected exception : " << e.what() << std::endl;
			emit statusUpdated(statusType::Warning, e.what());
      result = false;
  }
}

bool FLIRChameleon::executeReadCommand() {
  bool result = true;
  try {
      m_pCam->FileOperationSelector.SetValue(FileOperationSelector_Read);
      m_pCam->FileOperationExecute.Execute();
      if (m_pCam->FileOperationStatus.GetValue() !=
						FileOperationStatus_Success) {
          std::cout << "Failed to read file!" << std::endl;
          return false;
      }
  }
  catch (Spinnaker::Exception& e) {
      std::cout << "Unexpected exception : " << e.what() << std::endl;
			emit statusUpdated(statusType::Warning, e.what());
      result = false;
  }
  return result;
}


bool FLIRChameleon::executeWriteCommand() {
    bool result = true;
    try {
        m_pCam->FileOperationSelector.SetValue(FileOperationSelector_Write);
        m_pCam->FileOperationExecute.Execute();
        if (m_pCam->FileOperationStatus.GetValue() !=
							FileOperationStatus_Success) {
            std::cout << "Failed to write to file!" << std::endl;
            return false;
        }
    }
    catch (Spinnaker::Exception& e)
    {
        std::cout << "Unexpected exception : " << e.what() << std::endl;
				emit statusUpdated(statusType::Warning, e.what());
        result = false;
    }
    return result;
}


bool FLIRChameleon::executeDeleteCommand() {
    bool result = true;
    try {
        m_pCam->FileOperationSelector.SetValue(FileOperationSelector_Delete);
        m_pCam->FileOperationExecute.Execute();

        if (m_pCam->FileOperationStatus.GetValue() !=
							FileOperationStatus_Success) {
            std::cout << "Failed to delete file!" << std::endl;
            return false;
        }
    }
    catch (Spinnaker::Exception& e) {
        std::cout << "Unexpected exception : " << e.what() << std::endl;
				emit statusUpdated(statusType::Warning, e.what());
        result = false;
    }
    return result;
}
