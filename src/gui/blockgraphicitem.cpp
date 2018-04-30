#include "blockgraphicitem.h"

BlockGraphicItem::BlockGraphicItem(SchemeScene *scene, QString name)
{
    // --- Settings ---
    this->setFlag(QGraphicsItem::ItemIsMovable);
    this->setAcceptHoverEvents(true);

    // --- Defautl values ---
    this->pressed = false;
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

    // --- Transparent ---
    if(this->pressed == true)
        painter->setOpacity(0.7);   // Block is dragged
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
        this->pressed = true;
        this->update(); // Force paint()
        QGraphicsItem::mousePressEvent(event);  // Propagate further
    }
}

void BlockGraphicItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)   // Pressed left mouse button
    {
        //SchemeScene *myParent = qobject_cast<SchemeScene *>(this->parentObject());

        if(this->parentScene->connectingBlocks == true)
            qDebug("connecting blocks");
        else
             qDebug("not connecting blocks");

        this->pressed = false;

        //if(this->collidingItems().count() != 0) @todo

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
            delete this;

        else if(selectedAction == connectDebugAction)
            this->parentScene->connectingBlocks = true;

    }
}

void BlockGraphicItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    qDebug("hover");
}
