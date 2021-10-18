/*------------------------------------------------------------
 *  mainbar.hpp
 *  Created: 23. October 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#ifndef MAINBAR_H
#define MAINBAR_H

#include "globals.hpp"
#include "settingswindow.hpp"
#include "helpwindow.hpp"

#include <QLabel>
#include <QLineEdit>
#include <QToolBar>


class MainBar : public QToolBar {
	Q_OBJECT
	public:
		explicit MainBar(QWidget *parent = nullptr);

	private:
		SettingsWindow *settingsWindow;
		HelpWindow *helpWindow;
		QToolButton *settingsButton;
		QAction *settingsAction;
		QToolButton *helpButton;
		QAction *helpAction;

	private slots:
		void settingsClickedSlot();
		void helpClickedSlot();
};

#endif
