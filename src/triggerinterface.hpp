/*******************************************************************************
 * File:        triggerinterface.hpp
 * Created:     23. October 2020
 * Author:      Timo Hueser
 * Contact:     timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#ifndef TRIGGERINTERFACE_H
#define TRIGGERINTERFACE_H

#include "globals.hpp"
#include "settingsnode.hpp"
#include "settingsobject.hpp"

#include <QTreeWidget>

class TriggerInterface : public QObject {
    Q_OBJECT

  public:
    static TriggerInterface *triggerInstance;
    enum TriggerType { testTrigger, arduinoTrigger };
    explicit TriggerInterface(TriggerType triggerType)
        : m_triggerType{triggerType} {}

    TriggerType triggerType() const { return m_triggerType; }
    SettingsObject *triggerSettings() const { return m_triggerSettings; }
    void setTriggerStatus(const statusType &status) {
        m_triggerStatus = status;
    }
    statusType triggerStatus() const { return m_triggerStatus; }
    int getFrameRate() const { return m_frameRate; }
    int getFrameLimit() const { return m_frameLimit; }
    int getCmdDelay() const { return m_cmdDelay; }
    virtual void enable() = 0;
    virtual void disable() = 0;
    virtual void pause(bool state) = 0;
    virtual void changeSimpleSetting(const QString &setting,
                                     const QString &value) = 0;

  signals:
    void statusUpdated(statusType status, const QString &statusMessage);

  protected:
    QSettings *settings = new QSettings();
    const TriggerType m_triggerType;
    RootNode *m_triggerSettingsRootNode;
    SettingsObject *m_triggerSettings;
    statusType m_triggerStatus = Connecting;
    uint8_t m_frameRate = 100;
    uint32_t m_frameLimit = 0;
    uint32_t m_cmdDelay = 0;

  private slots:
    void statusInitReady() { emit statusUpdated(Ready, ""); };
};

#endif
