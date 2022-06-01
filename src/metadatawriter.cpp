#include "metadatawriter.hpp"
#include <iomanip>

MetaDataWriter::MetaDataWriter() {}

void MetaDataWriter::writeMetadata(const QString &frame_camera_name,
                                   uint64_t frame_id, uint64_t frame_timestamp,
                                   uint64_t frame_image_uid) {

    std::cout << "frame_camera_name: " << std::setw(10)
              << frame_camera_name.toStdString()
              << "; frame_id: " << std::setw(10) << frame_id
              << "; frame_timestamp: " << std::setw(20) << frame_timestamp
              << std::endl;
}