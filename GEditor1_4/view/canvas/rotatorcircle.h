#ifndef ROTATORCIRCLE_H
#define ROTATORCIRCLE_H

#include <QGraphicsEllipseItem>

class CanvasItem;

class RotatorCircle : public QGraphicsEllipseItem {

    public:
        explicit RotatorCircle(CanvasItem *parent = 0);

    public:
        void add(CanvasItem *item);

        void mousePressEvent(QGraphicsSceneMouseEvent *event);

        void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

        void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);

        void remove();

    private:

        inline QRectF pointBoundingRect(int i) const;

    private:

        QPointF _initialPos;

        QPolygonF _points;

        QSizeF _pointSize;

        /*!< The radius. */
        int _radius;

        /*!< The rotation. */
        qreal _rotation;

};

inline QRectF RotatorCircle::pointBoundingRect(int i) const {

    QPointF p = _points.at(i);
    qreal w = _pointSize.width();
    qreal h = _pointSize.height();
    qreal x = p.x() - 0.5 * w;
    qreal y = p.y() - 0.5 * h;

    return QRectF(x, y, w, h);
}

#endif // ROTATORCIRCLE_H
