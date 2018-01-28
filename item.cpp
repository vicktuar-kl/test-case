#include <QtWidgets>
#include "widgetdrag.h"
#include "item.h"

Item::Item(QString picture, QString type/* = ""*/, QWidget *parent/* = nullptr*/)
    : m_Type(type), m_Picture(picture), m_Pixmap(m_Picture), QLabel(parent) {
	qDebug() << "Item create";
    createFormInterior();
}

void Item::createFormInterior() {
    m_Pixmap.load(m_Picture);
    m_Pixmap = m_Pixmap.scaled(QSize(250, 250), Qt::KeepAspectRatio);
    setPixmap(m_Pixmap);
    setMinimumSize(250, 250);
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
}

void Item::startDrag() {
	Item* copyItem = new Item(m_Picture, m_Type);
	WidgetDrag* drag = new WidgetDrag(copyItem);
	drag->setWidget(copyItem);
	drag->exec(Qt::CopyAction);
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
            startDrag();
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

QPixmap Item::pixmap() const {
    return m_Pixmap;
}
