#include "schemescene.h"

SchemeScene::SchemeScene()
{
    this->isConnectingBlocks = false;
    this->connecting_temporaryLine_exists = false;

    this->highlightedBlock = NULL;
}

void SchemeScene::startConnectingBlocks(BlockGraphicItem *startingBlock, Port *startingPort)
{
    this->isConnectingBlocks = true;
    this->connecting_startingPort = startingPort;
    this->connecting_startingBlock = startingBlock;
}
