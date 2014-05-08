#include "manager.h"
#include "drawer.h"

// --------------------------------------------------------------------------------------
// static -------------------------------------------------------------------------------


bool Manager::forwardUpdate = true;


bool Manager::getForwardUpdate(){
    return forwardUpdate;
}

bool Manager::invertForwardUpdate(){
    return (forwardUpdate = !forwardUpdate);
}


// --------------------------------------------------------------------------------------
// magic --------------------------------------------------------------------------------


Manager::Manager() : QObject(),
    _depth(10),
    _height(800),
    _levelObjects(new QMap<QString, ToyObject *>()),
    _maxNumOfFrames(20),
    _maxNumOfLoops(20),
    SETTINGS_FILE(QApplication::applicationDirPath().left(1) + ":/settings.ini"),
    _width(500){

    connect(this, &Manager::notify, Drawer::instance(), &Drawer::drawObject);
    connect(Drawer::instance(), &Drawer::notify, this, &Manager::updateMap);
}


// --------------------------------------------------------------------------------------
// slots --------------------------------------------------------------------------------


void Manager::updateMap(QString key){

    //TODO
    //update manager

    //update drawer?

    if(!(Manager::forwardUpdate = !Manager::forwardUpdate))
        emit notify(key);
}

void Manager::updateName(QString oldName, QString newName){

    if(!_levelObjects->contains(newName) && _levelObjects->contains(oldName)){
        ToyObject *to = _levelObjects->value(oldName);
        to->setName(newName);
        _levelObjects->insert(newName, to);
        _levelObjects->remove(oldName);
    }
}


// --------------------------------------------------------------------------------------
// public -------------------------------------------------------------------------------


void Manager::addToyObject(QString id, ToyObject *object){

    _levelObjects->insert(id, object);
    emit notify(object->getName());
}

QVariant Manager::loadSettings(QString key){

    QSettings settings(SETTINGS_FILE, QSettings::NativeFormat, this);
    if(settings.contains(key))
        return settings.value(key, NULL);
    return NULL;
}

QMap<QString, ToyObject*> *Manager::getLevelObjects(){
    return _levelObjects;
}

bool Manager::removeToyObject(QString id){

    Drawer::instance()->removeItemFromScene(id);
    return (0 != _levelObjects->remove(id));
}

void Manager::setLevelObjects(QMap<QString, ToyObject *> *levelObjects){
    _levelObjects = levelObjects;
}

void Manager::writeSettings(QString key, QVariant value){

    QSettings settings(SETTINGS_FILE, QSettings::NativeFormat, this);

    if(!key.isEmpty() && NULL != value)
        settings.setValue(key, value);
}
