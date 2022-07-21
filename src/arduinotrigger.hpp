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

class ReceiveWorker : public QThread {
    Q_OBJECT
  public:
    ReceiveWorker(SerialPeer *m_serialPeer, SerialInterface *serialInterface);
    ~ReceiveWorker();

  public:
    void run() override;

  private:
    SerialPeer *m_serialPeer;
    SerialInterface *m_serialInterface;
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
    SerialInterface *serialInterface;
    SerialPeer *serialPeer;
    ReceiveWorker *receiveWorker;
    void createSettings();

  private slots:
    void intitialStatusSlot();
    void settingChangedSlot(const QString &name, QList<QString> subMenus,
                            SettingsNode::nodeType type, const QString &val,
                            bool update);
};

#endif
