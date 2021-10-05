/*****************************************************************
 * File:			  saveflirpresetswindow.hpp
 * Created: 	  23. October 2020
 * Author:		  Timo Hueser
 * Contact: 	  timo.hueser@gmail.com
 * Copyright:  2021 Timo Hueser
 * License:    GPL v3.0
 *****************************************************************/

#ifndef SAVEFLIRPRESETSWINDOW_H
#define SAVEFLIRPRESETSWINDOW_H

#include "globals.hpp"
#include "savecamerapresetsinterface.hpp"

#include <QToolButton>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>
#include <QGridLayout>
#include <QSettings>
#include <QToolBar>
#include <QDialog>



class SaveFlirPresetsWindow : public SaveCameraPresetsInterface {
	Q_OBJECT

	public:
		explicit SaveFlirPresetsWindow(QWidget *parent = nullptr);

	private:
		QPushButton *saveButton;
		QPushButton *closeButton;

		QListWidget *userSetList;

	signals:
};

#endif
