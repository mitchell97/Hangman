#include "wordinput.h"
#include <QBoxLayout>
#include <iostream>

WordInput::WordInput(ScreenManager *sm, QWidget *parent) : QWidget(parent), m_playingCPU(true)
{
    layout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    this->sm = sm;

    homeBtn = new QPushButton(this);
    homeBtn->setText("Home");

    playBtn = new QPushButton(this);
    playBtn->setText("Play");

    playHumanLbl = new QLabel(this);
    playHumanLbl->setText("Click here to play human:");

    playCPULbl =  new QLabel(this);
    playCPULbl->setText("Click here to play CPU:");

    playHumanBtn = new QPushButton(this);
    playHumanBtn->setText("Play Human");

    playCPUBtn = new QPushButton(this);
    playCPUBtn->setText("Play CPU");

    instruction = new QLabel(this);

    text = new QLineEdit(this);

    hor = new QBoxLayout(QBoxLayout::LeftToRight, this);
    if (m_playingCPU){
        playCPU();
    }else{
        playHuman();
    }

    layout->addWidget(homeBtn);
    layout->addItem(hor);
    layout->addWidget(instruction);
    layout->addWidget(text);
    layout->addWidget(playBtn);

    connect(homeBtn, SIGNAL(clicked(bool)), sm, SLOT(switchToHome()));
    connect(playBtn, SIGNAL(clicked(bool)), sm, SLOT(switchToPlay()));
    connect(text, SIGNAL(textChanged(QString)), sm, SLOT(updateWord(QString)));
    connect(playCPUBtn, SIGNAL(clicked(bool)), this, SLOT(playCPU()));
    connect(playHumanBtn, SIGNAL(clicked(bool)), this, SLOT(playHuman()));
}

void WordInput::playCPU(){
    m_playingCPU = true;
    sm->playingCPU(m_playingCPU);
    playCPULbl->hide();
    playCPUBtn->hide();
    hor->addWidget(playHumanLbl);
    hor->addWidget(playHumanBtn);
    playHumanLbl->show();
    playHumanBtn->show();
    instruction->setText("Currently playing CPU. Enter the number of letters in your word:");
}

void WordInput::playHuman(){
    m_playingCPU = false;
    sm->playingCPU(m_playingCPU);
    playHumanLbl->hide();
    playHumanBtn->hide();
    hor->addWidget(playCPULbl);
    hor->addWidget(playCPUBtn);
    playCPULbl->show();
    playCPUBtn->show();
    instruction->setText("Currently playing Human. Enter your word:");
}

void WordInput::updateWord(){
    sm->updateWord(text->text());
}

WordInput::~WordInput(){
    delete sm;
    delete homeBtn;
    delete playBtn;
    delete text;
    delete playHumanLbl;
    delete playCPULbl;
    delete playHumanBtn;
    delete playCPUBtn;
    delete instruction;
    delete layout;
    delete hor;
}
