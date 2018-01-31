#include <QtWidgets>
#include <QtSql>
#include "item.h"
#include "inventorycell.h"

Item::Item(QString type, QWidget* parent /*= nullptr*/)
	: QLabel(parent), m_Type(type) {
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName("db/testInventory");
	db.open();
	QSqlQuery query;
	QSqlRecord rec;
	query.exec("SELECT IconPath, SoundPath FROM 'Item' WHERE Type = '" + m_Type + "';");
	while (query.next()) {
		m_IconPath = query.value(rec.indexOf("IconPath")).toString();
		qDebug() << m_IconPath;
		m_SoundEffect.setSource(QUrl::fromLocalFile(":/" + query.value(rec.indexOf("SoundPath")).toString()));
	}
	createFormInterior();
}

Item::Item(QString type, QString picture, QWidget* parent/* = nullptr*/)
	: QLabel(parent), m_Type(type), m_IconPath(picture) {
	m_SoundEffect.setSource(QUrl::fromLocalFile(":/crunch.wav"));
	createFormInterior();
}

void Item::createFormInterior() {
	setPixmap(QPixmap(":/" + m_IconPath).scaled(QSize(250, 250), Qt::KeepAspectRatio));
    setMinimumSize(250, 250);
	setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
}

QString Item::iconPath() const {
	return m_IconPath;
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
	m_IconPath = Picture;
}
