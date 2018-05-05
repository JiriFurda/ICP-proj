#ifndef CONNECTIONLINEITEM_H
#define CONNECTIONLINEITEM_H

#include <QGraphicsLineItem>
#include <QGraphicsSceneHoverEvent>
#include <QToolTip>

#include <gui/blockgraphicitem.h>

#include <blocks/port.h>

class BlockGraphicItem; // Forward declaration beacuse of mutual including of connectionlineitem.h and blockgraphicitem.h


class ConnectionLineItem : public QGraphicsLineItem
{
public:
    ConnectionLineItem(QGraphicsScene *scene, BlockGraphicItem *blockA, BlockGraphicItem *blockB, Port *portA, Port *portB);
    ~ConnectionLineItem();

    void refreshPos();
    bool containsPort(Port *searched);

    QGraphicsLineItem *visibleLine;

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

private:
    BlockGraphicItem *blockA;
    BlockGraphicItem *blockB;
    Port *backendPortA;
    Port *backendPortB;

    void showToolTip(QGraphicsSceneHoverEvent *event);
};

#endif // CONNECTIONLINEITEM_H
