/*
 * @todo Moving block should also be here not in schemeview
 * @todo Moving block fucks up context menu
 */

#include "blockwidget.h"
#include "ui_blockwidget.h"

BlockWidget::BlockWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlockWidget)
{
    ui->setupUi(this);

    resize(256,256);

    // --- Image ---
    QLabel *block = new QLabel(this);
    block->setPixmap(QPixmap(":/block/img/blocks/block.png"));
    block->show();
    block->setAttribute(Qt::WA_DeleteOnClose);


    // --- Right click menu ---
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(showContextMenu(const QPoint&)));
}

BlockWidget::~BlockWidget()
{
    delete ui;
}

void BlockWidget::showContextMenu(const QPoint& pos)
{
    QPoint globalPos = this->mapToGlobal(pos);  // Position where to show menu
    // for QAbstractScrollArea and derived classes you would use:
    // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);

    // --- Context menu ---
    QMenu *menu = new QMenu();
    menu->addAction("Remove block");

    // -- Input ports submenu --
    QMenu *inputMenu = menu->addMenu("Connect input port");
    inputMenu->addAction("Operand 1 [float]");
    inputMenu->addAction("Operand 2 [float]");

    // -- Output ports submenu --
    QMenu *outputMenu = menu->addMenu("Connect output port");
    outputMenu->addAction("Result [float]");

    // -- Selected item --
    QAction* selectedItem = menu->exec(globalPos);
    if (selectedItem)
    {
        // something was chosen, do stuff
    }
    else
    {
        // nothing was chosen
    }
}
