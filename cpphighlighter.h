#ifndef CODEGEN_CPPHLIGHTER_H_
#define CODEGEN_CPPHIGHLIGHTER_H_

#include <QSyntaxHighlighter>


class CppHighlighter : public QSyntaxHighlighter
{

public:
    explicit CppHighlighter(QTextDocument* parent = 0);

protected:
    void highlightBlock(const QString& text) Q_DECL_OVERRIDE;

private:

	struct HighlightingRule
	{
		QRegExp m_pattern;
		QTextCharFormat m_format;
	};

    QVector<HighlightingRule> m_highlightingRules;

    QRegExp m_commentStartExpression;
    QRegExp m_commentEndExpression;

    QTextCharFormat m_preprocessorFormat;

    QTextCharFormat m_singleLineCommentFormat;
    QTextCharFormat m_multiLineCommentFormat;
    QTextCharFormat m_quotationFormat;

    QTextCharFormat m_keywordFormat;
    QTextCharFormat m_classFormat;
    QTextCharFormat m_functionFormat;
};


#endif // !CODEGEN_CPPHLIGHTER_H_


