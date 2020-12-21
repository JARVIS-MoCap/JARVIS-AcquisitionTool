/*------------------------------------------------------------
 *  camconnectionpanel.hpp
 *  Created: 23. October 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#ifndef CAMCONNECTIONPANEL_H
#define CAMCONNECTIONPANEL_H

#include "globals.hpp"
#include "statuslogwindow.hpp"
#include "camerainterface.hpp"

#include <QStackedWidget>
#include <QGroupBox>
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

	//ConfigureMode
	QLineEdit *camNameEdit;
	QComboBox *camTypeCombo;

	//InfoMode
	QWidget *camInfoWidget;
	QGridLayout *caminfolayout;
	QLineEdit *infoToolBarLabel;
	QLabel *camStatusInfoIcon;
	QLabel *camStatusInfo;
	QPushButton *camStatusButton;

	//Flir Chameleon
	QGroupBox *flirBox;
	QLineEdit *camIDEdit;
	QGroupBox *flirInfoBox;
	QLineEdit *camIDInfo;

	//Test Camera
	QGroupBox *testBox;
	QLineEdit *example1Edit;
	QComboBox *example2Combo;
	QGroupBox *testInfoBox;
	QLineEdit *example1Info;
	QLineEdit *example2Info;


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

	//InfoMode
	QWidget *camInfoContainer;
	QToolBar *infoToolBar;
	QToolButton *deleteButton;
	QAction *deleteAction;

	void createFlirBoxes();
	void createTestBoxes();
	void toggleItemsDisplayed(QList<QWidget*>, bool);

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
