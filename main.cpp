#include <QApplication>

#include "mainwindow.h"


int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
    app.setOrganizationName("Ampersand");
    app.setApplicationName("CodeGEN");
    app.setFont(QFont("Courier", 10));

	MainWindow window;
	window.show();

	return app.exec();
}

