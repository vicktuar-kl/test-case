#include <QLabel>
#include <QLayout>
#include <QDebug>
#include "item.h"

Item::Item(QString picture, QString type/* = ""*/, QWidget *parent/* = nullptr*/)
    : m_Type(type), m_Picture(picture), QLabel(parent) {

    createFormInterior();
}

void Item::createFormInterior() {
    qDebug() << "Item";
    QPixmap pixmap(m_Picture);
    pixmap = pixmap.scaled(QSize(250, 250), Qt::KeepAspectRatio);
    setPixmap(pixmap);
    setMinimumSize(250, 250);
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
}

QString Item::picture() const {
    return m_Picture;
}

QString Item::type() const {
    return m_Type;
}
