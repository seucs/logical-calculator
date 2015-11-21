#-------------------------------------------------
#
# Project created by QtCreator 2015-10-19T18:14:45
#
#-------------------------------------------------

QT       += core gui
QT       += axcontainer
QT       += multimedia

#


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

RC_FILE  += logo.rc
TARGET = LogicalCalculator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qm.cpp \
    iconhelper.cpp

HEADERS  += mainwindow.h \
    qm.h \
    iconhelper.h

FORMS    += mainwindow.ui
