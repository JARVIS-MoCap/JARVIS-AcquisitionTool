/*******************************************************************************
 * File:        main.cpp
 * Created:     23. October 2020
 * Author:      Timo Hueser
 * Contact:     timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#include "DarkStyle.hpp"
#include "camerainterface.hpp"
#include "flirconfigbackend.hpp"
#include "globals.hpp"
#include "mainwindow.hpp"
#include "triggerinterface.hpp"

#include <QApplication>
#include <QImage>
#include <QSettings>
#include <QSplashScreen>
#include <iostream>

Q_DECLARE_METATYPE(QList<int>)
Q_DECLARE_METATYPE(statusType)

#include <libusb-1.0/libusb.h>

static void print_devs(libusb_device **devs) {
    libusb_device *dev;
    int i = 0, j = 0;
    uint8_t path[8];

    while ((dev = devs[i++]) != NULL) {
        struct libusb_device_descriptor desc;
        int r = libusb_get_device_descriptor(dev, &desc);
        if (r < 0) {
            fprintf(stderr, "failed to get device descriptor");
            return;
        }

        printf("%04x:%04x (bus %d, device %d)", desc.idVendor, desc.idProduct,
               libusb_get_bus_number(dev), libusb_get_device_address(dev));

        libusb_device_handle *dev_handle;

        r = libusb_get_port_numbers(dev, path, sizeof(path));
        if (r > 0) {
            printf(" path: %d", path[0]);
            for (j = 1; j < r; j++)
                printf(".%d", path[j]);
        }
        printf("\n");
        int err = libusb_open(dev, &dev_handle);
        if (!err) {
            unsigned char manufacturer[200];
            libusb_get_string_descriptor_ascii(dev_handle, desc.iManufacturer,
                                               manufacturer, 200);
            printf("Manufacturer: %s \n", manufacturer);

            unsigned char name[200];
            libusb_get_string_descriptor_ascii(dev_handle, desc.iProduct,
                                               name, 200);
            printf("Name: %s \n", name);

            unsigned char serialNumber[200];
            libusb_get_string_descriptor_ascii(dev_handle, desc.iSerialNumber,
                                               serialNumber, 200);
            printf("SerialNumber: %s \n", serialNumber);
        }
        printf("\n");
    }
}

int main(int argc, char **argv) {
    libusb_device **devs;
    int r;
    ssize_t cnt;

    r = libusb_init(NULL);
    if (r < 0)
        return r;

    cnt = libusb_get_device_list(NULL, &devs);
    if (cnt < 0) {
        libusb_exit(NULL);
        return (int)cnt;
    }

    print_devs(devs);
    libusb_free_device_list(devs, 1);

    libusb_exit(NULL);

    qSetMessagePattern(QStringLiteral("%{time}"
                                      //"%{appname}"
                                      ": ["
                                      "%{if-debug}D%{endif}"
                                      "%{if-info}I%{endif}"
                                      "%{if-warning}W%{endif}"
                                      "%{if-critical}C%{endif}"
                                      "%{if-fatal}F%{endif}"
                                      "] "
                                      "%{message}"
                                      " ("
                                      "%{function} - %{file}:%{line}"
                                      ")"));

    QCoreApplication::setOrganizationName("Test");
    QCoreApplication::setOrganizationDomain("test");
    QCoreApplication::setApplicationName("Camera Controller");
    // qRegisterMetaTypeStreamOperators<QList<QString>>("QList<QString>");
    // qRegisterMetaTypeStreamOperators<QVector<QPoint>>("QVector<QPoint>");
    qRegisterMetaType<statusType>();
    QApplication app(argc, argv);
    app.setStyle(new DarkStyle);

    QStringList themeSearchPaths = {
        "/home/trackingsetup/Documents/AnnotationToolbox/IconThemes",
        "IconThemes", "../IconThemes",
        "/usr/local/share/JARVIS-AcquisitionTool/icons"};
    QIcon::setThemeSearchPaths(themeSearchPaths);
    QIcon::setThemeName("DarkIconTheme");

    // QPixmap pixmap("/home/trackingsetup/Pictures/Screenshot from 2021-04-21
    // 15-58-12.png");
    // QSplashScreen splash(pixmap);
    // splash.show();
    app.processEvents();
    // delayl(100);
    FlirConfigBackend::getInstance();

    MainWindow m_window;
    m_window.show();
    // splash.finish(&m_window);
    return app.exec();
}
