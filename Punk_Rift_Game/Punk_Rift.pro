#-------------------------------------------------
#
# Project created by QtCreator 2017-01-24T02:14:28
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Punk_Rift
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    logo.cpp \
    levelone.cpp \
    backgrounditem.cpp \
    player.cpp \
    platform.cpp \
    leveltwo.cpp \
    levelthree.cpp \
    optionswindow.cpp \
    levelfour.cpp \
    levelfive.cpp \
    ground.cpp \
    aboutdialog.cpp

HEADERS  += mainwindow.h \
    logo.h \
    levelone.h \
    backgrounditem.h \
    player.h \
    platform.h \
    leveltwo.h \
    levelthree.h \
    optionswindow.h \
    levelfour.h \
    levelfive.h \
    ground.h \
    aboutdialog.h

FORMS    += \
    optionswindow.ui \
    mainwindow.ui \
    aboutdialog.ui

RESOURCES += \
    punk_rift.qrc \
    punk_rift_music.qrc \
    punk_rift_backgrounds.qrc
