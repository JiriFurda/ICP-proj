#include "connectionlineitem.h"

ConnectionLineItem::ConnectionLineItem(BlockGraphicItem *blockA, BlockGraphicItem *blockB)
{
    // --- Settings ---
    this->setAcceptHoverEvents(true);
    this->setZValue(-1);    // Drawn behind blocks
    this->setPen(QPen(Qt::black, 2));

    // --- Fill attributes ---
    this->blockA = blockA;
    this->blockB = blockB;

    // --- Link blocks to this ---
    // (Used for moving with objects etc)
    /*
    blockA->connections.append(this);
    blockB->connections.append(this);
    */

    // --- Prepare to draw ---
    this->refreshPos();
}

void ConnectionLineItem::refreshPos()
{
    QPointF centerOffset = this->blockA->boundingRect().topLeft() - this->blockA->boundingRect().center(); // Offset from topLeft (0x0) pixel to center of block

    this->setLine(QLineF(this->blockA->scenePos() - centerOffset, this->blockB->scenePos() - centerOffset));
}

void ConnectionLineItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QToolTip::showText(event->screenPos(),QString("[float] 42.0"));

    QGraphicsLineItem::hoverEnterEvent(event);
}
