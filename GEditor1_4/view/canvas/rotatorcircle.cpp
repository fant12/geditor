#include "rotatorcircle.h"
#include "canvasitem.h"

#include <QPainter>

RotatorCircle::RotatorCircle(CanvasItem *parent) : QGraphicsEllipseItem(parent){

    _rotation = 0;
    _pointSize = QSize(11, 11);

    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

void RotatorCircle::mousePressEvent(QGraphicsSceneMouseEvent *event){

    _initialPos = mapToScene(event->pos());
    setTransformOriginPoint(x(), y());
    QGraphicsItem::mousePressEvent(event);
}

void RotatorCircle::mouseMoveEvent(QGraphicsSceneMouseEvent *event){

    QPointF pos = mapToScene(event->pos());

    if(pos.y() > _initialPos.y())
        ++_rotation;
    else
        --_rotation;

    qreal xCenter = boundingRect().x() + 0.5 * boundingRect().width();
    qreal yCenter = boundingRect().y() + 0.5 * boundingRect().height();

    QTransform xform;
    xform.translate(xCenter, yCenter); // translate matrix
    setTransform(xform);
    if(0 != parentItem()) parentItem()->setTransform(xform);

    xform.rotate(_rotation);
    setTransform(xform);
    if(0 != parentItem()) parentItem()->setTransform(xform);

    xform.translate(-xCenter, -yCenter); // translate matrix back to origin point
    setTransform(xform);
    if(0 != parentItem()) parentItem()->setTransform(xform);

    _initialPos = pos;
}

void RotatorCircle::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){

    painter->setPen(QPen(QBrush(Qt::blue), 2));
    painter->drawLine(QPointF(boundingRect().x(), boundingRect().center().y()),
                      QPointF(boundingRect().x() +boundingRect().width(), boundingRect().center().y()));
    painter->drawLine(QPointF(boundingRect().center().x(), boundingRect().y()),
                      QPointF(boundingRect().center().x(), boundingRect().y() +boundingRect().height()));

}
