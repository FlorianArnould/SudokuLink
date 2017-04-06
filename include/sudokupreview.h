#ifndef SUDOKUPREVIEW_H
#define SUDOKUPREVIEW_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include "sudokumodel.h"
#include <QFont>

class SudokuPreview : public QWidget
{
public:
    explicit SudokuPreview(QWidget *parent = 0);
    void setModel(SudokuModel * sudokuModel);

signals:
    void selected(int row, int column);

private:
    int xFirstPosition, yFirstPosition, squareSize;

    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    SudokuModel * model;

};

#endif // SUDOKUPREVIEW_H
