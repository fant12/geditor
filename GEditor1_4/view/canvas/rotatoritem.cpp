#include "rotatoritem.h"

#include <math.h>
#include <QPainter>
#include <QPen>

#define SIZE 10;
const qreal PI = 3.14;

RotatorItem::RotatorItem(QGraphicsItem *parent) : QGraphicsPolygonItem(parent){

    _polygon << QPointF(-100, -100)
             << QPointF(100, -100)
             << QPointF(100, 100)
             << QPointF(-100, 100)
             << QPointF(-100, -100);

    setPolygon(_polygon);

    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

void RotatorItem::addConnector(Connector *connector){
    _connector = connector;
}

QVariant RotatorItem::itemChange(GraphicsItemChange change, const QVariant &value){

    if(QGraphicsItem::ItemPositionChange == change)
        _connector->updatePosition();

    return value;
}

QPolygonF RotatorItem::polygon() const {
    return _polygon;
}

void RotatorItem::removeConnector(){
    _connector = 0;
}


Connector::Connector(RotatorItem *start, RotatorItem *end, QGraphicsItem *parent) : QGraphicsLineItem(parent){

    _start = start;
    _end = end;

    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

QRectF Connector::boundingRect() const {

    qreal extra = 0.5 * (20 + pen().width());

    return QRectF(line().p1(),
                  QSizeF(line().p2().x() - line().p1().x(),
                         line().p2().y() - line().p1().y()))
            .normalized()
            .adjusted(-extra, -extra, extra, extra);
}

RotatorItem *Connector::endItem() const {
    return _end;
}

void Connector::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){

    if(_start->collidesWithItem(_end))
        return;

    painter->setPen(pen());
    setLine(QLineF(_end->pos(), _start->pos()));
    double angle = ::acos(line().dx() / line().length());

    if(0 <= line().dy())
        angle = (2 * PI) - angle;

    painter->drawLine(line());

    if(isSelected()){
        QLineF ln = line();
        ln.translate(0, 4);
        painter->drawLine(ln);

        ln.translate(0, -8);
        painter->drawLine(ln);
    }
}

RotatorItem *Connector::startItem() const {
    return _start;
}

void Connector::updatePosition(){
    QLineF ln(mapFromItem(_start, 0, 0), mapFromItem(_end, 0, 0));
    setLine(ln);
}
