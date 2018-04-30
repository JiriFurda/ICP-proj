#ifndef BLOCKGRAPHICITEM_H
#define BLOCKGRAPHICITEM_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QList>

#include "schemescene.h"
//#include "connectionlineitem.h"


class BlockGraphicItem : public QGraphicsItem
{
public:
    BlockGraphicItem(SchemeScene *scene, QString name);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    //QList<ConnectionLineItem *> connections;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    bool isMoving;
    bool isPressed;
    QString name;

private:
    SchemeScene *parentScene;

    void on_moving_started();
    void on_moving_ended();
};

#endif // BLOCKGRAPHICITEM_H
