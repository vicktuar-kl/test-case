#include <QtWidgets>
#include "widgetdrag.h"
#include "item.h"

Item::Item(QString picture, QString type/* = ""*/, QWidget *parent/* = nullptr*/)
	: m_Type(type), m_Picture(picture), m_ToCopy(true), QLabel(parent) {
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
	Item* draggedItem = new Item(m_Picture, m_Type);
	WidgetDrag* drag = new WidgetDrag(draggedItem);
	drag->setWidget(draggedItem);
	drag->exec(Qt::MoveAction);
}

/*virtual*/ void Item::mousePressEvent(QMouseEvent *event) /*override*/ {
    if (event->button() == Qt::LeftButton)
        m_DragStart = event->pos();
    QLabel::mousePressEvent(event);
}

/*virtual*/ void Item::mouseMoveEvent(QMouseEvent *event) /*override*/ {
    if (event->buttons() & Qt::LeftButton) {
        int distance = (event->pos() - m_DragStart).manhattanLength();
        if (distance > QApplication::startDragDistance()) {
			if (m_ToCopy) {
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

void Item::setToCopy(bool ToCopy) {
	m_ToCopy = ToCopy;
}

void Item::eat() {
	m_Type = "";
	m_Picture = "";
	clear();
	m_Player->play();
}
