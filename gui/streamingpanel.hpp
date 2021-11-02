/*******************************************************************************
 * File:			  streamingpanel.hpp
 * Created: 	  23. October 2020
 * Author:		  Timo Hueser
 * Contact: 	  timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#ifndef STREAMINGPANEL_H
#define STREAMINGPANEL_H

#include "globals.hpp"
#include "imageviewer.hpp"
#include "camerainterface.hpp"

#include <QGridLayout>
#include <QLabel>
#include <QToolBar>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QFrame>


class StreamingPanel : public QWidget {
	Q_OBJECT
	
	public:
		explicit StreamingPanel(CameraInterface * camera = nullptr,
					QWidget *parent = nullptr);
		QLabel *camNameLabel;
		ImageViewer *imgViewer;
		QToolBar *toolBar;
		void setSize(int w, int h) {m_size = QSize(w,h);}
		QSize sizeHint() const override {return m_size;}
		void setCamera(CameraInterface * cam);

	signals:
		void closeClicked(CameraInterface* cam);

	private:
		CameraInterface *m_camera;
		QSize m_size;
		QToolButton *closeButton;
		QAction *closeAction;

	private slots:
		void closeClickedSlot();
};

#endif
