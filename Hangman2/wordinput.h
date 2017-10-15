#ifndef WORDINPUT_H
#define WORDINPUT_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include "screenmanager.h"

class WordInput : public QWidget
{
    Q_OBJECT
public:
    WordInput(ScreenManager *sm, QWidget *parent);
    ~WordInput();

    bool playingCPU(){return m_playingCPU;}
private slots:
    void updateWord();
    void playHuman();
    void playCPU();
private:
    QLayout *layout;
    QLayout *hor;

    ScreenManager *sm;
    QPushButton *homeBtn;
    QPushButton *playBtn;
    QLineEdit *text;

    QLabel *playHumanLbl;
    QLabel *playCPULbl;
    QPushButton *playHumanBtn;
    QPushButton *playCPUBtn;
    QLabel *instruction;

    bool m_playingCPU;
};

#endif // WORDINPUT_H
