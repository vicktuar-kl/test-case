#include <QtWidgets>
#include "item.h"
#include "inventorycell.h"

Item::Item(QString type, QString picture, QWidget* parent/* = nullptr*/)
	: QLabel(parent), m_Type(type), m_Picture(picture) {
	m_SoundEffect.setSource(QUrl::fromLocalFile(":/crunch.wav"));
	createFormInterior();
}

void Item::createFormInterior() {
	setPixmap(QPixmap(m_Picture).scaled(QSize(250, 250), Qt::KeepAspectRatio));
    setMinimumSize(250, 250);
	setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
}

QString Item::picture() const {
    return m_Picture;
}

QString Item::type() const {
	return m_Type;
}

void Item::action() {
	m_SoundEffect.play();
}

QString Item::mimeType() {
	return "application/x-item";
}

void Item::setType(const QString& Type) {
	m_Type = Type;
}

void Item::setPicture(const QString& Picture) {
	m_Picture = Picture;
}
