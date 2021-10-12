/*------------------------------------------------------------
 *  streamingpanel.cpp
 *  Created:  10. July 2018
 *  Author:   Timo Hüser
 *
 *------------------------------------------------------------*/

#include "streamingpanel.hpp"


StreamingPanel::StreamingPanel(CameraInterface * camera, QWidget *parent)
			: QWidget(parent), m_camera{camera} {
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QSizePolicy spRetain = this->sizePolicy();
	spRetain.setRetainSizeWhenHidden(true);
	this->setSizePolicy(spRetain);
	QGridLayout *layout = new QGridLayout(this);
	toolBar = new QToolBar(this);
	toolBar->setFixedHeight(25);
	toolBar->setIconSize(QSize(16,16));
	toolBar->setStyleSheet("QToolBar {background-color: palette(base);}");
	camNameLabel = new QLabel("Camera",this);
	camNameLabel->setFont(QFont("Sans Serif", 11, QFont::Bold));
	QWidget *spacer = new QWidget();
	spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	closeButton = new QToolButton(this);
	closeAction = new QAction(this);
	createToolBarButton(closeButton, closeAction, QIcon::fromTheme("discard"), true,
				false, QSize(22,22));
	connect(closeAction, &QAction::triggered, this, &StreamingPanel::closeClickedSlot);
	toolBar->addWidget(camNameLabel);
	toolBar->addWidget(spacer);
	toolBar->addWidget(closeButton);

	imgViewer = new ImageViewer();
	imgViewer->setImage(QImage("icons/hand_hires"));
	layout->addWidget(toolBar,0,0);
	layout->addWidget(imgViewer,1,0);
	layout->setSpacing(0);
	layout->setMargin(0);


	//--- SIGNAL-SLOT Connections ---//
	//-> Incoming Signals

	//<- Outgoing Signals

	//<-> Relayed Signals
	if (m_camera != nullptr) {
		connect(m_camera, &CameraInterface::streamImage, imgViewer, &ImageViewer::setImage);
	}
}


void StreamingPanel::setCamera(CameraInterface * cam) {
	if (cam != nullptr) {
		camNameLabel->setText(cam->cameraName());
	}
}

void StreamingPanel::closeClickedSlot() {
	emit closeClicked(m_camera);
}
