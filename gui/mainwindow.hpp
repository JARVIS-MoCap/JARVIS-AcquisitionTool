/*------------------------------------------------------------
 *  mainwindow.hpp
 *  Created: 23. October 2020
 *  Author:  Timo Hüser
 *------------------------------------------------------------*/

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
