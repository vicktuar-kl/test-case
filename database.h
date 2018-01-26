#pragma once

#include <QObject>

class DataBase : public QObject {
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = nullptr);

signals:

public slots:
};
