#-------------------------------------------------
#
# Project created by QtCreator 2017-01-17T21:51:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GenomeAntivirus
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logoanimation.cpp \
    aboutdialog.cpp \
    thread.cpp

HEADERS  += mainwindow.h \
    logoanimation.h \
    aboutdialog.h \
    thread.h

FORMS    += mainwindow.ui \
    aboutdialog.ui

RESOURCES += \
    genome.qrc
