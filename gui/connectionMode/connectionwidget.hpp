/*------------------------------------------------------------
 *  connectinwidget.hpp
 *  Created: 23. October 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#ifndef CONNECTIONWIDGET_H
#define CONNECTIONWIDGET_H

#include "globals.hpp"
#include "presetswindow.hpp"
#include "camconnectionpanel.hpp"
#include "triggerconnectionpanel.hpp"

#include <QSettings>
#include <QSplitter>


class ConnectionWidget : public QWidget {
	Q_OBJECT
	public:
		explicit ConnectionWidget(QWidget *parent = 0);
		TriggerConnectionPanel *triggerPanel;

	signals:
		void camListChanged();
		void camAdded(CameraInterface *);
		void triggerInstanceChanged();
		void statusUpdated(CameraInterface *, statusType, QString);

	private:
		QSettings *settings;
		QSplitter *splitter;
		QList<QString> camPresets;
		QList<QString> triggerPresets;

		QWidget *camWidget;
		PresetsWindow *camLoadPresetsWindow;
		PresetsWindow *camSavePresetsWindow;
		QToolBar *camToolBar;
		QToolButton *camSavePresetButton;
		QAction *camSavePresetAction;
		QToolButton *camLoadPresetButton;
		QAction *camLoadPresetAction;
		QWidget *camPanelWidget;
		QGridLayout *campanellayout;
		CamConnectionPanel *camPanels[NUM_CAMS];

		QWidget *triggerWidget;
		PresetsWindow *triggerLoadPresetsWindow;
		PresetsWindow *triggerSavePresetsWindow;
		QToolBar *triggerToolBar;
		QToolButton *triggerSavePresetButton;
		QAction *triggerSavePresetAction;
		QToolButton *triggerLoadPresetButton;
		QAction *triggerLoadPresetAction;
		QWidget *triggerPanelWidget;
		QGridLayout *triggerpanellayout;

	private slots:
		void camListChangedSlot();
		void camAddedSlot(CameraInterface *);
		void triggerInstanceChangedSlot();
		void statusUpdatedSlot(CameraInterface *, statusType, QString);
		void camSavePresetsClickedSlot();
		void camLoadPresetsClickedSlot();
		void camLoadPresetSlot(QString);
		void camSavePresetSlot(QString);
		void triggerSavePresetsClickedSlot();
		void triggerLoadPresetsClickedSlot();
		void triggerLoadPresetSlot(QString);
		void triggerSavePresetSlot(QString);
};

#endif
