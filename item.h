#pragma once

#include <QtWidgets>
#include <QMediaPlayer>
#include <QMediaPlaylist>


class Item : public QLabel {
    Q_OBJECT

private:
    QString m_Type;
    QString m_Picture;

	QMediaPlayer* m_Player;
	QMediaPlaylist* m_Playlist;

    void createFormInterior();

public:
	explicit Item(QString picture, QString type, QWidget *parent = nullptr);

    QString picture() const;
    QString type() const;
	void reset();
	void eat();
	static QString mimeType();

signals:

public slots:
};
