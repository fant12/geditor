#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QPlainTextEdit;
class QLabel;
class QLineEdit;
class QTextDocument;
QT_END_NAMESPACE

// class --------------------------------------------------------------------------------

//! SearchDialog class.
/*!
 * \brief The SearchDialog class describes the dialog for word searching in the
 * scripteditor.
 */
class SearchDialog : public QDialog {

        Q_OBJECT

    // ----------------------------------------------------------------------------------
    public:

        /*!
         * \brief The default constructor.
         * \param textbox the script editor text box
         * \param parent the parent widget
         */
        explicit SearchDialog(QPlainTextEdit *textbox, QWidget *parent = 0);

    // ----------------------------------------------------------------------------------
    private slots:

        /*!
         * \brief Removes the current selection if possible.
         */
        void removeSelection();

        /*!
         * \brief Searches a word.
         */
        void search();

    // ----------------------------------------------------------------------------------
    private:

        /*!< The text document. */
        QTextDocument *_document;

        /*!< Defines whether this is the first search. */
        bool _isFirstTime;

        /*!< The label for messages to the user. */
        QLabel *_messageLabel;

        /*!< The input field for search. */
        QLineEdit *_searchField;

};

#endif // SEARCHDIALOG_H
