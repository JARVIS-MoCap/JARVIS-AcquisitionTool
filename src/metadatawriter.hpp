#ifndef METADATAWRITER_H
#define METADATAWRITER_H

#include "globals.hpp"
#include <QTextStream>

class MetaDataWriter : public QObject {
    Q_OBJECT

  public:
    MetaDataWriter();

    void newFile(QString filepath);
    void closeFile();

  public slots:
    void writeMetadataSlot(QString frame_camera_uid, QString frame_camera_name,
                           int frame_id, uint64_t frame_timestamp,
                           int frame_image_uid);

  signals:
  private:
    void writeHeader();

    QFile current_file;
    QTextStream current_file_out;
};

#endif
