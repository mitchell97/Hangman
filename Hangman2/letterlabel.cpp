#include "letterlabel.h"

LetterLabel::LetterLabel(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent), currentlyClicked(false), clickable(true){
    this->resetStyle();
    this->setAlignment(Qt::AlignCenter);
}

void LetterLabel::turnOffHover(){
    this->setStyleSheet("");
}
void LetterLabel::mousePressEvent(QMouseEvent* event) {
    if (!clickable) return;

    if (!currentlyClicked){
        currentlyClicked = true;
        setStyleSheet(" QLabel{ background-color: rgb(255,0,0);}");
    }
    else{
        currentlyClicked = false;
        resetStyle();
    }
    emit clicked();
}
