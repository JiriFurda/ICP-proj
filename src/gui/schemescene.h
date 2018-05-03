#ifndef SCHEMESCENE_H
#define SCHEMESCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

//#include "blockgraphicitem.h";

class BlockGraphicItem;
class ConnectionLineItem;

class SchemeScene : public QGraphicsScene
{
public:
    SchemeScene();

    bool isConnectingBlocks;  // Is user connecting blocks?
    BlockGraphicItem *connecting_startingBlock;
    ConnectionLineItem *connecting_temporaryLine;
    bool connecting_temporaryLine_exists;
};

#endif // SCHEMESCENE_H
