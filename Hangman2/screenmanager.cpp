#include <playscreen.h>
#include <homescreen.h>
#include <wordinput.h>
#include<time.h>

#include <QLayout>
#include <QBoxLayout>
#include <QTextStream>

#include<iostream>
using namespace std;

ScreenManager::ScreenManager() : wordList(":/dictionary/words.txt"), playCPU(false)
{
    srand(time(NULL));
    word = "DEFAULT WORD";
    word = generateWord();

    cout << "DONE"  << word.toStdString() << endl;

    mainFrame = new QWidget(NULL);
    currentScreen = new HomeScreen(this, mainFrame);
    mainFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainFrame->setFixedSize(500,500);
    mainFrame->show();
}

void ScreenManager::switchToPlay(){
    if(playCPU){
        if (word.toStdString().size() > 2){
            return;
        }
        for (int i = 0 ; i < word.toStdString().size(); i++){
            if (word.toStdString()[i] < 48 || word.toStdString()[i] > 57)
                return;
        }
    }
    currentScreen->close();
    currentScreen = new PlayScreen(word, this, playCPU, mainFrame);
    currentScreen->show();
}

void ScreenManager::switchToHome(){
    currentScreen->close();
    word = "DEFAULT WORD";
    word = generateWord();
    playCPU = false;
    currentScreen = new HomeScreen(this, mainFrame);
    currentScreen->show();
}

void ScreenManager::switchToInput(){
    currentScreen->close();
    currentScreen = new WordInput(this, mainFrame);
    currentScreen->show();
}

QString ScreenManager::generateWord(){
    wordList.open(QIODevice::ReadOnly | QIODevice::Text);

    int num = (rand() * rand()) % 466547;
    int lines = 0;

    string temp;
    QTextStream in(&wordList);

    while (!in.atEnd()){
        if (lines == num){
            temp = in.readLine().toStdString();

            while (!WordStructure::isWord(temp)){
                temp = in.readLine().toStdString();
            }
            break;
        }
        lines++;
        in.readLine();
//        cout << in.pos() <<endl;
       // QString line = in.readLine();
    }

    wordList.close();

    std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

    return QString::fromStdString(temp);
}

void ScreenManager::updateWord(QString word){
    this->word = word;
}

ScreenManager::~ScreenManager(){
    delete currentScreen;
    delete mainFrame;
}
