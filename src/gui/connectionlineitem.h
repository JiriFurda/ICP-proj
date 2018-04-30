#ifndef CONNECTIONLINEITEM_H
#define CONNECTIONLINEITEM_H

#include <QGraphicsLineItem>
#include <QGraphicsSceneHoverEvent>
#include <QToolTip>

#include <blockgraphicitem.h>

class ConnectionLineItem : public QGraphicsLineItem
{
public:
    ConnectionLineItem(BlockGraphicItem *blockA, BlockGraphicItem *blockB);
    void refreshPos();

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

private:
    BlockGraphicItem *blockA;
    BlockGraphicItem *blockB;
};

#endif // CONNECTIONLINEITEM_H
