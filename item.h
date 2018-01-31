#pragma once

#include <QtWidgets>
#include <QSoundEffect>


class Item : public QLabel {
    Q_OBJECT

private:
    QString m_Type;
    QString m_Picture;

	QSoundEffect m_SoundEffect;

    void createFormInterior();

public:
	explicit Item(QString type, QString picture, QWidget *parent = nullptr);

    QString picture() const;
    QString type() const;
	void action();
	static QString mimeType();
	void setType(const QString& Type);
	void setPicture(const QString& Picture);

signals:

public slots:
};
