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


    // --- Debug ---
    /*
    BlockGraphicItem *blockA = new BlockGraphicItem(scene, QString("A"));
    BlockGraphicItem *blockB = new BlockGraphicItem(scene, QString("B"));
    scene->addItem(blockA);
    scene->addItem(blockB);
    blockA->moveBy(150,50);
*/
    //ConnectionLineItem *line = new ConnectionLineItem(blockA, blockB);
    //scene->addItem(line);

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
    scene->addItem(new BlockGraphicItem(scene, name));
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
