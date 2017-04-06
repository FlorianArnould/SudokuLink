#ifndef ONWINDIALOG_H
#define ONWINDIALOG_H

#include <QDialog>

namespace Ui {
class OnWinDialog;
}

class OnWinDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OnWinDialog(int minutes, int seconds, QWidget *parent = 0);
    QString getName();
    ~OnWinDialog();

private:
    Ui::OnWinDialog *ui;
};

#endif // ONWINDIALOG_H
