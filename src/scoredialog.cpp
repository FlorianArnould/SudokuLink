#include "include/scoredialog.h"
#include "ui_scoredialog.h"

ScoreDialog::ScoreDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScoreDialog)
{
    ui->setupUi(this);
    QWidget * tab[] = {ui->easyTab, ui->mediumTab, ui->hardTab, ui->insaneTab};
    QStringList titles;
    titles << tr("Name") << tr("Time");
    ScoreStorage storage;
    QTableWidget * tables[8];
    for(int i=0;i<4;i++){
        QHBoxLayout * hLayout = new QHBoxLayout(tab[i]);
        QVBoxLayout * normalLayout = new QVBoxLayout();
        QVBoxLayout * helpedLayout = new QVBoxLayout();
        hLayout->addLayout(normalLayout);
        hLayout->addLayout(helpedLayout);
        normalLayout->addWidget(new QLabel(tr("Normal"), tab[i]));
        helpedLayout->addWidget(new QLabel(tr("With help"), tab[i]));
        for(int j=0;j<2;j++){
            tables[i*2+j] = new QTableWidget(tab[i]);
            tables[i*2+j]->setColumnCount(2);
            tables[i*2+j]->setHorizontalHeaderLabels(titles);
        }
        normalLayout->addWidget(tables[i*2]);
        helpedLayout->addWidget(tables[i*2+1]);
        for(int k=0;k<2;k++){
            std::vector<ScoreStorage::Score> vector = storage.getScores((ScoreStorage::Difficulty)i, k);
            tables[i*2+k]->setRowCount(vector.size());
            for(unsigned int j=0;j<vector.size();j++){
                tables[i*2+k]->setCellWidget(j, 0, new QLabel(vector[j].getName()));
                tables[i*2+k]->setCellWidget(j, 1, new QLabel(vector[j].getTime()));
            }
        }
    }
}

ScoreDialog::~ScoreDialog()
{
    delete ui;
}
