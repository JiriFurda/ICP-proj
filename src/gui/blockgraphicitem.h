#ifndef BLOCKGRAPHICITEM_H
#define BLOCKGRAPHICITEM_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QList>
#include <QMessageBox>

#include "gui/schemescene.h"
#include "gui/connectionlineitem.h"

#include "blocks/block.h"
#include "blocks/port.h"

class ConnectionLineItem; // Forward declaration beacuse of mutual including of connectionlineitem.h and blockgraphicitem.h


class BlockGraphicItem : public QGraphicsItem
{
public:
    BlockGraphicItem(SchemeScene *scene, QString name, Block *backendObject);
    ~BlockGraphicItem();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QList<ConnectionLineItem *> connections;

    void highlight();
    void unhighlight();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    SchemeScene *parentScene;

    void on_moving_started();
    void on_moving_ended();
    void on_connectingToThisBlock(QGraphicsSceneMouseEvent *event);

    void showToolTip(QGraphicsSceneMouseEvent *event);

    bool isMoving;
    bool isPressed;
    bool isHighlighted;
    QString name;
    Block *backendObject;
};

#endif // BLOCKGRAPHICITEM_H
