#include "door.h"

// --------------------------------------------------------------------------------------
// magic --------------------------------------------------------------------------------


Door::Door(QObject *parent) : ClickArea(parent), _anchor(0){}


// --------------------------------------------------------------------------------------
// public -------------------------------------------------------------------------------


int Door::getToyType(){
    return TDoor;
}