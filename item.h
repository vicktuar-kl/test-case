#pragma once

#include <QtWidgets>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "database.h"

class Item : public QLabel {
    Q_OBJECT

private:
    QString m_Type;
    QString m_Picture;
    QPixmap m_Pixmap;
	QMediaPlayer* m_Player;
	QMediaPlaylist* m_Playlist;

    QPoint m_DragStart;

    void createFormInterior();
    void startDrag();

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

public:
    explicit Item(QString picture, QString type = "", QWidget *parent = nullptr);

    QString picture() const;
    QString type() const;
    QPixmap pixmap() const;
	void eat();

signals:

public slots:
};
