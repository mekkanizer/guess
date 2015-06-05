#-------------------------------------------------
#
# Project created by QtCreator 2015-05-21T16:06:18
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = guess
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    question.cpp \
    database.cpp

HEADERS  += mainwindow.h \
    question.h \
    database.h

FORMS    += mainwindow.ui \
    question.ui
