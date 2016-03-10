#ifndef CODEGEN_CLASSGEN_MAINWINDOW_H_
#define CODEGEN_CLASSGEN_MAINWINDOW_H_

#include <QtWidgets>


class MainWindow : public QWidget
{
	Q_OBJECT

public:
	MainWindow();

private slots:
	void GenerateCode();

private:
    QLineEdit* m_className;
    QLineEdit* m_parentClassName;

    QCheckBox* m_addProtections;
    QCheckBox* m_generateConstructor;
    QCheckBox* m_generateDestructor;

    QGroupBox* m_comments;
	QTextEdit* m_description;
	QLineEdit* m_package;
	QLineEdit* m_project;
    QLineEdit* m_author;
    QPushButton* m_generate;
    QPushButton* m_quit;
};

#endif // !CODEGEN_CLASSGEN_MAINWINDOW_H_


