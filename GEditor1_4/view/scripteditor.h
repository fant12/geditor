#ifndef SCRIPTEDITOR_H
#define SCRIPTEDITOR_H

#include <QPlainTextEdit>

class QAbstractItemModel;
class QCompleter;
class QPaintEvent;
class QResizeEvent;
class QSize;
class LineNumberArea;

// class --------------------------------------------------------------------------------

//! ScriptEditor class.
/*!
 * \brief The ScriptEditor class describes the script editor.
 */
class ScriptEditor : public QPlainTextEdit {

        Q_OBJECT

    // ----------------------------------------------------------------------------------
    public:

        /*!
         * \brief The default constructor.
         * \param parent the parent widget
         */
        explicit ScriptEditor(QWidget *parent = 0);

    // ----------------------------------------------------------------------------------
    public:

        /*!
         * \brief Paints the number area.
         * \param event the catched paint event
         */
        void lineNumberAreaPaintEvent(QPaintEvent *event);

        /*!
         * \brief Computes the width of number area.
         * \returns an integer value for number area width
         */
        int lineNumberAreaWidth();

        /*!
         * \brief Loads a document file.
         * \param fileName the loaded document
         * \returns true if loading file was successful, otherwise false
         */
        bool loadFile(QString &fileName);

        /*!
         * \brief Asks user to save last document modifications.
         * \returns a boolean value whether user want to save or not
         */
        bool maybeSave();

        /*!
         * \brief Saves the document modifications.
         * \returns true if saving was successful, otherwise false
         */
        bool save();

    // ----------------------------------------------------------------------------------
    protected:

        /*!
         * \brief Receives keyboard focus events.
         * \param event the catched focus in event
         */
        void focusInEvent(QFocusEvent *event);

        /*!
         * \brief Receives pressed key events.
         * \param event the catched key event
         */
        void keyPressEvent(QKeyEvent *event);

        /*!
         * \brief Resizes the box.
         * \param event the catched resize event
         */
        void resizeEvent(QResizeEvent *event);

    // ----------------------------------------------------------------------------------
    private slots:

        /*!
         * \brief Sets the document as modified.
         */
        void documentWasModified();

        /*!
         * \brief Marks the current line.
         */
        void highlightCurrentLine();

        /*!
         * \brief Inserts the completion.
         * \param completion the choosen completion
         */
        void insertCompletion(const QString &completion);

        /*!
         * \brief Updates the line number on left side.
         * \param rect the number area
         * \param dy the current or maximal position of area
         */
        void updateLineNumberArea(const QRect &rect, int dy);

        /*!
         * \brief Updates the width of number area.
         * \param int defines the width of area
         */
        void updateLineNumberAreaWidth(int);

    // ----------------------------------------------------------------------------------
    private:

        /*!
         * \brief Initializes the completer.
         * \param completer the completer object
         */
        void initCompleter();

        /*!
         * \brief Loads the model for the completer.
         * \param fileName the file
         * \returns the model
         */
        QAbstractItemModel *loadCompleterModel(const QString &fileName);

        /*!
         * \brief Gives the current selected text.
         * \returns the selected text
         */
        QString textUnderCursor() const;

    // ----------------------------------------------------------------------------------
    private:

        /*!< The completer object for auto completing. */
        QCompleter *_completer;

        /*!< The path to the current file. */
        QString _curFile;

        /*!< The number area. */
        QWidget *_lineNumberArea;

};

// class --------------------------------------------------------------------------------

//! LineNumberArea class.
/*!
 * \brief The LineNumberArea class is a widget that describes the area that displays
 * the line number in each row.
 */
class LineNumberArea : public QWidget {

    // ----------------------------------------------------------------------------------
    public:

        /*!
         * \brief The default constructor.
         * \param editor the assigned script editor widget
         */
        LineNumberArea(ScriptEditor *editor);

    // ----------------------------------------------------------------------------------
    public:

        /*!
         * \brief Gives the recommended size for the widget.
         * \returns an instance of QSize
         */
        QSize sizeHint() const;

    // ----------------------------------------------------------------------------------
    protected:

        /*!
         * \brief Paints the area.
         * \param event the catched paint event
         */
        void paintEvent(QPaintEvent *event);

    // ----------------------------------------------------------------------------------
    private:

        /*!< The assigned script editor widget. */
        ScriptEditor *_scriptEditor;

};

#endif // SCRIPTEDITOR_H
