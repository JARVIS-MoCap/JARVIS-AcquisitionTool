/*******************************************************************************
 * File:			  monitoringwindow.cpp
 * Created: 	  17. October 2021
 * Author:		  Timo Hueser
 * Contact: 	  timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#include "monitoringwindow.hpp"

#include <QLineEdit>
#include <QGroupBox>
#include <QFrame>


MonitoringWindow::MonitoringWindow(QWidget *parent) :
      QDockWidget(parent, Qt::Window){
	setMinimumSize(325,300);
	setWindowTitle("Performance");

  QFrame* mainWidget = new QFrame(this);
  mainWidget->setFrameShape(QFrame::NoFrame);
  QGridLayout *layout = new QGridLayout(mainWidget);
  setWidget(mainWidget);

	toolBar = new QToolBar(this);
	toolBar->setFixedHeight(40);
  toolBar->setIconSize(QSize(25,25));
	toolBar->setStyleSheet("QToolBar {background-color: palette(base);}");
	QLabel *settingsLabel = new QLabel("Performance Monitoring");
	settingsLabel->setFont(QFont("Sans Serif", 11, QFont::Bold));
	QWidget *spacer = new QWidget();
	spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  showGraphsButton = new QToolButton(this);
  showGraphsAction = new QAction(this);
  createToolBarButton(showGraphsButton, showGraphsAction,
        QIcon::fromTheme("show"), true, true, QSize(35,35));
  connect(showGraphsAction, &QAction::toggled,
          this, &MonitoringWindow::showGraphsSlot);
	toolBar->addWidget(settingsLabel);
	toolBar->addWidget(spacer);
  toolBar->addWidget(showGraphsButton);
	setTitleBarWidget(toolBar);

  QGroupBox *mainBox = new QGroupBox(mainWidget);
  mainBox->setStyleSheet(
        "QGroupBox{margin-top:0px; background-color:rgb(34, 36, 40)}");
  QScrollArea *mainScrollArea = new QScrollArea(mainBox);
  mainScrollArea->setObjectName("mainScrollArea");
  mainScrollArea->setFrameShape(QFrame::NoFrame);
  mainScrollArea->setWidgetResizable(true);
  QWidget *mainInnerWidget = new QWidget(mainScrollArea);
  mainInnerWidget->setObjectName("mainInnerWidget");
  mainInnerWidget->setStyleSheet(
        "QWidget#mainInnerWidget{background-color: rgba(0,0,0,0)}");
  mainScrollArea->setStyleSheet(
        "QScrollArea#mainScrollArea{background-color: rgba(0,0,0,0)}");

  mainlayout = new QGridLayout(mainInnerWidget);
  QGridLayout *mainouterlayout = new QGridLayout(mainBox);
  mainouterlayout->setMargin(0);
  mainouterlayout->addWidget(mainScrollArea,0,0);
  mainScrollArea->setWidget(mainInnerWidget);
	layout->addWidget(mainBox,0,0);
}


void MonitoringWindow::updateListSlot() {
	for (const auto & monitor : cameraMonitorMap) {
    delete monitor;
  }
  cameraMonitorMap.clear();
  int idx = 0;
  for (const auto & cam : CameraInterface::cameraList) {
    CameraMonitor * newMonitor = new CameraMonitor(cam);

    cameraMonitorMap[cam] = newMonitor;
    mainlayout->addWidget(newMonitor,idx++,0);
    connect(cam, &CameraInterface::latencyAndFrameNumberUpdate,
            newMonitor, &CameraMonitor::latencyAndFrameNumberUpdateSlot);
  }
  updateBufferStates();
}


void MonitoringWindow::updateBufferStates() {
  for (const auto & cam : CameraInterface::cameraList) {
    cameraMonitorMap[cam]->updateBufferState();
  }
}


void MonitoringWindow::showGraphsSlot(bool toggle) {
  	for (const auto & monitor : cameraMonitorMap) {
      monitor->toggleGraph(!toggle);
    }
}


CameraMonitor::CameraMonitor(CameraInterface * cam, QWidget *parent) :
      QGroupBox(parent), m_cam(cam) {
  setStyleSheet("QGroupBox{margin-top:0px; background-color:rgb(34, 36, 40)}");
  //setMinimumSize(150,240);
  QGridLayout *layout = new QGridLayout(this);
  QLabel *cameraNameLabel = new QLabel(m_cam->cameraName());
  cameraNameLabel->setFont(QFont("Sans Serif", 11, QFont::Bold));
  QLabel *bufferLabel = new QLabel("Buffer Usage:");
  bufferStatusBar = new QProgressBar(this);
  bufferStatusBar->setMinimum(0);
  bufferStatusBar->setAlignment(Qt::AlignCenter);
  bufferStatusBar->setTextVisible(false);
  bufferStatusBar->setMinimumSize(10,15);
  bufferStatusBar->setMaximumSize(9999,15);
  latencyChartView = new LatencyChartView();
  latencyChartView->hide();
  QWidget *bottomSpacer = new QWidget(this);
  bottomSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  layout->addWidget(cameraNameLabel,0,0,1,2);
  layout->addWidget(bufferLabel,1,0);
  layout->addWidget(bufferStatusBar,1,1);
  layout->addWidget(latencyChartView,3,0,1,2);
  layout->addWidget(bottomSpacer,4,0,1,2);
}


void CameraMonitor::latencyAndFrameNumberUpdateSlot(int latency,
      unsigned long frameNumber) {
  m_frameNumber = frameNumber;
  if (latencyChartView->isVisible()) {
    latencyChartView->update(latency);
    std::cout << "Updateing" << std::endl;
  }
  if (m_bufferUpdateCounter %10 == 0) {
      updateBufferState();
  }
  m_bufferUpdateCounter = (m_bufferUpdateCounter+1)%20;
}


void CameraMonitor::updateBufferState() {
  int bufferUsage = m_cam->getBufferUsage();
  int bufferSize = m_cam->getBufferSize();
  bufferStatusBar->setMaximum(bufferSize);
  bufferStatusBar->setValue(bufferUsage+1);
  if (bufferUsage*100/bufferSize < 50) {
    bufferStatusBar->setStyleSheet("QProgressBar {border-radius: 6px; "
          "background-color: rgb(24,24,24);} QProgressBar::chunk "
          "{border-radius: 6px; background-color: rgb(100,164,32);}");
  }
  else if (bufferUsage*100/bufferSize < 85) {
    bufferStatusBar->setStyleSheet("QProgressBar {border-radius: 6px; "
    "background-color: rgb(24,24,24);} QProgressBar::chunk "
    "{border-radius: 6px; background-color: rgb(187,109,39);}");
  }
  else {
    bufferStatusBar->setStyleSheet("QProgressBar {border-radius: 6px; "
    "background-color: rgb(24,24,24);} QProgressBar::chunk "
    "{border-radius: 6px; background-color: rgb(164,34,32);}");
  }
}

void CameraMonitor::toggleGraph(bool toggle) {
  if (!toggle) {
    latencyChartView->show();
  }
  else {
    latencyChartView->hide();
  }
}
