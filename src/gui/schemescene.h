#ifndef SCHEMESCENE_H
#define SCHEMESCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QMessageBox>

//#include "blockgraphicitem.h";
#include "blocks/port.h"

class BlockGraphicItem;
class ConnectionLineItem;

class SchemeScene : public QGraphicsScene
{
public:
    SchemeScene();

    void startConnectingBlocks(BlockGraphicItem *startingBlock, Port *startingPort);

    bool isConnectingBlocks;  // Is user connecting blocks?
    BlockGraphicItem *connecting_startingBlock;
    Port *connecting_startingPort;
    ConnectionLineItem *connecting_temporaryLine;
    bool connecting_temporaryLine_exists;
    void exitConnectingBlocks();

    BlockGraphicItem *highlightedBlock;
};

#endif // SCHEMESCENE_H
