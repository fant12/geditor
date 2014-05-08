#include "abstractspritestate.h"
#include "../../../view/canvas/sprite.h"

AbstractSpriteState::AbstractSpriteState(Sprite *sprite) : QState(0),
    _sprite(sprite),
    _maxRangeX(0),
    _maxRangeY(0),
    _minRangeX(0),
    _minRangeY(0){

}

void AbstractSpriteState::onEntry(QEvent *){
    connect(_sprite, &Sprite::tick, this, &AbstractSpriteState::nextFrame);
}

void AbstractSpriteState::onExit(QEvent *event){
    disconnect(_sprite, &Sprite::tick, this, &AbstractSpriteState::nextFrame);
}
