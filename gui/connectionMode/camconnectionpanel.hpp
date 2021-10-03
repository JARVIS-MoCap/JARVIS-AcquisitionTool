/*****************************************************************
 * File:			  camconnectionpanelwidget.hpp
 * Created: 	  23. October 2020
 * Author:		  Timo Hueser
 * Contact: 	  timo.hueser@gmail.com
 * Copyright:  2021 Timo Hueser
 * License:    GPL v3.0
 *****************************************************************/

#ifndef CAMCONNECTIONPANEL_H
#define CAMCONNECTIONPANEL_H

#include "globals.hpp"
#include "statuslogwindow.hpp"
#include "camerainterface.hpp"
#include "camconfiginterface.hpp"

#include <QStackedWidget>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>


class CamConnectionPanel : public QFrame {
	Q_OBJECT
	public:
		explicit CamConnectionPanel(QWidget *parent = 0);
		~CamConnectionPanel();
		CameraInterface *camera = nullptr;
		StatusLogWindow *statusLogWindow;
		QStackedWidget *stackWidget;
		CamConfigInterface *camConfigInterface;
		//ConfigureMode
		QComboBox *camTypeCombo;
		//InfoMode
		QLineEdit *infoToolBarLabel;

private:
	//AddMode
	QPushButton *addButton;
	//ConfigureMode
	QWidget *camConfigureContainer;
	QToolBar *configToolBar;
	QToolButton *confirmButton;
	QAction *confirmAction;
	QToolButton *exitButton;
	QAction *exitAction;
	QWidget *camConfigureWidget;
	QGridLayout *camconfigurelayout;
	QLineEdit *camNameEdit;
	//InfoMode
	QWidget *camInfoContainer;
	QToolBar *infoToolBar;
	QToolButton *deleteButton;
	QAction *deleteAction;
	QWidget *camInfoWidget;
	QGridLayout *caminfolayout;
	QLabel *camStatusInfoIcon;
	QLabel *camStatusInfo;
	QPushButton *camStatusButton;

	signals:
		void camListChanged();
		void camAdded(CameraInterface *);
		void statusUpdated(CameraInterface*, statusType, QString);

	private slots:
		void addClickedSlot();
		void exitConfigClickedSlot();
		void confirmConfigClickedSlot();
		void deleteCamClickedSlot();
		void typeComboChangedSlot(QString);
		void nameEditedSlot();
		void statusUpdatedSlot(statusType, QString);
		void showLogClickedSlot();
		void logsClearedSlot();
		bool eventFilter(QObject*, QEvent*);
};

#endif
