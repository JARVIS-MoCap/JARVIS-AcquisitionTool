/*------------------------------------------------------------
 *  controlbar.hpp
 *  Created: 23. October 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#ifndef CONTROLBAR_H
#define CONTROLBAR_H

#include "globals.hpp"
#include "streamingwidget.hpp"
#include "camerainterface.hpp"
#include "triggerinterface.hpp"

#include <QLabel>
#include <QLineEdit>
#include <QToolBar>


class ControlBar : public QToolBar {
	Q_OBJECT
	public:
		explicit ControlBar(QWidget *parent = nullptr);

	public slots:
		void updateListSlot();
		void camAddedSlot(CameraInterface *cam);
		void camVisibilityToggledSlot(CameraInterface * cam, bool toggled);

	signals:
		void startAcquisition(AcquisitionSpecs);
		void stopAcquisition();
		void updateStreamingPanels(StreamingWidget::layoutType);
		void openTimeStampWindow();
		void recordingInfoFileCreated(QFile *file, QTime *time);
		void acquisitionStarted(int width);

	private:
		//SerialInterface *serialInterface;
		QFile *m_recordingInfoFile;
		QSettings *settings;
		QDir saveFileDir;
		QToolButton *recordButton;
		QAction *recordAction;
		QToolButton *startButton;
		QAction *startAction;
		QToolButton *stopButton;
		QAction *stopAction;
		QToolButton *pauseButton;
		QAction *pauseAction;
		QLabel *recordingTimeLabel;
		QTimer *recordingTimer;
		QTime *recordingTime;
		QTime *startTime;
		QLineEdit *recordingNameEdit;
		QToolButton *saveFolderButton;
		QAction *saveFolderAction;
		QToolButton *timeStampButton;
		QAction *timeStampAction;

		StreamingWidget::layoutType m_activeLayout;
		QMap<QString, QIcon> iconList;
		QToolButton *defaultButton;
		QAction *defaultAction;
		QAction *defaultVisAction;
		QToolButton *oneBigButton;
		QAction *oneBigAction;
		QAction *oneBigVisAction;
		QToolButton *twoBigButton;
		QAction *twoBigAction;
		QAction *twoBigVisAction;
		QToolButton *fourBigButton;
		QAction *fourBigAction;
		QAction *fourBigVisAction;

	private slots:
		void recordClickedSlot(bool toggled);
		void startClickedSlot(bool toggled);
		void pauseClickedSlot(bool toggled);
		void stopClickedSlot();
		void recordingTimerSlot();
		void saveFolderClickedSlot();
		void defaultLayoutSlot();
		void oneBigLayoutSlot();
		void twoBigLayoutSlot();
		void fourBigLayoutSlot();
};

#endif
