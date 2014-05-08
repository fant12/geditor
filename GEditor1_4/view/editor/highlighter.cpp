#include "highlighter.h"

Highlighter::Highlighter(QTextDocument *parent) : QSyntaxHighlighter(parent){

    HighlightingRule rule;

    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);

    QStringList keywordPatterns;
    keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
                    << "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
                    << "\\bfriend\\b" << "\\binline\\b" << "\\bint\\b"
                    << "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
                    << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                    << "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
                    << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
                    << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
                    << "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
                    << "\\bvoid\\b" << "\\bvolatile\\b";

    foreach(const QString &pattern, keywordPatterns){
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    // class
    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
    rule.format = classFormat;
    highlightingRules.append(rule);

    // comments
    singleLineCommentFormat.setForeground(Qt::gray);
    rule.pattern = QRegExp("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);
    multiLineCommentFormat.setForeground(Qt::gray);

    commentStartExpression = QRegExp("/\\*");
    commentEndExpression = QRegExp("\\*/");

    // strings
    quotationFormat.setForeground(QBrush(QColor(180, 180, 0)));
    rule.pattern = QRegExp("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    // functions
    functionFormat.setFontItalic(true);
    functionFormat.setForeground(Qt::darkBlue);
    rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);
}

void Highlighter::highlightBlock(const QString &text){

    foreach(const HighlightingRule &rule, highlightingRules){

        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);

        while(0 <= index){
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, length + index);
        }
    }
    setCurrentBlockState(0);

    int startIndex = 0;
    if(1 != previousBlockState())
        startIndex = commentStartExpression.indexIn(text);

    while(0 <= startIndex){
        int endIndex = commentEndExpression.indexIn(text, startIndex);
        int commentLength;

        if(-1 == endIndex){
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        }
        else
            commentLength = endIndex - startIndex + commentEndExpression.matchedLength();

        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = commentStartExpression.indexIn(text, commentLength + startIndex);
    }
}
