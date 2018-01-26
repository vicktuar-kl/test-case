#include <QtWidgets>
#include "item.h"

Item::Item(QString picture, QString type/* = ""*/, QWidget *parent/* = nullptr*/)
    : m_Type(type), m_Picture(picture), m_Pixmap(m_Picture), QLabel(parent) {

    createFormInterior();
}

void Item::createFormInterior() {
    qDebug() << "Item";
    m_Pixmap.load(m_Picture);
    m_Pixmap = m_Pixmap.scaled(QSize(250, 250), Qt::KeepAspectRatio);
    setPixmap(m_Pixmap);
    setMinimumSize(250, 250);
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
}

void Item::startDrag() {
    QMimeData * mimeData = new QMimeData;
    QByteArray data;
    QDataStream dataStream(&data, QIODevice::WriteOnly);

    dataStream << m_Pixmap << m_Type << m_Picture;
    mimeData->setData("application/x-item", data);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(m_Pixmap);
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
