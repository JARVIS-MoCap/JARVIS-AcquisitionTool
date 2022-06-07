#include "metadatawriter.hpp"
#include <iomanip>

MetaDataWriter::MetaDataWriter() {}

void MetaDataWriter::newFile(QString filepath) {
    if (current_file.isOpen()) {
        std::cout << "Error: already open file!" << std::endl;
        return;
    }
    current_file.setFileName(filepath);
    current_file.open(QIODevice::WriteOnly);

    if (current_file.isOpen()) {
        std::cout << "Could not create/open file: " << std::endl;
    }
    std::cout << "Metadata filepath: " << filepath.toStdString() << std::endl;

    current_file_out.setDevice(&current_file);

    writeHeader();
}
void MetaDataWriter::writeHeader() {
    current_file_out
        << "frame_camera_uid;frame_camera_name;frame_id;frame_timestamp"
        << "\n";
}

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
    if (!current_file.isWritable()) {
        std::cout << "Error: No open file! Skipping..." << std::endl;
        return;
    }
    current_file_out << frame_camera_uid << ";" << frame_camera_name << ";"
                     << frame_id << ";" << frame_timestamp << "\n";
}

void MetaDataWriter::closeFile() {
    current_file_out.flush();
    current_file.close();
}