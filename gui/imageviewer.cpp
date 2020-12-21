/*------------------------------------------------------------
 *  imageviewer.cpp
 *  Created:  10. July 2018
 *  Author:   Timo Hüser
 *
 *------------------------------------------------------------*/

#include "imageviewer.hpp"

#include <QPainter>
#include <QMouseEvent>

void ImageViewer::scale(float s) {
	m_scale *= s;
	update();
}


void ImageViewer::fitToScreen(int pixmapWidth) {
	m_scale = static_cast<float>(this->size().width())/pixmapWidth;
	m_delta = QPoint(0,0);
	update();
}


void ImageViewer::setPixmap(QPixmap pix) {
	m_pixmap = pix;
	m_rect = m_pixmap.rect();
	m_rect.translate(-m_rect.center());
	update();
}


void ImageViewer::paintEvent(QPaintEvent *) {
	QPainter p{this};
	p.translate(rect().center());
	p.scale(m_scale, m_scale);
	p.translate(m_delta);
	p.drawPixmap(m_rect.topLeft(), m_pixmap);
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
		fitToScreen(m_pixmap.size().width());
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
