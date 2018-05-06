/**
 * Graphics item representing connection between ports.
 * @brief Header file for ConnectionLineItem
 * @file connectionlineitem.h
 * @author Jiri Furda (xfurda00)
 */

#ifndef CONNECTIONLINEITEM_H
#define CONNECTIONLINEITEM_H

// === Includes ===
// Qt libraries
#include <QGraphicsLineItem>
#include <QGraphicsSceneHoverEvent>
#include <QToolTip>

// GUI headers
#include <gui/blockgraphicitem.h>

// Backend headers
#include <blocks/port.h>


// === Forward declarations ===
class BlockGraphicItem;


/**
 * @brief The ConnectionLineItem class is graphics item based on QGraphicsLineItem representing connection between ports.
 * It is composited from two lines. The main one is bigger and is invisible but it handles mouse and hover actions.
 * When right-clicked on this line, user is able to delete this connection. When hovered on this line, actual values
 * stored in this connection are shown.
 * The secondary is the visible one.
 */
class ConnectionLineItem : public QGraphicsLineItem
{
public:
    /**
     * @brief Constructor of this class.
     * @param scene Pointer to parent scene where this connection is shown.
     * @param blockA    Pointer to GUI Block class on one side of the connection.
     * @param blockB    Pointer to GUI Block class on other side of the connection.
     * @param portA Pointer to backend Port class on one side of the connection.
     * @param portB Pointer to backend Port class on other side of the connection.
     */
    ConnectionLineItem(QGraphicsScene *scene, BlockGraphicItem *blockA, BlockGraphicItem *blockB, Port *portA, Port *portB);

    ~ConnectionLineItem();  /// @brief Destructor of this class.

    void refreshPos();  /// @brief refreshPos is method used to recalculate starting and ending point of the lines

    /**
     * @brief containsPort is method used to search if particular backend Port object is used in this connection
     * @param searched backend Port object that is searched
     * @return true when backend Port object is found, false when not
     */
    bool containsPort(Port *searched);

    /**
     * @brief visibleLine is pointer to secondary line of this connection that is visible on the scene.
     */
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
