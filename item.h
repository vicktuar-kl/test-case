#pragma once

#include <QWidget>
#include <QLabel>

class Item : public QLabel {
    Q_OBJECT
private:
    QString m_Type;
    QString m_Picture;
    QPixmap m_Pixmap;

    QPoint m_DragStart;

    void createFormInterior();
    void startDrag();

protected:
//    void dragEnterEvent(QDragEnterEvent *event) override;
//    void dragMoveEvent(QDragMoveEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

public:
    explicit Item(QString picture, QString type = "", QWidget *parent = nullptr);

    QString picture() const;
    QString type() const;
    QPixmap pixmap() const;

signals:

public slots:
};
