/*******************************************************************************
 * File:			  mainwindow.hpp
 * Created: 	  23. October 2020
 * Author:		  Timo Hueser
 * Contact: 	  timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "globals.hpp"
#include "acquisitionmode.hpp"
#include "connectionmode.hpp"
#include "mainbar.hpp"

class MainWindow : public QMainWindow {
	Q_OBJECT

	public:
		explicit MainWindow(QMainWindow *parent = nullptr);

	private:
		void closeEvent(QCloseEvent *event);
		MainBar *mainBar;
		QTabWidget *modesWidget;
		AcquisitionMode *acquisitionMode;
		ConnectionMode *connectionMode;
		QMainWindow *viewerMode;
};

#endif
