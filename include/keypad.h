#ifndef KEYPAD_H
#define KEYPAD_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QButtonGroup>

class KeyPad : public QWidget
{
    Q_OBJECT
public:
    enum Button {Button_Clear = 0, Button_1, Button_2, Button_3, Button_4, Button_5, Button_6, Button_7, Button_8, Button_9};
    explicit KeyPad(QWidget *parent = 0);

signals:
    void buttonClicked(int);

public slots:

private:
    QPushButton * buttons[11];
    QButtonGroup group;
};

#endif // KEYPAD_H
