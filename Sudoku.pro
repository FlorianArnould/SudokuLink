#-------------------------------------------------
#
# Project created by QtCreator 2017-03-14T15:36:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sudoku
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
        src/sudokupreview.cpp \
        src/keypad.cpp \
        src/case.cpp \
        src/sudokumodel.cpp \
    	src/scoredialog.cpp \
    	src/scores.cpp \
    	src/onwindialog.cpp \
    	src/aboutdialog.cpp

HEADERS += include/mainwindow.h \
        include/sudokupreview.h \
        include/keypad.h \
        include/case.h \
        include/sudokumodel.h \
    	include/scoredialog.h \
    	include/scores.h \
    	include/onwindialog.h \
    	include/aboutdialog.h

FORMS    += ui/mainwindow.ui \
    	ui/scoredialog.ui \
    	ui/onwindialog.ui \
    	ui/aboutdialog.ui

RESOURCES += resources/grids.qrc

TRANSLATIONS += translation/sudoku_en.ts \
             translation/sudoku_fr.ts

CONFIG += c++11

RC_FILE = resources/app.rc
