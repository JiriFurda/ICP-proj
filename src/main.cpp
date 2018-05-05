/**
 * Main class creating main window of the application.
 * @brief Generated source file for main
 * @file main.cpp
 * @author Jiri Furda (xfurda00)
 */

#include "gui/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
