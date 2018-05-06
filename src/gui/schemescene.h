/**
 * Graphics scene representing scheme.
 * @brief Header file for SchemeScene
 * @file schemescene.h
 * @author Jiri Furda (xfurda00)
 */

#ifndef SCHEMESCENE_H
#define SCHEMESCENE_H


// === Includes ===
// Qt libraries
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QMessageBox>

// Backend headers
#include "blocks/port.h"


// === Forward declaration ===
class BlockGraphicItem;
class ConnectionLineItem;



/**
 * @brief The SchemeScene class is graphics scene based on QGraphicsScene displaying scheme.
 */
class SchemeScene : public QGraphicsScene
{
public:
    SchemeScene();  /// @brief Constructor of this class.

    /**
     * @brief startConnectingBlocks is method used to switch editor's edit mode to connecting mode.
     * Then user can't start connecting from new port and when user hovers on other block, dotted
     * line indicating new connection is drawn and when user left-clicks on the block, menu for
     * selecting port that new connection is going to be connected to is shown.
     * @param startingBlock Pointer to GUI block from which is new connection going to be.
     * @param startingPort  Pointer to backend Port from whick is new connection going to be.
     */
    void startConnectingBlocks(BlockGraphicItem *startingBlock, Port *startingPort);

    bool isConnectingBlocks;  /// @brief Bool value indicating if connecting mode is activated or not
    BlockGraphicItem *connecting_startingBlock; /// @brief Pointer to GUI block from which is new connection going to be.
    Port *connecting_startingPort;  /// @brief Pointer to backend Port from whick is new connection going to be.
    ConnectionLineItem *connecting_temporaryLine;   /// @brief Poitner to new GUI connection line indicator.
    bool connecting_temporaryLine_exists;   /// @brief Bool value indicating if new GUI connection line indicator exists.
    void exitConnectingBlocks();    /// @brief Method switching from connecting mode back to edit mode.

    BlockGraphicItem *highlightedBlock; /// @brief Pointer to GUI block that is highlighted.
};

#endif // SCHEMESCENE_H
