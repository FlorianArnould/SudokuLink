#include "include/mainwindow.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("BSSC");
    QCoreApplication::setOrganizationDomain("bssc.fr");
    QCoreApplication::setApplicationName("SudokuLink");
    QApplication a(argc, argv);
    a.setStyleSheet( "QStatusBar::item { border: 0px}" ) ;
    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    translator.load("sudoku_" + locale);
    a.installTranslator(&translator);
    MainWindow w;
    w.show();

    return a.exec();
}
