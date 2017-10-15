#ifndef ABSTRACTSCREEN_H
#define ABSTRACTSCREEN_H

#include <QWidget>
#include <screenmanager.h>

class AbstractScreen : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractScreen(QWidget *parent = nullptr, ScreenManager sm = NULL);

signals:

public slots:
    virtual void back() = 0;

private:
    ScreenManager sm;
};

#endif // ABSTRACTSCREEN_H
