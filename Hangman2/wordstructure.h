#ifndef WORDSTRUCTURE_H
#define WORDSTRUCTURE_H
#define NUM_OF_LETTERS 26
#include <QFile>
#include <gameword.h>
#include <vector>
#include <lettermap.h>

class WordStructure
{
public:
    WordStructure(int wordLength);
    ~WordStructure();

    void filter(char letter, int locations [], int numOfPos);
    void printValidWords();
    char formulateGuess();
    std::vector<std::string>* validWords();
    void letterGuessed(char letter);
    char findMostCommonLetter(std::vector<std::string>* words);
    static bool isWord(std::string str);

private:
    bool wasLetterGuessed(char letter);
    int numChar(std::string check, char lett);

    QFile wordList;
    std::vector<GameWord> *cachedWords;
    int numValidWords;
    LetterMap lettMap;
    bool lettersGuessed [NUM_OF_LETTERS];
};

#endif // WORDSTRUCTURE_H
