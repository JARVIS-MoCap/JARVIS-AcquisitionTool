/*****************************************************************
 * File:			  triggerconnectionpanel.hpp
 * Created: 	  03. October 2021
 * Author:		  Timo Hueser
 * Contact: 	  timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     GPL v3.0
 *****************************************************************/

#ifndef TRIGGERCONNECTIONPANEL_H
#define TRIGGERCONNECTIONPANEL_H

#include "globals.hpp"
#include "statuslogwindow.hpp"
#include "triggerconfiginterface.hpp"

#include <QStackedWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>


class TriggerConnectionPanel : public QFrame {
	Q_OBJECT
public:
	explicit TriggerConnectionPanel(QWidget *parent = 0);
	~TriggerConnectionPanel();
	StatusLogWindow *statusLogWindow;
	QStackedWidget *stackWidget;
	TriggerConfigInterface *triggerConfigInterface;

	//ConfigureMode
	QLineEdit *triggerNameEdit;
	QComboBox *triggerTypeCombo;

	//InfoMode
	QWidget *triggerInfoWidget;
	QGridLayout *tiggerinfolayout;
	QLabel *triggerStatusInfoIcon;
	QLabel *triggerStatusInfo;
	QPushButton *triggerStatusButton;

	//Test Trigger
	QGroupBox *testBox;
	QLineEdit *example1Edit;
	QComboBox *example2Combo;
	QGroupBox *testInfoBox;
	QLineEdit *example1Info;
	QLineEdit *example2Info;


private:
	QGridLayout *triggerconfigurelayout;
	QGridLayout *triggerinfolayout;
	QWidget *configureBottomSpacer;
	QWidget *infoBottomSpacer;

	//AddMode
	QPushButton *addButton;

	//ConfigureMode
	QWidget *triggerConfigureContainer;
	QToolBar *configToolBar;
	QToolButton *confirmButton;
	QAction *confirmAction;
	QToolButton *exitButton;
	QAction *exitAction;
	QWidget *triggerConfigureWidget;

	//InfoMode
	QWidget *triggerInfoContainer;
	QToolBar *infoToolBar;
	QToolButton *deleteButton;
	QAction *deleteAction;

	void createTestBoxes();

signals:
	void triggerInstanceChanged();
	void triggerStatusUpdated(statusType, QString);

private slots:
	void addClickedSlot();
	void exitConfigClickedSlot();
	void confirmConfigClickedSlot();
	void deleteTriggerClickedSlot();
	void typeComboChangedSlot(QString);
	void statusUpdatedSlot(statusType, QString);
	void showLogClickedSlot();
	void logsClearedSlot();
};

#endif
