/*------------------------------------------------------------
 *  timestampwindow.hpp
 *  Created: 23. October 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#ifndef TIMESTAMPWINDOW_H
#define TIMESTAMPWINDOW_H

#include "globals.hpp"
#include "presetswindow.hpp"

#include <QDockWidget>
#include <QSplitter>
#include <QTextEdit>
#include <QPushButton>
#include <QListWidget>


class TimeStampWindow : public QDockWidget {
	Q_OBJECT
	public:
		explicit TimeStampWindow(QWidget *parent = nullptr);

	public slots:
		void recordingInfoFileCreatedSlot(QFile *file, QTime * recordingTime);
		void acquisitionStoppedSlot();

	signals:

	private:
		void resizeEvent(QResizeEvent *) override;

		QFile *m_recordingInfoFile = nullptr;
		QTime *m_recordingTime;
		QSettings *settings;
		PresetsWindow *loadPresetsWindow;
		PresetsWindow *savePresetsWindow;
		QList<QString> presets;
		QSplitter *mainSplitter;

		QToolBar *toolBar;
		QToolButton *savePresetButton;
		QAction *savePresetAction;
		QToolButton *loadPresetButton;
		QAction *loadPresetAction;
		QToolButton *closeButton;
		QAction *closeAction;

		QWidget *firstWidget;
		QGridLayout *firstlayout;
		QWidget *secondWidget;
		QGridLayout *secondlayout;

		QLineEdit *currentStampEdit;
		QPushButton *addButton;
		QTableWidget *timeStampTable;

		QWidget *labelSelectorWidget;
		QGridLayout *labelselectorlayout;
		QListWidget *labelSelectorList;
		QPushButton *moveLabelUpButton;
		QPushButton *moveLabelDownButton;
		QPushButton * addLabelButton;
		QPushButton  * deleteLabelButton;




	private slots:
		void addTimeStampSlot();
		void labelSelectedSlot(QListWidgetItem *item);
		void moveLabelUpSlot();
		void moveLabelDownSlot();
		void addLabelSlot();
		void removeLabelSlot();
		void savePresetsClickedSlot();
		void loadPresetsClickedSlot();
		void loadPresetSlot(const QString& preset);
		void savePresetSlot(const QString& preset);
		void closeClickedSlot();
};

#endif
