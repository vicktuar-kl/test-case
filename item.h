#pragma once

#include <QtWidgets>
#include <QSoundEffect>

// ============================================================================
// Класс, описывающий характеристики предмета, яблока

class Item : public QLabel {
    Q_OBJECT

private:
	QString m_Type;				// тип предмета
	QString m_IconPath;			// путь до картинки с предметом

	QSoundEffect m_SoundEffect;	// звуковой эффект для действия с предметом в инвентаре

	void createFormInterior();	// фиксация размером виджета (иконки)

public:
	explicit Item(QString type, QWidget *parent = nullptr);	// Создаём объект, по его типу выбирается иконка и звук для действия

	QString iconPath() const;
    QString type() const;
	void action();					// действие с предметом
	static QString mimeType();
};
