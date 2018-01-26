#pragma once

#include <QWidget>
#include <QLabel>

class Item : public QLabel {
    Q_OBJECT
private:
    QString m_Type;
    QString m_Picture;

    void createFormInterior();

public:
    explicit Item(QString picture, QString type = "", QWidget *parent = nullptr);

    QString picture() const;
    QString type() const;

signals:

public slots:
};
