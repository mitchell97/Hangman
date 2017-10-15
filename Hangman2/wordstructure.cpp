#include "wordstructure.h"
#include <iostream>
#include <stdexcept>
#include <QTextStream>
#include <vector>
using namespace std;

WordStructure::WordStructure(int wordLength) : wordList(":/dictionary/words.txt"), lettMap()
{
    //cout << "checkpoint. length of words:" << wordLength << endl;
    if (wordLength <= 0){
        throw std::invalid_argument("Invalid wordlength ");
    }

    for (int i = 0; i < NUM_OF_LETTERS; i++){
        lettersGuessed[i] = false;
    }

    wordList.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&wordList);

    cout << "checkpoint 2" << endl;
    string currentWord = "";
    cachedWords = new vector<GameWord>();

    currentWord = "";
    int index = 0;
    while(!in.atEnd()){
        currentWord = in.readLine().toStdString();
        if (currentWord.length() != wordLength)
            continue;
        std::transform(currentWord.begin(), currentWord.end(), currentWord.begin(), ::tolower);

        if (!isWord(currentWord))
            continue;

        cachedWords->push_back(GameWord(currentWord));
        index++;
    }
    cachedWords->shrink_to_fit();
    numValidWords = index;


//    for (int i =0; i < cachedWords->size(); i++){
//        cout << i << cachedWords->at(i).getWord() << endl;
//    }
    cout << "Number of initial Words: " << numValidWords << endl;

    cout << "checkpoint3" << endl;

    wordList.close();
}

bool WordStructure::isWord(string str){
    for (int i = 0; i < str.size(); i++){
        if (str[i] < 97 || str[i] >122 )
            return false;
    }
    return true;
}

void WordStructure::filter(char letter, int locations[], int numOfPos){
    if (numOfPos == 0){
        for (int i = 0; i < cachedWords->size(); i++){
            if (!cachedWords->at(i).isValid())
                continue;
            if (string::npos != cachedWords->at(i).getWord().find(letter)){
                cachedWords->at(i).setValidity(false);
                numValidWords--;
            }
        }
        return;
    }

    for (int i = 0; i < cachedWords->size(); i++){
        if (!cachedWords->at(i).isValid())
            continue;
        if (numOfPos < numChar(cachedWords->at(i).getWord(), letter)){
            cachedWords->at(i).setValidity(false);
            numValidWords--;
            continue;
        }
        for (int j = 0; j < numOfPos; j++){
            if (cachedWords->at(i).getWord()[locations[j]] != letter){
                cachedWords->at(i).setValidity(false);
                numValidWords--;
                break;
            }
        }
    }
}

int WordStructure::numChar(string check, char lett){
    int rtn = 0;
    for (int i = 0; i < check.size(); i++){
        if (check[i] == lett)
            rtn++;
    }
    return rtn;
}

void WordStructure::printValidWords(){
    for (int i =0; i < cachedWords->size(); i++){
        if (cachedWords->at(i).isValid())
            cout << cachedWords->at(i).getWord() << endl;
    }
    cout << "Total words: " << numValidWords << endl;
    cout << "----------------------------------------" << endl;

  //  cout << "Guess: " << formulateGuess() << endl;
}

char WordStructure::formulateGuess(){
    float num = ((rand() * rand()) % 100000) / 1000.0;
    cout << "Random num: " << num << endl;

    if (numValidWords > 100){
       // cout << lettMap.generateLetter(num) << endl;
        char rtn =tolower(lettMap.generateLetter(num));
        while (wasLetterGuessed(rtn)){
            rtn = tolower(lettMap.generateLetter(num));
            num = ((rand() * rand()) % 100000) / 1000.0;
        }
        return rtn;
    }else{
        if (numValidWords > 2){
            vector<string>* words = validWords();
            char letter = findMostCommonLetter(words);
            delete words;
            return letter;
        }else{
            if (numValidWords == 2){
                vector<string> *words = validWords();
                char rtn;
                string str1 = words->at(0);
                string str2 = words->at(1);
                for (int i = 0; i < words->at(0).size(); i++){
                    if (str1[i] != str2[i]){
                        if (wasLetterGuessed(str1[i]) || wasLetterGuessed(str2[i]))
                            continue;
                        if (lettMap.getPercent(str1[i]) >= lettMap.getPercent(str2[i])){
                            rtn = str1[i];
                        }else{
                            rtn = str2[i];
                        }
                    }
                }
                delete words;
                return rtn;
            }else{
                if (numValidWords == 1){
                    vector<string> *words = validWords();
                    char rtn;
                    for(int i = 0; i < words->at(0).size(); i++){
                        if (!wasLetterGuessed(words->at(0)[i]))
                            rtn = words->at(0)[i];
                    }
                    delete words;
                    return rtn;
                }else{
                    // NO VALID WORDS
                    cout << "No valid words to guess" << endl;
                    return '?';
                }
            }
        }
    }
    return '?';
}

vector<string>* WordStructure::validWords(){
    vector<string>* words = new vector<string>();

    for (int i = 0; i < cachedWords->size(); i++){
        if (cachedWords->at(i).isValid()){
            words->push_back(cachedWords->at(i).getWord());
        }
    }

    return words;
}


char WordStructure::findMostCommonLetter(std::vector<string>* words){
    unordered_map<char, int> lettNums;

    string currentWord = "";
    for (int i =0; i < words->size(); i++){
        currentWord = words->at(i);
        for (int j = 0; j < currentWord.size(); j++){
            char letter = tolower(currentWord[j]);
            if (!wasLetterGuessed(letter)){
                if (lettNums.end() == lettNums.find(letter)){
                    lettNums[letter] = 1;
                }else{
                   int occurances = lettNums[letter];
                   occurances++;
                   lettNums[letter] = occurances;
                }
            }
        }
    }

    char letter;
    int value = -1;
    for (unordered_map<char, int>::iterator itr = lettNums.begin(); itr != lettNums.end(); itr++){
//        cout << "test: " << itr->first << " " << itr->second << endl;
        if (itr->second >= value){
            if (itr->second == value){
                if (lettMap.getPercent(letter) < lettMap.getPercent(itr->first)){
                    letter = itr->first;
                    value = itr->second;
                }
            }else{
                letter = itr->first;
                value = itr->second;
            }
        }
    }

    cout << "Most common letter: " << letter << " occurs " << value << " times" << endl;

    return letter;
  //  return 'a';
}

void WordStructure::letterGuessed(char letter){
    letter = tolower(letter);
    letter -= 97;
    if (!lettersGuessed[letter]){
        lettersGuessed[letter] = true;
    }else{
        // Letter was already guessed
    }

//    for (char i = 'a'; i <= 'z' ; i++){
//        cout << i << ": " << lettersGuessed[i] << endl;
//    }
}

bool WordStructure::wasLetterGuessed(char letter){
    letter = tolower(letter);
    letter -= 97;
    return lettersGuessed[letter];
}
WordStructure::~WordStructure(){
    delete[] cachedWords;
}
