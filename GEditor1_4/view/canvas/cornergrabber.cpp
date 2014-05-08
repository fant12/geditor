#include "cornergrabber.h"

CornerGrabber::CornerGrabber(QGraphicsItem *parent, int corner) : QGraphicsItem(parent),
    _mouseDownX(0),
    _mouseDownY(0),
    _outterborderColor(Qt::black),
    _outterborderPen(),
    _width(5),
    _height(5),
    _corner(corner),
    _mouseButtonState(kMouseReleased){

    setParentItem(parent);
    _outterborderPen.setWidth(2);
    _outterborderPen.setColor(_outterborderColor);
    setAcceptHoverEvents(true);
}

int CornerGrabber::getCorner(){
    return _corner;
}

// we have to implement the mouse events to keep the linker happy,
// but just set accepted to false since are not actually handling them

void CornerGrabber::mouseMoveEvent(QGraphicsSceneDragDropEvent *event){
    event->setAccepted(false);
}

void CornerGrabber::mousePressEvent(QGraphicsSceneDragDropEvent *event){
    event->setAccepted(false);
}

void CornerGrabber::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    event->setAccepted(true);
}

void CornerGrabber::mousePressEvent(QGraphicsSceneMouseEvent *event){
    event->setAccepted(false);
}

void CornerGrabber::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    event->setAccepted(false);
}

// change the color on hover events to indicate to the use the object has
// been captured by the mouse

void CornerGrabber::hoverLeaveEvent(QGraphicsSceneHoverEvent *){
    _outterborderColor = Qt::black;
    update(0, 0, _width, _height);
}

void CornerGrabber::hoverEnterEvent(QGraphicsSceneHoverEvent *){
    _outterborderColor = Qt::red;
    update(0, 0, _width, _height);
}

QRectF CornerGrabber::boundingRect() const{
    return QRectF(0, 0, _width, _height);
}

void CornerGrabber::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){

    // fill the box with solid color, use sharp corners
    _outterborderPen.setCapStyle(Qt::SquareCap);
    _outterborderPen.setStyle(Qt::SolidLine);
    painter->setPen(_outterborderPen);

    QPointF topLeft(0, 0);
    QPointF bottomRight( _width, _height);

    QRectF rect(topLeft, bottomRight);

    QBrush brush(Qt::SolidPattern);
    brush.setColor(_outterborderColor);
    painter->fillRect(rect, brush);
}
