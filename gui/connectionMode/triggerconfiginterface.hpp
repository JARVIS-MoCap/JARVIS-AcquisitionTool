/*******************************************************************************
 * File:        triggerconfiginterface.hpp
 * Created:     03. October 2021
 * Author:      Timo Hueser
 * Contact:     timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/

#ifndef TRIGGERCONFIGINTERFACE_H
#define TRIGGERCONFIGINTERFACE_H

#include "globals.hpp"
#include "triggerinterface.hpp"

#include <QGroupBox>
#include <QSettings>

class TriggerConfigInterface : public QWidget {
    Q_OBJECT

  public:
    explicit TriggerConfigInterface(QWidget *parent = 0) {}

    QGroupBox *configEditBox;
    QGroupBox *configInfoBox;

    virtual bool confirmConfigClicked() = 0;
    virtual void loadPreset(QSettings *settings) = 0;
    virtual void savePreset(QSettings *settings) = 0;
    virtual TriggerInterface *getTrigger() = 0;
};

#endif
