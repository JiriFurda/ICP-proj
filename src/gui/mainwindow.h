#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtWidgets>

// Other windows
#include "aboutdialog.h"
#include "creditsdialog.h"
#include "addblockdialog.h"

#include "blockgraphicitem.h"

//#include "schemeview.h"

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

    void on_actionAdd_triggered();

    void on_actionExit_triggered();

public slots:
    void createBlock(QString);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
};

#endif // MAINWINDOW_H
