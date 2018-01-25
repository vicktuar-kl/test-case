#include <QLabel>
#include <QLayout>
#include <QDebug>
#include "item.h"

Item::Item(QString picture, QString type/* = ""*/, QWidget *parent/* = nullptr*/)
    : m_Type(type), m_Picture(picture), QWidget(parent) {
    m_Label = new QLabel;
    m_Label->setPixmap(QPixmap(m_Picture));

    createFormInterior();
}

void Item::createFormInterior() {
    qDebug() << "Item";
}

QString Item::picture() const {
    return m_Picture;
}

QString Item::type() const {
    return m_Type;
}
