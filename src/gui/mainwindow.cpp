#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // === Scheme view ===
    QGraphicsView *view = new QGraphicsView(this);
    this->centralWidget()->layout()->addWidget(view);

    scene = new QGraphicsScene(this);
    view->setScene(scene);

    // --- Blocks ---
    /*
    QGraphicsRectItem* item1 = new QGraphicsRectItem(0,0,100,100);
    item1->setBrush(QBrush(Qt::white));
    item1->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(item1);
    */
    //scene->addItem(new BlockGraphicItem("Add"));
    this->createBlock("Default");

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
    scene->addItem(new BlockGraphicItem(name)); // This doesn't work
}

void MainWindow::debug()
{
    scene->addItem(new BlockGraphicItem("Debug"));  // This works
}

