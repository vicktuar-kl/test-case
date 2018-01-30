#include <QtWidgets>
#include "widgetdrag.h"
#include "item.h"
#include "inventorycell.h"

Item::Item(QString picture, QString type, QWidget *parent/* = nullptr*/)
	: QLabel(parent), m_Picture(picture), m_Type(type) {
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

QString Item::picture() const {
    return m_Picture;
}

QString Item::type() const {
	return m_Type;
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
