#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    keypad(this)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    srand(time(NULL));
    connect(difficultyMapper(), SIGNAL(mapped(int)), this, SLOT(newGrid(int)));
    //KeyPad
    QActionGroup * group = new QActionGroup(this);
    group->addAction(ui->actionNo_Key_Pad);
    group->addAction(ui->actionTop_Key_Pad);
    group->addAction(ui->actionLeft_KeyPad);
    group->addAction(ui->actionBottom_KeyPad);
    group->addAction(ui->actionRight_KeyPad);
    connect(keyPadPositionMapper(), SIGNAL(mapped(int)), this, SLOT(setKeyPadPosition(int)));
    setKeyPadPosition(HIDDEN);
    //Status Bar
    difficultyLabel = new QLabel(this);
    ui->statusBar->addWidget(difficultyLabel, 1);
    chronoLabel = new QLabel(this);
    chronoLabel->setAlignment(Qt::AlignRight);
    ui->statusBar->addWidget(chronoLabel, 1);
    connect(timer, SIGNAL(timeout()), this, SLOT(incrementChrono()));
    //Preview widget size and placement
    gridLayout = new QGridLayout(ui->centralWidget);
    gridLayout->addWidget(&preview, 1, 1);
    preview.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //Menu actions
    connect(&model, SIGNAL(finish()), this, SLOT(gameEnded()));
    connect(ui->actionShow_scores, SIGNAL(triggered(bool)), this, SLOT(showScores()));
    connect(ui->actionQuit, SIGNAL(triggered(bool)), this, SLOT(close()));
    connect(ui->actionAbout_SudokuLink, SIGNAL(triggered(bool)), this, SLOT(showAboutDialog()));
    connect(ui->actionAutomatic_help, SIGNAL(toggled(bool)), &model, SLOT(setHelp(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QSignalMapper * MainWindow::difficultyMapper()
{
    QSignalMapper * mapper = new QSignalMapper(this);
    QAction * tab[] = {ui->actionEasy, ui->actionMedium, ui->actionHard, ui->actionInsane};
    for(int i=0;i<4;i++){
        connect(tab[i], SIGNAL(triggered(bool)), mapper, SLOT(map()));
        mapper->setMapping(tab[i], i);
    }
    return mapper;
}

QSignalMapper * MainWindow::keyPadPositionMapper()
{
    QSignalMapper * mapper = new QSignalMapper(this);
    QAction * tab[] = {ui->actionNo_Key_Pad, ui->actionTop_Key_Pad, ui->actionBottom_KeyPad,
                       ui->actionLeft_KeyPad, ui->actionRight_KeyPad};
    for(int i=0;i<5;i++){
        connect(tab[i], SIGNAL(triggered(bool)), mapper, SLOT(map()));
        mapper->setMapping(tab[i], i);
    }
    return mapper;
}

void MainWindow::newGrid(int difficulty)
{
    currentDifficulty = (ScoreStorage::Difficulty)difficulty;
    switch(difficulty){
        case ScoreStorage::EASY:
            loadNewGrid(":/grids/Easy.txt");
            difficultyLabel->setText(tr("Easy"));
            break;
        case ScoreStorage::MEDIUM:
            loadNewGrid(":/grids/Medium.txt");
            difficultyLabel->setText(tr("Medium"));
            break;
        case ScoreStorage::HARD:
            loadNewGrid(":/grids/Hard.txt");
            difficultyLabel->setText(tr("Hard"));
            break;
        case ScoreStorage::INSANE:
            loadNewGrid(":/grids/Insane.txt");
            difficultyLabel->setText(tr("Insane"));
            break;
    }
    preview.setModel(&model);
    initializeChrono();
    connect(this, SIGNAL(buttonClicked(int)), &model, SLOT(setUserNumber(int)));
    connect(&keypad, SIGNAL(buttonClicked(int)), &model, SLOT(setUserNumber(int)));
}

void MainWindow::loadNewGrid(QString fileName)
{
    QFile file(fileName);
    file.open(QFile::ReadOnly);
    QTextStream in(&file);
    if(!file.isOpen()){
        qCritical() << tr("The grid file wasn't opened");
        return;
    }
    int max = in.readLine().toInt();
    int random = rand()%max;
    for(int i=0;i<random;i++){
        in.readLine();
    }
    QString line = in.readLine();
    file.close();
    QStringList stringList = line.split(" ");
    int numbers[9][9];
    for(int i=0; i<9;i++){
        for(int j=0;j<9;j++){
            QString string = stringList.at(i*9+j);
            numbers[i][j] = string.toInt();
        }
    }
    model.setNewGrid(numbers);
}

void MainWindow::setKeyPadPosition(int position)
{
    keypad.setVisible(true);
    switch(position){
        case HIDDEN:
            keypad.setVisible(false);
            break;
        case TOP:
            gridLayout->addWidget(&keypad, 0, 1);
            break;
        case BOTTOM:
            gridLayout->addWidget(&keypad, 2, 1);
            break;
        case LEFT:
            gridLayout->addWidget(&keypad, 1, 0);
            break;
        case RIGHT:
            gridLayout->addWidget(&keypad, 1, 2);
            break;
    }
}

void MainWindow::incrementChrono()
{
    timer->start(1000);
    seconds++;
    if(seconds == 60){
        seconds = 0;
        minutes++;
    }
    QString message = QString::number(minutes) + ":";
    if(seconds < 10){
        message += "0";
    }
    chronoLabel->setText(message + QString::number(seconds));
}

void MainWindow::initializeChrono()
{
    timer->stop();
    minutes = 0;
    seconds = 0;
    timer->start(1000);
    chronoLabel->setText("0:00");
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        model.moveUp();
        break;
    case Qt::Key_Down:
        model.moveDown();
        break;
    case Qt::Key_Left:
        model.moveLeft();
        break;
    case Qt::Key_Right:
        model.moveRight();
        break;
    case Qt::Key_1:
        emit buttonClicked(1);
        break;
    case Qt::Key_2:
        emit buttonClicked(2);
        break;
    case Qt::Key_3:
        emit buttonClicked(3);
        break;
    case Qt::Key_4:
        emit buttonClicked(4);
        break;
    case Qt::Key_5:
        emit buttonClicked(5);
        break;
    case Qt::Key_6:
        emit buttonClicked(6);
        break;
    case Qt::Key_7:
        emit buttonClicked(7);
        break;
    case Qt::Key_8:
        emit buttonClicked(8);
        break;
    case Qt::Key_9:
        emit buttonClicked(9);
        break;
    case Qt::Key_Delete:
    case Qt::Key_Backspace:
        emit buttonClicked(KeyPad::Button_Clear);
        break;
    default:
        return;
    }
    event->accept();
}

void MainWindow::gameEnded()
{
    disconnect(this, SIGNAL(buttonClicked(int)), &model, SLOT(setUserNumber(int)));
    disconnect(this, SIGNAL(buttonClicked(int)), &model, SLOT(setUserNumber(int)));
    timer->stop();
    OnWinDialog dialog(minutes, seconds, this);
    if(dialog.exec() == QDialog::Accepted){
        ScoreStorage::saveScore(ScoreStorage::Score(dialog.getName(), minutes, seconds, model.wasHelpActivated()), currentDifficulty);
    }
}

void MainWindow::showScores()
{
    ScoreDialog(this).exec();
}

void MainWindow::showAboutDialog()
{
    AboutDialog(this).exec();
}
