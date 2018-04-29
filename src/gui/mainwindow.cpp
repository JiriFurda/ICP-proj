#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //this->showFullScreen();

    // === Scheme view ===
    QGraphicsView *view = new QGraphicsView(this);
    this->centralWidget()->layout()->addWidget(view);

    scene = new QGraphicsScene(this);
    view->setScene(scene);
//    view->centerOn(0, 0);
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

void MainWindow::createBlock(QString name)  // @todo Rename to on_addBlock_requested (don't know why the fuck it's not working rename) -> QMetaObject::connectSlotsByName: No matching signal for on_addBlock_requested(QString)
{
    scene->addItem(new BlockGraphicItem(name));
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}
