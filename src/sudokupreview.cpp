#include "include/sudokupreview.h"
#include <QDebug>
SudokuPreview::SudokuPreview(QWidget *parent) : QWidget(parent), model(nullptr)
{
    setMinimumHeight(400);
    setMinimumWidth(400);
}

void SudokuPreview::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    /*Offset for drawing the rectangle and filling them with the numbers*/
    int verticalOffset = 0;
    int horizontalOffset = 0;
    int gridOffset = 2;

    /*Adapt to the widget size*/
    int MainBlockLength = height() - 2*gridOffset;
    if(width() > height()){
        horizontalOffset = (width() - height())/2;
    }else if(height() > width()){
        verticalOffset = (height() - width())/2;
        MainBlockLength = width() - 2*gridOffset;
    }

    /*Size of the squares to draw the grid*/
    int smallSquare = MainBlockLength / 9;
    int mediumSquare = smallSquare * 3;

    /*Shifts needed to align the number in the case depending on the window size*/
    int yTextPosition= 2.2*smallSquare/3 + 3;
    int xTextPosition = 0.25*smallSquare+2;

    /*Font sizes to adjust the number in the cases*/
    QFont normalFont = painter.font();
    normalFont.setPointSize(0.2*mediumSquare);
    QFont smallFont = painter.font();
    smallFont.setPointSize(0.2*smallSquare);

    xFirstPosition = gridOffset + horizontalOffset;
    yFirstPosition = gridOffset + verticalOffset;
    squareSize = smallSquare;

    painter.setPen(QPen(Qt::gray,2));

    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            painter.drawRect(gridOffset + horizontalOffset + i*smallSquare, gridOffset + verticalOffset + j*smallSquare, smallSquare, smallSquare);
        }
    }

    painter.setPen(QPen(Qt::black,2));

    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            painter.drawRect(gridOffset + horizontalOffset + i*mediumSquare , gridOffset + verticalOffset + j*mediumSquare, mediumSquare, mediumSquare);
        }
    }

    if(model != nullptr){
        int selectedValue = model->getCase(model->getSelectedRow(), model->getSelectedColumn()).getValue();
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                painter.setFont(normalFont);
                Case sudokuCase = model->getCase(i, j);
                if(i == model->getSelectedRow() && j == model->getSelectedColumn()){
                    painter.setPen(QPen(Qt::blue, 3));
                    painter.drawRect(xFirstPosition + model->getSelectedColumn()*smallSquare, yFirstPosition + model->getSelectedRow()*smallSquare, smallSquare, smallSquare);
                }
                switch(sudokuCase.getState()){

                case Case::ORIGINAL:
                    if(sudokuCase.getValue() == selectedValue){
                        painter.setPen(Qt::green);
                    }else{
                        painter.setPen(Qt::black);
                    }
                    painter.drawText(xFirstPosition + xTextPosition + j*smallSquare, yFirstPosition + i*smallSquare + yTextPosition, QString::number(sudokuCase.getValue()));
                    break;

                case Case::POSSIBLE:
                    if(sudokuCase.getValue() == selectedValue){
                        painter.setPen(Qt::green);
                    }else{
                        painter.setPen(Qt::blue);
                    }
                    painter.drawText(xFirstPosition + xTextPosition + j*smallSquare, yFirstPosition+i*smallSquare + yTextPosition, QString::number(sudokuCase.getValue()));
                    break;

                case Case::ERROR:
                    painter.setPen(Qt::red);
                    painter.drawText(xFirstPosition + xTextPosition + j*smallSquare, yFirstPosition+i*smallSquare + yTextPosition, QString::number(sudokuCase.getValue()));
                    break;

                case Case::MULTIPLE_POSSIBLE:
                    painter.setFont(smallFont);
                    painter.setPen(Qt::blue);
                    std::set<int> possibilities = sudokuCase.getPossibilities();
                    for(int k=0;k<3;k++)
                    {
                        for(int l=0;l<3;l++)
                        {
                            if(possibilities.find(k*3+l+1) != possibilities.end()){
                                painter.drawText(xFirstPosition + 6 + l*smallSquare/3 + j*smallSquare, yFirstPosition+i*smallSquare + (k+1)*smallSquare/3 - 4, QString::number(k*3+l+1));
                            }
                        }
                    }
                }
            }
        }
    }
}

void SudokuPreview::mousePressEvent(QMouseEvent *event)
{
    if(model != nullptr){
        model->setSelected((event->y()-yFirstPosition)/squareSize, (event->x()-xFirstPosition)/squareSize);
    }
}

void SudokuPreview::setModel(SudokuModel * sudokuModel)
{
    model = sudokuModel;
    connect(model, SIGNAL(notify()), this, SLOT(update()));
    update();
}
