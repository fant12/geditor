#include "rotatordialog.h"
#include "../../control/drawer.h"

RotatorDialog::RotatorDialog(QWidget *parent) : QDialog(parent){

    _item = NULL;

    if(!Drawer::instance()->getScene()->selectedItems().empty())
        _item = Drawer::instance()->getScene()->selectedItems().first();

    // top group box

    QGroupBox *toolGroupBox = new QGroupBox(tr("Rotation"));
    QVBoxLayout *lay = new QVBoxLayout;

        _spin = new QSpinBox(this);
        _spin->setMaximum(360);
        _spin->setValue((_item) ? _item->rotation() : 5);
        lay->addWidget(_spin);

        _dial = new QDial(this);
        _dial->setMaximum(360);
        lay->addWidget(_dial);

        connect(_spin, SIGNAL(valueChanged(int)), _dial, SLOT(setValue(int)));
        connect(_dial, SIGNAL(valueChanged(int)), _spin, SLOT(setValue(int)));

        if(_item)
            connect(_spin, SIGNAL(valueChanged(int)), this, SLOT(changeItemRotation(int)));

    toolGroupBox->setLayout(lay);


    // bottom button
    QPushButton *closeButton = new QPushButton("Close", this);
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    // layout
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(toolGroupBox, 0, 0);
    mainLayout->addWidget(closeButton, 2, 0);
    setLayout(mainLayout);

    mainLayout->setSizeConstraint(QLayout::SetMinimumSize);
    setWindowTitle(tr("Rotate"));
    setWindowFlags(windowFlags() & (~Qt::WindowContextHelpButtonHint));
}

void RotatorDialog::changeItemRotation(int value){

    qreal xCenter = _item->boundingRect().x() + 0.5 * _item->boundingRect().width();
    qreal yCenter = _item->boundingRect().y() + 0.5 * _item->boundingRect().height();

    QTransform xform;
    xform.translate(xCenter, yCenter); // translate matrix
    _item->setTransform(xform);

    xform.rotate(value);
    _item->setTransform(xform);

    xform.translate(-xCenter, -yCenter); // translate matrix back to origin point
    _item->setTransform(xform);
}
