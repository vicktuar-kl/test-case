#include "inventorycell.h"

// конструктор по-умолчанию, вечный генератор яблок
InventoryCell::InventoryCell(bool isSource/* = true*/, QWidget* parent/* = nullptr*/)
	: QWidget(parent), m_Number(1), m_isSource(isSource) {
	if (!m_isSource)
		setAcceptDrops(true);
	else {
		m_Content = new Item("Apple");
	}
}

// конструктор для создания заполненной ячейки, в итоге не успел пригодится,
// но должен был служить для заполнения инвентаря из БД
InventoryCell::InventoryCell(int row, int col, int number,
							 Item* item, bool isSource/* = false*/,
							 QWidget* parent/* = nullptr*/)
	: QWidget(parent), m_Row(row), m_Col(col), m_Number(number),
	  m_isSource(isSource), m_Content(item) {
	if (!m_isSource)
		setAcceptDrops(true);
}

// для заполнения инвентаря пустыми ячейками, строки и столбцы -
// для внесения в БД местоположения ячейки вместе с её содержимым и его количеством
InventoryCell::InventoryCell(int row, int col, QWidget* parent/* = nullptr*/)
	: QWidget(parent), m_Row(row), m_Col(col), m_Number(0), m_isSource(false) {
	setAcceptDrops(true);
}

// слот для совершения действия над предметом в ячейке,
// количество предметов при действии уменьшается, если их нет, то ячейка очищается
void InventoryCell::actionWithItem() {
	m_Content->action();
	--m_Number;
	updateNumberText();
	if (m_Number == 0) {
		clearCell();
	}
}

// на зажатие левой кнопки - вычисление позиции m_DragStart, на правую - действия с предметом (поедание яблок)
/*virtual*/ void InventoryCell::mousePressEvent(QMouseEvent *event) /*override*/ {
	if (event->button() == Qt::LeftButton) {
		m_DragStart = event->pos();
	} else if (!m_isSource && event->button() == Qt::RightButton) {
		actionWithItem();
	}
	QWidget::mousePressEvent(event);
}

// обработка перетаскивания предмета из ячейки, из источника - копируем, из обычной ячейки - переносим
/*virtual*/ void InventoryCell::mouseMoveEvent(QMouseEvent *event) /*override*/ {
	if (event->buttons() & Qt::LeftButton) {
		int distance = (event->pos() - m_DragStart).manhattanLength();
		if (distance > QApplication::startDragDistance()) {
			QByteArray data;
			QDataStream dataStream(&data, QIODevice::WriteOnly);
			QMimeData* mimeData = new QMimeData;

			dataStream << m_Content->type() << m_Number;
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

// При входе в зону сброса предмета, проверяем mime-type, должен соответствовать специальному типу предмета
/*virtual*/ void InventoryCell::dragEnterEvent(QDragEnterEvent* event) /*override*/ {
	if (event->mimeData()->hasFormat(Item::mimeType())) {
		event->acceptProposedAction();
	}
}

// "Принятие" предмета ячейкой и его отображение вместе с количеством
/*virtual*/ void InventoryCell::dropEvent(QDropEvent* event) /*override*/ {
	if (event->mimeData()->hasFormat(Item::mimeType())) {
		QByteArray data = event->mimeData()->data(Item::mimeType());
		QDataStream dataStream(&data, QIODevice::ReadOnly);

		QString type;
		int tempNumber;
		dataStream >> type >> tempNumber;
		Item* tempItem = new Item(type);

		if (m_Number == 0) {
			m_Content = tempItem;
			m_Number += tempNumber;
			view();
		} else {
			m_Number += tempNumber;
			updateNumberText();
		}
	}
}


// компоновка виджета предмета и виджета отображения количества предметов, для источника нет надписи с количеством
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

// "Опустошение" ячейки от её содержимого и очистка компоновки
void InventoryCell::clearCell() {
	delete m_NumberText;
	delete m_Content;
	delete layout();
	m_Number = 0;
}

// Обновление виджета отображения количества элементов
void InventoryCell::updateNumberText() {
	m_NumberText->setText(QString::number(m_Number));
}
