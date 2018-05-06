/**
 * Graphics item representing block.
 * @brief Header file for BlockGraphicItem
 * @file blockgraphicitem.h
 * @author Jiri Furda (xfurda00)
 */

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

// --- Forward delcations ---
class ConnectionLineItem;


/**
 * @brief BlockGraphicItem is graphics item based on QGraphicsItem representing block.
 * Block has its name based on type of the block. It is movable around the scene.
 * When clicked with left mouse button, blocks show values of its ports.
 * When clicked with right mouse button, user is able to delete this block or
 * connect this block's port to other ports.
 */
class BlockGraphicItem : public QGraphicsItem
{
public:
    /**
     * @brief Constructor of this class.
     * @param scene Pointer to parent scene where block is shown.
     * @param name  Text showing type of the block.
     * @param backendObject Pointer to backend Block object represeting this block.
     */
    BlockGraphicItem(SchemeScene *scene, QString name, Block *backendObject);
    ~BlockGraphicItem();    /// Destructor of this class

    /**
     * @brief boundingRect is method returning rectangle bounding this block in scene.
     * @return Rectangle bounding this block in scene.
     */
    QRectF boundingRect() const;

    /**
     * @brief paint is method called everytime this block is rendered on screen.
     * @param painter   Pointer to QPainter used to paint this block.
     * @param option    Options for the item (state, LoD etc.)
     * @param widget    Pointer to widget that is this block painted on.
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /**
     * @brief connections is QList containing pointers to ConnectionLineItem objects
     * connected to this block.
     */
    QList<ConnectionLineItem *> connections;

    /**
     * @brief highlight is method used to change color of this block to highlight it.
     * It is called from backend Scheme class when execution process is running.
     * Highlighting new block also unhiglight previusly highlighted block.
     */
    void highlight();

    /**
     * @brief unhighlight is method used to reset color of this block to default.
     * It is called from backend Scheme class when execution process is running.
     */
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
