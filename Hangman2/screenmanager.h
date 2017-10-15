#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include<QWidget>
#include<QMainWindow>
#include<QFile>

class ScreenManager : public QObject
{
    Q_OBJECT
public:
    ScreenManager();
    ~ScreenManager();

public slots:
    void switchToPlay();
    void switchToHome();
    void switchToInput();
    void updateWord(QString word);
    void playingCPU(bool CPU){playCPU = CPU;}

private:
    QString generateWord();

    QFile wordList;
    QWidget *mainFrame;
    QWidget *currentScreen;
    QString word;
    bool playCPU;
};

#endif // SCREENMANAGER_H
