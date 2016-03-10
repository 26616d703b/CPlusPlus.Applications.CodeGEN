#include "generatedcodewindow.h"


GeneratedCodeWindow::GeneratedCodeWindow(QString& code, QWidget* parent = 0) : QDialog(parent)
{
    m_generatedCode = new QTextEdit();
    m_generatedCode->setPlainText(code);
    m_generatedCode->setReadOnly(true);
    m_generatedCode->setFont(QFont("Courier"));
    m_generatedCode->setLineWrapMode(QTextEdit::NoWrap);

    m_highlighter = new CppHighlighter(m_generatedCode->document());

	m_copy = new QPushButton("&Copier");

	m_close = new QPushButton("&Fermer");

	QVBoxLayout* main_layout = new QVBoxLayout;
    main_layout->addWidget(m_generatedCode);
	main_layout->addWidget(m_copy);
	main_layout->addWidget(m_close);

	resize(800, 800);
	setLayout(main_layout);

	connect(m_copy, SIGNAL(clicked()), this, SLOT(CopyToClipboard()));
	connect(m_close, SIGNAL(clicked()), this, SLOT(accept()));
}

void GeneratedCodeWindow::CopyToClipboard() const
{
	QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(m_generatedCode->document()->toPlainText());
}

