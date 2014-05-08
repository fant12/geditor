#include "elist.h"

#include <QHeaderView>
#include <QInputDialog>

// --------------------------------------------------------------------------------------
// magic --------------------------------------------------------------------------------


EList::EList(QWidget *parent) : QTableWidget(parent){

    horizontalHeader()->setHighlightSections(false);
    setSelectionBehavior(QAbstractItemView::SelectRows); //select full row

    //selection color
    QPalette p = palette();
    p.setColor(QPalette::Highlight, QColor(0, 220, 0, 200));
    p.setColor(QPalette::HighlightedText, "#ffffff");
    setPalette(p);
}


// --------------------------------------------------------------------------------------
// slots --------------------------------------------------------------------------------


void EList::setLayerName(QString newName){

    newName = newName.simplified();

    if(!selectedItems().isEmpty() && !newName.isEmpty()){

        //name has to be unique
        for(int i = 0; rowCount() > i; ++i)
            if(item(i, 0)->text() == newName)
                return;

        QRegularExpression regexp("[^0-9a-zA-Z]");
        if(!regexp.match(newName).hasMatch()){

            //if second column use first column
            if(1 == selectedItems().first()->column())
                item(selectedItems().first()->row(), 0)->setText(newName);
            else
                selectedItems().first()->setText(newName);
        }
    }
}


// --------------------------------------------------------------------------------------
// private ------------------------------------------------------------------------------


void EList::keyPressEvent(QKeyEvent *event){
    event->ignore();
}

void EList::mouseDoubleClickEvent(QMouseEvent *){

    if(0 < rowCount() && 0 == column(selectedItems().first())){

        int index = selectedItems().first()->row();
        QString oldName = selectedItems().first()->text();
        QString newName = QInputDialog::getText(this, tr("Umbenennen"), tr("Name der Ebene:"), QLineEdit::Normal, oldName, 0);
        if(!newName.isEmpty()){

            //name has to be unique
            for(int i = 0; rowCount() > i; ++i)
                if(item(i, 0)->text() == newName)
                    return;

            item(index, 0)->setText(newName);
            emit updateObjectName(newName);
        }
    }
}
