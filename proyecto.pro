#-------------------------------------------------
#
# Project created by QtCreator 2013-06-05T17:47:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = proyecto
TEMPLATE = app


SOURCES += main.cpp\
        sudoku.cpp \
    ventanaprincipal.cpp \
    cargarsudoku.cpp \
    puntajes.cpp

HEADERS  += sudoku.h \
    ventanaprincipal.h \
    cargarsudoku.h \
    puntajes.h

FORMS    += sudoku.ui \
    ventanaprincipal.ui \
    cargarsudoku.ui \
    puntajes.ui

RESOURCES += \
    Image.qrc
