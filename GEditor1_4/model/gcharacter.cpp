#include "gcharacter.h"

#include <QStringList>

// --------------------------------------------------------------------------------------
// magic --------------------------------------------------------------------------------


GCharacter::GCharacter(QObject *parent) : ToyObject(parent),
    _animDelay(0),
    _numOfFrames(0),
    _numOfLoop(1),
    _isDropable(false),
    _adjVolumWithScaling(true),
    _urls(QStringList()),
    _inventar(0)
    //TODO state(GCState::STANDING)
{}


// --------------------------------------------------------------------------------------
// public -------------------------------------------------------------------------------


int GCharacter::getToyType(){
    return TGCharacter;
}

bool GCharacter::isCollide(){
    return false;
}

//TODO
void GCharacter::walking(){}
