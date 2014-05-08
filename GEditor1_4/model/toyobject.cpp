#include "toyobject.h"
#include "../control/manager.h"

// --------------------------------------------------------------------------------------
// magic --------------------------------------------------------------------------------


ToyObject::ToyObject(QObject *parent) : ISerializable(parent),
    _cursor(new GCursor),
    _name(""),
    _height(150),
    _width(150),
    _x(10),
    _y(10),
    _z(0),
    _isMovable(true),
    _visibility(true){

    if(!_name.isEmpty())
        Manager::instance()->addToyObject(_name, this);
}


// --------------------------------------------------------------------------------------
// public -------------------------------------------------------------------------------


//TODO
void ToyObject::crop(quint32, quint32, quint32, quint32){}
