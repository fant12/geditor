#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <QHash>
#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QTextDocument>

class QTextDocument;

// class --------------------------------------------------------------------------------

class Highlighter : public QSyntaxHighlighter {

        Q_OBJECT

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief The default constructor.
         * \param parent the parent text document object
         */
        Highlighter(QTextDocument *parent = 0);

    // --------------------------------------------------------------------------------
    protected:

        /*!
         * \brief Highlights a text block.
         * \param text the text
         */
        void highlightBlock(const QString &text);

    // --------------------------------------------------------------------------------
    private:

        /*!< A highlight structure for regular expressions and assigned format. */
        struct HighlightingRule {
                QRegExp pattern;
                QTextCharFormat format;
        };

        /*!< The format for classes. */
        QTextCharFormat classFormat;

        /*!< The start expression for comments. */
        QRegExp commentStartExpression;

        /*!< The end expression for comments. */
        QRegExp commentEndExpression;

        /*!< The format for functions. */
        QTextCharFormat functionFormat;

        /*!< The highlighting rules. */
        QVector<HighlightingRule> highlightingRules;

        /*!< The format for special keywords. */
        QTextCharFormat keywordFormat;

        /*!< The format for multiline comments. */
        QTextCharFormat multiLineCommentFormat;

        /*!< The format for string literals. */
        QTextCharFormat quotationFormat;

        /*!< The format for single line comments. */
        QTextCharFormat singleLineCommentFormat;

};

#endif // HIGHLIGHTER_H
