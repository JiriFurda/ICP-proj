#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Other windows
#include "aboutdialog.h"
#include "creditsdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionAbout_BlockEditor_triggered();

    void on_actionCredits_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
