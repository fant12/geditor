#ifndef CANVASITEM_H
#define CANVASITEM_H

#include "cornergrabber.h"
#include "rotatorcircle.h"
#include "rotatoritem.h"

// class --------------------------------------------------------------------------------

//! CanvasItem class.
/*!
 * \brief The CanvasItem class describes a canvas item that can
 * be rotated or scaled.
 */
class CanvasItem : public QGraphicsItem {

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief The default constructor.
         * \param name the item name
         * \param x the position on x-axis
         * \param y the position on y-axis
         * \param width the item width
         * \param height the item height
         * \param penStyle the pen style
         * \param color the color
         * \param url the url
         * \param parent the parent object
         */
        explicit CanvasItem(QString name, qreal x, qreal y, qreal width, qreal height, Qt::PenStyle penStyle = Qt::SolidLine, QColor color = QColor(0, 0, 0, 0), QString url = 0, QGraphicsItem *parent = 0);

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief Gives the middlepoint on x-axis.
         * \returns the x-value
         */
        int getCenterX();

        /*!
         * \brief Gives the middlepoint on y-axis.
         * \returns the y-value
         */
        int getCenterY();

        /*!
         * \brief Gives the inner rotator anchor.
         * \returns a rotator item
         */
        RotatorCircle *getRotator();

        /*!
         * \brief Sets the rotator to midpoint.
         */
        void setRotator();

    // --------------------------------------------------------------------------------
    protected:

        /*!
         * \brief Notifies about a position change.
         * \param pos the position
         * \param value the value
         */
        void notify(QString pos, QVariant value);

    // --------------------------------------------------------------------------------
    private:

        /*!
         * \brief Adjusts the size.
         * \param x the size on horizontal axis
         * \param y the size on vertical axis
         */
        void adjustSize(int x, int y);

        /*!
         * \brief Defines the outer bounds of the item.
         * \returns the rectangle object
         */
        virtual QRectF boundingRect() const; ///< must be re-implemented in this class to provide the diminsions of the box to the QGraphicsView

        /*!
         * \brief Receives hover enter events for this item.
         * \param event the hover enter event
         */
        virtual void hoverEnterEvent ( QGraphicsSceneHoverEvent * event ); ///< must be re-implemented to handle mouse hover enter events

        /*!
         * \brief Receives hover leave events for this item.
         * \param event the hover leave event
         */
        virtual void hoverLeaveEvent ( QGraphicsSceneHoverEvent * event ); ///< must be re-implemented to handle mouse hover leave events

        /*!
         * \brief Receives mouse move events for this item.
         * \param event the mouse move event
         */
        virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );///< allows the main object to be moved in the scene by capturing the mouse move events

        /*!
         * \brief Receives mouse move events for this item.
         * \param event the mouse move event
         */
        virtual void mouseMoveEvent(QGraphicsSceneDragDropEvent *event);

        /*!
         * \brief Receives mouse press events for this item.
         * \param event the mouse press event
         */
        virtual void mousePressEvent(QGraphicsSceneMouseEvent * event );

        /*!
         * \brief Receives mouse press events for this item.
         * \param event the mouse press event
         */
        virtual void mousePressEvent(QGraphicsSceneDragDropEvent *event);

        /*!
         * \brief Receives mouse release events for this item.
         * \param event the mouse release event
         */
        virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event );

        /*!
         * \brief Paints the contents of the item in local coordinates.
         * \param painter paints the content
         * \param option provides style options for the item
         * \param widget points to the widget that is being painted on
         */
        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); ///< must be re-implemented here to pain the box on the paint-event

        /*!
         * \brief Filters events.
         * \param watched the watched item
         * \param event the filtered event
         * \returns true to prevents further processing of the given event, otherwise false
         */
        virtual bool sceneEventFilter(QGraphicsItem * watched, QEvent * event ) ;

        /*!
         * \brief Sets the corner positions.
         */
        void setCornerPositions();

    // --------------------------------------------------------------------------------
    protected:

        /*!< The color. */
        QColor _color;

        /*!< The corner start point for dragging. */
        QPointF _cornerDragStart;

        /*!< The corner grabbers. */
        CornerGrabber *_corners[4];

        /*!< The start point for dragging. */
        QPointF _dragStart;

        /*!< The location. */
        QPointF _location;

        /*!< The border color. */
        QColor _outerborderColor;

        /*!< The border pen. */
        QPen _outerborderPen;

        /*!< The pen style. */
        Qt::PenStyle _penStyle;

        /*!< The rotation anchor. */
        RotatorCircle *_rotator;

        /*!< The image path. */
        QString _url;

        /*!< The corner on x-axis. */
        int _XcornerGrabBuffer;

        /*!< The corner on y-axis. */
        int _YcornerGrabBuffer;


        /*!< The grid space. */
        GETSET(int, gridSpace, GridSpace)

        /*!< The item height. */
        GETSET(qreal, height, Height)

        /*!< The object name or id. */
        GETSET(QString, name, Name)

        /*!< The item width. */
        GETSET(qreal, width, Width)

        /*!< The position on x-axis. */
        GETSET(qreal, x, X)

        /*!< The position on y-axis. */
        GETSET(qreal, y, Y)


        // has to be declared after width and height, whyever

        /*!< The drawing height. */
        GETSET(qreal, drawingHeight, DrawingHeight)

        /*! The drawing width. */
        GETSET(qreal, drawingWidth, DrawingWidth)

        /*!< The origin point on x-axis. */
        GETSET(qreal, drawingOrigenX, DrawingOrigenX)

        /*!< The origin point on y-axis. */
        GETSET(qreal, drawingOrigenY, DrawingOrigenY)

};

#endif // CANVASITEM_H
