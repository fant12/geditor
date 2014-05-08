#ifndef ROTATORITEM_H
#define ROTATORITEM_H

#include <QGraphicsLineItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsSceneMouseEvent>
#include <QPolygonF>
#include <QRectF>

class Connector;

class RotatorItem : public QGraphicsPolygonItem {

    public:
        RotatorItem(QGraphicsItem *parent = 0);

    public:
        void addConnector(Connector *connector);

        QPolygonF polygon() const;

        void removeConnector();

    protected:
        QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    private:
        Connector *_connector;

        QPolygonF _polygon;

};

class Connector : public QGraphicsLineItem {

    public:

        Connector(RotatorItem *start, RotatorItem *end, QGraphicsItem *parent = 0);

    public:

        QRectF boundingRect() const;

        RotatorItem *endItem() const;

        RotatorItem *startItem() const;

        void updatePosition();

    protected:

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    private:

        RotatorItem *_end;

        RotatorItem *_start;

};

#endif // ROTATORITEM_H
