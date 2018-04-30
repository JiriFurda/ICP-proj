#include "connectiongraphicsitem.h"

ConnectionGraphicsItem::ConnectionGraphicsItem(BlockGraphicItem *blockA, BlockGraphicItem *blockB)
{
    //this->addLine(QLineF(QPointF(0, 0), QPointF(10, 10)));

    this->blockA = blockA;
    this->blockB = blockB;
}

QRectF ConnectionGraphicsItem::boundingRect() const
{
    return QRectF(0,0,100,100); // @todo
}

void ConnectionGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // --- Painter settings ---
    painter->setRenderHint(QPainter::Antialiasing); // Enable antialiasing
    painter->setPen(QPen(Qt::black, 2));    // 2px black border

    QPointF centerOffset = this->blockA->boundingRect().topLeft() - this->blockA->boundingRect().center(); // Offset from topLeft (0x0) pixel to center of block

    painter->drawLine(this->blockA->scenePos() - centerOffset, this->blockB->scenePos() - centerOffset);
}


void ConnectionGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    qDebug("connection hover"); // not working
}
