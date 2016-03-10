#include "cpphighlighter.h"


CppHighlighter::CppHighlighter(QTextDocument* parent) : QSyntaxHighlighter(parent)
{
	HighlightingRule rule;

    m_keywordFormat.setForeground(Qt::darkBlue);
    m_keywordFormat.setFontWeight(QFont::Bold);

	QStringList keywordPatterns;
	keywordPatterns << "\\bclass\\b" << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
		<< "\\bexplicit\\b" << "\\bfriend\\b" << "\\bconst\\b" << "\\binline\\b" << "\\boperator\\b"
		<< "\\benum\\b" << "\\bnamespace\\b" << "\\bstatic\\b" << "\\bstruct\\b"
		<< "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b" << "\\bvoid\\b"
		<< "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b" << "\\bvolatile\\b"

		<< "\\bchar\\b" << "\\bdouble\\b" << "\\bint\\b" << "\\blong\\b"
		<< "\\bshort\\b" << "\\bsigned\\b";	

	foreach(const QString &pattern, keywordPatterns)
		{
			rule.m_pattern = QRegExp(pattern);
            rule.m_format = m_keywordFormat;
            m_highlightingRules.append(rule);
		}

    m_commentStartExpression = QRegExp("/\\*");
    m_commentEndExpression = QRegExp("\\*/");

    m_preprocessorFormat.setForeground(Qt::darkYellow);
	rule.m_pattern = QRegExp("#[a-z]+");
    rule.m_format = m_preprocessorFormat;
    m_highlightingRules.append(rule);

    m_singleLineCommentFormat.setForeground(Qt::darkGreen);
	rule.m_pattern = QRegExp("//[^\n]*");
    rule.m_format = m_singleLineCommentFormat;
    m_highlightingRules.append(rule);

    m_multiLineCommentFormat.setForeground(Qt::darkGreen);

    m_quotationFormat.setForeground(Qt::darkGreen);
	rule.m_pattern = QRegExp("\".*\"");
    rule.m_format = m_quotationFormat;
    m_highlightingRules.append(rule);

    m_classFormat.setFontWeight(QFont::Bold);
    m_classFormat.setForeground(Qt::green);
	rule.m_pattern = QRegExp("\\bQ[A-Za-z]+\\b");
    rule.m_format = m_classFormat;
    m_highlightingRules.append(rule);

    m_functionFormat.setFontItalic(true);
    m_functionFormat.setForeground(Qt::blue);
	rule.m_pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
    rule.m_format = m_functionFormat;
    m_highlightingRules.append(rule);
}

void CppHighlighter::highlightBlock(const QString& text)
{
    foreach(const HighlightingRule &rule, m_highlightingRules)
        {
            QRegExp expression(rule.m_pattern);
            int index = expression.indexIn(text);

            while (index >= 0)
            {
                int length = expression.matchedLength();

                setFormat(index, length, rule.m_format);
                index = expression.indexIn(text, index + length);
            }
        }

    setCurrentBlockState(0);

    int startIndex = 0;

    if (previousBlockState() != 1)
    {
        startIndex = m_commentStartExpression.indexIn(text);
    }

    while (startIndex >= 0)
    {
        int endIndex = m_commentEndExpression.indexIn(text, startIndex);
        int commentLength;

        if (endIndex == -1)
        {
            setCurrentBlockState(1);

            commentLength = text.length() - startIndex;
        }
        else
        {
            commentLength = endIndex - startIndex + m_commentEndExpression.matchedLength();
        }

        setFormat(startIndex, commentLength, m_multiLineCommentFormat);
        startIndex = m_commentStartExpression.indexIn(text, startIndex + commentLength);
    }
}

