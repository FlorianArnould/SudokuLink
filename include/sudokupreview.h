#ifndef SUDOKUPREVIEW_H
#define SUDOKUPREVIEW_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include "sudokumodel.h"
#include <QFont>
#include <QColor>

class SudokuPreview : public QWidget
{
    Q_OBJECT
public:
    explicit SudokuPreview(QWidget *parent = 0);
    void setModel(SudokuModel * sudokuModel);

signals:
    void selected(int row, int column);

public slots:
    void setColorMode(bool activated);

private:
    int xFirstPosition, yFirstPosition, squareSize;
    SudokuModel * model;
    bool colorMode;
    const QColor colors[9];

    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
};

#endif // SUDOKUPREVIEW_H
