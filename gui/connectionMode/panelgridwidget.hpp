/*------------------------------------------------------------
 *  panelgridwidget.hpp
 *  Created: 23. October 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#ifndef PANELGRIDWIDGET_H
#define PANELGRIDWIDGET_H

#include "globals.hpp"

#include <QSettings>


class PanelGridWidget : public QWidget {
	Q_OBJECT
	public:
		explicit PanelGridWidget(QWidget *parent = nullptr);

	signals:

	private:
		QSettings *settings;
		QList<QString> presets;

		QWidget *mainWidget;
		PresetsWindow *loadPresetsWindow;
		PresetsWindow *savePresetsWindow;
		QToolBar *toolBar;
		QToolButton *savePresetButton;
		QAction *savePresetAction;
		QToolButton *loadPresetButton;
		QAction *loadPresetAction;
		QWidget *panelWidget;
		QGridLayout *panellayout;
		CamConnectionPanel *panels[NUM_CAMS];

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
