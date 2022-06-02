#include "metadatawriter.hpp"
#include <iomanip>

MetaDataWriter::MetaDataWriter() {}

void MetaDataWriter::writeMetadataSlot(QString frame_camera_uid,
                                       QString frame_camera_name, int frame_id,
                                       uint64_t frame_timestamp,
                                       int frame_image_uid) {
    std::cout << "frame_camera_uid: " << std::setw(35)
              << frame_camera_uid.toStdString() << "; "
              << "frame_camera_name: " << std::setw(10)
              << frame_camera_name.toStdString() << "; "
              << "frame_id: " << std::setw(10) << frame_id << "; "
              << "frame_timestamp: " << std::setw(20) << frame_timestamp
              << std::endl;
}
