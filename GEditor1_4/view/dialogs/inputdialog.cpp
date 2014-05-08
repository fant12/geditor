#include "inputdialog.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

// --------------------------------------------------------------------------------------
// magic --------------------------------------------------------------------------------


InputDialog::InputDialog(QStringList *data, OInspector *oi, QWidget *parent) : QDialog(parent),
    _data(data),
    _oi(oi){

    setFixedSize(300, 180);
    setWindowIcon(QIcon(":/images/images/icons/newl.ico"));
    setWindowTitle("Choose plain type and name");
    setWindowFlags(windowFlags() & (~Qt::WindowContextHelpButtonHint));

        QVBoxLayout *layout = new QVBoxLayout;

            _lEdit = new QLineEdit(this);

            _cBox = new QComboBox(this);
            for(int i = 0; TOTYPES_LENGTH > i; ++i)
                _cBox->addItem(TOTYPES[i]);

            QPushButton *btn = new QPushButton("OK", this);
            btn->setFixedWidth(50);

            QHBoxLayout *row1 = new QHBoxLayout;
            row1->addWidget(new QLabel("Name:", this));
            row1->addWidget(_lEdit);

            QHBoxLayout *row2 = new QHBoxLayout;
            row2->addWidget(new QLabel("Type:", this));
            row2->addWidget(_cBox);

        layout->addLayout(row1);
        layout->addLayout(row2);
        layout->addWidget(btn);
    setLayout(layout);

    connect(btn, SIGNAL(clicked()), this, SLOT(setData()));

    show();
}


// --------------------------------------------------------------------------------------
// slots --------------------------------------------------------------------------------


void InputDialog::setData(){

    _lEdit->setText(_lEdit->text().simplified()); // trim

    // input shouldn't be empty and object name shouldn't already existing
    if(!_lEdit->text().isEmpty() &&
            !Manager::instance()->getLevelObjects()->contains(_lEdit->text())){

        QRegularExpression regexp("[^0-9a-zA-Z]");
        if(!regexp.match(_lEdit->text()).hasMatch()){
            _data->append(_lEdit->text());
            _data->append(_cBox->currentText());
            _selected = _cBox->currentIndex();
            close();
        }
    }
}
