#include "gobject.h"

// --------------------------------------------------------------------------------------
// magic --------------------------------------------------------------------------------


GObject::GObject(QObject *parent) : ToyObject(parent),
    _isDropable(false),
    _clickAreaIdx(0),
    _textRelation(0),
    _urls(QStringList()),
    _inventar(0) {}

GObject::~GObject(){
    delete _inventar;
    _inventar = 0;
}


// --------------------------------------------------------------------------------------
// public -------------------------------------------------------------------------------


int GObject::getToyType(){
    return TGObject;
}
