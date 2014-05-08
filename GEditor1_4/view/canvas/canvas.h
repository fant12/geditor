#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QRectF>

// class --------------------------------------------------------------------------------

//! Canvas class.
/*!
 * \brief The Canvas class describes a scene for all graphic elements
 * in game.
 */
class Canvas : public QGraphicsScene {

        Q_OBJECT

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief The default constructor.
         * \param x the position on x-axis
         * \param y the position on y-axis
         * \param width the scene width
         * \param height the scene height
         * \param parent the parent object
         */
        explicit Canvas(qreal x, qreal y, qreal width, qreal height, QObject *parent = 0);

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief Sets the image path for the background.
         * \param url is a string which contains path to an image file.
         */
        void setUrl(const QString url);

    // --------------------------------------------------------------------------------
    protected:

        /*!
         * \brief Draws the scene background.
         * \param painter paints the scene
         * \param rect the scene rect
         */
        void drawBackground(QPainter *painter, const QRectF &rect);


        /*!< The background rectangle. */
        QGraphicsPixmapItem *_backgroundRect;

        /*!< The background image url. */
        QString _url;

};

#endif // CANVAS_H
