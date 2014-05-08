#include "cadialog.h"

#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

// --------------------------------------------------------------------------------------
// magic --------------------------------------------------------------------------------


CADialog::CADialog(QWidget *parent) : QDialog(parent),
    _dLayout(new QVBoxLayout),
    _numObjects(new QList<QComboBox *>()){

    QHBoxLayout *aLine = new QHBoxLayout;

    QPushButton *plus = new QPushButton("+", this);
    QPushButton *ok = new QPushButton("OK", this);

    aLine->addWidget(new QLabel("Combine with object:"));
    aLine->addWidget(plus);
    _dLayout->addLayout(aLine);

    connect(plus, SIGNAL(clicked()), this, SLOT(addLineEdit()));
    connect(ok, SIGNAL(clicked()), this, SLOT(close()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(_dLayout);
    layout->addWidget(ok);
    setLayout(layout);

    setWindowFlags(windowFlags() & (~Qt::WindowContextHelpButtonHint));
    setWindowTitle(tr("Clickarea Connector"));
}


// --------------------------------------------------------------------------------------
// slots --------------------------------------------------------------------------------


void CADialog::addLineEdit(){

    QComboBox *cb = new QComboBox(this);
    _numObjects->append(cb);
    _dLayout->addWidget(cb);
}
