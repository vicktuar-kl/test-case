#include "widgetmimedata.h"
#include "widgetdrag.h"
#include "inventorycell.h"

InventoryCell::InventoryCell(int row, int col, QWidget* parent /*= nullptr*/)
	: QWidget(parent), m_Row(row), m_Col(col), m_Quantity(0), m_Content(nullptr) {
	setAcceptDrops(true);
}

void InventoryCell::createFormInterior() {
	QHBoxLayout* cellLayout = new QHBoxLayout;
	m_labelQuantityItems = new QLabel("");

	cellLayout->addWidget(m_Content, 0, Qt::AlignCenter | Qt::AlignRight);
	cellLayout->addWidget(m_labelQuantityItems, 0, Qt::AlignBottom | Qt::AlignLeft);

	setLayout(cellLayout);
	updateLabel();
	m_labelQuantityItems->setStyleSheet("color: black");
}

void InventoryCell::startDrag() {
//	InventoryCell* draggedCell = new InventoryCell(0, 0);
//	draggedCell->setContent(new Item(m_Content->picture(), m_Content->type()));
//	draggedCell->setQuantity(m_Quantity);
	WidgetDrag* drag = new WidgetDrag(this);
	drag->setWidget(this);
	drag->exec();
	updateLabel();
}

/*virtual*/ void InventoryCell::mouseMoveEvent(QMouseEvent *event) /*override*/ {
	if (event->buttons() & Qt::LeftButton) {
		int distance = (event->pos() - m_DragStart).manhattanLength();
		if (distance > QApplication::startDragDistance()) {
			startDrag();
		}
	}
	QWidget::mouseMoveEvent(event);
}

/*virtual*/ void InventoryCell::mousePressEvent(QMouseEvent* event) /*override*/ {
	if (event->button() == Qt::RightButton) {
		--m_Quantity;
		if (m_Quantity == 0) {
			m_Content->eat();
			updateLabel();
		}
	} else if (event->button() == Qt::LeftButton) {
		m_DragStart = event->pos();
		qDebug() << "InventoryCell::mousePressEvent";
	}

	QWidget::mousePressEvent(event);
}

void InventoryCell::dragEnterEvent(QDragEnterEvent* event) {
	if (event->mimeData()->hasFormat(WidgetMimeData::mimeType())) {
		event->acceptProposedAction();
	}
	QWidget::dragEnterEvent(event);
}

void InventoryCell::dropEvent(QDropEvent* event) {
	const WidgetMimeData* md =
			dynamic_cast<const WidgetMimeData*>(event->mimeData());
	emit droppedItem(m_Row, m_Col);
//	Item* tempItem = dynamic_cast<Item*>(md->widget());
//	if (tempItem) {
//		qDebug() << "tempItem address: " << tempItem;
//		if (m_Quantity == 0) {
//			m_Content = new Item(tempItem->picture(), tempItem->type());
//			m_Content->setToCopy(false);
////				createFormInterior();
//			qDebug() << "m_Content address: " << m_Content;
//		}
//		incQuantity();
//	} else {
//		InventoryCell* tempCell = dynamic_cast<InventoryCell*>(md->widget());
//		m_Content =	tempCell->content();
//		m_Quantity += tempCell->quantity();
////			createFormInterior();
//	}
	InventoryCell* temp = dynamic_cast<InventoryCell*>(md->widget());
	if (isEmpty()) {
		setContent(temp->content());
		m_Content->setDragEnable(false);
		createFormInterior();
	}
	m_Quantity += temp->quantity();
	updateLabel();
}

void InventoryCell::updateLabel() {
	m_labelQuantityItems->setText(m_Quantity > 0 ? QString::number(m_Quantity) : "");
}

uint InventoryCell::quantity() const {
	return m_Quantity;
}

void InventoryCell::incQuantity() {
	++m_Quantity;
	updateLabel();
}

void InventoryCell::decQuantity() {
	--m_Quantity;
	updateLabel();
}

Item* InventoryCell::content() const {
	return m_Content;
}
void InventoryCell::setQuantity(const uint& quantity) {
	m_Quantity = quantity;
}

void InventoryCell::setContent(Item* content) {
	m_Content = content;
	m_Content->setPixmap(*content->pixmap());
}

bool InventoryCell::isEmpty() {
	if (m_Content)
		return false;
	else
		return true;
}
