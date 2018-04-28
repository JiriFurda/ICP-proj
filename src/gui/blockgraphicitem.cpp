#include "blockgraphicitem.h"

BlockGraphicItem::BlockGraphicItem()
{
    this->setFlag(QGraphicsItem::ItemIsMovable);

    this->pressed = false;
}

QRectF BlockGraphicItem::boundingRect() const
{
    return QRectF(0,0,100,100);
}

void BlockGraphicItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // --- Painter settings ---
    painter->setRenderHint(QPainter::Antialiasing); // Enable antialiasing
    painter->setPen(QPen(Qt::black, 2));    // 1px black border

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
    painter->drawText(boundingRect(), Qt::AlignCenter|Qt::TextWrapAnywhere, "Test Block");   // @todo Choose if Qt::TextWrapAnywhere or Qt::TextWordWrap and if adding Qt::TextDontClip is a good idea



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
        this->pressed = false;
        this->update(); // Force paint()
        QGraphicsItem::mouseReleaseEvent(event);  // Propagate further
    }
}

void BlockGraphicItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    // --- Context menu ---
    QMenu *menu = new QMenu();
    menu->addAction("Remove block");

    // -- Input ports submenu --
    QMenu *inputMenu = menu->addMenu("Connect input port");
    inputMenu->addAction("Operand 1 [float]");
    inputMenu->addAction("Operand 2 [float]");

    // -- Output ports submenu --
    QMenu *outputMenu = menu->addMenu("Connect output port");
    outputMenu->addAction("Result [float]");

    // -- Show menu --
    menu->popup(event->screenPos());

    /* @todo
    connect(menu, SIGNAL(triggered(QAction *)),
                 object, SLOT(triggered(QAction *)));
    */
}
