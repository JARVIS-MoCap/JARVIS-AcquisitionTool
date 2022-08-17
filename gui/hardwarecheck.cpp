/*******************************************************************************
 * File:        hardwarecheck.cpp
 * Created:     23. October 2020
 * Author:      Timo Hueser
 * Contact:     timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#include "hardwarecheck.hpp"

#define LIBUSB_DEBUG

HardwareCheck::HardwareCheck(QWidget *parent) : QWidget(parent) {
    QGridLayout *layout = new QGridLayout(this);

    usbTree = new QTreeView();
    usbTree->setStyleSheet(
        "QTreeView::branch:open:has-children:!has-siblings,QTreeView::branch:"
        "open:has-children:has-siblings{border-image:none;"
        "image:url(:/darkstyle/icon_branch_end.png);}");
    usbBusModel = new QStandardItemModel();
    QStandardItem *parentItem = usbBusModel->invisibleRootItem();
    for (int i = 0; i < 4; ++i) {
        QStandardItem *item = new QStandardItem(QString("item %0").arg(i));
        item->setSelectable(false);
        item->setBackground(QBrush(QColor(255, 0, 0)));
        parentItem->appendRow(item);
        parentItem = item;
        }
        usbTree->setModel(usbBusModel);

        runCheckButton = new QPushButton("Check System");
        runCheckButton->setMinimumSize(30, 30);
        connect(runCheckButton, &QPushButton::clicked, this,
                &HardwareCheck::runCheckSlot);

        layout->addWidget(usbTree, 0, 0);
        layout->addWidget(runCheckButton, 1, 0, Qt::AlignRight);
}

void HardwareCheck::runCheckSlot() {
    QList<QList<USBDevice>> deviceList = createDeviceList();

    for (auto &singleDeviceList : deviceList) {
        for (auto &device : singleDeviceList) {
            std::cout << device.busID << "." << device.deviceID << ": "
                      << m_speeds[device.speed].toStdString() << " ";
            if (device.deviceName != "") {
                std::cout << device.deviceName.toStdString() << std::endl;
            } else {
                std::cout << "--> ";
            }
        }
    }

    updateUSBBusModel(deviceList);
}

QList<QList<HardwareCheck::USBDevice>> HardwareCheck::createDeviceList() {
    libusb_device **devs;
    ssize_t cnt;
    libusb_context *ctx = NULL;
    libusb_init(&ctx);
    cnt = libusb_get_device_list(ctx, &devs);
    if (cnt < 0) {
        libusb_exit(ctx);
    }
    libusb_device *dev;
    int i = 0, j = 0;
    uint8_t path[8];

    QList<QList<USBDevice>> allDevices;
    while ((dev = devs[i++]) != NULL) {
        struct libusb_device_descriptor desc;
        libusb_get_device_descriptor(dev, &desc);
        libusb_device_handle *dev_handle;
        int err = libusb_open(dev, &dev_handle);
        qDebug() << desc.idVendor;

        qDebug() << libusb_get_bus_number(dev) << libusb_get_port_number(dev)
                 << m_speeds[libusb_get_device_speed(dev)];

        if (m_validManufacturers.contains(desc.idVendor)) {
            unsigned char manufacturer_c[200];
            unsigned char name_c[200];
            if (!err) {
                libusb_get_string_descriptor_ascii(dev_handle, desc.idProduct,
                                                   manufacturer_c, 200);

                libusb_get_string_descriptor_ascii(dev_handle, desc.iProduct,
                                                   name_c, 200);
            }
            QString manufacturer =
                QString::fromUtf8((char *)manufacturer_c, -1);
            USBDevice camera;
                
            camera.deviceName = QString::fromUtf8((char *)name_c, -1);
            camera.manufacturer = manufacturer;
            camera.speed = libusb_get_device_speed(dev);
            camera.busID = libusb_get_bus_number(dev);
            camera.deviceID = libusb_get_device_address(dev);
            QList<USBDevice> deviceList = {camera};

            libusb_device *parent = dev;
            while (libusb_get_parent(parent) != NULL) {
                parent = libusb_get_parent(parent);
                USBDevice hub;
                hub.speed = libusb_get_device_speed(parent);
                hub.busID = libusb_get_bus_number(parent);
                hub.deviceID = libusb_get_device_address(parent);
                deviceList.prepend(hub);
            }
            allDevices.append(deviceList);
        }
    }
    libusb_free_device_list(devs, 1);
    libusb_exit(ctx);
    return allDevices;
}

void HardwareCheck::updateUSBBusModel(QList<QList<USBDevice>> deviceList) {
    usbBusModel->clear();
    for (const auto & singleDeviceList : deviceList) {
        QStandardItem *parentItem = usbBusModel->invisibleRootItem();
        for (const auto &device : singleDeviceList) {
            if (usbBusModel->findItems("Bus " + QString::number(device.busID) + ", Device " + QString::number(device.deviceID), Qt::MatchRecursive).size() == 0) {
                QStandardItem *item = new QStandardItem(
                    "Bus " + QString::number(device.busID) + ", Device " +
                    QString::number(device.deviceID));
                item->setSelectable(false);
                //item->setBackground(QBrush(QColor(255, 0, 0)));
                QStandardItem *speedItem = new QStandardItem(m_speeds[device.speed]);
                speedItem->setSelectable(false);
                //speedItem->setBackground(QBrush(QColor(255, 0, 0)));
                parentItem->appendRow({item, speedItem});
                parentItem = item;
            }
            else {
                parentItem = usbBusModel->findItems(
                    "Bus " + QString::number(device.busID) + ", Device " +
                        QString::number(device.deviceID),
                    Qt::MatchRecursive)[0];
            }
        }
    }
    usbTree->expandAll();
    usbTree->resizeColumnToContents(0);
}