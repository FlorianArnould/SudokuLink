#include "include/onwindialog.h"
#include "ui_onwindialog.h"

OnWinDialog::OnWinDialog(int minutes, int seconds, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OnWinDialog)
{
    ui->setupUi(this);
    QString str = QString::number(minutes)+":";
    if(seconds<10){
        str+="0";
    }
    ui->timeLabel->setText(str+QString::number(seconds));
    connect(ui->cancelButton, SIGNAL(clicked(bool)), this, SLOT(reject()));
    connect(ui->saveButton, SIGNAL(clicked(bool)), this, SLOT(accept()));
}

OnWinDialog::~OnWinDialog()
{
    delete ui;
}

QString OnWinDialog::getName()
{
    return ui->nameEdit->text();
}
