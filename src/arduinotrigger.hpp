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
    void createSettings();

  private slots:
    void intitialStatusSlot();
    void settingChangedSlot(const QString &name, QList<QString> subMenus,
                            SettingsNode::nodeType type, const QString &val,
                            bool update);
    void serialReadReadySlot();
};

#endif
