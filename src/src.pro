#-------------------------------------------------
#
# Project created by QtCreator 2018-05-04T00:45:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = blockeditor
TEMPLATE = app
CONFIG += c++11


SOURCES += main.cpp\
    gui/mainwindow.cpp \
    gui/schemescene.cpp \
    gui/aboutdialog.cpp \
    gui/addblockdialog.cpp \
    gui/blockgraphicitem.cpp \
    gui/connectionlineitem.cpp \
    gui/creditsdialog.cpp \
    blocks/block.cpp \
    blocks/blockArithmetic.cpp \
    blocks/blockLogic.cpp \
    blocks/port.cpp \
    blocks/scheme.cpp

HEADERS  += gui/mainwindow.h \
    gui/schemescene.h \
    gui/aboutdialog.h \
    gui/addblockdialog.h \
    gui/blockgraphicitem.h \
    gui/connectionlineitem.h \
    gui/creditsdialog.h \
    blocks/block.h \
    blocks/blockArithmetic.h \
    blocks/blockLogic.h \
    blocks/port.h \
    blocks/scheme.h

FORMS    += gui/mainwindow.ui \
			gui/aboutdialog.ui \
			gui/creditsdialog.ui

RESOURCES += \
    gui/imagesresource.qrc
