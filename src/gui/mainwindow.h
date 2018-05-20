/**
 * Main window of the application.
 * @brief Header file for MainWindow
 * @file mainwindow.h
 * @author Jiri Furda (xfurda00)
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

// Dialog headers
#include "aboutdialog.h"
#include "creditsdialog.h"
#include "addblockdialog.h"

// GUI headers
#include "gui/schemescene.h"
#include "gui/blockgraphicitem.h"
#include "gui/connectionlineitem.h"

// Backend headers
#include "blocks/scheme.h"

namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class is main window of the application based on QMainWindow.
 * It contains buttons for most of actions available and it contains scheme view scene.
 * It also handles creating GUI blocks.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructor of this class.
     * @param parent Pointer to parent widget with default value 0.
     */
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();  /// @brief Destructor of this class.

    Scheme *backendScheme;  /// @brief Pointer to backend class Scheme corresponding to opened scheme and its scene.

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
    void on_actionRun_triggered();
    void on_actionStep_triggered();
    void on_actionExit_connection_mode_triggered();
    void on_actionRename_file_triggered();

    void on_actionRevert_triggered();

public slots:
    /**
     * @brief createBlock is slot used to create new block on the scheme.
     * @param QString determining type of new block.
     */
    void createBlock(QString);

private:
    Ui::MainWindow *ui;
    SchemeScene *scene;


};

#endif // MAINWINDOW_H
