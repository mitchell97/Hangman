#ifndef GAMEWORD_H
#define GAMEWORD_H
#include<string>

class GameWord
{
public:
    GameWord(std::string word, bool validity = true);
    ~GameWord();

    bool isValid(){return valid;}
    void setValidity(bool validity){valid = validity;}
    std::string getWord(){return word;}
    void setWord(std::string word){this->word = word;}
private:
    std::string word;
    bool valid;
};

#endif // GAMEWORD_H
