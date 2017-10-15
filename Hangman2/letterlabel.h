#ifndef LETTERLABEL_H
#define LETTERLABEL_H
#include <QLabel>

class LetterLabel : public QLabel
{
    Q_OBJECT
public:
    LetterLabel(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());

    void turnOffHover();
    void setIndex(int i){index = i;}
    int getIndex(){return index;}
    bool isClicked(){return currentlyClicked;}
    void resetStyle(){this->setStyleSheet("QLabel:hover {border: 1px solid black}");}
    bool isClickable(){return clickable;}
    void setClickable(bool click){
        if (click == false){
            setStyleSheet("");
        }else{
            resetStyle();
        }
        clickable =click;
    }
signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event);
    int index;
    bool currentlyClicked;
    bool clickable;
};

#endif // LETTERLABEL_H
