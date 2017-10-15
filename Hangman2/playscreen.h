#ifndef PLAYSCREEN_H
#define PLAYSCREEN_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QSignalMapper>
#include <screenmanager.h>
#include <wordstructure.h>
#include <letterlabel.h>

class PlayScreen : public QWidget
{
    Q_OBJECT
public:
    explicit PlayScreen(QString word, ScreenManager *sm, bool CPU, QWidget *parent = nullptr);
    ~PlayScreen();

signals:
public slots:
    void guessMade();
    void letterLocator(int i);
    void handleCPUGuess();
private:
    bool gameOver();
    void startCPU();
    void startHuman();
    void displayLetters();
    void showLetterGuessed(char guess);

    ScreenManager *sm;
    QLabel *label;
    QString word;
    QPushButton *homeBtn;
    QLineEdit *lineEdit;
    QPushButton *guessBtn;
    QLayout *wordLayout;
    QLayout *layout;
    LetterLabel **letters;
    QWidget *placeHolder;
    QLabel *output;
    QSignalMapper *map;
    QLabel * lettsGuessedLbl;
    QLabel *incorrectGuessLbl;

    bool playingCPU;
    int wordLength;
    int incorrectGuesses;
    char CPUguess;
    std::string lettsGuessed;
    WordStructure *structure;
};
#endif // PLAYSCREEN_H
