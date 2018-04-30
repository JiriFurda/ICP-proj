#include "schemescene.h"

SchemeScene::SchemeScene()
{
    this->connectingBlocks = false;

    //this->addLine(QLineF(QPointF(0, 0), QPointF(10, 10)));

}

/*
void SchemeScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    static QGraphicsLineItem *temporaryLine;
    delete temporaryLine;

    temporaryLine = this->addLine(QLineF(QPointF(0, 0), event->scenePos()));

    QGraphicsScene::mouseMoveEvent(event);
}
*/
