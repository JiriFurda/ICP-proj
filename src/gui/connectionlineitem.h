#ifndef CONNECTIONLINEITEM_H
#define CONNECTIONLINEITEM_H

#include <QGraphicsLineItem>
#include <QGraphicsSceneHoverEvent>
#include <QToolTip>

#include <blockgraphicitem.h>

class BlockGraphicItem; // Forward declaration beacuse of mutual including of connectionlineitem.h and blockgraphicitem.h


class ConnectionLineItem : public QGraphicsLineItem
{
public:
    ConnectionLineItem(BlockGraphicItem *blockA, BlockGraphicItem *blockB);
    ~ConnectionLineItem();

    void refreshPos();

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

private:
    BlockGraphicItem *blockA;
    BlockGraphicItem *blockB;
};

#endif // CONNECTIONLINEITEM_H
