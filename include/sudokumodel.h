#ifndef SUDOKUMODEL_H
#define SUDOKUMODEL_H

#include <QObject>
#include <set>
#include "case.h"
#include "keypad.h"

class SudokuModel : public QObject
{
    Q_OBJECT
public:
    explicit SudokuModel(QObject *parent = 0);
    void setNewGrid(int numbers[9][9]);
    Case getCase(int row, int column);
    int getSelectedRow();
    int getSelectedColumn();
    bool wasHelpActivated();

signals:
    void notify();
    void finish();

public slots:
    void setSelected(int row, int column);
    void setUserNumber(int number);
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void setHelp(bool helped);

private:
    int initialGrid[9][9];
    int userGrid[9][9];
    int selectedRow, selectedColumn;
    std::set<int> possibilities[9][9];
    bool isHelped, wasHelped;
    void initializeAllPossibilities();
    void updatePossibilitiesFrom(int row, int column, int number, void (SudokuModel::*method)(int, int, int));
    void updatePossibilitiesForWith(int row, int column, int newNumber);
    void neighborGot(int row, int column, int number);
    void neighborLose(int row, int column, int number);
    void clearUserNumber();
    void validate();
};

#endif // SUDOKUMODEL_H
