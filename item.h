#pragma once

#include <QWidget>
#include <QLabel>

class Item : public QWidget {
    Q_OBJECT
private:
    QString m_Type;
    QString m_Picture;
    QLabel *m_Label;

    void createFormInterior();

public:
    explicit Item(QString picture, QString type = "", QWidget *parent = nullptr);

    QString picture() const;
    QString type() const;
    QLabel *label() const;

signals:

public slots:
};
