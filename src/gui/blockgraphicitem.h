#ifndef BLOCKGRAPHICITEM_H
#define BLOCKGRAPHICITEM_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>

#include "schemescene.h"


class BlockGraphicItem : public QGraphicsItem
{
public:
    BlockGraphicItem(SchemeScene *scene, QString name);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

    bool pressed;
    QString name;

private:
    SchemeScene *parentScene;
};

#endif // BLOCKGRAPHICITEM_H
