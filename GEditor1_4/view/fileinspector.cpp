#include "fileinspector.h"

#include <QTreeView>
#include <QDirModel>
FileInspector::FileInspector(QString root, QWidget *parent) : QTableWidget(parent){

    _model.setRootPath(root);

    QTreeView *tree = new QTreeView(this);
    tree->setModel(&_model);
    tree->setRootIndex(_model.index(_model.rootPath()));

    // look and feel
    tree->setAnimated(true);
    tree->setIndentation(10);
    tree->setSortingEnabled(true);
    tree->setFixedHeight(295);
}

void FileInspector::setRoot(QString root){

    _model.setRootPath(root);
}
