#include "schemeview.h"
#include "ui_schemeview.h"

SchemeView::SchemeView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SchemeView)
{
    ui->setupUi(this);

    // --- Settings ---
    setMinimumSize(400, 400);
    setAcceptDrops(true);


    // --- Background ---
    QPalette backgroundPalette;
    backgroundPalette.setColor(QPalette::Window, QColor(50,50,50));
    setPalette(backgroundPalette);
    setAutoFillBackground(true);


    // --- Border ---
    // @todo Change QWidget to QFrame


    // --- Scrollbars ---
    // @todo
    /*
    QScrollArea *scrollArea;
    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(this);
    */


    // --- Test block ---
    QLabel *block = new QLabel(this);
    block->setPixmap(QPixmap(":/block/img/blocks/block.png"));
    block->move(10, 10);
    block->show();
    block->setAttribute(Qt::WA_DeleteOnClose);
}

SchemeView::~SchemeView()
{
    delete ui;
}

void SchemeView::mousePressEvent(QMouseEvent *event)
{
    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if (!child)
        return;

    QPixmap pixmap = *child->pixmap();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPoint(event->pos() - child->pos());

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos() - child->pos());

    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    painter.end();

    child->setPixmap(tempPixmap);

    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
        child->close();
    } else {
        child->show();
        child->setPixmap(pixmap);
    }
}

void SchemeView::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;

        QLabel *newIcon = new QLabel(this);
        newIcon->setPixmap(pixmap);
        newIcon->move(event->pos() - offset);
        newIcon->show();
        newIcon->setAttribute(Qt::WA_DeleteOnClose);



        if (event->source() == this)    // Dropped inside widget
        {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        }
        else    // Dropped outside widget
        {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void SchemeView::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void SchemeView::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}
