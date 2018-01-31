#include "inventorycell.h"

InventoryCell::InventoryCell(int row, int col, int number,
							 Item* item, bool isSource/* = false*/,
							 QWidget* parent/* = nullptr*/)
	: QWidget(parent), m_Row(row), m_Col(col), m_Number(number),
	  m_isSource(isSource), m_Content(item) {
	if (!m_isSource)
		setAcceptDrops(true);
}

InventoryCell::InventoryCell(bool isSource/* = false*/, QWidget* parent/* = nullptr*/)
	: QWidget(parent), m_Number(1), m_isSource(isSource) {
	if (!m_isSource)
		setAcceptDrops(true);
	else {
		m_Content = new Item("Apple", ":/apple.jpg");
	}
}

InventoryCell::InventoryCell(int row, int col, QWidget* parent/* = nullptr*/)
	: QWidget(parent), m_Row(row), m_Col(col), m_Number(0), m_isSource(false) {
	setAcceptDrops(true);
}

Item* InventoryCell::content() const {
	return m_Content;
}

void InventoryCell::setContent(Item* Content) {
	m_Content = Content;
}

void InventoryCell::actionWithItem() {
	m_Content->action();
	--m_Number;
	updateNumberText();
	if (m_Number == 0) {
		clearCell();
	}
}

void InventoryCell::setNumber(int number) {
	m_Number = number;
}

int InventoryCell::number() const {
	return m_Number;
}

/*virtual*/ void InventoryCell::mousePressEvent(QMouseEvent *event) /*override*/ {
	if (event->button() == Qt::LeftButton) {
		m_DragStart = event->pos();
	} else if (!m_isSource && event->button() == Qt::RightButton) {
		actionWithItem();
	}
	QWidget::mousePressEvent(event);
}

/*virtual*/ void InventoryCell::mouseMoveEvent(QMouseEvent *event) /*override*/ {
	if (event->buttons() & Qt::LeftButton) {
		int distance = (event->pos() - m_DragStart).manhattanLength();
		if (distance > QApplication::startDragDistance()) {
			QByteArray data;
			QDataStream dataStream(&data, QIODevice::WriteOnly);
			QMimeData* mimeData = new QMimeData;

			dataStream << m_Content->type() << m_Content->picture() << m_Number;
			mimeData->setData(m_Content->mimeType(), data);

			QDrag* drag = new QDrag(this);
			drag->setMimeData((mimeData));
			drag->setPixmap(*(m_Content->pixmap()));


			if (m_isSource)
				drag->exec(Qt::CopyAction);
			else {
				drag->exec(Qt::MoveAction);
				clearCell();
				m_Number = 0;
			}
		}
	}
	QWidget::mouseMoveEvent(event);
}

/*virtual*/ void InventoryCell::dragEnterEvent(QDragEnterEvent* event) /*override*/ {
	if (event->mimeData()->hasFormat(Item::mimeType())) {
		event->acceptProposedAction();
	}
}

/*virtual*/ void InventoryCell::dropEvent(QDropEvent* event) /*override*/ {
	if (event->mimeData()->hasFormat(Item::mimeType())) {
		QByteArray data = event->mimeData()->data(Item::mimeType());
		QDataStream dataStream(&data, QIODevice::ReadOnly);

		QString type, picture;
		int tempNumber;
		dataStream >> type >> picture >> tempNumber;
		Item* tempItem = new Item(type, picture);

		if (m_Number == 0) {
			m_Content = tempItem;
			m_Number += tempNumber;
			view();
		} else {
			m_Number += tempNumber;
			updateNumberText();
		}
	}
	emit selectInvCellSignal(m_Row, m_Col);
}

void InventoryCell::view() {
	QHBoxLayout* layout = new QHBoxLayout;
	layout->addWidget(m_Content);
	if (!m_isSource) {
		m_NumberText = new QLabel(QString::number(m_Number));
		m_NumberText->setStyleSheet("color: black");
		layout->addWidget(m_NumberText, 0, Qt::AlignBottom | Qt::AlignRight);
	}
	setLayout(layout);
}

void InventoryCell::clearCell() {
	delete m_NumberText;
	m_Content->setPixmap(QPixmap(""));
	m_Content->setPicture("");
	m_Content->setType("");
	//delete m_Content; // расскоментировать на Windows
	delete layout();
	m_Number = 0;
}

void InventoryCell::updateNumberText() {
	m_NumberText->setText(m_Number > 0 ? QString::number(m_Number) : "");
}
