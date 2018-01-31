#pragma once

#include <QtWidgets>
#include <QSoundEffect>


class Item : public QLabel {
    Q_OBJECT

private:
    QString m_Type;
	QString m_IconPath;

	QSoundEffect m_SoundEffect;

    void createFormInterior();

public:
	explicit Item(QString type, QWidget* parent = nullptr);
	explicit Item(QString type, QString iconPath, QWidget *parent = nullptr);

	QString iconPath() const;
    QString type() const;
	void action();
	static QString mimeType();
	void setType(const QString& Type);
	void setPicture(const QString& Picture);

signals:

public slots:
};
