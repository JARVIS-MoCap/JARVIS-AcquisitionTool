/*------------------------------------------------------------
cudarecorder.hpp
 *  Created: 05. June 2020
 *  Author:   Timo Hüser
 *------------------------------------------------------------*/

#ifndef CUDARECORDER_H
#define CUDARECORDER_H


#include "globals.hpp"
#include "recordinginterface.hpp"
#include "cudajpegencoder.hpp"

class CudaRecorder : public RecordingInterface {
	Q_OBJECT
	public:
		explicit CudaRecorder(const QString& cameraName, const AcquisitionSpecs& acquisitionSpecs);
		~CudaRecorder();
		QPixmap recordFrame(uchar* frame);
	private:
		CudaJPEGEncoder * m_cudaJPEGEncoder;
};

#endif
