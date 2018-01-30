#include <QtWidgets>
#include "widgetdrag.h"
#include "item.h"
#include "inventorycell.h"

Item::Item(QString picture, QString type/* = ""*/, QWidget *parent/* = nullptr*/)
	: m_Type(type), m_Picture(picture), m_dragEnable(true), QLabel(parent) {
	qDebug() << "Create Item";
	m_Player = new QMediaPlayer;
	m_Playlist = new QMediaPlaylist(m_Player);
	m_Player->setPlaylist(m_Playlist);
	m_Playlist->addMedia(QUrl("qrc:/crunch.mp3"));

    createFormInterior();
}

void Item::createFormInterior() {
	setPixmap(QPixmap(m_Picture).scaled(QSize(250, 250), Qt::KeepAspectRatio));
    setMinimumSize(250, 250);
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
}

void Item::startDrag() {
	InventoryCell* draggedItem = new InventoryCell(0, 0);
	draggedItem->setContent(new Item(m_Picture, m_Type));
	draggedItem->setQuantity(1);
	WidgetDrag* drag = new WidgetDrag(draggedItem);
	drag->setWidget(draggedItem);
	drag->exec(Qt::MoveAction);
}

/*virtual*/ void Item::mousePressEvent(QMouseEvent *event) /*override*/ {
	if (event->button() == Qt::LeftButton) {
        m_DragStart = event->pos();
		qDebug() << "Item::mousePressEvent";
	}
    QLabel::mousePressEvent(event);
}

/*virtual*/ void Item::mouseMoveEvent(QMouseEvent *event) /*override*/ {
    if (event->buttons() & Qt::LeftButton) {
        int distance = (event->pos() - m_DragStart).manhattanLength();
        if (distance > QApplication::startDragDistance()) {
			if (m_dragEnable) {
				startDrag();
			}
        }
    }
    QLabel::mouseMoveEvent(event);
}

QString Item::picture() const {
    return m_Picture;
}

QString Item::type() const {
    return m_Type;
}

void Item::setDragEnable(bool dragEnable) {
	m_dragEnable = dragEnable;
}

void Item::reset() {
	m_Type = "";
	m_Picture = "";
	setPixmap(QPixmap());
}

void Item::eat() {
	reset();
	m_Player->play();
}
