#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QGridLayout>
#include <QSignalMapper>
#include <QLabel>
#include "include/sudokupreview.h"
#include "include/sudokumodel.h"
#include "include/keypad.h"
#include "include/scoredialog.h"
#include "include/scores.h"
#include <cstdlib>
#include <ctime>
#include <QTimer>
#include "include/onwindialog.h"
#include "include/aboutdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum Position {HIDDEN = 0, TOP, BOTTOM, LEFT, RIGHT};
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void buttonClicked(int);

public slots:
    void newGrid(int difficulty);
    void setKeyPadPosition(int position);
    void incrementChrono();
    void gameEnded();
    void showScores();
    void showAboutDialog();

private:
    int minutes, seconds;
    Ui::MainWindow *ui;
    QGridLayout * gridLayout;
    SudokuPreview preview;
    SudokuModel model;
    KeyPad keypad;
    Position keyPadPosition;
    QLabel * difficultyLabel;
    QLabel * chronoLabel;
    QTimer * timer;
    ScoreStorage::Difficulty currentDifficulty;

    QSignalMapper * difficultyMapper();
    QSignalMapper * keyPadPositionMapper();
    void loadNewGrid(QString fileName);
    void initializeChrono();
    void keyReleaseEvent(QKeyEvent * event);
};

#endif // MAINWINDOW_H
