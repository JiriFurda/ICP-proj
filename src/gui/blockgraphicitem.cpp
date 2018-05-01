#include "blockgraphicitem.h"

BlockGraphicItem::BlockGraphicItem(SchemeScene *scene, QString name)
{
    // --- Settings ---
    this->setFlag(QGraphicsItem::ItemIsMovable);
    this->setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    this->setAcceptHoverEvents(true);
    this->setZValue(0);

    // --- Defautl values ---
    this->isMoving = false;
    this->isPressed = false;
    this->name = name;
    this->parentScene = scene;
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

    // --- Image ---
    QPainterPath path;  // something like group??
    path.addRoundedRect(boundingRect(), 10, 10);
    painter->fillPath(path, Qt::white);

    // --- Name ---
    painter->drawText(boundingRect(), Qt::AlignCenter|Qt::TextWrapAnywhere, this->name);   // @todo Choose if Qt::TextWrapAnywhere or Qt::TextWordWrap and if adding Qt::TextDontClip is a good idea



    // --- Draw result ---
    painter->drawPath(path);
}

void BlockGraphicItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // @todo check if also changes position or only pressed
    if(event->button() == Qt::LeftButton)   // Pressed left mouse button
    {
        this->update(); // Force paint()
        this->isPressed = true;
        QGraphicsItem::mousePressEvent(event);  // Propagate further
    }
}

void BlockGraphicItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)   // Pressed left mouse button
    {
        // --- Debug: @todo for creating connections ---
        if(this->parentScene->isConnectingBlocks == true)
        {
            this->on_connectingToThisBlock(event);
        }


        this->on_moving_ended();

        this->update(); // Force paint()

        QGraphicsItem::mouseReleaseEvent(event);  // Propagate further
    }
}

void BlockGraphicItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    // --- Context menu ---
    QMenu *menu = new QMenu();
    QAction *removeAction = menu->addAction("Remove block");

    // -- Input ports submenu --
    QMenu *inputMenu = menu->addMenu("Connect input port");
    QAction *connectDebugAction = inputMenu->addAction("Operand 1 [float]");
    inputMenu->addAction("Operand 2 [float]");

    // -- Output ports submenu --
    QMenu *outputMenu = menu->addMenu("Connect output port");
    outputMenu->addAction("Result [float]");

    // -- Show menu --
    QAction *selectedAction = menu->exec(event->screenPos());

    /* @todo
    menu->popup(event->screenPos()); // Someone said this is better than exec because it does't block loop but whatever
    connect(menu, SIGNAL(triggered(QAction *)),
                 object, SLOT(triggered(QAction *)));
    */
    if(selectedAction)  // Some action was selected
    {
        if(selectedAction == removeAction)
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(0, QString("Delete block"),
                QString("Do you really want to delete block \""+this->name+"\"?"),
                QMessageBox::Yes | QMessageBox::No);

             if(reply == QMessageBox::Yes)
                delete this;
             else
                 return;
        }
        else if(selectedAction == connectDebugAction)
        {
            this->parentScene->isConnectingBlocks = true;
            this->parentScene->connecting_startingBlock = this;
        }
    }
}

void BlockGraphicItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if(this->parentScene->isConnectingBlocks == true    // User is connecting blocks
            && this->parentScene->connecting_startingBlock != this) // Hovered block is not starting one
    {
        ConnectionLineItem *line = new ConnectionLineItem(this->parentScene->connecting_startingBlock, this);

        QPen temporaryConnectionPen;
        temporaryConnectionPen.setStyle(Qt::DashLine);
        temporaryConnectionPen.setWidth(2);
        temporaryConnectionPen.setBrush(Qt::gray);
        line->setPen(temporaryConnectionPen);

        parentScene->connecting_temporaryLine = line;
        parentScene->addItem(line);
        parentScene->connecting_temporaryLine_exists = true;
    }

    QGraphicsItem::hoverEnterEvent(event);
}

void BlockGraphicItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
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
    this->isPressed = false;
    this->isMoving = false;
    this->setZValue(0); // Set draw priority to standard

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

    this->scene()->removeItem(this);
}





void BlockGraphicItem::on_connectingToThisBlock(QGraphicsSceneMouseEvent *event)
{
    // --- Context menu ---
    QMenu *menu = new QMenu();
    menu->addAction("[float] Operand A");
    menu->addAction("[float] Operand A (used)");

    // -- Show menu --
    QAction *selectedAction = menu->exec(event->screenPos());


    if(selectedAction)  // Some action was selected
    {
        // @todo
    }
    else
        return;


    // --- Remove new connection indicator ---
    if(this->parentScene->connecting_temporaryLine_exists)  // Temporary line exists
    {
        // @todo This is also in on_connectingToThisBlock -> make a new method
        delete this->parentScene->connecting_temporaryLine;
        this->parentScene->connecting_temporaryLine_exists = false;
    }

    // --- Exit connecting mode ---
    this->parentScene->isConnectingBlocks = false;

    // --- Create new connection ---
    ConnectionLineItem *line = new ConnectionLineItem(this->parentScene->connecting_startingBlock, this);
    this->parentScene->addItem(line);
}
