#include "include/keypad.h"

KeyPad::KeyPad(QWidget *parent) :
    QWidget(parent)
{
    buttons[Button_Clear] = new QPushButton("Clear", this);
    buttons[Button_Clear]->setShortcut(QKeySequence::Delete);
    group.addButton(buttons[Button_Clear], Button_Clear);
    for(int i=1;i<10;i++){
        buttons[i] = new QPushButton(QString::number(i), this);
        group.addButton(buttons[i], i);
    }
    QGridLayout * gridLayout = new QGridLayout(this);
    int position[11] = {Button_7, Button_8, Button_9,
                        Button_4, Button_5, Button_6,
                        Button_1, Button_2, Button_3,
                        Button_Clear};
    for(int i=0;i<11;i++){
        gridLayout->addWidget(buttons[position[i]], i/3, i%3);
    }
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    connect(&group, SIGNAL(buttonClicked(int)), this, SIGNAL(buttonClicked(int)));
}
