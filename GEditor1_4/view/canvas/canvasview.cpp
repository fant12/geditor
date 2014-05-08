#include "canvasview.h"

#include <QKeyEvent>
#include <QWheelEvent>

CanvasView::CanvasView(QGraphicsScene *scene, QWidget *parent) : QGraphicsView(scene, parent){

    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate); //slowly rendering while resizing
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setOptimizationFlags(QGraphicsView::DontSavePainterState);

    scene->setBackgroundBrush(Qt::gray);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    _bg = scene->addRect(0, 0, 2000, 2000, QPen(), QBrush(QColor(255, 255, 255)));
    _bg->setZValue(-1);

    setScene(scene);

    // use scrollhand drag mode to enable panning
    setDragMode(ScrollHandDrag);
}

void CanvasView::keyPressEvent(QKeyEvent *event){

    switch(event->key()) {
        case Qt::Key_Plus:
            scaleView(qreal(1.2));
            break;
        case Qt::Key_Minus:
            scaleView(1 / qreal(1.2));
            break;
        default: QGraphicsView::keyPressEvent(event);
    }
}

#ifndef QT_NO_WHEELEVENT
void CanvasView::wheelEvent(QWheelEvent *event){

    scaleView(pow((double)2, -event->delta() / 240.0));

    /*setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    // scale the view / zoom in or out
    double scaleFactor = 1.15;

    if(0 < event->delta())
        scale(scaleFactor, scaleFactor); // zoom in
    else
        scale(1.0 / scaleFactor, 1.0 / scaleFactor); // zoom out*/

}
#endif

void CanvasView::scaleView(qreal scaleFactor){

    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if(factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}
