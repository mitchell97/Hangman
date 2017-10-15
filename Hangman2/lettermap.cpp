#include "lettermap.h"
#include <QTextStream>
#include <iostream>
using namespace std;

LetterMap::LetterMap() : letterPercent(":/data/letterpercentages.txt")
{
    lettMap = new unordered_map<char, float>();
    QTextStream in(&letterPercent);

    letterPercent.open(QIODevice::ReadOnly | QIODevice::Text);


    string currentWord = "";
    while (!in.atEnd()){
       currentWord = in.readLine().toStdString();
       char key = currentWord[0];
       float value = stof(currentWord.substr(1));
       lettMap->insert({key, value});
    }

    float total = 0.0;
    for (char let = 'a'; let <= 'z'; let++){
        //cout<< let << ": " << getPercent(let) << endl;
        total += getPercent(let);
    }
   // cout << "Total: " << total << endl;

    letterPercent.close();
}

float LetterMap::getPercent(char letter){
    letter = toupper(letter);

    if (lettMap->end() == lettMap->find(letter))
        return -1.0;

    return lettMap->at(letter);
}

char LetterMap::generateLetter(float num){
    if (num < 0 || num > 100)
        return NULL;

    char current = 'a';
    float index = 0;
    for (; current <= 'z'; current++){
        index += getPercent(current);
        if(num < index)
            break;
    }
    return current;
}
LetterMap::~LetterMap()
{
    delete lettMap;
}
