#ifndef BLOCKGRAPHICITEM_H
#define BLOCKGRAPHICITEM_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>


class BlockGraphicItem : public QGraphicsItem
{
public:
    BlockGraphicItem();

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

    bool pressed;
};

#endif // BLOCKGRAPHICITEM_H
