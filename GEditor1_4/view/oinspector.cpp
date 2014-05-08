#include "oinspector.h"

#include "dialogs/cadialog.h"

#include <QFileDialog>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QPushButton>

#define ROWIH 22
#define ROWH 35

// --------------------------------------------------------------------------------------
// magic --------------------------------------------------------------------------------


OInspector::OInspector(EList *elist, QWidget *parent) : QTableWidget(parent),
    _curObject(NULL),
    _elist(elist){

    _elist->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    setColumnCount(2);
    setHorizontalHeaderItem(0, new QTableWidgetItem("Attribute"));
    setHorizontalHeaderItem(1, new QTableWidgetItem("Value"));
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setSpan(1, 1, 2, 2);

    verticalHeader()->setVisible(false);
    horizontalHeader()->setHighlightSections(false);
    horizontalHeader()->setStretchLastSection(true);
    horizontalHeaderItem(0)->setTextAlignment(Qt::AlignCenter);
    horizontalHeaderItem(1)->setTextAlignment(Qt::AlignCenter);
}


// --------------------------------------------------------------------------------------
// slots --------------------------------------------------------------------------------


void OInspector::createCADialog(){

    CADialog caDialog(this);
    caDialog.exec();
}

void OInspector::createGameElem(TObjectTypes type, QString name){

    clearTable();

    switch(type){
        case TBackground: {
            Background *bg = new Background(this);
            initNewObject(bg, name);
            prepare(bg);
            break;
        }
        case TCamera: {
            Camera *cm = new Camera(this);
            initNewObject(cm, name);
            prepare(cm);
            break;
        }
        case TClickArea: {
            ClickArea *ca = new ClickArea(this);
            initNewObject(ca, name);
            prepare(ca);
            break;
        }
        case TDoor: {
            Door *dr = new Door(this);
            initNewObject(dr, name);
            prepare(dr);
            break;
        }
        case TGCharacter: {
            GCharacter *gc = new GCharacter(this);
            initNewObject(gc, name);
            prepare(gc);
            break;
        }
        case TGObject: {
            GObject *go = new GObject(this);
            initNewObject(go, name);
            prepare(go);
            break;
        }
        case TInventar: {
            Inventar *iv = new Inventar(this);
            initNewObject(iv, name);
            prepare(iv);
            break;
        }
        case TItem: {
            Item *it = new Item(this);
            initNewObject(it, name);
            prepare(it);
            break;
        }
        case TPlayer: {
            Player *pl = new Player(this);
            initNewObject(pl, name);
            prepare(pl);
            break;
        }
        case TSoundArea: {
            SoundArea *sa = new SoundArea(this);
            initNewObject(sa, name);
            prepare(sa);
            break;
        }
        case TVideoArea: {
            VideoArea *va = new VideoArea(this);
            initNewObject(va, name);
            prepare(va);
            break;
        }
    }
}

void OInspector::setBGColor(int row, int col){

    if(item(row, 0)->text()=="Color" && 1 == col){

        QString value = item(row, col)->text();

        if(!value.isEmpty() && 7 == value.length()){

            QRegExp regex("^#([A-Fa-f0-9]{6}|[A-Fa-f0-9]{3})$");
            if(value.contains(regex)){
                item(row, col)->setBackgroundColor(QColor(value));

                if(NULL != _curObject && TBackground == _curObject->getToyType())
                    ((Background *) _curObject)->setColor(QColor(value));
            }
        }
    }
}

void OInspector::setBGURL(QString url){

    if(NULL != _curObject && TBackground == _curObject->getToyType())
        ((Background *) _curObject)->setUrl(url);
}

void OInspector::setCALocked(int locked){

    if(NULL != _curObject && TClickArea == _curObject->getToyType())
        ((ClickArea *) _curObject)->setLocked(locked);
}

void OInspector::setDRAnchor(QString value){

    if(NULL != _curObject && TDoor == _curObject->getToyType())
        ((Door *) _curObject)->setAnchor(value.toInt());
}

void OInspector::setGCAdjVolumWithScaling(QString adjVolumWithScaling){

    if(NULL != _curObject && TGCharacter == _curObject->getToyType())
        ((GCharacter *) _curObject)->setAdjVolumWithScaling(adjVolumWithScaling.toFloat());
}

void OInspector::setGCAnimDelay(QString animDelay){

    if(NULL != _curObject)
        if(TGCharacter == _curObject->getToyType() || TPlayer == _curObject->getToyType())
            ((GCharacter *) _curObject)->setAnimDelay(animDelay.toInt());
}

void OInspector::setGCDropable(int isDropable){

    if(NULL != _curObject)
        if(TGCharacter == _curObject->getToyType() || TPlayer == _curObject->getToyType())
            ((GCharacter *) _curObject)->setIsDropable(isDropable);
}

void OInspector::setGCUrls(QString urls){

    if(NULL != _curObject)
        if(TGCharacter == _curObject->getToyType() || TPlayer == _curObject->getToyType())
            ((GCharacter *) _curObject)->setUrls(urls.split(';'));
}

void OInspector::setGODropable(int isDropable){

    if(NULL != _curObject && TGObject == _curObject->getToyType())
        ((GObject *) _curObject)->setIsDropable(isDropable);
}

void OInspector::setGOUrls(QString urls){

    if(NULL != _curObject && TGObject == _curObject->getToyType())
        ((GObject *) _curObject)->setUrls(urls.split(';'));
}

void OInspector::setMALoop(int loop){

    if(NULL != _curObject)
        if(TSoundArea == _curObject->getToyType() || TVideoArea == _curObject->getToyType())
            ((MediaArea *) _curObject)->setLoop(loop);
}

void OInspector::setTOCursor(int idx){

    if(NULL != _curObject)
        _curObject->getCursor()->setCursor(idx);
}

void OInspector::setTOMovable(int isMovable){

    if(NULL != _curObject)
        _curObject->setIsMovable((bool) isMovable);
}

void OInspector::setTOVisibility(int visibility){

    if(NULL != _curObject)
        _curObject->setVisibility((bool) visibility);
}

void OInspector::setUrl(){
    emit fieldChanged((QFileDialog::getOpenFileName(this, tr("Background Image"), QDir::homePath(), tr("Images (*.png *.jpg *.svg)"))));
}

void OInspector::setUrls(){

    QStringList urls = QFileDialog::getOpenFileNames(this, tr("Images"), QDir::homePath(), tr("Images (*.png *.jpg *.svg)"));
    emit fieldChanged(urls.join(';'));
}

void OInspector::update(ToyObject *to){

    clearTable();

    switch(to->getToyType()){
        case TBackground:
            prepare(dynamic_cast<Background *>(to));
            break;
        case TCamera:
            prepare(dynamic_cast<Camera *>(to));
            break;
        case TClickArea:
            prepare(dynamic_cast<ClickArea *>(to));
            break;
        case TDoor:
            prepare(dynamic_cast<Door *>(to));
            break;
        case TGCharacter:
            prepare(dynamic_cast<GCharacter *>(to));
            break;
        case TGObject:
            prepare(dynamic_cast<GObject *>(to));
            break;
        case TInventar:
            prepare(dynamic_cast<Inventar *>(to));
            break;
        case TItem:
            prepare(dynamic_cast<Item *>(to));
            break;
        case TPlayer:
            prepare(dynamic_cast<Player *>(to));
            break;
        case TSoundArea:
            prepare(dynamic_cast<SoundArea *>(to));
            break;
        case TVideoArea:
            prepare(dynamic_cast<VideoArea *>(to));
            break;
    }
}

void OInspector::updateName(QString newName){

    if(NULL != _curObject && !newName.isEmpty() &&
            !Manager::instance()->getLevelObjects()->contains(newName)){

        _curObject->setName(newName);
        _elist->selectedItems().first()->setText(newName);

        Manager *man = Manager::instance();
        man->removeToyObject(_curObject->getName());
        man->addToyObject(_curObject->getName(), _curObject);
    }
}

void OInspector::updateSelectedObject(int row){

    QString objName = _elist->item(row, 0)->text();
    QMap<QString, ToyObject*> *objMap = Manager::instance()->getLevelObjects();

    if(objMap->contains(objName))
        _curObject = objMap->value(objName, NULL);

    update(_curObject);
}


// --------------------------------------------------------------------------------------
// private ------------------------------------------------------------------------------


void OInspector::clearTable(){

    for(int i = rowCount()-1; 0 <= i; --i)
        removeRow(i);
}

QComboBox *OInspector::createBoolCBox(bool value){

    QComboBox *cbox = new QComboBox(this);
    cbox->addItem("false", QVariant(false)); // false == (bool)0
    cbox->addItem("true", QVariant(true));
    cbox->setCurrentIndex(value);

    return cbox;
}

QSpinBox *OInspector::createSpinner(quint32 value, quint32 max){

    QSpinBox *spin = new QSpinBox(this);
    spin->setRange(0, max);
    spin->setSingleStep(1);
    spin->setValue(value);

    return spin;
}

void OInspector::defaultPreparation(ToyObject *to){

    int row;

    // name
    insertRow(row = rowCount());
    setItem(row, 0, new QTableWidgetItem("name"));
    QLineEdit *nameEdit = new QLineEdit(to->getName(), this);
    setCellWidget(row, 1, nameEdit);

    connect(_elist, &EList::updateObjectName, nameEdit, &QLineEdit::setText);
    connect(nameEdit, &QLineEdit::textChanged, this, &OInspector::updateName);


    // cursor
    insertRow(row = rowCount());
    setItem(row, 0, new QTableWidgetItem("cursor"));
    QComboBox *cboxCurs = new QComboBox(this);
    cboxCurs->addItems(*GCursor::getPosCursorNames());
    cboxCurs->setCurrentIndex(to->getCursor()->getCursor());
    setCellWidget(row, 1, cboxCurs);

    connect(cboxCurs, SIGNAL(currentIndexChanged(int)), this, SLOT(setTOCursor(int)));


    // isMovable
    insertRow(row = rowCount());
    setItem(row, 0, new QTableWidgetItem("isMovable"));
    QComboBox *cboxIsM = createBoolCBox(to->getIsMovable());
    setCellWidget(row, 1, cboxIsM);

    connect(cboxIsM, SIGNAL(currentIndexChanged(int)), this, SLOT(setTOMovable(int)));


    // visibility
    insertRow(row = rowCount());
    setItem(row, 0, new QTableWidgetItem("visibility"));
    QComboBox *cboxVis = createBoolCBox(to->getVisibility());
    setCellWidget(row, 1, cboxVis);

    //connect(cmbProfiles, static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
    //        this, &MyClass::loadProfilesDetails);
    connect(cboxVis, SIGNAL(currentIndexChanged(int)), this, SLOT(setTOVisibility(int)));


    // width
    insertRow(row = rowCount());
    setItem(row, 0, new QTableWidgetItem("width"));
    QSpinBox *spinW = createSpinner(to->getWidth(), Manager::instance()->getWidth());
    setCellWidget(row, 1, spinW);

    connect(spinW, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            to, &ToyObject::setWidth);


    // height
    insertRow(row = rowCount());
    setItem(row, 0, new QTableWidgetItem("height"));
    QSpinBox *spinH = createSpinner(to->getHeight(), Manager::instance()->getHeight());
    setCellWidget(row, 1, spinH);

    connect(spinH, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            to, &ToyObject::setHeight);

    // rotation
    insertRow(row = rowCount());
    setItem(row, 0, new QTableWidgetItem("rotation"));
    QSpinBox *spinR = createSpinner(to->getRotation(), 360);
    setCellWidget(row, 1, spinR);

    connect(spinR, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            to, &ToyObject::setRotation);

    // x
    insertRow(row = rowCount());
    setItem(row, 0, new QTableWidgetItem("x"));
    QSpinBox *spinX = createSpinner(to->getX(), Manager::instance()->getWidth());
    setCellWidget(row, 1, spinX);

    connect(spinX, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            to, &ToyObject::setX);


    // y
    insertRow(row = rowCount());
    setItem(row, 0, new QTableWidgetItem("y"));
    QSpinBox *spinY = createSpinner(to->getY(), Manager::instance()->getHeight());
    setCellWidget(row, 1, spinY);

    connect(spinY, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            to, &ToyObject::setY);


    // z
    insertRow(row = rowCount());
    setItem(row, 0, new QTableWidgetItem("z"));
    QSpinBox *spinZ = createSpinner(to->getZ(), Manager::instance()->getDepth());
    setCellWidget(row, 1, spinZ);

    connect(spinZ, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            to, &ToyObject::setZ);
}

void OInspector::formatCells(){

    for(int i = 0; rowCount() > i; ++i){
        setRowHeight(i, ROWH);
        item(i, 0)->setTextAlignment(Qt::AlignCenter);
        item(i, 0)->setFlags(item(i, 0)->flags() ^ Qt::ItemIsEditable);
    }
}

void OInspector::initNewObject(ToyObject *to, QString name){

    to->setName(name);
    Manager::instance()->addToyObject(name, to);
}

void OInspector::prepare(Background *background){

    defaultPreparation(background);

    int row;


    // color
    insertRow(row = rowCount());
    setItem(row, 0, new QTableWidgetItem("Color"));
    setItem(row, 1, new QTableWidgetItem(background->getColor().name()));
    item(row, 1)->setBackgroundColor(background->getColor().name());
    item(row, 1)->setTextAlignment(Qt::AlignCenter);

    connect(this, &OInspector::cellChanged, this, &OInspector::setBGColor);


    // url
    insertRow(row = rowCount());
    setItem(row, 0, new QTableWidgetItem("URL"));
    QWidget *urlAttr = new QWidget(this);
        QHBoxLayout *urlLayout = new QHBoxLayout(urlAttr);
            QLineEdit *urlEdit = new QLineEdit(background->getUrl(), urlAttr);
            urlEdit->setFixedHeight(ROWIH);

            QPushButton *urlBtn = new QPushButton("...", urlAttr);
            urlBtn->setFixedSize(20, ROWIH);
        urlLayout->addWidget(urlEdit);
        urlLayout->addWidget(urlBtn);
    urlAttr->setLayout(urlLayout);
    setCellWidget(row, 1, urlAttr);
    formatCells();

    connect(urlBtn, &QPushButton::clicked, this, &OInspector::setUrl);
    connect(this, &OInspector::fieldChanged, urlEdit, &QLineEdit::setText);
    connect(urlEdit, &QLineEdit::textChanged, this, &OInspector::setBGURL);
}

void OInspector::prepare(Camera *camera){

    defaultPreparation(camera);
    formatCells();
}

void OInspector::prepare(ClickArea *clickArea){

    defaultPreparation(clickArea);

    int row;


    // locked
    insertRow(row = rowCount());
    setItem(row, 0, new QTableWidgetItem("locked"));
    QComboBox *cboxLock = createBoolCBox(clickArea->getLocked());
    setCellWidget(row, 1, cboxLock);
    formatCells();

    connect(cboxLock, SIGNAL(currentIndexChanged(int)), this, SLOT(setCALocked(int)));
}

void OInspector::prepare(Door *door){

    defaultPreparation(door);

    int row;


    // anchor
    insertRow(row = rowCount());
    setRowHeight(row, ROWH);
    setItem(row, 0, new QTableWidgetItem("anchor"));
    QComboBox *cboxAnc = new QComboBox(this);
    if(cboxAnc->count() > 0)
        cboxAnc->setCurrentText(QString::number(door->getAnchor()));
    setCellWidget(row, 1, cboxAnc);
    formatCells();

    connect(cboxAnc, SIGNAL(currentIndexChanged(QString)), this, SLOT(setDRAnchor(QString)));
}

void OInspector::prepare(GCharacter *gCharacter){

    defaultPreparation(gCharacter);

    int row;


    // animation delay
    insertRow(row = rowCount());
    setItem(row, 0, new QTableWidgetItem("animDelay"));
    QLineEdit *delayLE = new QLineEdit(QString::number(gCharacter->getAnimDelay()), this);
    setCellWidget(row, 1, delayLE);

    connect(delayLE, &QLineEdit::textChanged, this, &OInspector::setGCAnimDelay);


    // number of frames
    insertRow(row = rowCount());
    setItem(row, 0, new QTableWidgetItem("frames"));
    QSpinBox *spinFram = createSpinner(gCharacter->getNumOfFrames(), Manager::instance()->getMaxNumOfFrames());
    setCellWidget(row, 1, spinFram);

    connect(spinFram, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            gCharacter, &GCharacter::setNumOfFrames);


    // number of loops
    insertRow(row = rowCount());
    setItem(row, 0, new QTableWidgetItem("loops"));
    QSpinBox *spinLoop = createSpinner(gCharacter->getNumOfLoop(), Manager::instance()->getMaxNumOfLoops());
    spinLoop->setSingleStep(5);
    setCellWidget(row, 1, spinLoop);

    connect(spinLoop, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            gCharacter, &GCharacter::setNumOfLoop);


    // is dropable
    insertRow(row = rowCount());
    setItem(row, 0, new QTableWidgetItem("isDropable"));
    QComboBox *cboxDrop = createBoolCBox(gCharacter->getIsDropable());
    setCellWidget(row, 1, cboxDrop);

    connect(cboxDrop, SIGNAL(currentIndexChanged(int)), this, SLOT(setGCDropable(int)));


    // adjustment volume with scaling
    insertRow(row = rowCount());
    setItem(row, 0, new QTableWidgetItem("adjVolumWithScaling"));
    QLineEdit *adjLE = new QLineEdit(QString::number(gCharacter->getAdjVolumWithScaling()));
    setCellWidget(row, 1, adjLE);

    connect(adjLE, &QLineEdit::textChanged, this, &OInspector::setGCAdjVolumWithScaling);


    // urls
    insertRow(row = rowCount());
    setItem(row, 0, new QTableWidgetItem("Images"));
    QWidget *urlsAttr = new QWidget(this);
        QHBoxLayout *urlsLayout = new QHBoxLayout(urlsAttr);
            QLineEdit *urlsGCEdit = new QLineEdit(gCharacter->getUrls().join(';'), urlsAttr);
            urlsGCEdit->setFixedHeight(ROWIH);
            urlsLayout->addWidget(urlsGCEdit);

            QPushButton *urlsBtn = new QPushButton("...", urlsAttr);
            urlsBtn->setFixedSize(20, ROWIH);
        urlsLayout->addWidget(urlsBtn);
    urlsAttr->setLayout(urlsLayout);
    setCellWidget(row, 1, urlsAttr);
    formatCells();

    connect(this, &OInspector::fieldChanged, urlsGCEdit, &QLineEdit::setText);
    connect(urlsBtn, &QPushButton::clicked, this, &OInspector::setUrls);
}

void OInspector::prepare(GObject *gObject){

    defaultPreparation(gObject);

    int row;


    // click area
    insertRow(row = rowCount());
    setItem(row, 0, new QTableWidgetItem("clickAreas"));
    QPushButton *assign = new QPushButton("Assign", this);
    setCellWidget(row, 1, assign);

    connect(assign, &QPushButton::clicked, this, &OInspector::createCADialog);


    // is dropable
    insertRow(row = rowCount());
    setItem(row, 0, new QTableWidgetItem("isDropable"));
    QComboBox *cboxDrop = createBoolCBox(gObject->getIsDropable());
    setCellWidget(row, 1, cboxDrop);

    connect(cboxDrop, SIGNAL(currentIndexChanged(int)), this, SLOT(setGODropable(int)));


    // urls
    insertRow(row = rowCount());
    setItem(row, 0, new QTableWidgetItem("Images"));
    QWidget *urlsAttr = new QWidget(this);
        QHBoxLayout *urlsLayout = new QHBoxLayout(urlsAttr);
            QLineEdit *urlsGOEdit = new QLineEdit(gObject->getUrls().join(';'), urlsAttr);
            urlsGOEdit->setFixedHeight(ROWIH);

            QPushButton *urlsBtn = new QPushButton("...", urlsAttr);
            urlsBtn->setFixedSize(20, ROWIH);
        urlsLayout->addWidget(urlsGOEdit);
        urlsLayout->addWidget(urlsBtn);
    urlsAttr->setLayout(urlsLayout);
    setCellWidget(row, 1, urlsAttr);
    formatCells();

    connect(this, &OInspector::fieldChanged, urlsGOEdit, &QLineEdit::setText);
    connect(urlsBtn, &QPushButton::clicked, this, &OInspector::setUrls);
}

void OInspector::prepare(Inventar *inventar){

    defaultPreparation(inventar);

    int row;


    // items
    insertRow(row = rowCount());
    setItem(row, 0, new QTableWidgetItem("Items"));
    QWidget *itemsAttr = new QWidget(this);
        QHBoxLayout *itemsLayout = new QHBoxLayout(itemsAttr);
            _itemsEdit = new QTextEdit(itemsAttr);
            _itemsEdit->setFixedHeight(ROWIH);

            QPushButton *itemsBtn = new QPushButton("...", itemsAttr);
            itemsBtn->setFixedSize(20, ROWIH);
        itemsLayout->addWidget(_itemsEdit);
        itemsLayout->addWidget(itemsBtn);
    itemsAttr->setLayout(itemsLayout);
    setCellWidget(row, 1, itemsAttr);
    formatCells();
}

void OInspector::prepare(Item *item){

    defaultPreparation(item);
}

void OInspector::prepare(Player *player){

    defaultPreparation(player);
    prepare((GCharacter *)player);
}

void OInspector::prepare(MediaArea *mediaArea){

    defaultPreparation(mediaArea);

    int row;

    // loop
    insertRow(row = rowCount());
    setRowHeight(row, ROWH);
    setItem(row, 0, new QTableWidgetItem("loop"));
    QComboBox *cboxLoop = createBoolCBox(mediaArea->getLoop());
    setCellWidget(row, 1, cboxLoop);
    formatCells();

    connect(cboxLoop, SIGNAL(currentIndexChanged(int)), this, SLOT(setMALoop(int)));
}
