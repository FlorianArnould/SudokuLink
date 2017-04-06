#ifndef SCOREDIALOG_H
#define SCOREDIALOG_H

#include <QDialog>
#include <QTableView>
#include <QTableWidget>
#include <QLabel>
#include "scores.h"

namespace Ui {
class ScoreDialog;
}

class ScoreDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScoreDialog(QWidget *parent = 0);
    ~ScoreDialog();

private:
    Ui::ScoreDialog *ui;
};

#endif // SCOREDIALOG_H
