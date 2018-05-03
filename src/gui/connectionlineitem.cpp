#include "connectionlineitem.h"

ConnectionLineItem::ConnectionLineItem(QGraphicsScene *scene, BlockGraphicItem *blockA, BlockGraphicItem *blockB)
{
    // --- Settings ---
    this->setAcceptHoverEvents(true);
    this->setZValue(-1);    // Drawn behind blocks
    this->setPen(QPen(Qt::NoBrush, 30)); // Invisible line (Easier to click on)

    // --- Fill attributes ---
    this->blockA = blockA;
    this->blockB = blockB;

    // --- Link blocks to this ---
    // (Used for moving with objects etc)
    blockA->connections.append(this);
    blockB->connections.append(this);

    // --- Visible line ---
    this->visibleLine = scene->addLine(QLineF(0,0,0,0), QPen(Qt::black, 2));
    this->visibleLine->setZValue(-2);    // Drawn behind invisible line

    // --- Prepare to draw ---
    this->refreshPos();

    scene->addItem(this);
}

ConnectionLineItem::~ConnectionLineItem()
{
    // --- Remove links to this connection  ---
    this->scene()->removeItem(this->visibleLine);
    delete this->visibleLine;
    this->scene()->removeItem(this);
    blockA->connections.removeOne(this);
    blockB->connections.removeOne(this);
}


void ConnectionLineItem::refreshPos()
{
    QPointF centerOffset = this->blockA->boundingRect().topLeft() - this->blockA->boundingRect().center(); // Offset from topLeft (0x0) pixel to center of block

    QPointF start = this->blockA->scenePos() - centerOffset;
    QPointF end = this->blockB->scenePos() - centerOffset;

    this->setLine(QLineF(start, end));
    this->visibleLine->setLine(QLineF(start, end));
}


void ConnectionLineItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QToolTip::hideText();
    QToolTip::showText(event->screenPos(),QString("[float] 42.0 (Result -> Operand A)\n[float] 69.0 (Reuslt 2 -> Operand B"));

    QGraphicsLineItem::hoverEnterEvent(event);
}

void ConnectionLineItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if(!QToolTip::isVisible())
    {
        QToolTip::showText(event->screenPos(),QString("[float] 42.0 (Result -> Operand A)\n[float] 69.0 (Reuslt 2 -> Operand B"));
    }

    QGraphicsLineItem::hoverMoveEvent(event);
}

void ConnectionLineItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QToolTip::hideText();

    QGraphicsLineItem::hoverLeaveEvent(event);
}


void ConnectionLineItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    // --- Context menu ---
    QMenu *menu = new QMenu();
    QAction *removeAction = menu->addAction("Remove connection");
    QAction *selectedAction = menu->exec(event->screenPos());
    if(selectedAction)  // Some action was selected
    {
        if(selectedAction == removeAction)
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(0, QString("Delete connection"),
                QString("Do you really want to delete this connection?"),
                QMessageBox::Yes | QMessageBox::No);

             if(reply == QMessageBox::Yes)
                delete this;
             else
                 return;
        }
    }
}
/*
void ConnectionLineItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // --- Left Button ---
    if(event->button() == Qt::RightButton)   // Pressed left mouse button
    {

    }

    QGraphicsLineItem::mouseReleaseEvent(event);
}
*/
