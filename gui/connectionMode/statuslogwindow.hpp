/*------------------------------------------------------------
 *  statuslogwinwow.hpp
 *  Created: 23. October 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#ifndef STATUSLOGWINDOW_H
#define STATUSLOGWINDOW_H

#include "globals.hpp"

#include <QGridLayout>
#include <QToolBar>
#include <QTableWidget>

class StatusLogWindow : public QWidget {
	Q_OBJECT
public:
	explicit StatusLogWindow(QWidget *parent = 0);
	std::list<statusLog> statusLogList;

private:
	QToolBar *toolBar;
	QToolButton *discardButton;
	QAction *discardAction;
	QTableWidget *statusLogsTable;

signals:
	void logsCleared();

private slots:
	void discardClickedSlot();

public slots:
	void updateListSlot();
};


#endif
