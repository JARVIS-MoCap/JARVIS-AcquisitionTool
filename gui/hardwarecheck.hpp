/*******************************************************************************
 * File:        hardwarecheck.hpp
 * Created:     23. October 2020
 * Author:      Timo Hueser
 * Contact:     timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#ifndef HADWARECHECK_H
#define HADWARECHECK_H

#include "globals.hpp"
#include <libusb-1.0/libusb.h>

#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QStandardItemModel>
#include <QTreeView>

class HardwareCheck : public QWidget {
    Q_OBJECT

  public:
    explicit HardwareCheck(QWidget *parent = nullptr);

  signals:

  public slots:

  private:
    typedef struct USBDevice {
        int busID;
        int deviceID;
        QString manufacturer;
        QString deviceName;
        int speed;
    } USBDevice;

    QTreeView *usbTree;
    QStandardItemModel *usbBusModel;
    QPushButton *runCheckButton;

    QList<QString> m_validManufacturers = {"FLIR"};
    QList<QString> m_speeds = {"Unknown",   "1.5MBit/s",  "12MBit/s",
                               "480MBit/s", "5000MBit/s", "10000MBit/s"};

    QList<QList<USBDevice>> createDeviceList();
    void updateUSBBusModel(QList<QList<USBDevice>> deviceList);

  private slots:
    void runCheckSlot();
};

#endif
