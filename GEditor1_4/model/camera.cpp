#include "camera.h"

// --------------------------------------------------------------------------------------
// magic --------------------------------------------------------------------------------


Camera::Camera(QObject *parent) : ToyObject(parent), _background(0){}

Camera::~Camera(){
    delete _background;
    _background = 0;
}


// --------------------------------------------------------------------------------------
// public -------------------------------------------------------------------------------


int Camera::getToyType(){
    return TCamera;
}

//TODO
void Camera::move(qint32, qint32){}
