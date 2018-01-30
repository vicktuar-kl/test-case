#include "inventorycell.h"

InventoryCell::InventoryCell(int row, int col, int number,
							 Item* item, bool isSource/* = false*/,
							 QWidget* parent/* = nullptr*/)
	: QWidget(parent), m_Row(row), m_Col(col), m_Number(number),
	  m_isSource(isSource), m_Content(item) {
	view();
}

InventoryCell::InventoryCell(QWidget* parent) { }

void InventoryCell::startDrag() {
	QByteArray data;
	QDataStream dataStream(&data, QIODevice::WriteOnly);
	QMimeData* mimeData = new QMimeData;

	// TODO: передавать Item и количество
	dataStream << m_Content->picture() << m_Content->type() << m_Number;
	mimeData->setData("application/x-item", data);

	QDrag* drag = new QDrag(this);
	drag->setMimeData((mimeData));
	drag->setPixmap(*(m_Content->pixmap()));
	drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction);
}

/*virtual*/ void InventoryCell::mousePressEvent(QMouseEvent *event) /*override*/ {
	if (event->button() == Qt::LeftButton) {
		m_DragStart = event->pos();
	}
	QWidget::mousePressEvent(event);
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

void InventoryCell::view() {
	QHBoxLayout* layout = new QHBoxLayout;
	m_NumberText = new QLabel(m_Number > 0 ? QString::number(m_Number) : "");
	if (m_isSource)
		m_NumberText->hide();
	m_NumberText->setStyleSheet("color: black");

	layout->addWidget(m_Content);
	layout->addWidget(m_NumberText, 0, Qt::AlignBottom | Qt::AlignRight);
	setLayout(layout);
}

void InventoryCell::setNumber(int number) {
	m_Number = number;
}

int InventoryCell::number() const {
	return m_Number;
}

void InventoryCell::updateNumberText() {
	m_NumberText->setText(m_Number > 0 ? QString::number(m_Number) : "");
}
