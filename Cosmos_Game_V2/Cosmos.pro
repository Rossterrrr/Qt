#-------------------------------------------------
#
# Project created by QtCreator 2017-02-21T06:17:47
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Cosmos
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
    ground.cpp \
    levelfive.cpp \
    levelfour.cpp \
    levelone.cpp \
    levelthree.cpp \
    leveltwo.cpp \
    logo.cpp \
    platform.cpp \
    player.cpp \
    backgrounditem.cpp \
    aboutdialog.cpp \
    parallaxlayerone.cpp \
    alien.cpp \
    path.cpp \
    bullet.cpp

HEADERS  += mainwindow.h \
    ground.h \
    levelfive.h \
    levelfour.h \
    levelone.h \
    levelthree.h \
    leveltwo.h \
    logo.h \
    platform.h \
    player.h \
    backgrounditem.h \
    aboutdialog.h \
    parallaxlayerone.h \
    alien.h \
    objecttype.h \
    path.h \
    bullet.h

FORMS    += mainwindow.ui \
    aboutdialog.ui

RESOURCES += \
    cosmos_images.qrc \
    cosmos_music.qrc \
    audio_level_one.qrc
