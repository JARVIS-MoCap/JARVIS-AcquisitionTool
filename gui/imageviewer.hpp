/*------------------------------------------------------------
 *  imageviewer.hpp
 *  Created: 23. October 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include "globals.hpp"

class ImageViewer : public QWidget {
	Q_OBJECT
	public:
		void scale(float s);
		void fitToScreen(int imageWidth = 0);
		void setSize(int w, int h) {m_size = QSize(w,h);}
		QSize sizeHint() const override {return m_size;}

	public slots:
	void setImage(const QImage & img);

	private:
		QPixmap m_pixmap;
		QImage m_image;
		QSize m_size;
		QRectF m_rect;
		QPointF m_reference;
		QPointF m_delta;
		float m_scale = 1.0;
		bool m_moving = false;
		void paintEvent(QPaintEvent *) override;
		void mousePressEvent(QMouseEvent *event);
		void mouseDoubleClickEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mouseReleaseEvent(QMouseEvent *);
		void wheelEvent(QWheelEvent *event);
};

#endif
