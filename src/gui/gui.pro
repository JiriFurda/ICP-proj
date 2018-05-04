#-------------------------------------------------
#
# Project created by QtCreator 2018-04-26T15:15:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    aboutdialog.cpp \
    creditsdialog.cpp \
    blockgraphicitem.cpp \
    addblockdialog.cpp \
    schemescene.cpp \
    connectionlineitem.cpp

HEADERS  += mainwindow.h \
    aboutdialog.h \
    creditsdialog.h \
    blockgraphicitem.h \
    addblockdialog.h \
    schemescene.h \
    connectionlineitem.h

FORMS    += mainwindow.ui \
    aboutdialog.ui \
    creditsdialog.ui

RESOURCES += \
    imagesresource.qrc

CONFIG += c++11 # Overriding functions