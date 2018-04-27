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
    schemeview.cpp \
    blockwidget.cpp

HEADERS  += mainwindow.h \
    aboutdialog.h \
    creditsdialog.h \
    schemeview.h \
    blockwidget.h

FORMS    += mainwindow.ui \
    aboutdialog.ui \
    creditsdialog.ui \
    schemeview.ui \
    blockwidget.ui

RESOURCES += \
    imagesresource.qrc
