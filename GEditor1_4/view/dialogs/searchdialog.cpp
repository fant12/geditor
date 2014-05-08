#include "searchdialog.h"

#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

SearchDialog::SearchDialog(QPlainTextEdit *textbox, QWidget *parent) : QDialog(parent){

    _isFirstTime = true;
    _document = textbox->document();

    _messageLabel = new QLabel("", this);
    _searchField = new QLineEdit(this);
    QPushButton *searchButton = new QPushButton("Search", this);
    QPushButton *removeSelection = new QPushButton("Remove Selection");

    connect(searchButton, &QPushButton::clicked, this, &SearchDialog::search);
    connect(removeSelection, &QPushButton::clicked, this, &SearchDialog::removeSelection);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(_searchField);
    layout->addWidget(searchButton);
    layout->addWidget(removeSelection);
    layout->addWidget(_messageLabel);
    setLayout(layout);

    setWindowTitle("Search");
    setWindowFlags(windowFlags() & (~Qt::WindowContextHelpButtonHint));
}

void SearchDialog::removeSelection(){

    if(_document->isUndoAvailable())
        _document->undo();
}

void SearchDialog::search(){

    QString searchString = _searchField->text();
    bool found = false;

    if(!_isFirstTime)
        _document->undo();

    if(searchString.isEmpty())
        _messageLabel->setText("Please enter a word for search.");
    else {

        QTextCursor highlightCursor(_document);
        QTextCursor cursor(_document);

        cursor.beginEditBlock();

        QTextCharFormat plainFormat(highlightCursor.charFormat());
        QTextCharFormat colorFormat = plainFormat;
        colorFormat.setBackground(Qt::yellow);

        while(!highlightCursor.isNull() && !highlightCursor.atEnd()){

            highlightCursor = _document->find(searchString, highlightCursor, QTextDocument::FindWholeWords);

            if(!highlightCursor.isNull()) {

                found = true;
                highlightCursor.movePosition(QTextCursor::WordRight, QTextCursor::KeepAnchor);
                highlightCursor.mergeCharFormat(colorFormat);
            }
        }

        cursor.endEditBlock();

        _isFirstTime = false;

        if(!found)
            _messageLabel->setText("Word not found.");

    }
}
