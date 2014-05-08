#include "canvasitem.h"
#include "math.h"

#include <QBrush>

CanvasItem::CanvasItem(QString name, qreal x, qreal y, qreal width, qreal height, Qt::PenStyle penStyle, QColor color, QString url, QGraphicsItem *parent) : QGraphicsItem(parent),
    _color(color),
    _cornerDragStart(0, 0),
    _dragStart(0, 0),
    _location(0, 0),
    _name(name),
    _gridSpace(10),
    _height(height),
    _outerborderColor(Qt::black),
    _outerborderPen(),
    _penStyle(penStyle),
    _url(url),
    _width(width),
    _x(x),
    _XcornerGrabBuffer(20),
    _y(y),
    _YcornerGrabBuffer(20),
    _drawingWidth(_width - _XcornerGrabBuffer),
    _drawingHeight(_height - _YcornerGrabBuffer),
    _drawingOrigenX(_XcornerGrabBuffer),
    _drawingOrigenY(_YcornerGrabBuffer){

    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable);

    //_rotator = new RotatorCircle(this);
    //setRotator();
}


// --------------------------------------------------------------------------------------
// public -------------------------------------------------------------------------------


int CanvasItem::getCenterX(){
    return _drawingOrigenX + 0.5 * _drawingWidth - _gridSpace;
}

int CanvasItem::getCenterY(){
    return _drawingOrigenY + 0.5 * _drawingHeight - _gridSpace;
}

RotatorCircle *CanvasItem::getRotator(){
    return _rotator;
}

void CanvasItem::setRotator(){

    _rotator->setRect(_drawingOrigenX + 2 * _XcornerGrabBuffer,
                      _drawingOrigenY + 2 * _YcornerGrabBuffer,
                      0.25 * _drawingWidth,
                      0.25 * _drawingHeight);
}


// --------------------------------------------------------------------------------------
// protected ----------------------------------------------------------------------------


void CanvasItem::notify(QString, QVariant){
    // TODO
}


// --------------------------------------------------------------------------------------
// private ------------------------------------------------------------------------------


void CanvasItem::adjustSize(int x, int y){

    _width += x;
    _height += y;

    _drawingWidth = _width - _XcornerGrabBuffer;
    _drawingHeight = _height - _YcornerGrabBuffer;
}

QRectF CanvasItem::boundingRect() const {
    return QRectF(_x, _y, _width, _height);
}

void CanvasItem::hoverEnterEvent(QGraphicsSceneHoverEvent *){

    _outerborderColor = Qt::red;

    for(int i = 0; 4 > i; ++i){
        _corners[i] = new CornerGrabber(this, i);
        _corners[i]->installSceneEventFilter(this);
    }
    setCornerPositions();
}

void CanvasItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *){

    _outerborderColor = Qt::black;

    for(int i = 0; 4 > i; ++i){
        _corners[i]->setParentItem(NULL);
        delete _corners[i];
    }
}

void CanvasItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event){

    QPointF newPos = event->pos();
    _location += (newPos - _dragStart);
    setPos(_location);
}

void CanvasItem::mouseMoveEvent(QGraphicsSceneDragDropEvent *event){
    event->setAccepted(false);
}

void CanvasItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    event->setAccepted(true);
    _dragStart = event->pos();
}

void CanvasItem::mousePressEvent(QGraphicsSceneDragDropEvent *event){
    event->setAccepted(false);
}

void CanvasItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){

    event->setAccepted(true);
    _location.setX(_gridSpace * (static_cast<int>(_location.x()) / _gridSpace));
    _location.setY(_gridSpace * (static_cast<int>(_location.y()) / _gridSpace));
    setPos(_location);
    notify("pos", _location);
}

void CanvasItem::paint (QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){

    if(NULL != _url)
        painter->drawPixmap(_drawingOrigenX, _drawingOrigenY, _drawingWidth, _drawingHeight, QPixmap(_url));
    else {
        _outerborderPen.setWidth(2);
        _outerborderPen.setColor(_outerborderColor);
        _outerborderPen.setStyle(_penStyle); //dashed or solid border
        painter->setPen(_outerborderPen);

        QBrush brush(_color, Qt::SolidPattern);
        painter->setBrush(brush);

        QPointF topLeft(_drawingOrigenX, _drawingOrigenY);
        QPointF bottomRight(_drawingWidth, _drawingHeight);
        QRectF rect(topLeft, bottomRight);

        painter->drawRect(rect);
    }

}

bool CanvasItem::sceneEventFilter(QGraphicsItem *watched, QEvent *event){

    CornerGrabber *corner = dynamic_cast<CornerGrabber *>(watched);
    if(NULL == corner)
        return false; // not expected to get here

    QGraphicsSceneMouseEvent *me = dynamic_cast<QGraphicsSceneMouseEvent *>(event);
    if(NULL == me)
        return false; // these mouse events are not interesting for me

    switch(event->type()){
        case QEvent::GraphicsSceneMousePress: {
            corner->setMouseButtonState(CornerGrabber::kMouseDown);
            corner->setMouseDownX(me->pos().x());
            corner->setMouseDownY(me->pos().y());
            break;
        }
        case QEvent::GraphicsSceneMouseRelease: {
            corner->setMouseButtonState(CornerGrabber::kMouseReleased);
            break;
        }
        case QEvent::GraphicsSceneMouseMove: {
            corner->setMouseButtonState(CornerGrabber::kMouseMoving);
            break;
        }
        default: return false;
    }

    if(CornerGrabber::kMouseMoving == corner->getMouseButtonState()){

        qreal x = me->pos().x();
        qreal y = me->pos().y();

        //depending on which corner has been grabbed, we want to move the position
        //of the item as it grows/shrinks accordingly. so we need to either add
        //or subtract the offsets based on which corner this is.

        int XaxisSign = 0;
        int YaxisSign = 0;

        switch(corner->getCorner()){
            case 0: {
                XaxisSign = 1;
                YaxisSign = 1;
                break;
            }
            case 1: {
                XaxisSign = -1;
                YaxisSign = 1;
                break;
            }
            case 2: {
                XaxisSign = -1;
                YaxisSign = -1;
                break;
            }
            case 3: {
                XaxisSign = 1;
                YaxisSign = -1;
                break;
            }
        }

        //if the mouse is being dragged, calculate a new size and also re-position
        //the box to give the appearance of dragging the corner out/in to resize
        //the box

        int xMoved = corner->getMouseDownX() - x;
        int yMoved = corner->getMouseDownY() - y;

        int newWidth = _width + (XaxisSign * xMoved);
        if(40 > newWidth) newWidth = 40;

        int newHeight = _height + (YaxisSign * yMoved);
        if(40 > newHeight) newHeight = 40;

        int deltaWidth = newWidth-_width;
        int deltaHeight = newHeight-_height;

        adjustSize(deltaWidth, deltaHeight);
        deltaWidth *= (-1);
        deltaHeight *= (-1);

        switch(corner->getCorner()){
            case 0: {
                int newXPos = pos().x() + deltaWidth;
                int newYPos = pos().y() + deltaHeight;
                setPos(newXPos, newYPos);
                break;
            }
            case 1: {
                setPos(pos().x(), pos().y() + deltaHeight);
                break;
            }
            case 3: {
                setPos(pos().x() + deltaWidth, pos().y());
                break;
            }
        }

        setCornerPositions();
        update();

        //TODO
        /*if(0 != _rotator){
            setRotator();
            _rotator->update();
        }*/

    }

    //true => do not send event to watched - we are finished with this event
    return true;
}

void CanvasItem::setCornerPositions()
{
    _corners[0]->setPos(_drawingOrigenX, _drawingOrigenY);
    _corners[1]->setPos(_drawingWidth - _corners[1]->getWidth(), _drawingOrigenY);
    _corners[2]->setPos(_drawingWidth - _corners[2]->getWidth(), _drawingHeight-_corners[2]->getHeight());
    _corners[3]->setPos(_drawingOrigenX, _drawingHeight - _corners[3]->getHeight());
}
