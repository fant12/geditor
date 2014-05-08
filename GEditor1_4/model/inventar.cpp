#include "inventar.h"

// --------------------------------------------------------------------------------------
// magic --------------------------------------------------------------------------------


Inventar::Inventar(QObject *parent) : ToyObject(parent),
    _items(new QList<Item *>()){}

Inventar::~Inventar(){
    delete _items;
    _items = 0;
}


// --------------------------------------------------------------------------------------
// public -------------------------------------------------------------------------------


void Inventar::addItem(Item *item){
    _items->append(item);
}

int Inventar::getToyType(){
    return TInventar;
}

bool Inventar::removeItem(Item *item){
    return _items->removeOne(item);
}
