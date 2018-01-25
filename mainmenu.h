#pragma once

#include <QWidget>
#include <QPushButton>

class MainMenu : public QWidget {
    Q_OBJECT
private:
    QPushButton *m_Start;
    QPushButton *m_Exit;

    void createFormInterior();

public:
    explicit MainMenu(QWidget *parent = nullptr);

signals:

public slots:
};
