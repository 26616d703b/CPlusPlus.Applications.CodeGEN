#ifndef CODEGEN_CLASSGEN_GENERATEDCODEWINDOW_H_
#define CODEGEN_CLASSGEN_GENERATEDCODEWINDOW_H_

#include <QtWidgets>

#include "cpphighlighter.h"


class GeneratedCodeWindow : public QDialog
{
	Q_OBJECT

public:
	GeneratedCodeWindow(QString& code, QWidget* parent);

private slots:
	void CopyToClipboard() const;

private:
    QTextEdit* m_generatedCode;

    CppHighlighter* m_highlighter;

    QPushButton* m_copy;
	QPushButton* m_close;
};

#endif // !CODEGEN_CLASSGEN_GENERATEDCODEWINDOW_H_


