#include "blockgraphicitem.h"

BlockGraphicItem::BlockGraphicItem(SchemeScene *scene, QString name, Block *backendObject)
{
    scene->addItem(this);

    // --- Settings ---
    this->setFlag(QGraphicsItem::ItemIsMovable);
    this->setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    this->setAcceptHoverEvents(true);
    this->setZValue(0);

    // --- Default values ---
    this->isMoving = false;
    this->isPressed = false;
    this->name = name;
    this->parentScene = scene;
    this->isHighlighted = false;

    // --- Backend ---
    this->backendObject = backendObject;
    backendObject->linkGUIobject(this);
    //this->parentScene->parent()->backendScheme->addBlock(backendObject);  // @todo Temporary in mainwindow

    // --- Move if stacked on other block ---
    if(this->collidingItems().count() > 0)  // If colliding with some item
    {
        for(int i=0; i<this->collidingItems().count(); ++i) // For every colliding item
        {
            if(this->collidingItems().at(i)->scenePos() == this->scenePos())    // Check if they are stacked on each other
            {
                this->moveBy(5,5);  // Move it
                i = -1; // Start over the check
            }
        }
    }
}

QRectF BlockGraphicItem::boundingRect() const
{
    return QRectF(0,0,100,100);
}

void BlockGraphicItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // --- Painter settings ---
    painter->setRenderHint(QPainter::Antialiasing); // Enable antialiasing
    painter->setPen(QPen(Qt::black, 2));    // 2px black border

    // --- Transparent when dragged ---
    if(this->isMoving == true)
        painter->setOpacity(0.7);
    else
        painter->setOpacity(1);

    // --- Highlight ---
    QBrush brush;
    if(this->isHighlighted)
        brush = Qt::yellow;
    else
        brush = Qt::white;

    // --- Image ---
    QPainterPath path;  // something like group??
    path.addRoundedRect(boundingRect(), 10, 10);
    painter->fillPath(path, brush);

    // --- Name ---
    painter->drawText(boundingRect(), Qt::AlignCenter|Qt::TextWrapAnywhere, this->name);   // @todo Choose if Qt::TextWrapAnywhere or Qt::TextWordWrap and if adding Qt::TextDontClip is a good idea

    // --- Draw result ---
    painter->drawPath(path);
}

void BlockGraphicItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // --- Left Button ---
    if(event->button() == Qt::LeftButton)   // Pressed left mouse button
        this->isPressed = true;

    // --- Propagate further ---
    QGraphicsItem::mousePressEvent(event);
}

void BlockGraphicItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // --- Left Button ---
    if(event->button() == Qt::LeftButton)   // Pressed left mouse button
    {
        this->isPressed = false;

        // -- Call events --
        if(this->isMoving)
            this->on_moving_ended();
        else
        {
            if(this->parentScene->isConnectingBlocks == true)
                this->on_connectingToThisBlock(event);
            else
                this->showToolTip(event); // Show port values
        }
    }

    // --- Propagate further ---
    QGraphicsItem::mouseReleaseEvent(event);  // Propagate further
}

void BlockGraphicItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    // --- Hide tooltip ---
    QToolTip::hideText();

    // --- Context menu ---
    QMenu *menu = new QMenu();
    QAction *removeAction = menu->addAction(QIcon(":/img/remove.png"),"Remove block");


    /* Not working! .contains(selectedAction) is always false
    // -- Input ports submenu --
    QMenu *inputMenu = menu->addMenu("Connect input port");
    QList<QAction *> connectInputActions;

    vector<Port> ports = this->backendObject->getInputPorts();
    for(vector<Port>::iterator port = ports.begin(); port != ports.end(); ++port)
    {
        connectInputActions.append(new QAction(inputMenu->addAction(port->print())));
    }


    // -- Output ports submenu --
    QMenu *outputMenu = menu->addMenu("Connect output port");
    QList<QAction *> connectOutputActions;

    ports = this->backendObject->getOutputPorts();
    for(vector<Port>::iterator port = ports.begin(); port != ports.end(); ++port)
    {
        QAction *action = new QAction(outputMenu->addAction(port->print()));
        qDebug(qUtf8Printable(action->text()));
        connectOutputActions.append(action);
    }
    */

    QMenu *inputMenu = new QMenu();
    QMenu *outputMenu = new QMenu();

    // --- Show connect option ---
    if(!this->parentScene->isConnectingBlocks)  // Only when not in connecting mode
    {
        inputMenu = menu->addMenu(QIcon(":/img/input.png"),"Connect input port");
        outputMenu  = menu->addMenu(QIcon(":/img/output.png"),"Connect output port");
    }

    // -- Input ports submenu --
    QAction *connectInput0Action(inputMenu->addAction(this->backendObject->getInputPort(0)->print()));
    QAction *connectInput1Action(inputMenu->addAction(this->backendObject->getInputPort(1)->print()));

    // -- Output ports submenu --
    QAction *connectOutput0Action(outputMenu->addAction(this->backendObject->getOutputPort(0)->print()));




    // -- Show menu --
    QAction *selectedAction = menu->exec(event->screenPos());

    /* @todo
    menu->popup(event->screenPos()); // Someone said this is better than exec because it does't block loop but whatever
    connect(menu, SIGNAL(triggered(QAction *)),
                 object, SLOT(triggered(QAction *)));
    */


    // --- Do action ---
    Port *selectedPort;
    if(selectedAction)  // Some action was selected
    {
        // --- Read selected action ---
        if(selectedAction == removeAction)
        {
            // --- Action delete ---
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(0, QString("Delete block"),
                QString("Do you really want to delete block \""+this->name+"\"?"),
                QMessageBox::Yes | QMessageBox::No);

             if(reply == QMessageBox::Yes)
                delete this;
            return;
        }
        // --- Action connect ---
        else if(selectedAction == connectInput0Action)
            selectedPort = this->backendObject->getInputPort(0);
        else if(selectedAction == connectInput1Action)
            selectedPort = this->backendObject->getInputPort(1);
        else if(selectedAction == connectOutput0Action)
            selectedPort = this->backendObject->getOutputPort(0);
        else
        {
            QMessageBox::critical(0, "Connecting port error", "Unexpected action selected");
            return;
        }


        // --- Action connect checks ---
        // -- Check occupied port --
        if(selectedPort->getConnectedPort() != NULL)
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(0, "Replace connection", "This port is already connect, do you want to replace this connection?",
                                          QMessageBox::Yes|QMessageBox::No);


            if(reply == QMessageBox::Yes)
            {
                Port* oldConnectionOtherPort = selectedPort->getConnectedPort();   // Port of other block that is connected to connection we need to replace

                // --- Destroy connections ---
                for(int i = 0; i < this->connections.count(); ++i)  // For every connection in this block
                {
                    if(connections.at(i)->containsPort(oldConnectionOtherPort)) // Check if it's connection we need to replace
                    {
                        delete this->connections.at(i);
                    }
                }
            }
            else
              return;
        }

        this->parentScene->startConnectingBlocks(this, selectedPort);

        /*  Not working! .contains(selectedAction) is always false
        if(connectInputActions.contains(selectedAction))
        {
            this->parentScene->startConnectingBlocks(this,
                this->backendObject->getInputPort(connectInputActions.indexOf(selectedAction)));
        }
        else if(connectOutputActions.contains(selectedAction))
        {
            this->parentScene->startConnectingBlocks(this,
                this->backendObject->getOutputPort(connectOutputActions.indexOf(selectedAction)));
        }
        */
    }
}

void BlockGraphicItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if(this->parentScene->isConnectingBlocks == true    // User is connecting blocks
            && this->parentScene->connecting_startingBlock != this) // Hovered block is not starting one
    {
        ConnectionLineItem *temporaryLine = new ConnectionLineItem(this->parentScene, this->parentScene->connecting_startingBlock, this, NULL, NULL);

        QPen temporaryConnectionPen;
        temporaryConnectionPen.setStyle(Qt::DashLine);
        temporaryConnectionPen.setWidth(2);
        temporaryConnectionPen.setBrush(Qt::gray);
        temporaryLine->visibleLine->setPen(temporaryConnectionPen);

        parentScene->connecting_temporaryLine = temporaryLine;
        parentScene->connecting_temporaryLine_exists = true;
    }

    QGraphicsItem::hoverEnterEvent(event);
}

void BlockGraphicItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QToolTip::hideText();

    if(this->parentScene->isConnectingBlocks == true)
    {
        if(parentScene->connecting_temporaryLine_exists)  // Temporary line exists
        {
            // @todo This is also in mousePressedEvent -> make a new method
            delete parentScene->connecting_temporaryLine;
            parentScene->connecting_temporaryLine_exists = false;
        }
    }

    QGraphicsItem::hoverLeaveEvent(event);
}

QVariant BlockGraphicItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if(change == ItemPositionChange && scene())
    {
        // --- Movement started ---
        if(this->isPressed && isMoving == false)    // Moving just started
            this->on_moving_started();


        // --- Redraw connections ---
        for(int i=0; i<connections.count(); ++i)
        {
            this->connections[i]->refreshPos();
        }
    }
    return QGraphicsItem::itemChange(change, value);
}

void BlockGraphicItem::on_moving_started()
{
    this->isMoving = true;
    this->setZValue(1); // Draw on top of already placed blocks
}

void BlockGraphicItem::on_moving_ended()
{
    this->isMoving = false;
    this->setZValue(0); // Set draw priority to standard
    this->update(); // Force paint()

    // @todo Check if colliding with other blocks, if yes -> move to previous location
}

BlockGraphicItem::~BlockGraphicItem()
{
    int count = connections.count(); // Save because it's decreasing every loop

    // --- Destroy connections ---
    for(int i = 0; i < count; ++i)
    {
        delete this->connections.first();
    }

    this->parentScene->removeItem(this);
    //this->parentScene->backendScheme->removeBlock(backendObject);
    //delete this->backendObject;
    this->backendObject->deleted = true;
}





void BlockGraphicItem::on_connectingToThisBlock(QGraphicsSceneMouseEvent *event)
{
    // --- Context menu ---
    QMenu *menu = new QMenu();
    Port *finishingPort;


    if(this->parentScene->connecting_startingPort->isOutputType())
    {
        // -- Input ports submenu --
        QAction *connectInput0Action(menu->addAction(this->backendObject->getInputPort(0)->print()));
        QAction *connectInput1Action(menu->addAction(this->backendObject->getInputPort(1)->print()));

        // -- Show menu --
        QAction *selectedAction = menu->exec(event->screenPos());


        if(selectedAction)  // Some action was selected
        {
            if(selectedAction == connectInput0Action)
                finishingPort = this->backendObject->getInputPort(0);
            else if(selectedAction == connectInput1Action)
                finishingPort = this->backendObject->getInputPort(1);
            else
                QMessageBox::critical(0, "Connecting port error", "Unexpected action selected");
        }
        else
            return;
    }
    else
    {
        // -- Output ports submenu --
        QAction *connectOutput0Action(menu->addAction(this->backendObject->getOutputPort(0)->print()));

        // -- Show menu --
        QAction *selectedAction = menu->exec(event->screenPos());

        if(selectedAction)  // Some action was selected
        {
            if(selectedAction == connectOutput0Action)
                finishingPort = this->backendObject->getOutputPort(0);
            else
                QMessageBox::critical(0, "Connecting port error", "Unexpected action selected");
        }
        else
            return;
    }

    // --- Check compatibility ---
    if(!this->parentScene->connecting_startingPort->compatible(*finishingPort))
    {
       QMessageBox::critical(0, "Compatibility error", "Connected ports are not compatibile");
       return;
    }

    // --- Check occupied port ---
    if(finishingPort->getConnectedPort() != NULL)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(0, "Replace connection", "This port is already connect, do you want to replace this connection?",
                                      QMessageBox::Yes|QMessageBox::No);


        if(reply == QMessageBox::Yes)
        {
            Port* oldConnectionOtherPort = finishingPort->getConnectedPort();   // Port of other block that is connected to connection we need to replace

            // --- Destroy connections ---
            for(int i = 0; i < this->connections.count(); ++i)  // For every connection in this block
            {
                if(connections.at(i)->containsPort(oldConnectionOtherPort)) // Check if it's connection we need to replace
                {
                    delete this->connections.at(i);
                }
            }
        }
        else
          return;
    }

    // --- Check connecting to self ---
    if(this->parentScene->connecting_startingBlock == this)
    {
        QMessageBox::critical(0, "Connecting port error", "Loop detected!\nCan't connect two ports of the same block");
        return;
    }
    // --- Remove new connection indicator ---
    if(this->parentScene->connecting_temporaryLine_exists)  // Temporary line exists
    {
        // @todo This is also in on_connectingToThisBlock -> make a new method
        delete this->parentScene->connecting_temporaryLine;
        this->parentScene->connecting_temporaryLine_exists = false;
    }

    // --- Create new connection ---
    ConnectionLineItem *line = new ConnectionLineItem(this->parentScene,
                                    this->parentScene->connecting_startingBlock, this,
                                    this->parentScene->connecting_startingPort, finishingPort);

    // --- Exit connecting mode ---
    this->parentScene->exitConnectingBlocks();
}

void BlockGraphicItem::showToolTip(QGraphicsSceneMouseEvent *event)
{
    QToolTip::showText(event->screenPos(),this->backendObject->printPorts());
}

void BlockGraphicItem::highlight()
{
    if(this->parentScene->highlightedBlock != NULL)
        this->parentScene->highlightedBlock->unhighlight();

    this->parentScene->highlightedBlock = this;
    this->isHighlighted = true;

    this->update(); // Force paint()
}

void BlockGraphicItem::unhighlight()
{
    if(this->parentScene->highlightedBlock == this)
        this->parentScene->highlightedBlock = NULL;
    // else qDebug

    this->isHighlighted = false;

    this->update(); // Force paint()
}
