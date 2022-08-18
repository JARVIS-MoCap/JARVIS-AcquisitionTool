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
#include <libusb.h>

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
        int vendorID;
        int speed;
    } USBDevice;

    QTreeView *usbTree;
    QStandardItemModel *usbBusModel;
    QPushButton *runCheckButton;

    QList<int> m_validVendorIDs = {7696};
    QList<QString> m_vendorNames = {"Flir"};
    QList<double> m_speeds = {0,   1.5,  12,
                               480, 5000, 10000};

    QList<QList<USBDevice>> createDeviceList();
    void updateUSBBusModel(QList<QList<USBDevice>> deviceList);
    void changeNamesRecursive(QStandardItem *parent);
    int traverseChildren(QStandardItem *parent);
    void updateSpeeds(QStandardItem *parent);

    private slots : 
      void runCheckSlot();
};

#endif
