/*------------------------------------------------------------
 *  StreamingWidget.cpp
 *  Created:  10. July 2018
 *  Author:   Timo Hüser
 *
 *------------------------------------------------------------*/

#include "streamingwidget.hpp"
#include "camselectorwindow.hpp"

#include <cmath>

#include <QMouseEvent>
#include <QApplication>

StreamingWidget::StreamingWidget(QWidget *parent) : QWidget(parent) {
	setAcceptDrops(true);
	layout = new QGridLayout(this);
	bigWidget = new QWidget(this);
	biglayout = new QGridLayout(bigWidget);
	layout->setSpacing(8);
	biglayout->setSpacing(8);
	biglayout->setMargin(0);
}

void StreamingWidget::acquisitionStartedSlot() {
	for (const auto& panel : streamingPanels) {
		panel->imgViewer->fitToScreen();
	}
}

void StreamingWidget::updateStreamingPanelsSlot(layoutType panelLayout) {
	m_panelLayout = panelLayout;
	delete layout;
	layout = new QGridLayout(this);
	layout->setSpacing(8);
	for (const auto& panel : streamingPanels) {
		delete panel;
	}
	streamingPanels.clear();
	for (const auto& cam : CameraInterface::cameraList) {
		if(CamSelectorWindow::camVisibilityMap[cam]) {
			StreamingPanel *newPanel = new StreamingPanel(cam);
			connect(newPanel, &StreamingPanel::closeClicked, this, &StreamingWidget::closePanelSlot);
			newPanel->camNameLabel->setText(cam->cameraName());
			streamingPanels.append(newPanel);
		}
	}
	setPanels();
}


void StreamingWidget::setPanels(bool onlySizes) {
	int margin = layout->margin();
	int totalWidth = this->size().width()-2*margin;
	int totalHeight = this->size().height()-2*margin;
	//std::cout << "Sizes: " << totalWidth+2*margin << ", " << totalHeight+2*margin << std::endl;
	int minWidths[] = {200,200,200,200,200,250,300,350,400,450,500,500};
	float oneBigRatios[] = {0,0,0.6,0.6,0.6,0.6,0.6,0.5,0.5,0.5,0.4,0.4};
	float twoBigRatios[] = {0,0,0,0,0.7,0.7,0.7,0.7,0.6,0.6,0.7,0.5,0.5};
	int numPanels = streamingPanels.size();
	if (numPanels == 0) return;
	if (m_panelLayout == Default) {
		configurePanels(numPanels,0,0,minWidths[numPanels-1], onlySizes);
	}
	else if (m_panelLayout == OneBig) {
		configurePanels(numPanels, 1,oneBigRatios[numPanels-1],minWidths[numPanels-1],onlySizes);
	}
	else if (m_panelLayout == TwoBig) {
		configurePanels(numPanels, 2,twoBigRatios[numPanels-1],minWidths[numPanels-1],onlySizes);
	}
	else if (m_panelLayout == FourBig) {
		configurePanels(numPanels, 4,twoBigRatios[numPanels-1],minWidths[numPanels-1],onlySizes);
	}
}


void StreamingWidget::setSinglePanel(StreamingPanel *panel, int row, int col, int r_span,
                                     int c_span,int width, int height, int minWidth,
                                     bool onlySizes, bool big) {
	if (!onlySizes) {
		if (big) biglayout->addWidget(panel,row,col,r_span, c_span, Qt::AlignCenter);
		else layout->addWidget(panel,row,col,r_span, c_span, Qt::AlignCenter);
	}
	else {
		if (big) panel = qobject_cast<StreamingPanel*>(biglayout->itemAtPosition(row,col)->widget());
		else panel = qobject_cast<StreamingPanel*>(layout->itemAtPosition(row,col)->widget());
	}
	panel->setMaximumSize(width, height);
	panel->setSize(width,height);
	panel->imgViewer->setSize(width,height-m_toolBarHeight);
	panel->imgViewer->setMaximumSize(width, height-m_toolBarHeight);
	panel->imgViewer->setMinimumSize(width, height-m_toolBarHeight);
	panel->imgViewer->fitToScreen();
	panel->imgViewer->setMinimumSize(minWidth,0);
}


void StreamingWidget::configurePanels(int numPanels, int numBigPanels, float ratio,
	                                    int minWidth, bool onlySizes) {
	int totalWidth = this->size().width()-2*layout->margin();
	int totalHeight = this->size().height()-2*layout->margin();
	int spacing = layout->spacing();
	int bigWidth, bigHeight;
	int maxBigWidth = totalWidth*ratio;
	int maxBigHeight = totalHeight;
	int bestConfig = 0, singleBigWidth, singleBigHeight;
	calculateEqualPanelSizes(numBigPanels, maxBigWidth, maxBigHeight, singleBigWidth,
				singleBigHeight, bestConfig);
	bigWidth = singleBigWidth*bestConfig;
	bigHeight = singleBigHeight*ceil(static_cast<float>(numBigPanels)/bestConfig);
	int rightPanelWidth = totalWidth-spacing-bigWidth;
	int rightPanelHeight = maxBigHeight;
	int bottomPanelWidth = totalWidth-spacing-rightPanelWidth;
	int bottomPanelHeight = totalHeight-spacing-bigHeight;
	int smallWidth = 0, smallHeight = 0;
	int bestNumPanelsRight,bestNumPanelsBottom, bestConfigRight, bestConfigBottom;
	for (int i = 0; i <= numPanels-numBigPanels; i++) {
		if (i == 0) bottomPanelWidth = totalWidth-spacing;
		else bottomPanelWidth = totalWidth-spacing-rightPanelWidth;
		int numPanelsRight = i;
		int numPanelsBottom = numPanels-numBigPanels-i;
		int rightWidth, rightHeight, bottomWidth, bottomHeight, configRight, configBottom ;
		calculateEqualPanelSizes(numPanelsRight, rightPanelWidth, rightPanelHeight,
					rightWidth, rightHeight, configRight);
		calculateEqualPanelSizes(numPanelsBottom, bottomPanelWidth, bottomPanelHeight,
					bottomWidth, bottomHeight, configBottom);
		if (std::min(rightWidth, bottomWidth) > smallWidth+20) {
			bestNumPanelsRight = numPanelsRight;
			bestNumPanelsBottom = numPanelsBottom;
			bestConfigRight = configRight;
			bestConfigBottom = configBottom;
			smallWidth = std::min(rightWidth, bottomWidth);
			smallHeight = std::min(rightHeight, bottomHeight);
			}
	}
	int spanHeightBig = std::max(static_cast<int>(ceil(static_cast<float>(bestNumPanelsRight)/bestConfigRight)-
				ceil(static_cast<float>(bestNumPanelsBottom)/bestConfigBottom)),1);

	for (int i = 0; i < bestNumPanelsRight; i++) {
		setSinglePanel(streamingPanels[i+numBigPanels],i/bestConfigRight,
					i%bestConfigRight+bestConfigBottom,1,1,smallWidth,smallHeight,150, onlySizes);
	}
	for (int i = 0; i < bestNumPanelsBottom; i++) {
		int colBottom = i/bestConfigBottom+spanHeightBig;
		setSinglePanel(streamingPanels[i+numBigPanels+bestNumPanelsRight],colBottom,
					i%bestConfigBottom,1,1,smallWidth,smallHeight,150, onlySizes);
	}
	if (numBigPanels != 0) {
		layout->addWidget(bigWidget, 0,0, spanHeightBig, bestConfigBottom ,Qt::AlignCenter);
		bigWidget->setMaximumSize(bigWidth, bigHeight);
	}
	for (int i = 0; i < numBigPanels; i++) {
		setSinglePanel(streamingPanels[i],i/bestConfig,i%bestConfig,1,1,singleBigWidth,
					singleBigHeight,150, onlySizes,true);
	}
	setMinimumSize(minWidth,0);
}


void StreamingWidget::calculateHeightWidth(int maxWidth, int maxHeight, int &width, int &height) {
	if ((maxHeight-m_toolBarHeight)*m_aspectRatio > maxWidth) {
		width = maxWidth;
		height = width/m_aspectRatio+m_toolBarHeight;
	}
	else {
		height = maxHeight;
		width =	(height-m_toolBarHeight)*m_aspectRatio;
	}
}

void StreamingWidget::calculateEqualPanelSizes(int numPanels,int totalWidth, int totalHeight,
	                                             int& width, int& height, int &bestConfig) {
	if (numPanels == 0) {
		width = 20000;	//random big number
		height = 20000;
		bestConfig = 1;
	}
	else {
		int spacing = layout->spacing();
		int maxHeight =0, maxWidth = 0;
		for (int i = 0; i < numPanels; i++) {
			int newMaxWidth = (totalWidth-i*spacing)/(i+1);
			int newMaxHeight = (totalHeight-(ceil(static_cast<float>(numPanels)/(i+1))-1)*spacing)/ceil(static_cast<float>(numPanels)/(i+1));
			if (std::min(newMaxWidth, static_cast<int>((newMaxHeight-m_toolBarHeight)*m_aspectRatio)) >
						std::min(maxWidth, static_cast<int>((maxHeight-m_toolBarHeight)*m_aspectRatio))) {
				maxWidth = newMaxWidth;
				maxHeight = newMaxHeight;
				bestConfig = i+1;
			}
		}
		calculateHeightWidth(maxWidth, maxHeight, width, height);
	}
}


void StreamingWidget::closePanelSlot(CameraInterface* cam) {
	emit togglePanel(cam, false);
}


void StreamingWidget::mousePressEvent(QMouseEvent *event) {
	if (event->button() == Qt::LeftButton)
	    m_dragStartPosition = event->pos();
}


void StreamingWidget::mouseMoveEvent(QMouseEvent *event) {
	if (!(event->buttons() & Qt::LeftButton)) return;
	if ((event->pos() - m_dragStartPosition).manhattanLength()
			< QApplication::startDragDistance()) return;
	QWidget *child = childAt(event->pos());
	QWidget *parent = nullptr;
	if (qobject_cast<QToolBar *>(child)) parent = child->parentWidget();
	else if (qobject_cast<QLabel *>(child) || (qobject_cast<QWidget *>(child) &&
				qobject_cast<QToolBar *>(child->parentWidget()))) parent = child->parentWidget()->parentWidget();
	if(qobject_cast<StreamingPanel *>(parent)) {
		createDrag(event->pos(), parent);
	}
}


void StreamingWidget::createDrag(const QPoint &pos, QWidget *widget){
	if(widget == Q_NULLPTR)
		return;
	QByteArray byteArray(reinterpret_cast<char*>(&widget),sizeof(QWidget*));
	QDrag *drag = new QDrag(this);
	QMimeData * mimeData = new QMimeData;
	mimeData->setData("Panel",byteArray);
	drag->setMimeData(mimeData);
	QPoint globalPos = mapToGlobal(pos);
	QPoint p = widget->mapFromGlobal(globalPos);
	drag->setHotSpot(p);
	drag->setPixmap(widget->grab());
	widget->hide();
	drag->exec(Qt::CopyAction | Qt::MoveAction);
}


void StreamingWidget::dragEnterEvent(QDragEnterEvent *event) {
	 if(event->mimeData()->hasFormat("Panel"))
		event->acceptProposedAction();
}


void StreamingWidget::dropEvent(QDropEvent *event){
	QByteArray byteArray = event->mimeData()->data("Panel");
	QWidget * widget = *reinterpret_cast<QWidget**>(byteArray.data());
	QWidget *current_child = childAt(event->pos());
	QWidget *parent = nullptr;
	if (qobject_cast<QToolBar *>(current_child) || qobject_cast<ImageViewer *>(current_child))
		parent = current_child->parentWidget();
	else if (qobject_cast<QLabel *>(current_child) || (qobject_cast<QWidget *>(current_child) &&
				qobject_cast<QToolBar *>(current_child->parentWidget()))) parent = current_child->parentWidget()->parentWidget();
	if(qobject_cast<StreamingPanel *>(parent)) {
		StreamingPanel *swap_widget;
		swap_widget = qobject_cast<StreamingPanel *>(parent);
		QGridLayout *oldlayout = layout;
		QGridLayout *newlayout = layout;
		if (widget->parent() == bigWidget) oldlayout = biglayout;
		if (swap_widget->parent() == bigWidget) newlayout = biglayout;
		if(widget!= swap_widget) {
			int index_old = oldlayout->indexOf(widget);
			int row_old, column_old, row_span_old, column_span_old;
			int row_new, column_new, row_span_new, column_span_new;
			oldlayout->getItemPosition(index_old, &row_old, &column_old, &row_span_old, &column_span_old);
			QWidget * item_old = (oldlayout->takeAt(index_old)->widget());
			int index_new = newlayout->indexOf(swap_widget);
			newlayout->getItemPosition(index_new, &row_new, &column_new, &row_span_new, &column_span_new);
			QWidget * item_new = newlayout->takeAt(index_new)->widget();
			newlayout->addWidget(item_old, row_new, column_new, row_span_new, column_span_new, Qt::AlignCenter);
			oldlayout->addWidget(item_new, row_old, column_old, row_span_old, column_span_old, Qt::AlignCenter);
		}
		event->acceptProposedAction();
	}
	widget->show();
	setPanels(true);
 }
