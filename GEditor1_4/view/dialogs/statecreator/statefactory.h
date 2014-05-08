#ifndef STATEFACTORY_H
#define STATEFACTORY_H

class AbstractSpriteState;
class QString;

class StateFactory {

    public:
        StateFactory();

    public:
        bool connectToSprite(AbstractSpriteState *state, QString name);

        void create(AbstractSpriteState *_state);
};

#endif // STATEFACTORY_H
