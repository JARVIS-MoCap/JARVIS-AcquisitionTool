/*******************************************************************************
 * File:			  streamingwidget.hpp
 * Created: 	  23. October 2020
 * Author:		  Timo Hueser
 * Contact: 	  timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#ifndef STREAMINGWIDGET_H
#define STREAMINGWIDGET_H

#include "globals.hpp"
#include "streamingpanel.hpp"
#include "camerainterface.hpp"

#include <QGridLayout>
#include <QLabel>
#include <QToolBar>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>


class StreamingWidget : public QWidget {
	Q_OBJECT
	public:
		explicit StreamingWidget(QWidget *parent = nullptr);
		enum layoutType {Default, OneBig, TwoBig, FourBig};

	public slots:
	 void updateStreamingPanelsSlot(StreamingWidget::layoutType layout);
	 void acquisitionStartedSlot();

	signals:
		void togglePanel(CameraInterface* cam, bool toggle);

	private:
		QGridLayout *layout;
		QWidget *bigWidget;
		QGridLayout *biglayout;
		layoutType m_panelLayout;
		QList<StreamingPanel*> streamingPanels;

		QPoint m_dragStartPosition;
		const int m_toolBarHeight = 25;
		float m_aspectRatio = 1280.0/1024.0;
		void setPanels(bool onlySizes = false);
		void setSinglePanel(StreamingPanel *panel, int row, int col, int r_span,
			int c_span, int width, int height, int minWidth, bool onlySizes,
			bool big = false);
		void configurePanels(int numPanels, int numBigPanels, float ratio,
					int minWidth, bool onlySizes);
		void calculateHeightWidth(int maxWidth, int maxHeight,
					int &width, int &height);
		void calculateEqualPanelSizes(int numPanels,int totalWidth,
					int totalHeight, int& width, int& height, int& bestConfig);
		void resizeEvent(QResizeEvent *) override {setPanels();}
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void createDrag(const QPoint &pos, QWidget *widget);
		void dragEnterEvent(QDragEnterEvent *event);
		void dropEvent(QDropEvent *event);

	private slots:
		void closePanelSlot(CameraInterface* cam);
};


#endif
