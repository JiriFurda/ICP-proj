#ifndef SCHEMESCENE_H
#define SCHEMESCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

class SchemeScene : public QGraphicsScene
{
public:
    SchemeScene();
    bool connectingBlocks;

/*
protected:
    //void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
*/
};

#endif // SCHEMESCENE_H
