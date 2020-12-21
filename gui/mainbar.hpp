/*------------------------------------------------------------
 *  mainbar.hpp
 *  Created: 23. October 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#ifndef MAINBAR_H
#define MAINBAR_H

#include "globals.hpp"

#include <QLabel>
#include <QLineEdit>
#include <QToolBar>

class MainBar : public QToolBar {
	Q_OBJECT
	public:
		explicit MainBar(QWidget *parent = nullptr);

	private:
		QToolButton *settingsButton;
		QAction *settingsAction;
};

#endif
