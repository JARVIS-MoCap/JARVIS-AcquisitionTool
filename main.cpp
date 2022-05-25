/*******************************************************************************
 * File:			  main.cpp
 * Created: 	  23. October 2020
 * Author:		  Timo Hueser
 * Contact: 	  timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#include "globals.hpp"
#include "DarkStyle.hpp"
#include "mainwindow.hpp"
#include "camerainterface.hpp"
#include "triggerinterface.hpp"
#include "flirconfigbackend.hpp"

#include <iostream>
#include <QApplication>
#include <QSplashScreen>
#include <QSettings>
#include <QImage>


Q_DECLARE_METATYPE(QList<int>)
Q_DECLARE_METATYPE(statusType)

int main(int argc, char **argv)
{
	QCoreApplication::setOrganizationName("Test");
	QCoreApplication::setOrganizationDomain("test");
	QCoreApplication::setApplicationName("Camera Controller");
	qRegisterMetaTypeStreamOperators<QList<QString> >("QList<QString>");
	qRegisterMetaTypeStreamOperators<QVector<QPoint> >("QVector<QPoint>");
	qRegisterMetaType<statusType>();
	QApplication app (argc, argv);
	app.setStyle(new DarkStyle);

	QStringList themeSearchPaths =
				{"/home/trackingsetup/Documents/AnnotationToolbox/IconThemes",
				"IconThemes", "../IconThemes", "/usr/local/share/JARVIS-AcquisitionTool/icons"};
	QIcon::setThemeSearchPaths(themeSearchPaths);
	QIcon::setThemeName("DarkIconTheme");

	//QPixmap pixmap("/home/trackingsetup/Pictures/Screenshot from 2021-04-21 15-58-12.png");
  //QSplashScreen splash(pixmap);
  //splash.show();
  app.processEvents();
	//delayl(100);
	FlirConfigBackend::getInstance();

	MainWindow m_window;
	m_window.show();
	//splash.finish(&m_window);
	return app.exec();
}
