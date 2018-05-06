/**
 * Main window of the application.
 * @brief Source file for MainWindow
 * @file mainwindow.c
 * @author Jiri Furda (xfurda00)
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->showMaximized();

    // === Scheme view ===
    QGraphicsView *view = new QGraphicsView(this);
    view->setRenderHint(QPainter::Antialiasing);
    this->centralWidget()->layout()->addWidget(view);

    scene = new SchemeScene();
    view->setScene(scene);

    // --- Backend ---
    this->backendScheme = new Scheme("Test Scheme");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_BlockEditor_triggered()
{
    AboutDialog dialog;
    dialog.setModal(true);  // Can't click on other window
    dialog.exec();
}

void MainWindow::on_actionCredits_triggered()
{
    CreditsDialog dialog;
    dialog.setModal(true);
    dialog.exec();
}

void MainWindow::on_actionAdd_triggered()
{
    AddBlockDialog dialog(this);
    dialog.setModal(true);
    dialog.exec();
}

void MainWindow::createBlock(QString name)
{
    Block *block;

    if(name == "Add")
        block = new BlockAdd();
    else if(name == "Sub")
        block = new BlockSub();
    else if(name == "Mul")
        block = new BlockMul();
    else if(name == "Div")
        block = new BlockDiv();
    else if(name == "CxAdd")
        block = new BlockCxAdd();
    else if(name == "CxSub")
        block = new BlockCxSub();
    else if(name == "CxMul")
        block = new BlockCxMul();
    else if(name == "CxDiv")
        block = new BlockCxDiv();
    //else if(name == "Not")
    //    block = new BlockNot();
    else if(name == "And")
        block = new BlockAnd();
    else if(name == "Or")
        block = new BlockOr();
    else if(name == "Xor")
        block = new BlockXor();
    else
    {
        QMessageBox::critical(this, "Error creating block", "Unexpect name received when creating block");
        return;
    }

    new BlockGraphicItem(this->scene, name, block);
    this->backendScheme->addBlock(block);   // @todo Temporary, should be in SchemeScene

}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    if (QMessageBox::Yes == QMessageBox::question(this, "Quit application", "Do you really want to quit this application?", QMessageBox::Yes | QMessageBox::No))
    {
        event->accept();
    }
}

void MainWindow::on_actionSave_File_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save scheme to file"), "",
        tr("Block scheme (*.scheme);;All Files (*)"));
}

void MainWindow::on_actionOpen_File_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open scheme from file"), "",
        tr("Block scheme (*.scheme);;All Files (*)"));
}

void MainWindow::on_actionNew_File_triggered()
{
    scene->clear();
}

void MainWindow::on_actionRun_triggered()
{
    this->backendScheme->run();
}

void MainWindow::on_actionStep_triggered()
{
    this->backendScheme->runStep(true);
}

void MainWindow::on_actionExit_connection_mode_triggered()
{
    this->scene->exitConnectingBlocks();
}
