/*****************************************************************
 * File:			  loadflirpresetswindow.hpp
 * Created: 	  23. October 2020
 * Author:		  Timo Hueser
 * Contact: 	  timo.hueser@gmail.com
 * Copyright:  2021 Timo Hueser
 * License:    GPL v3.0
 *****************************************************************/

#ifndef LOADFLIRPRESETSWINDOW_H
#define LOADFLIRPRESETSWINDOW_H

#include "globals.hpp"
#include "loadcamerapresetsinterface.hpp"

#include <QToolButton>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>
#include <QGridLayout>
#include <QSettings>
#include <QToolBar>
#include <QDialog>



class LoadFlirPresetsWindow : public LoadCameraPresetsInterface {
	Q_OBJECT

	public:
		explicit LoadFlirPresetsWindow(QWidget *parent = nullptr);

	signals:
};

#endif
