#include "scripteditor.h"

#include <QAbstractItemView>
#include <QApplication>
#include <QCompleter>
#include <QMessageBox>
#include <QPainter>
#include <QScrollBar>
#include <QStringListModel>
#include <QTextBlock>
#include <QTextStream>

// --------------------------------------------------------------------------------------
// magic --------------------------------------------------------------------------------

ScriptEditor::ScriptEditor(QWidget *parent) : QPlainTextEdit(parent), _completer(0){

    initCompleter();

    setAcceptDrops(true);
    setFont(QFont("Courier", 12));

    _curFile = "test.txt";
    _lineNumberArea = new LineNumberArea(this);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}


// --------------------------------------------------------------------------------------
// public -------------------------------------------------------------------------------


void ScriptEditor::lineNumberAreaPaintEvent(QPaintEvent *event){

    QPainter painter(_lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();

    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    while(block.isValid() && top <= event->rect().bottom()){

        if(block.isVisible() && bottom >= event->rect().top()){

            QString number = QString::number(1 + blockNumber);
            painter.setPen(Qt::black);
            painter.drawText(0, top, _lineNumberArea->width(), fontMetrics().height(), Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}

int ScriptEditor::lineNumberAreaWidth(){

    int digits = 1;
    int max = qMax(1, blockCount());

    while(100 <= max){
        max /= 10;
        ++digits;
    }

    return (13 + fontMetrics().width(QLatin1String("14")) * digits);
}

bool ScriptEditor::loadFile(QString &fileName){

    QFile file(fileName);

    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, tr("Error"), tr("Cannot read file %1:\n%2.")); //.arg(fileName).arg(file.errorString());
        return false;
    }

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();

    connect(document(), SIGNAL(contentsChanged()), this, SLOT(documentWasModified()));
    _curFile = fileName;

    return true;
}

bool ScriptEditor::maybeSave(){

    if(document()->isModified()){

        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("Save changes?"),
            tr("'%1' has been modified.\nDo you want to save your changes?").arg(_curFile),
                      QMessageBox::Save | QMessageBox::Discard
                      | QMessageBox::Cancel);

        if(QMessageBox::Save == ret)
            return save();
        else if(QMessageBox::Cancel == ret)
            return false;
    }

    return true;
}

bool ScriptEditor::save(){

    QFile file(_curFile);

    // if not open then error message to user
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, tr("Error"), tr("Cannot write file %1:\n%2.")
           .arg(_curFile).arg(file.errorString()));
        return false;
    }

    // append text stream
    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << toPlainText();
    QApplication::restoreOverrideCursor();

    return true;
}


// --------------------------------------------------------------------------------------
// private slots-------------------------------------------------------------------------


void ScriptEditor::documentWasModified(){
    setWindowModified(document()->isModified());
}

void ScriptEditor::highlightCurrentLine(){

    QList<QTextEdit::ExtraSelection> extraSelections;

    if(!isReadOnly()){
        QTextEdit::ExtraSelection selection;
        QColor lineColor = QColor(Qt::green).lighter(180);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();

        extraSelections.append(selection);
    }
    setExtraSelections(extraSelections);
}

void ScriptEditor::insertCompletion(const QString &completion){

    if(this != _completer->widget())
        return;

    QTextCursor cursor = textCursor();
    int extra = completion.length() - _completer->completionPrefix().length();
    cursor.movePosition(QTextCursor::Left);
    cursor.movePosition(QTextCursor::EndOfWord);
    cursor.insertText(completion.right(extra));
    setTextCursor(cursor);
}

void ScriptEditor::updateLineNumberArea(const QRect &rect, int dy){

    if(dy)
        _lineNumberArea->scroll(0, dy);
    else
        _lineNumberArea->update(0, rect.y(),_lineNumberArea->width(), rect.height());

    if(rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void ScriptEditor::updateLineNumberAreaWidth(int){
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}


// --------------------------------------------------------------------------------------
// protected ----------------------------------------------------------------------------


void ScriptEditor::focusInEvent(QFocusEvent *event){

    if(_completer)
        _completer->setWidget(this);


    QPlainTextEdit::focusInEvent(event);
}

void ScriptEditor::keyPressEvent(QKeyEvent *event){

    if(_completer && _completer->popup()->isVisible()){

        // these keys will be forwarded by the completer to the widget

        switch(event->key()){
            case Qt::Key_Enter:
            case Qt::Key_Return:
            case Qt::Key_Escape:
            case Qt::Key_Tab:
            case Qt::Key_Backtab:
                event->ignore();
                return; // do default behavior
            default: break;
       }
    }

    // prevent shortcuts
    bool isShortcut = ((event->modifiers() & Qt::ControlModifier) && event->key() == Qt::Key_Space);
    if(!_completer || !isShortcut)
        QPlainTextEdit::keyPressEvent(event);

    const bool ctrlOrShift = event->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier);
    if(!_completer || (ctrlOrShift && event->text().isEmpty()))
        return;

    // end of word
    static QString eow("~!@#$%^&*()_+{}|:\"<>?,./;'[]\\-=");
    bool hasModifier = (Qt::NoModifier != event->modifiers()) && !ctrlOrShift;
    QString completionPrefix = textUnderCursor();

    if(!isShortcut &&
            (hasModifier || event->text().isEmpty() ||
             3 > completionPrefix.length() ||
             eow.contains(event->text().right(1)))){

        _completer->popup()->hide();
        return;
    }

    if(_completer->completionPrefix() != completionPrefix){
        _completer->setCompletionPrefix(completionPrefix);
        _completer->popup()->setCurrentIndex(_completer->completionModel()->index(0, 0));
    }

    QRect cr = cursorRect();
    cr.setWidth(_completer->popup()->sizeHintForColumn(0) +
                _completer->popup()->verticalScrollBar()->sizeHint().width());

    _completer->complete(cr);
}

void ScriptEditor::resizeEvent(QResizeEvent *event){

    QPlainTextEdit::resizeEvent(event);
    QRect cr = contentsRect();
    _lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}


// --------------------------------------------------------------------------------------
// private ------------------------------------------------------------------------------


void ScriptEditor::initCompleter(){

    _completer = new QCompleter(this);
    _completer->setWidget(this);
    _completer->setModel(loadCompleterModel(":/editor/resources/editor/wordlist.txt"));
    _completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    _completer->setCompletionMode(QCompleter::PopupCompletion);
    _completer->setCaseSensitivity(Qt::CaseInsensitive);
    _completer->setWrapAround(false);

    connect(_completer, SIGNAL(activated(QString)), this, SLOT(insertCompletion(QString)));
}

QAbstractItemModel *ScriptEditor::loadCompleterModel(const QString &fileName){

    QFile file(fileName);
    if(!file.open(QFile::ReadOnly))
        return new QStringListModel(_completer);

#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
#endif

    QStringList words;

    while(!file.atEnd()){
        QByteArray ln = file.readLine();

        if(!ln.isEmpty())
            words << ln.trimmed();
    }

#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    return new QStringListModel(words, _completer);
}

QString ScriptEditor::textUnderCursor() const {

    QTextCursor cursor = textCursor();
    cursor.select(QTextCursor::WordUnderCursor);
    return cursor.selectedText();
}


//----------------------------------------------------------------------------------------------
//-- LineNumberArea
//----------------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------
// magic --------------------------------------------------------------------------------


LineNumberArea::LineNumberArea(ScriptEditor *editor) : QWidget(editor){
    _scriptEditor = editor;
}


// --------------------------------------------------------------------------------------
// public -------------------------------------------------------------------------------


QSize LineNumberArea::sizeHint() const {
    return QSize(_scriptEditor->lineNumberAreaWidth(), 0);
}


// --------------------------------------------------------------------------------------
// private ------------------------------------------------------------------------------


void LineNumberArea::paintEvent(QPaintEvent *event){
    _scriptEditor->lineNumberAreaPaintEvent(event);
}
