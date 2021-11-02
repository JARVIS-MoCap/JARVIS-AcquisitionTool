/*******************************************************************************
 * File:			  camselectorwindow.cpp
 * Created: 	  23. October 2020
 * Author:		  Timo Hueser
 * Contact: 	  timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#include "camselectorwindow.hpp"

#include <QLabel>
#include <QHeaderView>

QMap<CameraInterface*, bool> CamSelectorWindow::camVisibilityMap;


CamSelectorWindow::CamSelectorWindow(QWidget *parent) :
			QDockWidget(parent, Qt::Window) {
	this->setMinimumSize(300,100);
	this->setWindowTitle("Cameras");
	mainWidget = new QWidget();
	this->setWidget(mainWidget);
	QGridLayout *layout = new QGridLayout(mainWidget);

	toolBar = new QToolBar(this);
	toolBar->setFixedHeight(40);
	toolBar->setIconSize(QSize(25,25));
	toolBar->setStyleSheet("QToolBar {background-color: palette(base);}");
	QLabel *toolBarLabel = new QLabel("Cameras");
	toolBarLabel->setFont(QFont("Sans Serif", 11, QFont::Bold));
	QWidget *spacer = new QWidget();
	spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	toolBar->addWidget(toolBarLabel);
	toolBar->addWidget(spacer);
	this->setTitleBarWidget(toolBar);

	camsTable = new QTableWidget(0, 1);
	camsTable->setAlternatingRowColors(true);
	QStringList labels;
	labels << "Name";
	camsTable->setHorizontalHeaderLabels(labels);
	camsTable->horizontalHeader()-> setSectionResizeMode(0, QHeaderView::Stretch);
	camsTable->verticalHeader()->hide();
	camsTable->setShowGrid(false);
	camsTable->setSelectionBehavior(QAbstractItemView::SelectRows);

	connect(camsTable, &QTableWidget::cellDoubleClicked,
					this, &CamSelectorWindow::selectionChangedSlot);
	connect(camsTable, &QTableWidget::itemPressed,
					this, &CamSelectorWindow::tableItemPressed);
	connect(camsTable, &QTableWidget::itemClicked,
					this, &CamSelectorWindow::tableItemClicked);

	layout->addWidget(camsTable,0,0);
}


void CamSelectorWindow::updateListSlot() {
	m_camMap.clear();
	m_checkStateMap.clear();
	camsTable->setRowCount(CameraInterface::cameraList.size());
	int row = 0;
	for (const auto& cam : CameraInterface::cameraList) {
    QTableWidgetItem* nameItem = new QTableWidgetItem();
    nameItem->setText(cam->cameraName());
		nameItem->setFlags(nameItem->flags() ^ Qt::ItemIsEditable);
		nameItem->setCheckState(Qt::Checked);
		nameItem->setIcon(statusIcons[cam->cameraStatus()]);
		m_camMap[nameItem] = cam;
		m_checkStateMap[nameItem] = Qt::Checked;
    camsTable->setItem(row,0,nameItem);
		row++;
	}
	emit cameraSelected(nullptr);
}


void CamSelectorWindow::camVisibilityToggledSlot(CameraInterface* cam,
			bool toggle) {
	QTableWidgetItem *item = m_camMap.key(cam);
	if (toggle) {
		item->setCheckState(Qt::Checked);
		m_checkStateMap[item] = Qt::Checked;
	}
	else {
		item->setCheckState(Qt::Unchecked);
		m_checkStateMap[item] = Qt::Unchecked;
	}
}


void CamSelectorWindow::selectionChangedSlot(int row,int) {
	for (int i = 0; i < camsTable->rowCount(); i++) {
		if (i == row) camsTable->item(i,0)->setFont(
					QFont("Sans Serif", 11, QFont::Bold));
		else camsTable->item(i,0)->setFont(QFont("Sans Serif", 11));
	}
	emit cameraSelected(CameraInterface::cameraList[row]);
}

void CamSelectorWindow::statusUpdatedSlot(CameraInterface *cam,
			statusType status, const QString&) {
	camsTable->item(CameraInterface::cameraList.indexOf(cam),0)->setIcon(
				statusIcons[status]);
}


void CamSelectorWindow::tableItemPressed(QTableWidgetItem * item) {
    m_checkStateMap[item] = item->checkState();
}


void CamSelectorWindow::tableItemClicked(QTableWidgetItem * item) {
	if (m_checkStateMap[item] != item->checkState()) {
		emit camVisibilityToggled(m_camMap[item],
					item->checkState() == Qt::Checked);
    }
	m_checkStateMap[item] = item->checkState();
}
