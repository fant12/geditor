#ifndef CORNERGRABBER_H
#define CORNERGRABBER_H

#include "../../templates/GetSet.h"

#include <QColor>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QPainter>
#include <QPen>
#include <QPointF>

// class --------------------------------------------------------------------------------

//! CornerGrabber class.
/*!
 * \brief The CornerGrabber class describes a QGraphicsItem that handles direct
 * scaling manipulation of graphic items on canvas area.
 */
class CornerGrabber : public QGraphicsItem {

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief The default constructor.
         * \param parent the parent object
         * \param corner the active corner
         */
        explicit CornerGrabber(QGraphicsItem *parent = 0, int corner = 0);

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief Gives the currently used corner.
         * \returns the corner index
         */
        int getCorner();

    // --------------------------------------------------------------------------------
    private:

        /*!
         * \brief Provides the dimensions of the box to the graphics view object.
         * \returns the specified rectangle object
         */
        virtual QRectF boundingRect() const;

        // once the hover event handlers are implemented in this class,
        // the mouse events must allow be implemented because of some
        // linkage issue - apparrently there is some connection between
        // the hover events and mouseMove/Press/Release events which triggers
        // an issue

        /*!
         * \brief Handles mouse hover enter events.
         * \param event the catched event
         */
        virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

        /*!
         * \brief Handles mouse hover leave events.
         * \param event the catched event
         */
        virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

        /*!
         * \brief Handles mouse moving events.
         * \param event the catched events
         */
        virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

        /*!
         * \brief Handles mouse moving events.
         * \param event the catched events
         */
        virtual void mouseMoveEvent(QGraphicsSceneDragDropEvent *event);

        /*!
         * \brief Handles mouse pressing events.
         * \param event the catched events
         */
        virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

        /*!
         * \brief Handles mouse pressing events.
         * \param event the catched events
         */
        virtual void mousePressEvent(QGraphicsSceneDragDropEvent *event);

        /*!
         * \brief Handles mouse releasing events.
         * \param event the catched events
         */
        virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

        /*!
         * \brief Draws the box.
         * \param painter the object that draws the corner grabber
         * \param option the item style
         * \param widget the widget where the item could be mapped on
         */
        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // --------------------------------------------------------------------------------
    public:

        /*!< Defines the mouse states. */
        enum {
            kMouseReleased = 0, /*!< Mouse released */
            kMouseDown,         /*!< Mouse pressed down */
            kMouseMoving        /*!< Mouse moving */
        };

    // --------------------------------------------------------------------------------
    private:

        /*!< The current active cornergrabber.
         * \li 0 the corner at point 0, 0.
         * \li 1 the corner at point 1, 0.
         * \li 2 the corner at point 1, 1.
         * \li 3 the corner at point 0, 1.
         */
        int _corner;

        /*!< The border color for default (black) or hover (red) state. */
        QColor _outterborderColor;

        /*!< The pen for red or black border. */
        QPen _outterborderPen;


        /*!< The height of the corner grabber. */
        GETSET(qreal, height, Height)

        /*!< The current mouse button state. */
        GETSET(int, mouseButtonState, MouseButtonState)

        /*!< The value on x-axis where mouseclick event is triggered. */
        GETSET(qreal, mouseDownX, MouseDownX)

        /*!< The value on y-axis where mouseclick event is triggered. */
        GETSET(qreal, mouseDownY, MouseDownY)

        /*!< The width of the corner grabber. */
        GETSET(qreal, width, Width)

};

#endif // CORNERGRABBER_H
