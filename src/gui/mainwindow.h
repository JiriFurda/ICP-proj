#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtWidgets>

// Other windows
#include "aboutdialog.h"
#include "creditsdialog.h"
#include "addblockdialog.h"

#include "gui/schemescene.h"
#include "gui/blockgraphicitem.h"
#include "gui/connectionlineitem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_actionAbout_BlockEditor_triggered();
    void on_actionCredits_triggered();

    void on_actionAdd_triggered();

    void on_actionExit_triggered();

    void on_actionSave_File_triggered();

    void on_actionOpen_File_triggered();

    void on_actionNew_File_triggered();

public slots:
    void createBlock(QString);

private:
    Ui::MainWindow *ui;
    SchemeScene *scene;
};

#endif // MAINWINDOW_H
