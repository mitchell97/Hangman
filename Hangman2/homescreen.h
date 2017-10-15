#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <screenmanager.h>

class HomeScreen : public QWidget
{
    Q_OBJECT
public:
    explicit HomeScreen(ScreenManager *sm, QWidget *parent = nullptr);
    ~HomeScreen();

signals:
public slots:

private:
    ScreenManager *sm;
    QLabel *label;
    QPushButton *playBtn;
    QPushButton *inputBtn;
};

#endif // HOMESCREEN_H
