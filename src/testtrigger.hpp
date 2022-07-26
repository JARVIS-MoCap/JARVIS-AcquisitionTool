/*******************************************************************************
 * File:        testtrigger.hpp
 * Created:     05. June 2020
 * Author:      Timo Hueser
 * Contact:     timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#ifndef TESTTRIGGER_H
#define TESTTRIGGER_H

#include "globals.hpp"
#include "triggerinterface.hpp"

#include <QTreeWidget>

class TestTrigger : public TriggerInterface {
    Q_OBJECT

  public:
    explicit TestTrigger(const QString &example1 = "",
                         const QString &example2 = "");
    ~TestTrigger();
    void enable() {}
    void disable() {}
    void pause(bool state) {}
    void changeSimpleSetting(const QString &setting, const QString &value) {}

  private:
    void createSettings();

  private slots:
    void testStatusReadySlot();
    void testStatusWarningSlot();
    void testStatusErrorSlot();
};

#endif
