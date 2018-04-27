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
    schemeview.cpp

HEADERS  += mainwindow.h \
    aboutdialog.h \
    creditsdialog.h \
    schemeview.h

FORMS    += mainwindow.ui \
    aboutdialog.ui \
    creditsdialog.ui \
    schemeview.ui

RESOURCES += \
    imagesresource.qrc
