/*------------------------------------------------------------
 *  calibrationbackend.hpp
 *  Created: 23 June 2020
 *  Author:  Timo Hüser
 *------------------------------------------------------------*/

#ifndef CALIBRATIONBACKEND_H
#define CALIBRATIONBACKEND_H

#include "globals.hpp"
#include "camerainterface.hpp"

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/calib3d.hpp>



class CalibrationWorker : public QObject {
		Q_OBJECT
	public:
		explicit CalibrationWorker(QList<QPixmap> *pixCue)
					: m_pixCue{pixCue} { }

	signals:
		void streamCheckerBoardImage(QPixmap,bool,QVector<QPoint>);

	public slots:
	  void process();
	private:
		QList<QPixmap> *m_pixCue;
};


class CalibrationBackend : public QObject {
	Q_OBJECT
	public:
		explicit CalibrationBackend(QObject *parent = nullptr);

		void calibrate();
		int numberIntrinsics() {return imagePointsIntrinsics.size();}

		std::vector<double> reproErrorsIntrinsics;
		std::vector< std::vector< cv::Point3f > > objectPointsIntrinsics;
		std::vector< std::vector< cv::Point2f > > imagePointsIntrinsics;

	public slots:
		void imageStreamSlot(QPixmap pix);
		void streamCheckerBoardImageSlot(QPixmap pix, bool patternfound, QVector<QPoint > corners);
		void clearDataSlot();

	signals:
		void process();
		void streamCheckerBoardImage(QPixmap pix);
		void counterChanged(int);
		void calibrationFinished();


	private:
		void checkBuffers();

		QThread workerThread;
		CalibrationWorker *m_worker;
		QList<QPixmap> *m_cue;
		CameraIntrinsics m_cameraIntrinsics;

		cv::Size patternsize;
		std::vector<cv::Point3f> objPattern;

	private slots:

};

#endif
