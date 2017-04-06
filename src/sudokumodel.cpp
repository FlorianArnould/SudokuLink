#include "include/sudokumodel.h"

SudokuModel::SudokuModel(QObject *parent) : QObject(parent), selectedRow(0), selectedColumn(0), isHelped(false), wasHelped(false)
{

}

void SudokuModel::setUserNumber(int number)
{
    if(initialGrid[selectedRow][selectedColumn] != 0){
        return;
    }
    if(number == userGrid[selectedRow][selectedColumn]){
        return;
    }
    if(userGrid[selectedRow][selectedColumn] != 0){
        clearUserNumber();
    }
    if(number != KeyPad::Button_Clear){
        userGrid[selectedRow][selectedColumn] = number;
        updatePossibilitiesFrom(selectedRow, selectedColumn, number, &SudokuModel::neighborGot);
    }
    emit notify();
    validate();
}

void SudokuModel::clearUserNumber()
{
    if(userGrid[selectedRow][selectedColumn] == 0){
        return;
    }
    int old = userGrid[selectedRow][selectedColumn];
    userGrid[selectedRow][selectedColumn] = 0;
    updatePossibilitiesFrom(selectedRow, selectedColumn, old, &SudokuModel::neighborLose);
}

Case SudokuModel::getCase(int row, int column)
{
    if(initialGrid[row][column] != 0){
        return Case(initialGrid[row][column], Case::ORIGINAL);
    }
    if(userGrid[row][column] == 0){
        if(isHelped){
            return Case(possibilities[row][column], Case::MULTIPLE_POSSIBLE);
        }else{
            return Case(0, Case::NOTHING);
        }
    }
    if(possibilities[row][column].find(userGrid[row][column]) == possibilities[row][column].end()){
        return Case(userGrid[row][column], Case::ERROR);
    }
    return Case(userGrid[row][column], Case::POSSIBLE);
}

void SudokuModel::setNewGrid(int numbers[9][9])
{
    wasHelped = isHelped;
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            initialGrid[i][j] = numbers[i][j];
        }
    }
    initializeAllPossibilities();
    emit notify();
}

void SudokuModel::initializeAllPossibilities()
{
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(initialGrid[i][j] == 0){
                for(int k=1;k<=9;k++){
                    possibilities[i][j].insert(possibilities[i][j].end(), k);
                }
            }
            userGrid[i][j] = 0;
        }
    }
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(initialGrid[i][j] != 0){
                updatePossibilitiesFrom(i, j, initialGrid[i][j], &SudokuModel::neighborGot);
            }
        }
    }
}

void SudokuModel::updatePossibilitiesFrom(int row, int column, int number, void (SudokuModel::*method)(int, int, int))
{
    for(int i=0;i<9;i++){
        if(i != row){
            (this->*method)(i, column, number);
        }
        if(i != column){
            (this->*method)(row, i, number);
        }
    }
    int hPos = column%3, vPos = row%3;
    int hMin = -hPos, hMax = 2-hPos, vMin = -vPos, vMax = 2-vPos;
    for(int i=vMin;i<=vMax;i++){
        for(int j=hMin;j<=hMax;j++){
            if(i != 0 || j != 0){
                (this->*method)(row+i, column+j, number);
            }
        }
    }
}

void SudokuModel::neighborGot(int row, int column, int number)
{
    possibilities[row][column].erase(number);
}

void SudokuModel::neighborLose(int row, int column, int number)
{
    for(int i=0;i<9;i++){
        if(i != column && (initialGrid[row][i] == number || userGrid[row][i] == number)){
            return;
        }
        if(i != row && (initialGrid[i][column] == number || userGrid[i][column] == number)){
            return;
        }
    }
    int hPos = column%3, vPos = row%3;
    int hMin = -hPos, hMax = 2-hPos, vMin = -vPos, vMax = 2-vPos;
    for(int i=vMin;i<=vMax;i++){
        for(int j=hMin;j<=hMax;j++){
            if( (i != 0 || j != 0) && (initialGrid[row+i][column+j] == number || userGrid[row+i][column+j] == number)){
                return;
            }
        }
    }
    possibilities[row][column].insert(number);
}

int SudokuModel::getSelectedRow()
{
    return selectedRow;
}

int SudokuModel::getSelectedColumn()
{
    return selectedColumn;
}

void SudokuModel::setSelected(int row, int column)
{
    if(selectedRow != row || selectedColumn != column){
        selectedRow = row;
        selectedColumn = column;
        emit notify();
    }
}

void SudokuModel::moveUp()
{
    if(selectedRow > 0){
        selectedRow--;
        emit notify();
    }
}

void SudokuModel::moveDown()
{
    if(selectedRow < 8){
        selectedRow++;
        emit notify();
    }
}

void SudokuModel::moveLeft()
{
    if(selectedColumn > 0){
        selectedColumn--;
        emit notify();
    }
}

void SudokuModel::moveRight()
{
    if(selectedColumn < 8){
        selectedColumn++;
        emit notify();
    }
}

void SudokuModel::validate()
{
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            Case::State state = getCase(i, j).getState();
            if(state == Case::MULTIPLE_POSSIBLE || state == Case::ERROR || state == Case::NOTHING){
                return;
            }
        }
    }
    emit finish();
}

void SudokuModel::setHelp(bool helped)
{
    if(helped){
        wasHelped = true;
    }
    if(helped != isHelped){
        isHelped = helped;
        emit notify();
    }
}

bool SudokuModel::wasHelpActivated()
{
    return wasHelped;
}
