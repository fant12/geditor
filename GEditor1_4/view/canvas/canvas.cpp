#include "canvas.h"

// --------------------------------------------------------------------------------------
// magic --------------------------------------------------------------------------------


Canvas::Canvas(qreal x, qreal y, qreal width, qreal height, QObject *parent) : QGraphicsScene(x, y, width, height, parent),
    _backgroundRect(0){}


// --------------------------------------------------------------------------------------
// public -------------------------------------------------------------------------------


void Canvas::setUrl(const QString url){
    _url = url;
    update();
}


// --------------------------------------------------------------------------------------
// protected ----------------------------------------------------------------------------


void Canvas::drawBackground(QPainter *painter, const QRectF &rect){

    if(0 != _url){
        QPixmap origin(_url);
        QPixmap scaledPx = origin.scaled(2 * width(), 2 * height(), Qt::KeepAspectRatio);

        if(0 != _backgroundRect)
            _backgroundRect->setPixmap(scaledPx);
        else
            _backgroundRect = addPixmap(scaledPx);

        _backgroundRect->setPos((width() - scaledPx.width())/2, (height() - scaledPx.height())/2);
        _backgroundRect->setZValue(0);
    }

    QGraphicsScene::drawBackground(painter, rect);
}
