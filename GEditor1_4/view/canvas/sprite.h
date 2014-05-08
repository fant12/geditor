#ifndef SPRITE_H
#define SPRITE_H

#include "../../templates/getset.h"
#include <QGraphicsObject>
#include <QStateMachine>
#include "canvasitem.h"

class QEvent;
class QState;

class Sprite : public QGraphicsObject, public CanvasItem {

        Q_OBJECT

    private:
        static const QMap<int, QString> EVENT_TYPES;

        friend class SpriteState;

    public:
        Sprite(QString name, qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = 0);

        ~Sprite();

    signals:
        void tick();

        void triggered();

        void triggered(QString eventName);

    private slots:
        virtual void nextFrame();

    public:
        void addState(QState *state);

        virtual QRectF boundingRect() const;

        void changeDir();

        void init();

        /*!
         * \brief Paints the contents of the item in local coordinates.
         * \param painter paints the content
         * \param option provides style options for the item
         * \param widget points to the widget that is being painted on
         */
        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); ///< must be re-implemented here to pain the box on the paint-event

        void removeState(QState *state);

        virtual bool sceneEventFilter(QGraphicsItem *watched, QEvent *event);

    protected:
        void start();
        void stop();

    protected:
        bool _hasInitialState;

        QStateMachine *_stateMachine;

        GETSET(int, frameWidth, FrameWidth)

        GETSET(int, frameHeight, FrameHeight)

        GETSET(QPixmap*, image, Image)

        GETSET(int, x, X)

        GETSET(int, xDir, XDir)

        GETSET(int, y, Y)

};

#endif // SPRITE_H
