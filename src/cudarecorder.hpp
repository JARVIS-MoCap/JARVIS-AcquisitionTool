/*******************************************************************************
 * File:        cudarecorder.hpp
 * Created:     05. June 2020
 * Author:      Timo Hueser
 * Contact:     timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#ifndef CUDARECORDER_H
#define CUDARECORDER_H

#include "cudajpegencoder.hpp"
#include "globals.hpp"
#include "recordinginterface.hpp"

class CudaRecorder : public RecordingInterface {
    Q_OBJECT

  public:
    explicit CudaRecorder(const QString &cameraName,
                          const AcquisitionSpecs &acquisitionSpecs);
    ~CudaRecorder();
    QImage recordFrame(uchar *frame);

  private:
    CudaJPEGEncoder *m_cudaJPEGEncoder;
};

#endif
