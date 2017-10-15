#include "playscreen.h"
#include <QBoxLayout>
#include <iostream>
#include <lettermap.h>
using namespace std;

PlayScreen::PlayScreen(QString word, ScreenManager *sm, bool CPU, QWidget *parent)
    : QWidget(parent), word(word), playingCPU(CPU), lettsGuessed(""), incorrectGuesses(0)
{
    layout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    this->sm = sm;

    string low = word.toStdString();
    for (int i = 0; i < low.size(); i++){
        low[i] = tolower(low[i]);
    }
    this->word = QString::fromStdString(low);

    label = new QLabel(this);
    homeBtn = new QPushButton(this);
    homeBtn->setText("Home");
    lineEdit = new QLineEdit(this);
    guessBtn = new QPushButton(this);
    guessBtn->setText("Guess Letter");
    output = new QLabel(this);
    lettsGuessedLbl = new QLabel(this);
    incorrectGuessLbl = new QLabel(this);
    string s = "Incorrect Guesses: ";
    s.append(to_string(incorrectGuesses));
    incorrectGuessLbl->setText(QString::fromStdString(s));

    placeHolder = new QWidget(this);
    wordLayout = new QBoxLayout(QBoxLayout::LeftToRight, placeHolder);

    cout<< "WORD: " << this->word.toStdString() << endl;

    layout->addWidget(homeBtn);
    layout->addWidget(label);
    layout->addWidget(placeHolder);
    layout->addWidget(lineEdit);
    layout->addWidget(guessBtn);
    layout->addWidget(output);
    layout->addWidget(lettsGuessedLbl);
    layout->addWidget(incorrectGuessLbl);


    if (playingCPU){
        startCPU();
    }else{
        startHuman();
    }
    displayLetters();

    connect(homeBtn, SIGNAL(clicked(bool)), sm, SLOT(switchToHome()));
    connect(guessBtn, SIGNAL(clicked(bool)), this, SLOT(guessMade()));
}

void PlayScreen::displayLetters(){
    map = new QSignalMapper(this);
    letters = new LetterLabel*[wordLength];
    for (int i = 0; i < wordLength; i++){
        letters[i] = new LetterLabel(placeHolder);
        letters[i]->setText("-");
        letters[i]->setIndex(i);
        connect(letters[i], SIGNAL(clicked()), map, SLOT(map()));
        map->setMapping(letters[i], letters[i]->getIndex());
        wordLayout->addWidget(letters[i]);
    }

    connect(map, SIGNAL(mapped(int)), this, SLOT(letterLocator(int)));
}

void PlayScreen::letterLocator(int i){
//    if (letters[i]->isClicked()){
//        letters[i]->resetStyle();
//    }else{
//        letters[i]->setStyleSheet(" QLabel{ background-color: rgb(255,0,0);}");
//    }
}

void PlayScreen::startCPU(){
    label->setText("The CPU is guessing letters!");
    wordLength = atoi(word.toStdString().c_str());
    guessBtn->setText("Confirm Location");
    output->setText("");
    output->show();
    lineEdit->hide();
    structure = new WordStructure(wordLength);
    CPUguess = structure->formulateGuess();
    string s = "The CPU guesses '";
    s += CPUguess;
    s.append("'. Click on its spot(s)");
    output->setText(QString::fromStdString(s));
}

void PlayScreen::startHuman(){
    label->setText("Guess the letters in the word:");
    wordLength = word.size();
    guessBtn->setText("Confirm Guess");
    output->hide();
    lineEdit->show();
}

void PlayScreen::guessMade(){
    if (playingCPU){
        handleCPUGuess();
    }else{
        string dataEntered = lineEdit->text().toStdString();
        char c = dataEntered[0];
        c = tolower(c);
        if ( dataEntered.size() != 1 ||(c < 65 || c > 122) || (c > 90 && c < 97)){
            label->setText("BAD INPUT. TRY AGAIN");
            return;
        }else{
            if (string::npos != lettsGuessed.find(c)){
                label->setText("LETTER ALREADY GUESSED. TRY AGIAN");
                return;
            }
            label->setText("Guess the letters in the word:");
            lineEdit->setText("");
            lineEdit->setFocus();
            showLetterGuessed(c);

            string w = word.toStdString();

            bool correct = false;
            for (int i = 0; i < w.size(); i++){
                if (w[i] == c){
                    letters[i]->setText(QChar(c));
                    correct = true;
                }
            }

            if (!correct){
                incorrectGuesses++;
                string s = "Incorrect Guesses: ";
                s.append(to_string(incorrectGuesses));
                incorrectGuessLbl->setText(QString::fromStdString(s));
            }

            if (gameOver()){
                output->setText("Game Over! Press Home to return to the main menu");
                output->show();
                guessBtn->setEnabled(false);
                lineEdit->hide();
            }
        }
    }

}

void PlayScreen::handleCPUGuess(){
    int *locations = new int [wordLength];

    int index = 0;
    for (int i =0 ; i < wordLength; i++){
        if (letters[i]->isClicked() && letters[i]->isClickable()){
            letters[i]->setText(QChar(CPUguess));
            locations[index] = i;
            index++;
            letters[i]->setClickable(false);
        }
    }

    if (index == 0){
        incorrectGuesses++;
        string s = "Incorrect Guesses: ";
        s.append(to_string(incorrectGuesses));
        incorrectGuessLbl->setText(QString::fromStdString(s));
    }

    structure->filter(CPUguess, locations, index);
    structure->letterGuessed(CPUguess);
    showLetterGuessed(CPUguess);
    structure->printValidWords();
    delete locations;

    CPUguess = structure->formulateGuess();
    if (gameOver() || CPUguess == '?'){
        output->setText("Game Over! Press Home to return to the main menu");
        guessBtn->setEnabled(false);
    }else{
        string s = "The CPU guesses '";
        s += CPUguess;
        s.append("'. Click on its spot(s)");
        output->setText(QString::fromStdString(s));
    }
}
void PlayScreen::showLetterGuessed(char guess){
    lettsGuessed += guess;
    lettsGuessed += ' ';
    lettsGuessedLbl->setText(QString::fromStdString(lettsGuessed));
}

bool PlayScreen::gameOver(){
    for (int i = 0; i < wordLength; i++){
        if (string::npos != letters[i]->text().toStdString().find('-'))
            return false;
    }
    return true;
}

PlayScreen::~PlayScreen(){
    delete label;
    delete sm;
    delete homeBtn;
    delete lineEdit;
    delete guessBtn;
    delete wordLayout;
    delete letters;
    delete layout;
    delete placeHolder;
    delete output;
    delete lettsGuessedLbl;
    delete incorrectGuessLbl;
}
