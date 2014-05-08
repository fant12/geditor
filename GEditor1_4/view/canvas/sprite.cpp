#include "sprite.h"

#include <QApplication>
#include <QEvent>
#include <QPainter>
#include <QState>
#include <QStateMachine>
#include <QTimer>

static QMap<int, QString> values() {

    QMap<int, QString> map;
    map.insert(QEvent::DragEnter, QObject::tr("Drag & Enter"));
    map.insert(QEvent::DragMove, QObject::tr("Drag & Move"));
    map.insert(QEvent::Drop, QObject::tr("Drop"));
    map.insert(QEvent::Enter, QObject::tr("Enter"));
    map.insert(QEvent::FocusIn, QObject::tr("FocusIn"));
    map.insert(QEvent::FocusOut, QObject::tr("FocusOut"));
    map.insert(QEvent::GrabKeyboard, QObject::tr("Grab Keyboard"));
    map.insert(QEvent::GrabMouse, QObject::tr("Grab Mouse"));
    map.insert(QEvent::GraphicsSceneDragEnter, QObject::tr("Scene: Drag & Enter"));
    map.insert(QEvent::GraphicsSceneDragLeave, QObject::tr("Scene: Drag & Leave"));
    map.insert(QEvent::GraphicsSceneDragMove, QObject::tr("Scene: Drag & Move"));
    map.insert(QEvent::GraphicsSceneDrop, QObject::tr("Scene: Drop"));
    map.insert(QEvent::GraphicsSceneHoverEnter, QObject::tr("Scene: Hover & Enter"));
    map.insert(QEvent::GraphicsSceneHoverLeave, QObject::tr("Scene: Hover & Leave"));
    map.insert(QEvent::GraphicsSceneHoverMove, QObject::tr("Scene: Hover & Move"));
    map.insert(QEvent::GraphicsSceneMouseDoubleClick, QObject::tr("Scene: Double Click"));
    map.insert(QEvent::GraphicsSceneMouseMove, QObject::tr("Scene: Move Mouse"));
    map.insert(QEvent::GraphicsSceneMousePress, QObject::tr("Scene: Press Mousebutton"));
    map.insert(QEvent::GraphicsSceneMouseRelease, QObject::tr("Scene: Release Mousebutton"));
    map.insert(QEvent::GraphicsSceneMove, QObject::tr("Scene: Move"));
    map.insert(QEvent::GraphicsSceneResize, QObject::tr("Scene: Resize"));
    map.insert(QEvent::GraphicsSceneWheel, QObject::tr("Scene: Wheel"));
    map.insert(QEvent::Hide, QObject::tr("Hide"));
    map.insert(QEvent::HideToParent, QObject::tr("Hide to Parent"));
    map.insert(QEvent::HoverEnter, QObject::tr("Hover & Enter"));
    map.insert(QEvent::HoverLeave, QObject::tr("Hover & Leave"));
    map.insert(QEvent::HoverMove, QObject::tr("Hover & Move"));
    map.insert(QEvent::IconDrag, QObject::tr("Drag Icon"));
    map.insert(QEvent::IconTextChange, QObject::tr("Change Icon text"));
    map.insert(QEvent::InputMethod, QObject::tr("Input"));
    map.insert(QEvent::KeyPress, QObject::tr("Press Key"));
    map.insert(QEvent::KeyRelease, QObject::tr("Release Key"));
    map.insert(QEvent::Leave, QObject::tr("Leave"));
    map.insert(QEvent::NonClientAreaMouseButtonDblClick, QObject::tr("Double click outside"));
    map.insert(QEvent::NonClientAreaMouseButtonPress, QObject::tr("Press Mousebutton outside"));
    map.insert(QEvent::NonClientAreaMouseButtonRelease, QObject::tr("Release Mousebutton outside"));
    map.insert(QEvent::NonClientAreaMouseMove, QObject::tr("Move Mouse outside"));
    map.insert(QEvent::ModifiedChange, QObject::tr("Change modification"));
    map.insert(QEvent::MouseButtonDblClick, QObject::tr("Double click"));
    map.insert(QEvent::MouseButtonPress, QObject::tr("Press Mousebutton"));
    map.insert(QEvent::MouseButtonRelease, QObject::tr("Release Mousebutton"));
    map.insert(QEvent::MouseMove, QObject::tr("Move mouse"));
    map.insert(QEvent::MouseTrackingChange, QObject::tr("Change mouse tracking"));
    map.insert(QEvent::Move, QObject::tr("Move"));
    map.insert(QEvent::Paint, QObject::tr("Repaint"));
    map.insert(QEvent::PaletteChange, QObject::tr("Palette change"));
    map.insert(QEvent::ParentChange, QObject::tr("Parent change"));
    map.insert(QEvent::Resize, QObject::tr("Resize"));
    map.insert(QEvent::Shortcut, QObject::tr("Shortcut (default)"));
    map.insert(QEvent::ShortcutOverride, QObject::tr("Shortcut (custom)"));
    map.insert(QEvent::Show, QObject::tr("Show"));
    map.insert(QEvent::ShowToParent, QObject::tr("Show to parent"));
    map.insert(QEvent::StateMachineSignal, QObject::tr("State Machine"));
    map.insert(QEvent::StyleChange, QObject::tr("Style change"));
    map.insert(QEvent::UngrabKeyboard, QObject::tr("Ungrab keyboard"));
    map.insert(QEvent::UngrabMouse, QObject::tr("Ungrab mouse"));
    map.insert(QEvent::Wheel, QObject::tr("Wheel"));
    map.insert(QEvent::DynamicPropertyChange, QObject::tr("Dynamic property change"));
    map.insert(QEvent::TouchBegin, QObject::tr("Touch begin"));
    map.insert(QEvent::TouchUpdate, QObject::tr("Touch update"));
    map.insert(QEvent::TouchEnd, QObject::tr("Touch end"));
    map.insert(QEvent::Gesture, QObject::tr("Gesture (default)"));
    map.insert(QEvent::GestureOverride, QObject::tr("Gesture (custom)"));

    return map;
}
const QMap<int, QString> Sprite::EVENT_TYPES = values();

Sprite::Sprite(QString name, qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent)
    : QGraphicsObject(parent), CanvasItem(name, x, y, width, height),
    _frameHeight(0),
    _frameWidth(0),
    _hasInitialState(false),
    _image(new QPixmap("")),
    _stateMachine(new QStateMachine(this)),
    _x(0),
    _xDir(1),
    _y(0){

    changeDir();
    _stateMachine->start();
}

Sprite::~Sprite(){
    delete _image;
}

void Sprite::start(){

    stop();
    _stateMachine->start();
}

void Sprite::stop(){

    if(_stateMachine->isRunning())
        _stateMachine->stop();
}

void Sprite::addState(QState *state){

    stop();
    _stateMachine->addState(state);

    if(!_hasInitialState)
        _stateMachine->setInitialState(state);

    start();
}

void Sprite::removeState(QState *state){

    stop();
    _stateMachine->removeState(state);
}

QRectF Sprite::boundingRect() const {
    return QRectF(0, 0, _frameWidth, _frameHeight);
}

void Sprite::changeDir(){
    QGraphicsObject::setScale((0 < CanvasItem::scale()) ? -1 : 1);
}

bool Sprite::sceneEventFilter(QGraphicsItem *, QEvent *event){

    if(EVENT_TYPES.contains(event->type()))
        start();
    return true;
}

void Sprite::init(){

    QTimer *timer = new QTimer(qApp);
    //TODO timer->start(_frameDelay);

    connect(timer, &QTimer::timeout, this, &Sprite::nextFrame);
}

void Sprite::nextFrame(){

    emit tick();
    QGraphicsObject::update();
}

void Sprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){
    painter->drawPixmap(0, 0, *_image, _frameWidth * _x, _frameHeight * _y, _frameWidth, _frameHeight);
}
