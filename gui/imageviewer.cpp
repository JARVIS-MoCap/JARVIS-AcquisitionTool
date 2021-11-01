/*******************************************************************************
 * File:			  imageviewer.cpp
 * Created: 	  23. October 2020
 * Author:		  Timo Hueser
 * Contact: 	  timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#include "imageviewer.hpp"

#include <QPainter>
#include <QMouseEvent>


void ImageViewer::scale(float s) {
	m_scale *= s;
	update();
}


void ImageViewer::fitToScreen(int imageWidth) {
	if (imageWidth == 0) {
		m_scale = static_cast<float>(this->size().width())/m_image.size().width();
	}
	else {
		m_scale = static_cast<float>(this->size().width())/imageWidth;
	}
	m_delta = QPoint(0,0);
	update();
}

void ImageViewer::setImage(const QImage &img) {
	int old_imageWidth = m_image.size().width();
	m_image = img;
	m_rect = m_image.rect();
	m_rect.translate(-m_rect.center());
	if (old_imageWidth != m_image.size().width()) {
		fitToScreen();
	}
	else {
		update();
	}
}


void ImageViewer::paintEvent(QPaintEvent *) {
	QPainter p{this};
	p.translate(rect().center());
	p.scale(m_scale, m_scale);
	p.translate(m_delta);
	//p.drawPixmap(m_rect.topLeft(), m_pixmap);
	p.drawImage(m_rect, m_image);

}


void ImageViewer::mousePressEvent(QMouseEvent *event) {
	if (event->button() == Qt::LeftButton) {
		m_moving = true;
		m_reference = event->pos();
		this->setCursor(Qt::ClosedHandCursor);
		setMouseTracking(true);
	}
}


void ImageViewer::mouseDoubleClickEvent(QMouseEvent *event) {
	if (event->button() == Qt::LeftButton) {
		fitToScreen();
		update();
	}
}


void ImageViewer::mouseMoveEvent(QMouseEvent *event) {
	if (m_moving) {
		m_delta += (event->pos() - m_reference) * 1.0/m_scale;
		m_reference = event->pos();
		update();
	}
}


void ImageViewer::mouseReleaseEvent(QMouseEvent *event) {
	if (event->button() == Qt::LeftButton) {
		this->setCursor(Qt::ArrowCursor);
		setMouseTracking(false);
		m_moving = false;
	}
}


void ImageViewer::wheelEvent(QWheelEvent *event) {
	double s = 800.0/(800.0-event->angleDelta().y());
	scale(s);
}
