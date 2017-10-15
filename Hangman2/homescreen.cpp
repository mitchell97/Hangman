#include "homescreen.h"
#include<QBoxLayout>
HomeScreen::HomeScreen(ScreenManager *sm, QWidget *parent) : QWidget(parent)
{
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    this->sm = sm;

    label = new QLabel(this);
    label->setText("This is the homescreen");

    playBtn = new QPushButton(this);
    playBtn->setText("Guess Word");

    inputBtn = new QPushButton(this);
    inputBtn->setText("Input Word");

    layout->addWidget(label);
    layout->addWidget(playBtn);
    layout->addWidget(inputBtn);

    connect(playBtn, SIGNAL(clicked(bool)), sm, SLOT(switchToPlay()));
    connect(inputBtn, SIGNAL(clicked(bool)), sm, SLOT(switchToInput()));
}

HomeScreen::~HomeScreen(){
    delete label;
    delete sm;
    delete playBtn;
    delete inputBtn;
}
