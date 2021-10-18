/*****************************************************************
	* File:			  helpwindow.cpp
	* Created: 	  08. August 2021
	* Author:		  Timo Hueser
	* Contact: 	  timo.hueser@gmail.com
	* Copyright:  2021 Timo Hueser
	* License:    GPL v3.0
	*****************************************************************/

#include "helpwindow.hpp"

#include <QGridLayout>
#include <QLineEdit>
#include <QFileDialog>
#include <QGroupBox>
#include <QDirIterator>
#include <QThread>
#include <QTextStream>



HelpWindow::HelpWindow(QWidget *parent) : QWidget(parent, Qt::Window) {
	this->resize(1100,800);
	this->setMinimumSize(600,400);
	QGridLayout *layout = new QGridLayout(this);
	mainSplitter = new QSplitter(this);
	layout->addWidget(mainSplitter,0,0);

	textBrowser = new QTextBrowser();

	tableOfContents = new QTreeWidget();
	tableOfContents->setColumnCount(1);
	tableOfContents->setHeaderLabel("Table of Contents");
	tableOfContents->setMaximumSize(300,100000);
	connect(tableOfContents, &QTreeWidget::itemClicked, this, &HelpWindow::itemSlectedSlot);

	QTreeWidgetItem *gettingStartedItem = new QTreeWidgetItem(tableOfContents,
																						QStringList(QString("Getting Started")));
	QTreeWidgetItem *introductionItem = new QTreeWidgetItem(gettingStartedItem,
																					QStringList(QString("Introduction")));
	QTreeWidgetItem *setupItem = new QTreeWidgetItem(gettingStartedItem,
																		 QStringList(QString("Building Your Setup")));
	QTreeWidgetItem *cameraConfigItem = new QTreeWidgetItem(gettingStartedItem,
																		 QStringList(QString("Configuring Your Cameras")));
	gettingStartedItem->addChild(introductionItem);
	gettingStartedItem->addChild(setupItem);
	gettingStartedItem->addChild(cameraConfigItem);
	QTreeWidgetItem *acquisitionItem = new QTreeWidgetItem(tableOfContents,
																				 QStringList(QString("Acquisition Mode")));
	QTreeWidgetItem *connectionItem = new QTreeWidgetItem(tableOfContents,
																									QStringList(QString("Connection Mode")));

	gettingStartedItem->setExpanded(true);

	tableOfContents->addTopLevelItem(gettingStartedItem);
	tableOfContents->addTopLevelItem(acquisitionItem);
	tableOfContents->addTopLevelItem(connectionItem);


	m_contentMap[introductionItem] = "../help/introduction.html";
	m_contentMap[setupItem] = "../help/setup.html";
	m_contentMap[cameraConfigItem] = "../help/cameraconfig.html";
	m_contentMap[acquisitionItem] = "../help/acquisitionmode.html";
	m_contentMap[connectionItem] = "../help/connectionmode.html";

	mainSplitter->addWidget(tableOfContents);
	mainSplitter->addWidget(textBrowser);

	setDocument(m_contentMap[introductionItem]);
}

void HelpWindow::itemSlectedSlot(QTreeWidgetItem *item, int column) {
	Q_UNUSED(column);
	auto it = m_contentMap.find(item);
	if (it != m_contentMap.end()) {
		setDocument(m_contentMap[item]);
	}
}


void HelpWindow::setDocument(const QString &path) {
	QTextDocument *doc = new QTextDocument();
	QString markdownFileName;
	markdownFileName = "../help/github-markdown.css";
	QFile f1(markdownFileName);
	f1.open(QFile::ReadOnly | QFile::Text);
	QTextStream in1(&f1);
	doc->setDefaultStyleSheet(in1.readAll());
	textBrowser->setDocument(doc);
	f1.close();

	QFile f(path);
	f.open(QFile::ReadOnly | QFile::Text);
	QTextStream in(&f);
	QString html = in.readAll();
	doc->setHtml(html);
	f.close();
}
