/*******************************************************************************
 * File:        hardwarecheck.cpp
 * Created:     23. October 2020
 * Author:      Timo Hueser
 * Contact:     timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#include "hardwarecheck.hpp"


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

    // for (auto &singleDeviceList : deviceList) {
    //     for (auto &device : singleDeviceList) {
    //         if (device.deviceName != "") {
    //             std::cout << device.deviceName.toStdString() << std::endl;
    //         } else {
    //             std::cout << "--> ";
    //         }
    //     }
    // }

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
        if (m_validVendorIDs.contains(desc.idVendor)) {
            USBDevice camera;
            camera.vendorID = desc.idVendor;
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
    int camera_counter = 0;
    usbBusModel->clear();
    for (const auto & singleDeviceList : deviceList) {
        QStandardItem *parentItem = usbBusModel->invisibleRootItem();
        for (const auto &device : singleDeviceList) {
            if (usbBusModel->findItems("USB Bus " + QString::number(device.busID) + ", Device " + QString::number(device.deviceID), Qt::MatchRecursive).size() == 0) {
                QStandardItem *item = new QStandardItem(
                    "USB Bus " + QString::number(device.busID) +
                    ", Device " + QString::number(device.deviceID));
                if (m_validVendorIDs.contains(device.vendorID)) {
                    item->setText(m_vendorNames[m_validVendorIDs.indexOf(
                                      device.vendorID)] + " Camera " +
                                  QString::number(camera_counter));
                    camera_counter++;
                } 
                item->setSelectable(false);
                item->setEditable(false);
                //item->setBackground(QBrush(QColor(255, 0, 0)));
                QStandardItem *speedItem = new QStandardItem();
                speedItem->setData(m_speeds[device.speed]);
                if (m_speeds[device.speed] != 0) {
                    speedItem->setData(QString::number(m_speeds[device.speed]) + " MBit/s", Qt::DisplayRole);
                }
                else {
                    speedItem->setData("Unknown", Qt::DisplayRole);
                }
                speedItem->setEditable(false);
                speedItem->setSelectable(false);
                QStandardItem *connectionsItem = new QStandardItem();
                connectionsItem->setEditable(false);
                connectionsItem->setSelectable(false);
                if (m_validVendorIDs.contains(device.vendorID)) {
                    connectionsItem->setData(1, Qt::DisplayRole);
                }
                else {
                    connectionsItem->setData(0, Qt::DisplayRole);
                }
                parentItem->appendRow({item, speedItem, connectionsItem});
                parentItem = item;
            }
            else {
                parentItem = usbBusModel->findItems(
                    "USB Bus " + QString::number(device.busID) + ", Device " +
                        QString::number(device.deviceID),
                    Qt::MatchRecursive)[0];
            }
        }
    }

    changeNamesRecursive(usbBusModel->invisibleRootItem());

    traverseChildren(usbBusModel->invisibleRootItem());

    updateSpeeds(usbBusModel->invisibleRootItem());

    usbTree->expandAll();
    usbTree->resizeColumnToContents(0);
    usbTree->resizeColumnToContents(1);
}

void HardwareCheck::changeNamesRecursive(QStandardItem *parent) {
    if (parent != usbBusModel->invisibleRootItem()) {
        QString name = parent->text();
        if (parent->parent() == nullptr) {
            parent->setText(name.split(",")[0]);
        }
        else if (name.contains("USB Bus")) {
            parent->setText("Hub");
        }
    }
    for (int row = 0; row < parent->rowCount(); row++) {
        changeNamesRecursive(parent->child(row,0));
    }
}


int HardwareCheck::traverseChildren(QStandardItem *parent) {
    int connections = 0;
    for (int row = 0; row < parent->rowCount(); row++) {
        QStandardItem *child = parent->child(row, 0);
        connections += traverseChildren(child);
    }
    if (parent != usbBusModel->invisibleRootItem()) {
        QStandardItem *parentParent = parent->parent();
        if (parentParent == nullptr) parentParent = usbBusModel->invisibleRootItem();
        connections +=
            parentParent->child(parent->row(), 2)->data(Qt::DisplayRole).toInt();
        int speed = parentParent->child(parent->row(), 1)
                        ->data().toInt();
        parentParent->child(parent->row(), 2)
            ->setData(speed / connections);
    }
    return connections;
}

void HardwareCheck::updateSpeeds(QStandardItem *parent) {
    for (int row = 0; row < parent->rowCount(); row++) {
        QStandardItem *child = parent->child(row, 0);
        updateSpeeds(child);
    }
    if (parent->text().contains("Camera")) {
        QStandardItem *item = parent;
        int minSpeed = 999999;
        while (item->parent() != nullptr) {
            QStandardItem *itemParent = item->parent();
            if (itemParent == nullptr)
                itemParent = usbBusModel->invisibleRootItem();
            int speed = itemParent->child(item->row(), 2)->data().toInt();
            minSpeed = std::min(minSpeed, speed);
            item = itemParent;
        }
        parent->parent()
            ->child(parent->row(), 2)
            ->setData(QString::number(minSpeed) + " MBit/s", Qt::DisplayRole);
    } else if (parent != usbBusModel->invisibleRootItem()) {
        QStandardItem *parentParent = parent->parent();
        if (parentParent == nullptr)
            parentParent = usbBusModel->invisibleRootItem();
        parentParent->child(parent->row(), 2)->setText("");
    }
}