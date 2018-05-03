#ifndef CONNECTIONLINEITEM_H
#define CONNECTIONLINEITEM_H

#include <QGraphicsLineItem>
#include <QGraphicsSceneHoverEvent>
#include <QToolTip>

#include <gui/blockgraphicitem.h>

class BlockGraphicItem; // Forward declaration beacuse of mutual including of connectionlineitem.h and blockgraphicitem.h


class ConnectionLineItem : public QGraphicsLineItem
{
public:
    ConnectionLineItem(QGraphicsScene *scene, BlockGraphicItem *blockA, BlockGraphicItem *blockB);
    ~ConnectionLineItem();

    void refreshPos();

    QGraphicsLineItem *visibleLine;

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

private:
    BlockGraphicItem *blockA;
    BlockGraphicItem *blockB;
};

#endif // CONNECTIONLINEITEM_H
