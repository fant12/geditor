#include "workbox.h"
#include "fileinspector.h"
#include "dialogs/inputdialog.h"
#include "editor/highlighter.h"
#include "../control/drawer.h"

#include <QDialog>
#include <QMenu>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QScrollArea>
#include <QVBoxLayout>

// --------------------------------------------------------------------------------------
// magic --------------------------------------------------------------------------------


WorkBox::WorkBox(QWidget *parent) : QWidget(parent){

    QHBoxLayout *toolOrderLayout = new QHBoxLayout;
        QVBoxLayout *toolOrderSubLayout = new QVBoxLayout;

        _mainToolWindow = new QTabWidget(this);
        initMainToolWindow();

        _sideToolWindow = new QTabWidget(this);
        initSideToolWindow();   // create _objectsTab

        _attributeWindow = new OInspector(_objectsTab, this);

        //connect now because attributeWindow and _objectsTab previously not exist
        connect(_objectsTab, SIGNAL(objectNameChanged(QString)), _attributeWindow, SLOT(updateName(QString)));
        connect(_objectsTab, SIGNAL(cellClicked(int,int)), _attributeWindow, SLOT(updateSelectedObject(int)));

        //stretch to 2:1
        QSizePolicy spMainToolWindow(QSizePolicy::Preferred, QSizePolicy::Preferred);
        spMainToolWindow.setHorizontalStretch(2);
        _mainToolWindow->setSizePolicy(spMainToolWindow);

        QSizePolicy spRight(QSizePolicy::Preferred, QSizePolicy::Preferred);
        spRight.setHorizontalStretch(1);
        _attributeWindow->setSizePolicy(spRight);
        _sideToolWindow->setSizePolicy(spRight);

        toolOrderSubLayout->addWidget(_sideToolWindow);
        toolOrderSubLayout->addWidget(_attributeWindow);

    toolOrderLayout->addWidget(_mainToolWindow);
    toolOrderLayout->addLayout(toolOrderSubLayout);

    setLayout(toolOrderLayout);
}


// --------------------------------------------------------------------------------------
// slots --------------------------------------------------------------------------------


void WorkBox::addObject(){

    QStringList *data = new QStringList;
    InputDialog *dialog = new InputDialog(data, _attributeWindow, this);

    // while dialog is running
    if(QDialog::Accepted != dialog->exec()){

        // list shouldn't be empty and the name has to be unique
        if(!data->isEmpty() &&
           !Manager::instance()->getLevelObjects()->contains(data->first())){

            _objectsTab->insertRow(0); // add to begin

            _objectsTab->setItem(0, 0, new QTableWidgetItem(data->first()));
            _objectsTab->setItem(0, 1, new QTableWidgetItem(data->last()));
            _objectsTab->item(0, 0)->setFlags(_objectsTab->item(0, 0)->flags() ^ Qt::ItemIsEditable);
            _objectsTab->item(0, 0)->setFlags(_objectsTab->item(0, 1)->flags() ^ Qt::ItemIsEditable);
            _objectsTab->item(0, 0)->setTextAlignment(Qt::AlignCenter);
            _objectsTab->item(0, 1)->setTextAlignment(Qt::AlignCenter);
            _objectsTab->selectedItems().clear();
            _objectsTab->selectRow(0);

            _attributeWindow->createGameElem(static_cast<TObjectTypes>(dialog->getSelected()), data->first());
        }
    }

    dialog = 0;
    delete dialog;
}

void WorkBox::removeObject(){

    if(0 < _objectsTab->selectedItems().size()){

        // remove table in object inspector
        for(int i = _attributeWindow->rowCount()-1; 0 <= i; --i)
            _attributeWindow->removeRow(i);

        // remove object
        QString objName = _objectsTab->selectedItems().first()->text();
        if(Manager::instance()->getLevelObjects()->contains(objName))
            Manager::instance()->removeToyObject(objName);

        // remove entry in elist
        if(1 < _objectsTab->rowCount())
            _objectsTab->removeRow((_objectsTab->selectedItems().first())->row());
        else if(0 < _objectsTab->rowCount()){
            _sideToolWindow->clear();
            initSideToolWindow();
        }
    }
}

void WorkBox::showContextMenu(const QPoint &pos){

    QPoint globalPos = _objectsTab->mapToGlobal(pos);
    QMenu contextMenu;

    connect(contextMenu.addAction("Add"), SIGNAL(triggered()), this, SLOT(addObject()));
    connect(contextMenu.addAction("Remove"), SIGNAL(triggered()), this, SLOT(removeObject()));
    contextMenu.exec(globalPos);
}


// --------------------------------------------------------------------------------------
// private ------------------------------------------------------------------------------


void WorkBox::initMainToolWindow(){

    // graphics scene
    QScrollArea *viewArea = new QScrollArea(_mainToolWindow);
    QVBoxLayout *scrollbarLayout = new QVBoxLayout(this);

    Canvas *scene = new Canvas(0, 0, 1600, 1600, viewArea);
    _view = new CanvasView(scene, viewArea);
    Drawer::instance()->setScene(scene);
    Drawer::instance()->setView(_view);

    scrollbarLayout->addWidget(_view);
    viewArea->setLayout(scrollbarLayout);

    // editor
    _editor = new ScriptEditor(_mainToolWindow);
    new Highlighter(_editor->document());
    //TODO editor->loadFile("");

    _mainToolWindow->addTab(viewArea, "Level");
    _mainToolWindow->addTab(_editor, "Script");
}

void WorkBox::initSideToolWindow(){

    _objectsTab = new EList(this);
    _objectsTab->verticalHeader()->setVisible(false);
    _objectsTab->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _objectsTab->setColumnCount(2);
    _objectsTab->setSpan(1, 1, 2, 2);
    _objectsTab->horizontalHeader()->setStretchLastSection(true);

    _objectsTab->setHorizontalHeaderItem(0, new QTableWidgetItem("Plain"));
    _objectsTab->setHorizontalHeaderItem(1, new QTableWidgetItem("Plain-type"));

    _objectsTab->horizontalHeaderItem(0)->setTextAlignment(Qt::AlignCenter);
    _objectsTab->horizontalHeaderItem(1)->setTextAlignment(Qt::AlignCenter);

    // add context menu
    _objectsTab->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(_objectsTab, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));

    _sideToolWindow->addTab(_objectsTab, "Objects");
    _sideToolWindow->addTab(new FileInspector(QApplication::applicationDirPath(), this), "Project View");
}
