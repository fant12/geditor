#ifndef CANVASVIEW_H
#define CANVASVIEW_H

#include "../../templates/getset.h"

#include <QGraphicsObject>
#include <QGraphicsRectItem>
#include <QGraphicsView>

class QKeyEvent;
class QWheelEvent;

// class --------------------------------------------------------------------------------

//! CanvasView class.
/*!
 * \brief The CanvasView class describes the container for the
 * canvas object.
 */
class CanvasView : public QGraphicsView {

        Q_OBJECT

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief The default constructor.
         * \param scene the assigned canvas scene
         * \param parent the parent object
         */
        CanvasView(QGraphicsScene *scene, QWidget *parent = 0);

    // --------------------------------------------------------------------------------
    protected:

        /*!
         * \brief Reacts on key press events to zoom in and out
         * the scene.
         * \param event the catched key event
         */
        void keyPressEvent(QKeyEvent *event);

        /*!
         * \brief Zooms in and out the scene.
         * \param event the catched mouse wheel event
         */
        virtual void wheelEvent(QWheelEvent *event);

    // --------------------------------------------------------------------------------
    private:

        /*!
         * \brief Scales the view.
         * \param scaleFactor the scale factor
         */
        void scaleView(qreal scaleFactor);

    // --------------------------------------------------------------------------------
    private:

        /*!< Rectangle Item that contains the background image of canvas scene. */
        GETSET(QGraphicsRectItem *, bg, Bg)

};

#endif // CANVASVIEW_H
