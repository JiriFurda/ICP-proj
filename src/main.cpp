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

/*! \mainpage BlockEdior
 *
 * \section intro_sec Introduction
 *
 * BlockEditor by All Nighter Bros was developed as school project
 * for subject IPP at FIT VUT Brno.\n It allows user to design their
 * own block scheme and execute it.\n
 * This project is developed in C++ and it is using Qt for GUI.
 *
 * \section author_sec Authors (All Nighter Bros)
 *
 * Jiri Furda (xfurda00)\n
 * Peter Havan (xhavan00)
 */
