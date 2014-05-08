#include "statefactory.h"
#include "../../../control/drawer.h"
#include "../../canvas/sprite.h"

StateFactory::StateFactory(){
}

bool StateFactory::connectToSprite(AbstractSpriteState *state, QString name){

    CanvasItem *item = Drawer::instance()->getItems()->value(name, NULL);

    if(item){
        Sprite *sprite = new Sprite(name, item->getX(), item->getY(), item->getWidth(), item->getHeight());
        sprite->getStateMachine()->addState(state);
        Drawer::instance()->getItems()->insert(name, sprite);
        delete item;

        return true;
    }
    return false;
}

void StateFactory::create(AbstractSpriteState *_state){

    connectToSprite(state, "");
}
