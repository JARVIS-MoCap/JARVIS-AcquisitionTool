

#ifndef METADATAWRITER_H
#define METADATAWRITER_H

#include "globals.hpp"

class MetaDataWriter : public QObject {
    Q_OBJECT

  public:
    MetaDataWriter();

    void newFile(const char *filepath);

  public slots:
    void writeMetadata(const QString &frame_camera_name, uint64_t frame_id,
                       uint64_t frame_timestamp, uint64_t frame_image_uid);

  signals:
  private:
};

#endif
