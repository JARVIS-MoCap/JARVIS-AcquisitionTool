/*******************************************************************************
 * File:        arduinotrigger.hpp
 * Created:     03. October 2021
 * Author:      Timo Hueser
 * Contact:     timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#ifndef ARDUINOTRIGGER_H
#define ARDUINOTRIGGER_H

#include "arduinoserialpeer.hpp"
#include "globals.hpp"
#include "serialinterface.hpp"
#include "triggerinterface.hpp"

#include <QQueue>
#include <QThread>
#include <QTreeWidget>

class ArduinoTriggerWorker : public QObject {
    Q_OBJECT
  public:
    ArduinoTriggerWorker(const QString &deviceName);
    ~ArduinoTriggerWorker();

  private:
    SerialInterface *serialInterface;
    SerialPeer *serialPeer;

  public slots:
    void sendSetupSlot(int m_cmdDelay, int m_frameRate, int m_frameLimit);

  private slots:
    void recvSlot();

  signals:
    void statusUpdated(statusType status, const QString &statusMessage);
};

class ArduinoTrigger : public TriggerInterface {
    Q_OBJECT
  public:
    explicit ArduinoTrigger(const QString &deviceName);
    ~ArduinoTrigger();

    void enable();
    void disable();
    void changeSimpleSetting(const QString &setting, const QString &value);

  private:
    QThread workerThread;
    ArduinoTriggerWorker *workerClass;
    void createSettings();

  private slots:
    void intitialStatusSlot();
    void settingChangedSlot(const QString &name, QList<QString> subMenus,
                            SettingsNode::nodeType type, const QString &val,
                            bool update);

  signals:
    void sendSetupSignal(int m_cmdDelay, int m_frameRate, int m_frameLimit);
};

#endif
