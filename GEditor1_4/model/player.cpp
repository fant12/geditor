#include "player.h"

// --------------------------------------------------------------------------------------
// magic --------------------------------------------------------------------------------


Player::Player(QObject *parent) : GCharacter(parent){}


// --------------------------------------------------------------------------------------
// public -------------------------------------------------------------------------------


int Player::getToyType(){
    return TPlayer;
}

bool Player::isCollide(){
    return false;
}

void Player::walking(){}