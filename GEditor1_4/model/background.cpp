#include "background.h"

// --------------------------------------------------------------------------------------
// magic --------------------------------------------------------------------------------


Background::Background(QObject *parent) : ToyObject(parent),
    _color(QColor("#aaaaaa")),
    _url(""){}


// --------------------------------------------------------------------------------------
// public -------------------------------------------------------------------------------


int Background::getToyType(){
    return TBackground;
}
