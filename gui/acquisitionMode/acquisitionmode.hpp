/*------------------------------------------------------------
 *  acquisitionmode.hpp
 *  Created: 23. October 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#ifndef ACQUISITIONMODE_H
#define ACQUISITIONMODE_H

#include "globals.hpp"
#include "camerainterface.hpp"
#include "triggerinterface.hpp"
#include "controlbar.hpp"
#include "streamingwidget.hpp"
#include "settingswindow.hpp"
#include "camselectorwindow.hpp"
#include "timestampwindow.hpp"

#include <QMainWindow>

class AcquisitionMode : public QMainWindow {
	Q_OBJECT
	public:
		explicit AcquisitionMode(QMainWindow *parent = nullptr);

	public slots:
		void camSelectedSlot(CameraInterface * cam);
		void triggerInstanceChangedSlot();
		void openTimeStampWindowSlot();


	signals:
		void camListChanged();
		void camAdded(CameraInterface * cam);
		void statusUpdated(CameraInterface * cam, statusType status, const QString& message);

	private:
		CamSelectorWindow *camSelector;
		StreamingWidget *streamingWidget;
		ControlBar *controlBar;
		SettingsWindow *camSettingsWindow;
		SettingsWindow *triggerSettingsWindow;
		SettingsWindow *streamingSettingsWindow;
		TimeStampWindow *timeStampWindow;

	private slots:
		void loadCameraPresetSlot(settingsObject* activeSettings);
};


#endif
