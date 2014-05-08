#include "drawer.h"

// --------------------------------------------------------------------------------------
// magic --------------------------------------------------------------------------------


Drawer::Drawer() : QObject(), _items(new QMap<QString, CanvasItem *>()){}


// --------------------------------------------------------------------------------------
// slots --------------------------------------------------------------------------------


void Drawer::drawObject(QString key){

    ToyObject *to = Manager::instance()->getLevelObjects()->value(key);

    if(_items->contains(key))
        removeItemFromScene(key);

    switch(to->getToyType()){
        case TBackground:
            drawBackground(dynamic_cast<Background *>(to));
            break;
        case TCamera:
            drawCamera(dynamic_cast<Camera *>(to));
            break;
        case TClickArea:
            drawClickArea(dynamic_cast<ClickArea *>(to));
            break;
        case TDoor:
            drawDoor(dynamic_cast<Door *>(to));
            break;
        case TGCharacter:
            drawGCharacter(dynamic_cast<GCharacter *>(to));
            break;
        case TGObject:
            drawGObject(dynamic_cast<GObject *>(to));
            break;
        case TInventar:
            drawInventar(dynamic_cast<Inventar *>(to));
            break;
        case TItem:
            drawItem(dynamic_cast<Item *>(to));
            break;
        case TPlayer:
            drawPlayer(dynamic_cast<Player *>(to));
            break;
        case TSoundArea:
            drawSoundArea(dynamic_cast<SoundArea *>(to));
            break;
        case TVideoArea:
            drawVideoArea(dynamic_cast<VideoArea *>(to));
    }

    if(!Manager::invertForwardUpdate())
        emit notify(key);
}


// --------------------------------------------------------------------------------------
// public -------------------------------------------------------------------------------


QMap<QString, CanvasItem *> *Drawer::getItems(){
    return _items;
}

void Drawer::removeItemFromScene(QString key){

    if(_items->contains(key)){
        _scene->removeItem(_items->value(key));
        _items->remove(key);
    }
}

void Drawer::setItems(QMap<QString, CanvasItem *> *items){
    _items = items;
}

void Drawer::updateToyObject(CanvasItem *item, ToyObject *to){

    to->setHeight((int) item->getHeight());
    to->setWidth((int) item->getWidth());
    to->setRotation((int) item->rotation());
    to->setX((int) item->getX());
    to->setY((int) item->getY());
    to->setZ((int) item->zValue());
}

// --------------------------------------------------------------------------------------
// protected ----------------------------------------------------------------------------


void Drawer::drawBackground(Background *){}

void Drawer::drawCamera(Camera *cm){

    CanvasItem *it = new CanvasItem(cm->getName(), cm->getX(), cm->getY(), cm->getWidth(), cm->getHeight());
    it->setZValue(cm->getZ());
    _scene->addItem(it);
    _items->insert(cm->getName(), it);

    QGraphicsItem *a = _scene->addEllipse(50,50,100,100);
    a->setFlag(QGraphicsItem::ItemIsMovable);
    a->setFlag(QGraphicsItem::ItemIsSelectable);

    //RotatorCircle *rotator = new RotatorCircle;
    //rotator->setRect(150, 230, 80, 60);
    //_scene->addItem(rotator);

    /*RotatorItem *start = new RotatorItem;
    RotatorItem *end = new RotatorItem;
    Connector *connector = new Connector(start, end);
    start->addConnector(connector);
    end->addConnector(connector);
    _scene->addItem(start);
    _scene->addItem(end);
    _scene->addItem(connector);*/
}

void Drawer::drawClickArea(ClickArea *ca){

    CanvasItem *it = new CanvasItem(ca->getName(), ca->getX(), ca->getY(), ca->getWidth(), ca->getHeight(), Qt::DotLine, Qt::blue);
    it->setZValue(ca->getZ());
    _scene->addItem(it);
    _items->insert(ca->getName(), it);
}

void Drawer::drawDoor(Door *dr){

    CanvasItem *it = new CanvasItem(dr->getName(), dr->getX(), dr->getY(), dr->getWidth(), dr->getHeight(), Qt::DashDotDotLine, Qt::blue);
    it->setZValue(dr->getZ());
    _scene->addItem(it);
    _items->insert(dr->getName(), it);
}

void Drawer::drawGCharacter(GCharacter *gc){

    CanvasItem *it = new CanvasItem(gc->getName(), gc->getX(), gc->getY(), gc->getWidth(), gc->getHeight());
    it->setZValue(gc->getZ());
    _scene->addItem(it);
    _items->insert(gc->getName(), it);
}

void Drawer::drawGObject(GObject *go){

    CanvasItem *it = new CanvasItem(go->getName(), go->getX(), go->getY(), go->getWidth(), go->getHeight());
    it->setZValue(go->getZ());
    _scene->addItem(it);
    _items->insert(go->getName(), it);
}

void Drawer::drawInventar(Inventar *){}

void Drawer::drawItem(Item *){}

void Drawer::drawPlayer(Player *pl){

    CanvasItem *it = new CanvasItem(pl->getName(), pl->getX(), pl->getY(), pl->getWidth(), pl->getHeight());
    it->setZValue(pl->getZ());
    _scene->addItem(it);
    _items->insert(pl->getName(), it);
}

void Drawer::drawSoundArea(SoundArea *sa){

    CanvasItem *it = new CanvasItem(sa->getName(), sa->getX(), sa->getY(), sa->getWidth(), sa->getHeight());
    it->setZValue(sa->getZ());
    _scene->addItem(it);
    _items->insert(sa->getName(), it);
}

void Drawer::drawVideoArea(VideoArea *va){

    CanvasItem *it = new CanvasItem(va->getName(), va->getX(), va->getY(), va->getWidth(), va->getHeight());
    it->setZValue(va->getZ());
    _scene->addItem(it);
    _items->insert(va->getName(), it);
}
