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
	QString m_SoundPath;		// путь до звукового файла

	void createFormInterior();	// фиксация размером виджета (иконки)

public:
	explicit Item(const QString& type, QWidget *parent = nullptr);	// Создаём объект, по его типу выбирается иконка и звук для действия
	Item(const QString& type, const QString& iconPath,
		 const QString& soundPath, QWidget* parent = nullptr);

	QString iconPath() const;
	QString soundPath() const;
	QString type();
	static QString mimeType();
};
