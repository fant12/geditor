#ifndef ABSTRACTSPRITESTATE_H
#define ABSTRACTSPRITESTATE_H

#include "../../../templates/getset.h"
#include <QState>

class Sprite;

class AbstractSpriteState : public QState {

        Q_OBJECT

    public:
        explicit AbstractSpriteState(Sprite *sprite);

    protected slots:
        virtual void nextFrame() = 0;

    public:
        virtual void onEntry(QEvent *event);

        virtual void onExit(QEvent *event);

    protected:
        Sprite *_sprite;

        GETSET(int, frameDelay, FrameDelay)

        GETSET(int, maxRangeX, MaxRangeX)

        GETSET(int, maxRangeY, MaxRangeY)

        GETSET(int, minRangeX, MinRangeX)

        GETSET(int, minRangeY, MinRangeY)

        GETSET(int, steps, Steps)

};

#endif // ABSTRACTSPRITESTATE_H
