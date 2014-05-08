#include "geditor.h"
#include "view/dialogs/aboutdialog.h"
#include "view/dialogs/projectdialog.h"
#include "view/dialogs/searchdialog.h"
#include "control/drawer.h"
#include "view/dialogs/rotatordialog.h" // after Drawer
#include "view/dialogs/connector/connectordialog.h"
//#include "view/dialogs/spritecreator/spritedialog.h"
#include "ui_geditor.h"

#include <QFileDialog>
#include <QVBoxLayout>

// --------------------------------------------------------------------------------------
// magic --------------------------------------------------------------------------------


GEditor::GEditor(QWidget *parent) : QMainWindow(parent), ui(new Ui::GEditor){

    ui->setupUi(this);
    _area = new WorkBox(this);

    setCentralWidget(_area);
    setWindowTitle(tr("GEditor"));

    // windows
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));
    connect(ui->actionAudio, SIGNAL(triggered()), this, SLOT(showAudioWindow()));
    connect(ui->actionSprite, SIGNAL(triggered()), this, SLOT(showSpriteCreator()));
    connect(ui->actionHelp, SIGNAL(triggered()), this, SLOT(showHelp()));
    connect(ui->actionOptions, SIGNAL(triggered()), this, SLOT(showOptions()));

    // view
    connect(ui->action50, SIGNAL(triggered()), this, SLOT(triggerScaleChanged()));
    connect(ui->action75, SIGNAL(triggered()), this, SLOT(triggerScaleChanged()));
    connect(ui->action100, SIGNAL(triggered()), this, SLOT(triggerScaleChanged()));
    connect(ui->action125, SIGNAL(triggered()), this, SLOT(triggerScaleChanged()));
    connect(ui->action150, SIGNAL(triggered()), this, SLOT(triggerScaleChanged()));

    // project
    connect(ui->actionCloseProject, SIGNAL(triggered()), this, SLOT(closeProject()));
    connect(ui->actionExport, SIGNAL(triggered()), this, SLOT(exportProject()));
    connect(ui->actionImport, SIGNAL(triggered()), this, SLOT(import()));
    connect(ui->actionNewLevel, SIGNAL(triggered()), this, SLOT(newLevel()));
    connect(ui->actionNewProject, SIGNAL(triggered()), this, SLOT(newProject()));
    connect(ui->actionOpenProject, SIGNAL(triggered()), this, SLOT(open()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->actionSaveAs, SIGNAL(triggered()), this, SLOT(saveAs()));

    // tools
    connect(ui->actionCopy, SIGNAL(triggered()), this, SLOT(copy()));
    connect(ui->actionCut, SIGNAL(triggered()), this, SLOT(cut()));
    connect(ui->actionDefault, SIGNAL(triggered()), this, SLOT(useDefCursorMode()));
    connect(ui->actionFind, SIGNAL(triggered()), this, SLOT(search()));
    connect(ui->actionMove, SIGNAL(triggered()), this, SLOT(useDragCursorMode()));
    connect(ui->actionPaste, SIGNAL(triggered()), this, SLOT(paste()));
    connect(ui->actionRotation, SIGNAL(triggered()), this, SLOT(showRotator()));
}

GEditor::~GEditor(){
    delete ui;
}


// --------------------------------------------------------------------------------------
// protected ----------------------------------------------------------------------------


void GEditor::closeEvent(QCloseEvent *event){

    writeSettings();
    event->accept();
}


// --------------------------------------------------------------------------------------
// slots --------------------------------------------------------------------------------


void GEditor::close(){
    QApplication::closeAllWindows();
}

void GEditor::closeProject(){
    //TODO jede datei speichern
    //alle fenster leeren und schliessen

    _area->getEditor()->clear();
}

void GEditor::copy(){
    _area->getEditor()->copy();
}

void GEditor::cut(){
    _area->getEditor()->cut();
}

void GEditor::exportProject(){
    //TODO
}

void GEditor::import(){
    //TODO
}

void GEditor::newLevel(){
    save();
    _area->getEditor()->clear();
}

void GEditor::newProject(){
    ProjectDialog *dialog = new ProjectDialog(this);
    dialog->show();
}

void GEditor::open(){

    QString filename = QFileDialog::getOpenFileName(this, tr("Open Project"), "", tr("Project-Files (*.sab)"));
    if(!filename.isEmpty())
        _area->getEditor()->loadFile(filename);
}

void GEditor::paste(){
    _area->getEditor()->paste();
}

void GEditor::save(){

    // save script editor content
    _area->getEditor()->save();

    //TODO
    //Settings *settings = Settings::getinstance();
    //if(NULL != settings->loadSettings("CurrentFile"))
        //wenn gerade datei offen
}

void GEditor::saveAs(){
    //TODO
}

void GEditor::sceneScaleChanged(const QString &scale){

    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100;
    CanvasView *cv = _area->getView();
    QMatrix oldMatrix = cv->matrix();
    cv->resetMatrix();
    cv->translate(oldMatrix.dx(), oldMatrix.dy());
    cv->scale(newScale, newScale);
}

void GEditor::search(){

    SearchDialog *search = new SearchDialog(_area->getEditor(), this);
    search->show();
}

void GEditor::showAbout(){

    AboutDialog *about = new AboutDialog(this);
    about->show();
}

void GEditor::showAudioWindow(){
    //TODO
}

void GEditor::showConnector(){
//TODO currently unused
    ConnectorDialog *connector = new ConnectorDialog(this);
    connector->show();
}

void GEditor::showHelp(){
    //TODO
}

void GEditor::showOptions(){
    //TODO
}

void GEditor::showRotator(){

    RotatorDialog *dialog = new RotatorDialog(this);
    dialog->show();
}

void GEditor::showSpriteCreator(){

  //  SpriteDialog *dialog = new SpriteDialog(this);
  //  dialog->show();
}

void GEditor::triggerScaleChanged(){

    if(ui->action50->isChecked()){
        sceneScaleChanged(ui->action50->text());
        ui->action50->setChecked(false);
    }
    else if(ui->action75->isChecked()){
        sceneScaleChanged(ui->action75->text());
        ui->action75->setChecked(false);
    }
    else if(ui->action100->isChecked()){
        sceneScaleChanged(ui->action100->text());
        ui->action100->setChecked(false);
    }
    else if(ui->action125->isChecked()){
        sceneScaleChanged(ui->action125->text());
        ui->action125->setChecked(false);
    }
    else if(ui->action150->isChecked()){
        sceneScaleChanged(ui->action150->text());
        ui->action150->setChecked(false);
    }
}

void GEditor::useDefCursorMode(){
    Drawer::instance()->getView()->setDragMode(QGraphicsView::NoDrag);
    Drawer::instance()->getView()->setInteractive(true);
}

void GEditor::useDragCursorMode(){
    Drawer::instance()->getView()->setDragMode(QGraphicsView::ScrollHandDrag);
    Drawer::instance()->getView()->setInteractive(true);
}


// --------------------------------------------------------------------------------------
// private ------------------------------------------------------------------------------


void GEditor::readSettings(){

    QSettings settings("Cacao Productions", "GEditor");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    move(pos);
    resize(size);
}

void GEditor::writeSettings(){

    QSettings settings("Cacao Productions", "GEditor");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}
