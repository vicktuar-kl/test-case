#include <QtWidgets>
#include "item.h"
#include "inventorycell.h"

// Создаём объект, по его типу выбирается иконка и звук для действия
// пока только яблоки :(
Item::Item(QString type, QWidget* parent/* = nullptr*/)
	: QLabel(parent), m_Type(type) {
	if (m_Type.toLower() == "apple") {
		m_IconPath = ":/apple.jpg";
		m_SoundPath = ":/crunch.wav";
	}
	createFormInterior();
}

Item::Item(QString type, QString iconPath, QString soundPath, QWidget* parent/* = nullptr*/)
	: QLabel(parent), m_Type(type), m_IconPath(iconPath), m_SoundPath(soundPath) {
	createFormInterior();
}

// фиксация размеров виджета (иконки)
QString Item::soundPath() const
{
	return m_SoundPath;
}

void Item::createFormInterior() {
	setPixmap(QPixmap(m_IconPath).scaled(QSize(250, 250), Qt::KeepAspectRatio));
    setMinimumSize(250, 250);
	setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
}

// геттер для пути до иконки
QString Item::iconPath() const {
	return m_IconPath;
}

// геттер для типа предмета
QString Item::type() {
	return m_Type;
}

// статический метод класса для mime-типа этого класса (нужно для Drag'n'Drop)
QString Item::mimeType() {
	return "application/x-item";
}
