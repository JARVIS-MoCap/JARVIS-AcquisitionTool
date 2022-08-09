/*******************************************************************************
 * File:        cudajpegencoder.cpp
 * Created:     03. October 2021
 * Author:      Timo Hueser
 * Contact:     timo.hueser@gmail.com
 * Copyright:   2021 Timo Hueser
 * License:     LGPL v3.0
 ******************************************************************************/
#include "statuslogwindow.hpp"

#include <QHeaderView>

StatusLogWindow::StatusLogWindow(QWidget *parent)
    : QWidget(parent, Qt::Window) {
    resize(600, 400);
    setMinimumSize(600, 200);
    setWindowTitle("Status Logs");

    QGridLayout *layout = new QGridLayout(this);
    toolBar = new QToolBar(this);
    toolBar->setFixedHeight(45);
    toolBar->setMovable(false);
    discardButton = new QToolButton(toolBar);
    discardAction = new QAction(this);
    createToolBarButton(discardButton, discardAction,
                        QIcon::fromTheme("discard"), true, false,
                        QSize(40, 40));
    connect(discardAction, &QAction::triggered, this,
            &StatusLogWindow::discardClickedSlot);
    toolBar->addWidget(discardButton);

    statusLogsTable = new QTableWidget(0, 3);
    statusLogsTable->setAlternatingRowColors(true);
    QStringList labels;
    labels << "Status"
           << "Time"
           << "Message";
    statusLogsTable->setHorizontalHeaderLabels(labels);
    statusLogsTable->horizontalHeader()->setSectionResizeMode(
        2, QHeaderView::Stretch);
    statusLogsTable->verticalHeader()->hide();
    statusLogsTable->setShowGrid(false);
    statusLogsTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    layout->setMenuBar(toolBar);
    layout->addWidget(statusLogsTable, 0, 0);
    this->setLayout(layout);
}

void StatusLogWindow::updateListSlot() {
    statusLogsTable->setRowCount(statusLogList.size());
    int row = 0;
    for (const auto &status : statusLogList) {
        QTableWidgetItem *typeItem = new QTableWidgetItem();
        typeItem->setIcon(statusIcons[status.type]);
        typeItem->setFlags(typeItem->flags() ^ Qt::ItemIsEditable);
        statusLogsTable->setItem(row, 0, typeItem);
        QTableWidgetItem *timeItem = new QTableWidgetItem();
        timeItem->setText(status.time.toString());
        timeItem->setFlags(timeItem->flags() ^ Qt::ItemIsEditable);
        statusLogsTable->setItem(row, 1, timeItem);
        QTableWidgetItem *messageItem = new QTableWidgetItem();
        messageItem->setText(status.message);
        messageItem->setFlags(messageItem->flags() ^ Qt::ItemIsEditable);
        statusLogsTable->setItem(row, 2, messageItem);
        row++;
    }
}

void StatusLogWindow::discardClickedSlot() {
    statusLogList.clear();
    statusLogsTable->clearContents();
    statusLogsTable->setRowCount(0);
    emit logsCleared();
}
