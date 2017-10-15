#ifndef LETTERMAP_H
#define LETTERMAP_H
#include <unordered_map>
#include <QFile>

class LetterMap
{
public:
    LetterMap();
    ~LetterMap();

    float getPercent(char letter);
    char generateLetter(float num);
private:

    QFile letterPercent;
    std::unordered_map<char, float> *lettMap;
};

#endif // LETTERMAP_H
