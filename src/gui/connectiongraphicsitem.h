#ifndef CONNECTIONGRAPHICSITEM_H
#define CONNECTIONGRAPHICSITEM_H

#include "blockgraphicitem.h"

class ConnectionGraphicsItem : public QGraphicsItem
{
public:
    ConnectionGraphicsItem(BlockGraphicItem *blockA, BlockGraphicItem *blockB);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    BlockGraphicItem *blockA;
    BlockGraphicItem *blockB;

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
};

#endif // CONNECTIONGRAPHICSITEM_H
