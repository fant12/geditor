#include "projectdialog.h"

#include <QFile>
#include <QFileDialog>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>

// --------------------------------------------------------------------------------------
// magic --------------------------------------------------------------------------------


ProjectDialog::ProjectDialog(QWidget *parent) : QDialog(parent){

    setFixedSize(250, 350);
    setWindowTitle("New Project");
    setWindowFlags(windowFlags() & (~Qt::WindowContextHelpButtonHint));

    //initialize all elements
    _projNameField = new QLineEdit(this);
    _projAutorField = new QLineEdit(this);
    _projIconField = new QLineEdit(this);
    _projLocationField = new QLineEdit(this);

    _resolution = new QComboBox(this);
    _resolution->addItems(QStringList()<<"4:3"<<"16:9"<<"16:10");

    _error = new QLabel("", this);
    _error->setStyleSheet("QLabel{ color: red; font-style: italic }");

    QPushButton *iconLocationBtn = new QPushButton("Choose...", this);
    QPushButton *projLocationBtn = new QPushButton("Choose...", this);
    QPushButton *submit = new QPushButton("Ready", this);
    QPushButton *abort = new QPushButton("Abort", this);

    connect(iconLocationBtn, SIGNAL(clicked()), this, SLOT(iconSearch()));
    connect(projLocationBtn, SIGNAL(clicked()), this, SLOT(locationSearch()));
    connect(submit, SIGNAL(clicked()), this, SLOT(prepare()));
    connect(abort, SIGNAL(clicked()), this, SLOT(close()));

    //sub layouts
    QHBoxLayout *subLayoutIcon = new QHBoxLayout;
    subLayoutIcon->addWidget(_projIconField);
    subLayoutIcon->addWidget(iconLocationBtn);

    QHBoxLayout *subLayoutLocation = new QHBoxLayout;
    subLayoutLocation->addWidget(_projLocationField);
    subLayoutLocation->addWidget(projLocationBtn);

    QHBoxLayout *subLayoutBtn = new QHBoxLayout;
    subLayoutBtn->addWidget(submit);
    subLayoutBtn->addWidget(abort);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(new QLabel("Project title:", this));
    layout->addWidget(_projNameField);
    layout->addWidget(new QLabel("Icon:", this));
    layout->addLayout(subLayoutIcon);
    layout->addWidget(new QLabel("Author:", this));
    layout->addWidget(_projAutorField);
    layout->addWidget(new QLabel("Directory:", this));
    layout->addLayout(subLayoutLocation);
    layout->addWidget(new QLabel("Resolution:", this));
    layout->addWidget(_resolution);
    layout->addSpacing(20);
    layout->addLayout(subLayoutBtn);
    layout->addWidget(_error);

    setLayout(layout);
}


// --------------------------------------------------------------------------------------
// slots --------------------------------------------------------------------------------


void ProjectDialog::iconSearch(){
    _projIconField->setText(QFileDialog::getOpenFileName(this, tr("Icon wählen"), QDir::homePath(), tr("Images (*.ico *.png)")));
}

void ProjectDialog::locationSearch(){
    _projLocationField->setText(QFileDialog::getExistingDirectory(this, tr("Projektordner"), "C:/Users/mknolle/Documents/Programming/Qt"));
}

void ProjectDialog::prepare(){

    if(_projNameField->text().isEmpty() || _projLocationField->text().isEmpty()){
        _error->setText("There are missing inputs.");
        return;
    }

    save();

    QDir dir;
    if(dir.mkpath(_projLocationField->text() + "/level")){

        //level file
        QString f = _projLocationField->text() + "/level/level_01.sab";
        QFile file(f, this);
        file.open(QIODevice::WriteOnly);
        file.close();

        //settings
        Manager *man = Manager::instance();
        man->writeSettings("LevelFiles", QStringList()<<f);
        man->writeSettings("CurrentFile", f);
        man->writeSettings("CurrentFileNumber", 1);
    }
    else _error->setText("New level can not be created.");

    close();
}

void ProjectDialog::save(){

    Manager *man = Manager::instance();
    man->writeSettings("ProjectName", _projNameField->text());
    man->writeSettings("ProjectAuthor", _projAutorField->text());
    man->writeSettings("ProjectIcon", QIcon(_projIconField->text()));
    man->writeSettings("ProjectLocation", _projLocationField->text());
    man->writeSettings("Resolution", _resolution->currentText());
}
